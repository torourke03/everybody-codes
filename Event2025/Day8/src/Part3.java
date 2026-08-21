void main() throws FileNotFoundException {
    final int NUM_NAILS = 256;
    int total = 0;
    String filename = "input3.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    ArrayList<Integer> strings = new ArrayList<>();

    String[] strList = scnr.nextLine().split(",");
    for (String s : strList) {
        strings.add(Integer.parseInt(s));
    }
    scnr.close();
    
    for (int low = 1; low < NUM_NAILS - 1; low++) {
        for (int high = low + 2; high <= NUM_NAILS; high++) {
            int count = 0;
            for (int i = 0; i < strings.size() - 1; i++) {
                int[] c = new int[] {strings.get(i), strings.get(i + 1)};
                if ((c[0] > low && c[0] < high) && (c[1] > high || c[1] < low) || (c[1] > low && c[1] < high) && (c[0] > high || c[0] < low)) {
                    count++;
                }
                if ((c[0] == low && c[1] == high) || (c[0] == high && c[1] == low)) {
                    count++;
                }
            }
            if (count > total) total = count;
        }
    }

    System.out.printf("Total: %d\n", total);
}