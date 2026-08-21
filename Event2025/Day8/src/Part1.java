void main() throws FileNotFoundException {
    int total = 0;
    String filename = "input1.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    ArrayList<Integer> nails = new ArrayList<>();

    String[] strList = scnr.nextLine().split(",");
    for (String s : strList) {
        nails.add(Integer.parseInt(s));
    }
    scnr.close();
    
    for (int i = 0; i < nails.size() - 1; i++) {
        if (Math.abs(nails.get(i) - nails.get(i + 1)) == 32 / 2) total++;
    }
    
    System.out.printf("Total: %d\n", total);
}