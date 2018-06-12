
public class Maze {
    private int N;                 
    private boolean[][] north;     
    private boolean[][] east;
    private boolean[][] south;
    private boolean[][] west;
    private boolean[][] visited;
    private static MatrixVert[] edgeTo;     // Guarda os vizinhos de cada posicao
    private static MatrixVert [] Vertices; // Vetor de todos os possiveis vertices do labirinto
    private MatrixVert V;                 // Representacao da posicao da matriz num vertice
    private static boolean [] path;      // Matrizes que guardam os vertices visitados 
    private static boolean [] path2;
    
    public Maze(int N) {
        this.N = N;
        StdDraw.setXscale(0, N+2);
        StdDraw.setYscale(0, N+2);
        init();
        generate();
    }
    
    public Maze(int N, long seed) {
        this.N = N;
        StdRandom.setSeed(seed);
        StdDraw.setXscale(0, N+2);
        StdDraw.setYscale(0, N+2);
        init();
        generate();
    }

    /* Cria todos os vertices a serem considerados, para cada posicao
     * da matriz, que representa o labirinto. 
     */ 

    private void CreateVertices () {
        Vertices = new MatrixVert [(N+1)*(N+1)];
        int c = 0;
        for (int x = 1; x < N+1; x++)
            for (int y = 1; y < N+1; y++){
                V = new MatrixVert(x, y, (x-1) * N + y - 1);
                Vertices[c++] = V;
            }
    }

    //Identico ao original, mas com algumas inicializacoes a mais. 
     
    private void init() {
        visited = new boolean[N+2][N+2];
        edgeTo = new MatrixVert[N*N];
        for (int x = 0; x < N+2; x++) visited[x][0] = visited[x][N+1] = true;
        for (int y = 0; y < N+2; y++) visited[0][y] = visited[N+1][y] = true;

        north = new boolean[N+2][N+2];
        east  = new boolean[N+2][N+2];
        south = new boolean[N+2][N+2];
        west  = new boolean[N+2][N+2];
        for (int x = 0; x < N+2; x++)
            for (int y = 0; y < N+2; y++)
                north[x][y] = east[x][y] = south[x][y] = west[x][y] = true;
        CreateVertices();
    }


    /* O labirinto foi criado da mesma forma que o Maze.java original.
     * Porem, cada vez que uma parede eh "derrubada", colocamos em
     * edgeTo[] um novo caminho, fazendo com que os caminhos sejam
     * descobertos ja na criacao do labirinto. Assim, nao precisamos
     * calcular os possiveis caminhos para cada entrada.
     */

    private void generate(int x, int y) {
        visited[x][y] = true;

        while (!visited[x][y+1] || !visited[x+1][y] || !visited[x][y-1] || !visited[x-1][y]) {

            while (true) {
                
                double r = StdRandom.uniform();
                
                if (r < 0.25 && !visited[x][y+1]) {
                    north[x][y] = south[x][y+1] = false;
                    edgeTo[V.XYtoID(x, y+1, N)] = Vertices[V.XYtoID(x, y, N)];
                    generate(x, y + 1);
                    break;
                }
                else if (r >= 0.25 && r < 0.50 && !visited[x+1][y]) {
                    east[x][y] = west[x+1][y] = false;
                    edgeTo[V.XYtoID(x + 1, y, N)] = Vertices[V.XYtoID(x, y, N)];
                    generate(x+1, y);
                    break;
                }
                else if (r >= 0.5 && r < 0.75 && !visited[x][y-1]) {
                    south[x][y] = north[x][y-1] = false;
                    edgeTo[V.XYtoID(x, y - 1, N)] = Vertices[V.XYtoID(x, y, N)];
                    generate(x, y-1);
                    break;
                }
                else if (r >= 0.75 && r < 1.00 && !visited[x-1][y]) {
                    west[x][y] = east[x-1][y] = false;
                    edgeTo[V.XYtoID(x - 1, y, N)] = Vertices[V.XYtoID(x, y, N)];
                    generate(x-1, y);
                    break;
                }
            }
        }
    }
    
    private void generate() {
        generate(1, 1);
    }

    /* Parte principal da solucao. Aqui, depois de criados os caminhos, pela
     * propriedade dos labirintos perfeitos, temos que existe somente 1 cami-
     * nho possivel entre 2 pontos quaisquer. Assim, percorremos o caminho 
     * entre os pontos dados na entrada e a origem, ate que se encontrem. Ao
     * se encontrare, devolvemos a posicao correspondente desse ponto de in-
     * tersecao. Entao imprimimos os pontos nao comuns entre path[] e path2[].
     */

