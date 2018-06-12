

public class Sinfn implements HolomorphicFunction {
	private Complex c;
	
	public Sinfn(Complex c) { this.c = c; }
	
	// returns f(x) = sin(2\pi x) - c
	public Complex eval(Complex x) {
		return x.times(2*3.1415926535897932385).sin().minus(c);
	}
	
	// returns f'(x) = 2\pi cos(2\pi x)
	public Complex diff(Complex x) {
		return x.times(2*3.1415926535897932385).cos().times(2*3.1415926535897932385);
	}
}