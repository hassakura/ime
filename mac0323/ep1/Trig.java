public class Trig {

	public static void Fcos(Image im, double a, double b) {
		HolomorphicFunction h = new Cosfn(new Complex(a, b));
		NewtonBasins.draw(h, im);
	}

	public static void Fsin(Image im, double a, double b) {
		HolomorphicFunction h = new Sinfn(new Complex(a, b));
		NewtonBasins.draw(h, im);
	}

	public static void Ftan(Image im, double a, double b) {
		HolomorphicFunction h = new Tanfn(new Complex(a, b));
		NewtonBasins.draw(h, im);
	}

	public static void Trans1(Image im) {
		HolomorphicFunction h = new trans1();
		NewtonBasins.draw(h, im);
	}

	public static void main(String[] args) {
		long seed = Long.parseLong(args[0]);
		int maxI = Integer.parseInt(args[1]);
		double xc = Double.parseDouble(args[2]);
		double yc = Double.parseDouble(args[3]);
		double xsize = Double.parseDouble(args[4]);
		double ysize = Double.parseDouble(args[5]);
		int M = Integer.parseInt(args[6]);
		int N = Integer.parseInt(args[7]);
		double a = Double.parseDouble(args[8]);
		double b = Double.parseDouble(args[9]);
		StdOut.println("1: Sin (2*pi*z - c)");
		StdOut.println("2: Cos (2*pi*z - c)");
		StdOut.println("3: Tan (2*pi*z - c)");
		StdOut.println("4: x^pi");
		int f = StdIn.readInt();
		StdRandom.setSeed(seed);
		Image im = new Image(maxI, xc, yc, xsize, ysize, M, N);
		switch (f) {
		case 1:
			Fsin(im, a, b);
		case 2:
			Fcos(im, a, b);
		case 3:
			Ftan(im, a, b);
		case 4:
			Trans1(im);
		}
	}
}