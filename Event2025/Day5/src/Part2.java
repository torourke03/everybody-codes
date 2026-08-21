void main(String[] args) throws FileNotFoundException {
    long total = 0;
    String filename = "input2.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    ArrayList<ArrayList<Integer>> swords = new ArrayList<>();
    
    while (scnr.hasNextLine()) {
        String[] strList = scnr.nextLine().split(":")[1].split(",");
        ArrayList<Integer> list = new ArrayList<>();
        for (String s : strList) {
            list.add(Integer.parseInt(s));
        }
        swords.add(list);
    }
    scnr.close();
    
    long min = Long.MAX_VALUE;
    long max = 0;
    for (ArrayList<Integer> sword : swords) {
        Node root = new Node(sword.getFirst());
        for (int i = 1; i < sword.size(); i++) {
            root.insertValue(sword.get(i));
        }
        long quality = root.getQuality();
        if (quality < min) min = quality;
        if (quality > max) max = quality;
    }
    
    total = max - min;

    System.out.printf("Output: %d\n", total);
}