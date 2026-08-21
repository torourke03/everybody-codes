void main(String[] args) throws FileNotFoundException {
    long total = 0;
    String filename = "input3.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    ArrayList<ArrayList<Integer>> values = new ArrayList<>();
    ArrayList<Integer> ids = new ArrayList<>();
    ArrayList<Node> swords = new ArrayList<>();

    while (scnr.hasNextLine()) {
        String[] st = scnr.nextLine().split(":");
        String[] strList = st[1].split(",");
        ArrayList<Integer> list = new ArrayList<>();
        for (String s : strList) {
            list.add(Integer.parseInt(s));
        }
        ids.add(Integer.parseInt(st[0]));
        values.add(list);
    }
    scnr.close();
    
    for (int i = 0; i < values.size(); i++) {
        ArrayList<Integer> value = values.get(i);
        Node root = new Node(value.getFirst(), ids.get(i));
        for (int j = 1; j < value.size(); j++) {
            root.insertValue(value.get(j));
        }
        root.calcLevelQualities();
        swords.add(root);
    }
    
    Comparator myComparator = new SortSwords();
    Collections.sort(swords, myComparator);
    Collections.reverse(swords);
    
    for (int i = 0; i < swords.size(); i++) {
        total += (long) (i + 1) * swords.get(i).getId();
    }

    System.out.printf("Output: %d\n", total);
}