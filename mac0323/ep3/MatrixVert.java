
public class MatrixVert {
	
	private int x;
	private int y;
	private int ID;
	
	public MatrixVert(int x, int y, int ID) {
		this.x = x;
		this.y = y;
		this.ID = ID;
	}

	public int X(){ return x;	}
	
	public int Y(){ return y;	}
	
	public int getID (){ return ID;	}
	
	public int XYtoID (int x, int y, int N){
		return (x-1) * N + y - 1;
	}
	
	
	public static void main(String[] args) {
		MatrixVert bla = new MatrixVert (5, 5, 20);
		StdOut.println(bla.X());
		StdOut.println(bla.Y());
		StdOut.println(bla.getID());
	}

}