    public static MatrixVert pathTo(int start1,  int start2, int end, int N) {

        path = new boolean [N*N];
        path2 = new boolean [N*N];
        int x = start1; //Representacao do primeiro ponto da entrada padrao
        int y = start2; //Representacao do segundo ponto da entrada padrao
        MatrixVert v;

        /* Temos que procurar ate que ambos os caminhos se encontrem */
        while (path[y] != true && path2[x] != true){
            path[x] = true;
            path2[y] = true;
            if(x != end) x = edgeTo[x].getID();
            if (y != end) y = edgeTo[y].getID();
                
        }
        /* Verificamos se algum dos dois chegou no final. Isso pode acontecer,
         * ja que nem sempre o caminho ate a origem eh menor que o caminho ate
         * o outro ponto
         */
        if (x != end && path2[x] == true )
            v = new MatrixVert (edgeTo[x].X(), edgeTo[x].Y(), ToIndex(edgeTo[x].X(), edgeTo[x].Y(), N));
        else if (y != end && path[y] == true)
            v = new MatrixVert (edgeTo[y].X(), edgeTo[y].Y(), ToIndex(edgeTo[y].X(), edgeTo[y].Y(), N));
        else 
            v = new MatrixVert (1, 1, ToIndex(1, 1, N)); 
        return v; 
    }

    /* Funcao que desenha o caminho. Ele percorre o trajeto dos pontos,
     * partindo das entradas, ate o ponto de intesecao entre esses trajetos,
     * mas agora, pintando-o.
     */ 

    public static void drawsolve (int start1, int start2, int end){

         StdDraw.setPenColor(StdDraw.BLUE);
        for (int x = start1; x != end && edgeTo[x].getID() != end; x = edgeTo[x].getID()){
            if (path[x] != path2[x])
            StdDraw.filledCircle(edgeTo[x].X() + 0.5, edgeTo[x].Y() + 0.5, 0.25);
        }   
        for (int x = start2; x != end && edgeTo[x].getID() != end; x = edgeTo[x].getID()){
            if (path[x] != path2[x])
            StdDraw.filledCircle(edgeTo[x].X() + 0.5, edgeTo[x].Y() + 0.5, 0.25);
        }
    }
    
    public void draw() {
        StdDraw.setPenColor(StdDraw.BLACK);
        for (int x = 1; x <= N; x++) {
            for (int y = 1; y <= N; y++) {
                if (south[x][y]) StdDraw.line(x, y, x + 1, y);
                if (north[x][y]) StdDraw.line(x, y + 1, x + 1, y + 1);
                if (west[x][y])  StdDraw.line(x, y, x, y + 1);
                if (east[x][y])  StdDraw.line(x + 1, y, x + 1, y + 1);
            }
        }
    }
    
    // Funcao que transforma 2 coordenadas da matriz numa representacao de um inteiro 
    public static int ToIndex (int x, int y, int N){
        return ((x-1) * N + y - 1);
    }
    
    public static void main(String[] args) {
        Maze maze;
        MatrixVert v;
        int N = Integer.parseInt(args[0]);
        if (args.length == 1){
            maze = new Maze (N);
        }
        else {
            long seed = Long.parseLong(args[1]);
            maze = new Maze (N, seed);
        }
        StdDraw.show(0);
        while (!StdIn.isEmpty()){
            maze.draw();
            int Xorigin = StdIn.readInt();
            int Yorigin = StdIn.readInt();
            int Xdest = StdIn.readInt();
            int Ydest = StdIn.readInt();
            StdDraw.setPenColor(StdDraw.RED);
            StdDraw.filledCircle(Xorigin + 0.5, Yorigin + 0.5, 0.375);
            StdDraw.filledCircle(Xdest + 0.5, Ydest + 0.5, 0.375);
            v = pathTo (ToIndex (Xorigin, Yorigin, N), ToIndex (Xdest, Ydest, N),  ToIndex (1, 1, N), N);
            drawsolve(ToIndex (Xorigin, Yorigin, N), ToIndex (Xdest, Ydest, N), ToIndex(v.X(), v.Y(), N));
            StdDraw.show(3500);
            StdDraw.clear();
        }
    }
}