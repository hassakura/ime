import java.awt.event.KeyEvent;

// Classe usada para as funcoes de zoom e screenshot
public class ImgManipulation {
	public static Point2D coord1 = new Point2D(0, 0);
	public static Point2D coord2 = new Point2D(0, 0);
	public static Point2D p1 = new Point2D(0, 0);
	public static Point2D p2 = new Point2D(0, 0);

	/*
	 * Recebe uma imagem e caso o usuario pressione a tecla "9", salva a imagem
	 * no formato jpg, com o nome : Seed _ maxI _ xc _ yc _ xsize _ ysize _ M _
	 * N
	 */
	public static void ScreenShot(Image im) {
		if (StdDraw.hasNextKeyTyped()) {
			if (StdDraw.isKeyPressed(KeyEvent.VK_9)) {
				StdDraw.save(StdRandom.getSeed() + "_" + im.maxI + "_" + im.x
						+ "_" + im.y + "_" + im.xsize + "_" + im.ysize + "_"
						+ im.M + "_" + im.N + ".jpg");
			}
		}
	}

	public static void Zooming(HolomorphicFunction f, Image im) {

		if (StdDraw.mousePressed()) {

			// Leitura dos cliques do usuario, que ficarao em p1 e p2
			boolean Pressed = true;
			double xm = StdDraw.mouseX();
			double ym = StdDraw.mouseY();
			p1 = new Point2D(xm, ym);
			StdDraw.show(300);

			while (Pressed) {
				if (StdDraw.mousePressed()) {
					double xm2 = StdDraw.mouseX();
					double ym2 = StdDraw.mouseY();
					p2 = new Point2D(xm2, ym2);
					StdDraw.show(300);
					Pressed = false;
				}
			}

			/*
			 * Guarda os novos valores da dimensao a ser considerada no calculo
			 * das raizes em coord1 e coord2. Isso devido a possibilidade de
			 * fazer sucessivos Zooms, e ainda manter o tamanho do quadro. Por
			 * exemplo, temos uma imagem 500x500. Suponhamos que queremos dar
			 * zoom no retangulo formado pelas coordenadas (250, 250) e (500,
			 * 500). Ao dar o segundo zoom, temos que considerar apenas a região
			 * compreendida entre esses dois pontos. sum1 e sum2 sao usados para
			 * redimensionar o intervalo a ser considerado, para saber o ponto
			 * mais proximo dos limites da regiao anterior.
			 */
			
			double sumx = 0;
			double sumy = 0;
			
			if (coord1.x() <= coord2.x())
				sumx = coord1.x();
			else
				sumx = coord2.x();
			if (coord1.y() <= coord2.y())
				sumy = coord1.y();
			else
				sumy = coord2.y();

			// Redimensionamento proporcional ao tamanho do retangulo formado
			// por p1 e p2.

			coord1 = new Point2D(p1.x() * im.Mnew / im.M + sumx, p1.y()
					* im.Nnew / im.N + sumy);
			coord2 = new Point2D(p2.x() * im.Mnew / im.M + sumx, p2.y()
					* im.Nnew / im.N + sumy);

			// Aqui pegamos o intervalo a ser considerado para realizar o Zoom.

			double yim0 = (im.y - (im.ysize / 2) + im.ysize * (int) p1.y()
					/ im.N);
			double xim0 = (im.x - (im.xsize / 2) + im.xsize * (int) p1.x()
					/ im.M);
			double yim1 = (im.y - (im.ysize / 2) + im.ysize * (int) p2.y()
					/ im.N);
			double xim1 = (im.x - (im.xsize / 2) + im.xsize * (int) p2.x()
					/ im.M);

			// A nova imagem tem dimensoes MnewxNnew. Porem, ainda estaremos
			// mostrando
			// ela com dimensoes MxN

			im.Nnew = (int) Math.abs(coord2.y() - coord1.y());
			im.Mnew = (int) Math.abs(coord2.x() - coord1.x());

			// Atualizamos o centro e o intervalo.

			im.ysize = Math.abs(yim0 - yim1);
			im.xsize = Math.abs(xim0 - xim1);

			im.y = (yim0 + yim1) / 2;
			im.x = (xim0 + xim1) / 2;
			NewtonBasins.draw(f, im);
		}
	}

	public static void main(String[] args) {}

}
