void main() throws FileNotFoundException {
    int total = 0;
    String filename = "input1.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    ArrayList<Integer> temp = new ArrayList<>();
    ArrayList<Integer> vals = new ArrayList<>();
    
    vals.add(1);
    while (scnr.hasNextLine()) {
        temp.add(scnr.nextInt());
        vals.add(-1);
    }
    
    int low = 1;
    int high = vals.size() - 1;
    for (int i = 0; i < temp.size(); i++) {
        if (i % 2 == 0) {
            vals.set(low, temp.get(i));
            low++;
        }
        else {
            vals.set(high, temp.get(i));
            high--;
        }
    }
    
    total = vals.get(2025 % vals.size());
    
    System.out.printf("Total: %d\n", total);
}
