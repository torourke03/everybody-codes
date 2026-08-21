void main() throws FileNotFoundException {
    long total = 1;
    String filename = "input2.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile).useDelimiter(",");
    ArrayList<Integer> wall = new ArrayList<>();
    
    while (scnr.hasNextInt()) {
        wall.add(scnr.nextInt());
    }
    scnr.close();
    
    int tryVal = 1;
    while (!isWallEmpty(wall)) {
        boolean isValid = true;
        for (int i = -1 + tryVal; i < wall.size(); i += tryVal) {
            if (wall.get(i) <= 0) {
                isValid = false;
                break;
            }
        }
        if (isValid) {
            for (int i = -1 + tryVal; i < wall.size(); i += tryVal) {
                wall.set(i, wall.get(i) - 1);
            }
            System.out.println(tryVal);
            total *= tryVal;
        }
        tryVal++;
    }
    
    
    System.out.printf("Total: %d\n", total);
}

private boolean isWallEmpty(ArrayList<Integer> wall) {
    for (int i : wall) {
        if (i > 0) return false;
    }
    return true;
}