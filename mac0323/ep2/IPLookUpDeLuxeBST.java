public class IPLookUpDeLuxeBST {

	public static Long TopLongIPValue = 4294967296L;

	public static void CreateCityBST(BST <Long, String> CityBST, In in1) {
		while (in1.hasNextLine()) {
			String[] data = in1.readLine().split("\",\"");
			data[4] = data[4].replace("\"", "");
			CityBST.put(SetLongIPValue(data[1]), data[4] + ", " + data[3] + ", " + data[2]);
		}
	}

	public static void CreateLogBST(BST <Long, String> CityBST, BST <String, Integer> LogBST) {

		while (StdIn.hasNextLine()) {
			String[] data = StdIn.readLine().split(" ");
			Long act = SetLongIPValue(data[data.length - 1]);
			String key = CityBST.get(CityBST.ceiling(act));
			if (act < TopLongIPValue && act >= 0) {
				if (!LogBST.contains(key))
					LogBST.put(key, 1);
				else
					LogBST.put(key, LogBST.get(key) + 1);
			} 
			else
				StdOut.println("Not a valid IP Address.");
		}
		BST <Integer, Queue<String>> st = new BST <Integer, Queue<String>>();
		for (String CEP : LogBST.keys()){
			int index = LogBST.get(CEP);
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
			BST <Long, String> CityBST = new BST <Long, String>();
			BST <String, Integer> LogBST = new BST <String, Integer>();
			CreateCityBST(CityBST, in1);
			CreateLogBST(CityBST, LogBST);
		}
		else if (args.length == 1) {
			BST <Long, String> CityBST = new BST <Long, String>();
			In in1 = new In(args[0]);
			CreateCityBST(CityBST, in1);
			while (StdIn.hasNextLine()) {
				Long LongIPValue = SetLongIPValue(StdIn.readLine());
				Long key = CityBST.ceiling(LongIPValue);
				if (LongIPValue < TopLongIPValue && LongIPValue >= 0 && CityBST.contains(key))
					StdOut.println(CityBST.get(key));
				else
					StdOut.println("Not a valid IP Address.");
			}
		} 
		else
			StdOut.println("Invalid number of arguments");
	}
}
