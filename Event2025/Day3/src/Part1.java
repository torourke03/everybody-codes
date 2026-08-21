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
    ArrayList<Integer> crates = parseInput("input1.txt");
    
    Collections.sort(crates);
    Collections.reverse(crates);
    int curr = Integer.MAX_VALUE;
    for (int crate : crates) {
        if (crate < curr) {
            curr = crate;
            total += crate;
        }
    }
    
    System.out.printf("Output: %d\n", total);
}