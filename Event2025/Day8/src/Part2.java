void main() throws FileNotFoundException {
    int total = 0;
    String filename = "input2.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    ArrayList<Integer> strings = new ArrayList<>();

    String[] strList = scnr.nextLine().split(",");
    for (String s : strList) {
        strings.add(Integer.parseInt(s));
    }
    scnr.close();

    for (int i = 2; i < strings.size() - 1; i++) {
        int low = Math.min(strings.get(i), strings.get(i + 1));
        int high = Math.max(strings.get(i), strings.get(i + 1));
        for (int check = 0; check < i - 1; check++) {
            int[] c = new int[] {strings.get(check), strings.get(check + 1)};
            if ((c[0] > low && c[0] < high) && (c[1] > high || c[1] < low) || (c[1] > low && c[1] < high) && (c[0] > high || c[0] < low)) {
                total++;
            }
        }
    }

    System.out.printf("Total: %d\n", total);
}