void main() throws FileNotFoundException {
    final int WALL_LENGTH = 90;
    int total = 0;
    String filename = "input1.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    String[] dists;

    dists = scnr.nextLine().split(",");
    scnr.close();
    
    for (String dist : dists) {
        total += WALL_LENGTH / Integer.parseInt(dist);
    }
    
    System.out.printf("Total: %d\n", total);
}