public class IPLookUpDeLuxeRBBST {

	public static Long TopLongIPValue = 4294967296L;

	public static void CreateCityRBBST(RedBlackBST <Long, String> CityRBBST, In in1) {
		while (in1.hasNextLine()) {
			String[] data = in1.readLine().split("\",\"");
			data[4] = data[4].replace("\"", "");
			CityRBBST.put(SetLongIPValue(data[1]), data[4] + ", " + data[3] + ", " + data[2]);
		}
	}

	public static void CreateLogRBBST(RedBlackBST <Long, String> CityRBBST, RedBlackBST <String, Integer> LogRBBST) {

		while (StdIn.hasNextLine()) {
			String[] data = StdIn.readLine().split(" ");
			Long act = SetLongIPValue(data[data.length - 1]);
			String key = CityRBBST.get(CityRBBST.ceiling(act));
			if (act < TopLongIPValue && act >= 0) {
				if (!LogRBBST.contains(key))
					LogRBBST.put(key, 1);
				else
					LogRBBST.put(key, LogRBBST.get(key) + 1);
			} 
			else
				StdOut.println("Not a valid IP Address.");
		}
		RedBlackBST <Integer, Queue<String>> st = new RedBlackBST <Integer, Queue<String>>();
		for (String CEP : LogRBBST.keys()){
			int index = LogRBBST.get(CEP);
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
			RedBlackBST <Long, String> CityRBBST = new RedBlackBST <Long, String>();
			RedBlackBST <String, Integer> LogRBBST = new RedBlackBST <String, Integer>();
			CreateCityRBBST(CityRBBST, in1);
			CreateLogRBBST(CityRBBST, LogRBBST);
		}
		else if (args.length == 1) {
			RedBlackBST <Long, String> CityRBBST = new RedBlackBST <Long, String>();
			In in1 = new In(args[0]);
			CreateCityRBBST(CityRBBST, in1);
			while (StdIn.hasNextLine()) {
				Long LongIPValue = SetLongIPValue(StdIn.readLine());
				Long key = CityRBBST.ceiling(LongIPValue);
				if (LongIPValue < TopLongIPValue && LongIPValue >= 0 && CityRBBST.contains(key))
					StdOut.println(CityRBBST.get(key));
				else
					StdOut.println("Not a valid IP Address.");
			}
		} 
		else
			StdOut.println("Invalid number of arguments");
	}
}
