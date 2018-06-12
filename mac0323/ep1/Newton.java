public class Newton {

	/*
	 * Recebe um complexo (que vai de (x - xsize/2) + (y - ysize/2)i, (x +
	 * xsize/2) + (y + ysize/2)i) e retorna um complexo que, depois de N
	 * iterações, pode ter convergido para uma raiz.
	 */
	public static Complex findRoot(HolomorphicFunction f, Complex z0, Counter N) {
		double eps = 1.0E-10;
		Complex zk = new Complex(0, 0);

		// Realiza esse metodo ate 1000, no maximo. Caso tenha convergido antes,
		// retorna o complexo
		for (int i = 0; i < 1000; i++) {
			zk = z0;
			Complex f0 = f.eval(z0);
			Complex fp = f.diff(z0); // f'(z0)
			z0 = z0.minus(f0.divides(fp)); // z1 = z0 - (f(z0)/f'(z0))
			N.increment();

			// Verificação caso o termo Z(n-1) e Z(n) sejam relativamente
			// iguais, ou seja, a raiz foi encontrada.
			if (z0.minus(zk).abs() <= eps || fp.abs() <= Double.NaN)
				return z0;
		}
		return z0; // Não convergiu pra raiz
	}

	public static void main(String[] args) {}

}
