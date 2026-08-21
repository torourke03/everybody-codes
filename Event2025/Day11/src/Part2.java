void main() throws FileNotFoundException {
    int total = 0;
    String filename = "input2.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    ArrayList<Integer> ducks = new ArrayList<>();

    while (scnr.hasNextLine()) {
        ducks.add(Integer.parseInt(scnr.nextLine()));
    }

    int round = 1;
    while (true) {
        boolean isDone = true;
        for (int i = 0; i < ducks.size() - 1; i++) {
            if (ducks.get(i) > ducks.get(i + 1)) {
                ducks.set(i, ducks.get(i) - 1);
                ducks.set(i + 1, ducks.get(i + 1) + 1);
                isDone = false;
            }
        }
        if (isDone) break;
        round++;
    }
    while (true) {
        boolean isDone = true;
        for (int i = 0; i < ducks.size() - 1; i++) {
            if (ducks.get(i) < ducks.get(i + 1)) {
                ducks.set(i, ducks.get(i) + 1);
                ducks.set(i + 1, ducks.get(i + 1) - 1);
                isDone = false;
            }
        }
        if (isDone) break;
        round++;
    }
    total = round - 1;

    System.out.printf("Total: %d\n", total);
}

private int checksum(ArrayList<Integer> ducks) {
    int total = 0;
    for (int i = 0; i < ducks.size(); i++) {
        total += (i + 1) * ducks.get(i);
    }
    return total;
}