public static ArrayList<Integer> parseInput(String filename) throws FileNotFoundException {
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);

    String[] strList = scnr.nextLine().split(",");
    ArrayList<Integer> list = new ArrayList<>();
    for (String s : strList) {
        list.add(Integer.parseInt(s));
    }
    scnr.close();

    return list;
}

void main(String[] args) throws FileNotFoundException {
    int total = 0;
    ArrayList<Integer> crates = parseInput("input3.txt");

    Collections.sort(crates);
    Map<Integer, Integer> counts = new HashMap<>();
    for (int crate : crates) {
        if (!counts.containsKey(crate)) {
            counts.put(crate, 1);
        }
        else {
            counts.put(crate, counts.get(crate) + 1);
        }
    }
    
    
    for (Map.Entry<Integer, Integer> set : counts.entrySet()) {
        System.out.println(set.getKey() + ": " + set.getValue());
        if (set.getValue() > total) total = set.getValue();
    }

    System.out.printf("Output: %d\n", total);
}