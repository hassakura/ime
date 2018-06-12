
public class Tanfn implements HolomorphicFunction {
	private Complex c;

	public Tanfn(Complex c) {
		this.c = c;
	}

	public Complex sec(Complex x) {
		Complex um = new Complex(1, 0);
		return um.divides(x.cos());
	}

	// returns f(x) = sin(2\pi x) - c
	public Complex eval(Complex x) {
		return x.times(2 * 3.1415926535897932385).tan().minus(c);
	}

	// returns f'(x) = 2\pi cos(2\pi x)
	public Complex diff(Complex x) {
		Complex bla = sec(x.times(2 * 3.1415926535897932385));
		return bla.times(bla).times(2 * 3.1415926535897932385);
	}
}