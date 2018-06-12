import java.awt.Color;

public class Image {
	private static final double MAX = Math.pow(8941064, Math.E); // =)
	public int maxI = 0;
	public double x = 0;
	public double y = 0;
	public double xsize = 0;
	public double ysize = 0;
	public int M = 0;
	public int N = 0;
	public Complex[] Roots;
	public Color[] Colors;
	// Mnew e Nnew sao usados para guardar o tamanho da imagem ampliada
	public int Mnew = 0;
	public int Nnew = 0;

	public Image(int maxI, double x, double y, double xsize, double ysize,
			int M, int N) {
		this.maxI = maxI;
		this.x = x;
		this.y = y;
		this.xsize = xsize;
		this.ysize = ysize;
		this.M = M;
		this.N = N;
		Complex[] AllRoots = new Complex[2000];
		for (int k = 0; k < 2000; k++)
			AllRoots[k] = new Complex(MAX, MAX);
		Color[] Colors = new Color[2000];
		this.Roots = AllRoots;
		this.Colors = Colors;
		this.Mnew = M;
		this.Nnew = N;
	}

	public static void main(String[] args) {
		Complex[] AllRoots = new Complex[100];
		Color[] Colors = new Color[100];
		AllRoots[1] = new Complex(1, 0);
		Colors[1] = new Color(10, 10, 10);
		Image im = new Image(20, 0.0, 1.0, 2, 2, 200, 200);
		StdOut.println(im.maxI + " " + im.xsize + " " + im.Roots[1] + " "
				+ im.Colors[1]);
	}

}
