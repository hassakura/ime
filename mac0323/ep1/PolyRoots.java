public class PolyRoots {

	public static void main(String[] args) {
		long seed = Long.parseLong(args[0]);
		int maxI = Integer.parseInt(args[1]);
		double xc = Double.parseDouble(args[2]);
		double yc = Double.parseDouble(args[3]);
		double xsize = Double.parseDouble(args[4]);
		double ysize = Double.parseDouble(args[5]);
		int M = Integer.parseInt(args[6]);;
		int N = Integer.parseInt(args[7]);;
		StdOut.println("Qtde Raizes: ");
		int Times = StdIn.readInt();
		Complex[] r = new Complex[Times];
		for (int i = 0; i < Times; i++) {
			double a = StdIn.readDouble();
			double b = StdIn.readDouble();
			r[i] = new Complex(a, b);
		}
		HolomorphicFunction f = new Poly(r);
		StdRandom.setSeed(seed);
		Image im = new Image(maxI, xc, yc, xsize, ysize, M, N);
		NewtonBasins.draw(f, im);
	}
}
