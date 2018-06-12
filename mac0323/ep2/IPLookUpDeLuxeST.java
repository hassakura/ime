public class IPLookUpDeLuxeST {

	public static Long TopLongIPValue = 4294967296L;

	/* Recebe uma ST <Long, String> CityST e para cada linha de in1, coloca
	 * em CityST a representação em Long do IP lido, e seu respectivo
	 * lugar de origem.
	 */

	public static void CreateCityST(ST <Long, String> CityST, In in1) {
		while (in1.hasNextLine()) {
			String[] data = in1.readLine().split("\",\"");
			data[4] = data[4].replace("\"", "");
			CityST.put(SetLongIPValue(data[1]), data[4] + ", " + data[3] + ", " + data[2]);
		}
	}

	/* Recebe uma ST <Long, String> CityST e preenche uma outra ST <Sting, Integer> LogST com
	 * a localização dos IPs lidos pela entrada padrão. Então, imprime-os em ordem decrescente
	 */
	public static void CreateLogST(ST <Long, String> CityST, ST <String, Integer> LogST) {

		while (StdIn.hasNextLine()) {
			String[] data = StdIn.readLine().split(" ");
			Long act = SetLongIPValue(data[data.length - 1]);
			String key = CityST.get(CityST.ceiling(act));
			if (act < TopLongIPValue && act >= 0) {
				if (!LogST.contains(key))
					LogST.put(key, 1);
				else
					LogST.put(key, LogST.get(key) + 1);
			} 
			else
				StdOut.println("Not a valid IP Address.");
		}
		ST <Integer, Queue<String>> st = new ST <Integer, Queue<String>>();
		for (String CEP : LogST.keys()){
			int index = LogST.get(CEP);
			if (!st.contains(index)){
				st.put(index, new Queue<String>());
				st.get(index).enqueue(CEP);
			}
			else
				st.get(index).enqueue(CEP);
		}
		Queue<String> cty = new Queue<String>();
		while (!st.isEmpty()) {
			cty = st.get(st.max());
			while (!cty.isEmpty())
				StdOut.println(st.max() + " " + cty.dequeue());
			st.delete(st.max());
		}
	}

	/* Recebe o IP na forma de String e converte-o para um Long, único */

	public static long SetLongIPValue(String IP) {
		String[] IPArray = IP.split("\\.");
		return (16777216 * Long.parseLong(IPArray[0]))
				+ (65536 * Long.parseLong(IPArray[1]))
				+ (256 * Long.parseLong(IPArray[2]))
				+ Long.parseLong(IPArray[3]);
	}

	public static void main(String[] args) {

		if (args.length > 1) {
			In in1 = new In(args[0]);
			ST <Long, String> CityST = new ST <Long, String>();
			ST <String, Integer> LogST = new ST <String, Integer>();
			CreateCityST(CityST, in1);
			CreateLogST(CityST, LogST);
		}
		else if (args.length == 1) {
			ST <Long, String> CityST = new ST <Long, String>();
			In in1 = new In(args[0]);
			CreateCityST(CityST, in1);
			while (StdIn.hasNextLine()) {
				Long LongIPValue = SetLongIPValue(StdIn.readLine());
				Long key = CityST.ceiling(LongIPValue);
				if (LongIPValue < TopLongIPValue && LongIPValue >= 0 && CityST.contains(key))
					StdOut.println(CityST.get(key));
				else
					StdOut.println("Not a valid IP Address.");
			}
		} 
		else
			StdOut.println("Invalid number of arguments");
	}
}
