import java.awt.Color;

public class NewtonBasins {
	public static final double MAX = Math.pow(8941064, Math.E); // =)

	// Adiciona uma nova cor aleatoria (127 < R, G, B < 256) na posicao i do
	// vetor da Imagem. Esse intervalo foi usado para que as cores sejam claras
	// o bastante

	public static Color[] setNewColor(Color[] AllColors, int i) {
		AllColors[i] = new Color(StdRandom.uniform(128, 256),
				StdRandom.uniform(128, 256), StdRandom.uniform(128, 256));
		return AllColors;
	}

	// Recebe uma cor e "escurece" ela (maxI - C) vezes, para que fique claro a
	// convergencia.

	public static Color setDarkness(Counter C, Color c1, int maxI) {
		for (int l = 0; l < (maxI - C.tally()); l++) {
			int R = c1.getRed() - 10;
			int G = c1.getGreen() - 10;
			int B = c1.getBlue() - 10;

			if (R < 0)
				R = 0;
			if (G < 0)
				G = 0;
			if (B < 0)
				B = 0;

			c1 = new Color(R, G, B);
		}
		return c1;
	}

	// Define as dimensoes do quadro em que a imagem sera gerada e dos pontos
	// contidos nela

	public static void SetBoard(Image im) {
		StdDraw.setCanvasSize(im.M, im.N);
		StdDraw.setXscale(0, im.M);
		StdDraw.setYscale(0, im.N);
		StdDraw.clear(StdDraw.BLACK);
		StdDraw.show(0);
		StdDraw.setPenRadius(1 / ((im.M + im.N) / 2));
	}

	/*
	 * Desenha a imagem im. Para cada ponto contido em xsize e ysize,
	 * verificamos a quantidade de vezes em que o Metodo de Newton foi realizado
	 * ate convergir (ou nao) para uma raiz, e dependendo dessa quantidade,
	 * associamos uma tonalidade de uma cor. Cada raiz possui uma unica cor
	 * associada. Ainda podemos dar zoom ou salvar a imagem, no formato jpg, com
	 * o nome : Seed _ maxI _ xc _ yc _ xsize _ ysize _ M _ N
	 */

	public static void draw(HolomorphicFunction f, Image im) {
	//	StdRandom.setSeed(2024);
		double eps = 1.0E-10;
		Complex root = new Complex(0, 0);
		SetBoard(im);

		for (int i = 0; i < im.M; i++) {
			for (int j = 0; j < im.N; j++) {

				// Cria um complexo associado ao correspondente pixel, e executa
				// findRoot
				double x0 = im.x - (im.xsize / 2) + im.xsize * i / im.M;
				double y0 = im.y - (im.ysize / 2) + im.ysize * j / im.N;
				Complex z = new Complex(x0, y0);
				Counter C = new Counter("C");
				root = Newton.findRoot(f, z, C);

				// Depois de achar a raiz, verificamos se a raiz ja foi
				// encontrada.
				for (int k = 0; k < im.Roots.length; k++) {
					if (C.tally() < 1000) {

						// A raiz ja existe. Apenas escurecemos dependendo da
						// quantidade de iteracoes realizadas para descobri-la
						if (im.Roots[k].minus(root).abs() <= eps) {
							Color a1 = im.Colors[k];
							a1 = setDarkness(C, a1, im.maxI);
							StdDraw.setPenColor(a1);
							StdDraw.point(i, j);
							break;
						}

						// A raiz nao foi encontrada no vetor. Criamos uma cor e
						// associamos a essa raiz. Depois, escurecemos-a
						else if (Math.abs(im.Roots[k].re() - MAX) <= eps) {
							im.Roots[k] = root;
							im.Colors = setNewColor(im.Colors, k);
							Color a1 = im.Colors[k];
							a1 = setDarkness(C, a1, im.maxI);
							StdDraw.setPenColor(a1);
							StdDraw.point(i, j);
							break;
						} else ;
							
					} else break;
						
				}
			}
		}
		StdDraw.show(0);

		/*
		 * Depois de disponibilizar a imagem gerada para o usuario, ele pode
		 * tanto tirar uma ScreenShot (apertando a tecla "9") ou dar zoom em
		 * determinada regiao. Para usar o zoom, basta clicar em 2 partes da
		 * figura, e uma nova imagem sera gerada com dimensoes MxN, mas com
		 * coordenadas correspondente aos lados do retangulo formado por esses
		 * pontos.
		 */

		while (true) {
			ImgManipulation.ScreenShot(im);
			ImgManipulation.Zooming(f, im);
		}
	}

	public static void main(String[] args) {
		int maxI = 20;
		double x = 0;
		double y = 0;
		double xsize = 2;
		double ysize = 2;
		int M = 500;
		int N = 500;
		Complex[] r = new Complex[4];
		r[2] = new Complex(0, 1);
		r[3] = new Complex(0, -1);
		r[0] = new Complex(1, 0);
		r[1] = new Complex(-1, 0);
		HolomorphicFunction f = new Poly(r);
		Image im = new Image(maxI, x, y, xsize, ysize, M, N);
		draw(f, im);
	}
}
