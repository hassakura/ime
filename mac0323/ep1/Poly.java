public class Poly implements HolomorphicFunction {
	
	private int d;
	private Complex[] r;
	
	public Poly(Complex[] r) {
		this.d = r.length;
		this.r = r;
	}
		
	public Complex eval(Complex x) {
		Complex p = new Complex(1.0, 0.0);
		for (int i = 0; i < d; i++)
			p = p.times(x.minus(r[i]));
		return p;
	}
	
	public Complex diff(Complex x) {
		Complex s = new Complex(0.0, 0.0);
		for (int i = 0; i < d; i++) {
			Complex p = new Complex(1.0, 0.0);
			for (int j = 0; j < d; j++)
				if (j != i)
					p = p.times(x.minus(r[j]));
			s = s.plus(p);
		}
		return s;
	}
}
