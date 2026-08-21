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
    ArrayList<Integer> crates = parseInput("input2.txt");

    Collections.sort(crates);
    int curr = 0;
    int count = 0;
    for (int crate : crates) {
        if (crate > curr) {
            curr = crate;
            total += crate;
            //System.out.println("Adding " + crate);
            count++;
        }
        if (count >= 20) break;
    }

    System.out.printf("Output: %d\n", total);
}