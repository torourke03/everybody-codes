void main(String[] args) throws FileNotFoundException {
    long total = 0;
    String filename = "input1.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);

    String[] strList = scnr.nextLine().split(":")[1].split(",");
    ArrayList<Integer> list = new ArrayList<>();
    for (String s : strList) {
        list.add(Integer.parseInt(s));
    }
    scnr.close();
    
    Node root = new Node(list.getFirst());
    for (int i = 1; i < list.size(); i++) {
        root.insertValue(list.get(i));
    }

    total = root.getQuality();
    
    System.out.printf("Output: %d\n", total);
}