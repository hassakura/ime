
public class trans1 implements HolomorphicFunction {

	public trans1() {
	}

	public static Complex log(Complex z) {
		return new Complex(Math.log(z.abs()), z.phase());
	}

	// y^x
	public static Complex pow(Complex y, Complex x) {
		return x.times(log(y)).exp();
	}

	// x^pi
	public Complex eval(Complex x) {
		Complex y = new Complex(Math.PI, 0);
		return pow(x, y);
	}

	// pi * x^(pi - 1)
	public Complex diff(Complex x) {
		Complex y = new Complex(Math.PI - 1, 0);
		return pow(x, y).times(3.1415926535897932385);
	}
}
