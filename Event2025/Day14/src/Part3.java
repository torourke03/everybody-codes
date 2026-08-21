void main() throws FileNotFoundException {
    final int GRID_SIZE = 34;
    final int PATTERN_SIZE = 8;
    final long NUM_ROUNDS = 1000000000;
    long total = 0;
    String filename = "input3.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    ArrayList<ArrayList<Boolean>> grid = new ArrayList<>(GRID_SIZE);
    ArrayList<ArrayList<Boolean>> pattern = new ArrayList<>(PATTERN_SIZE);
    
    for (int x = 0; scnr.hasNextLine(); x++) {
        if (x >= PATTERN_SIZE) break;
        String line = scnr.nextLine();
        line = line.substring(0, line.length());
        ArrayList<Boolean> row = new ArrayList<>(PATTERN_SIZE);
        for (int i = 0; i < line.length(); i++) {
            if (line.charAt(i) == '#') row.add(true);
            else row.add(false);
        }
        pattern.add(row);
    }
    scnr.close();
    for (int i = 0; i < GRID_SIZE; i++) {
        ArrayList<Boolean> row = new ArrayList<>(GRID_SIZE);
        for (int j = 0; j < GRID_SIZE; j++) {
            row.add(true);
        }
        grid.add(row);
    }
    
    long loopSize = 0;
    long loopScore = 0;
    do {
        grid = updateGrid(grid);
        loopSize++;
        if (comparePattern(grid, pattern)) {
            loopScore += countTiles(grid);
        }
    } while (countTiles(grid) < GRID_SIZE * GRID_SIZE);
    
    long numLoops = NUM_ROUNDS / loopSize;
    long roundsRemaining = NUM_ROUNDS % loopSize;
    total = loopScore * numLoops;
    
    for (int i = 0; i < roundsRemaining; i++) {
        grid = updateGrid(grid);
        if (comparePattern(grid, pattern)) {
            total += countTiles(grid);
        }
    }

    System.out.printf("Total: %d\n", total);
}

private ArrayList<ArrayList<Boolean>> updateGrid(ArrayList<ArrayList<Boolean>> grid) {
    int[][] diagonals = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    ArrayList<ArrayList<Boolean>> newGrid = new ArrayList<>(grid.size());

    for (int i = 0; i < grid.size(); i++) {
        ArrayList<Boolean> row = new ArrayList<>();
        for (int j = 0; j < grid.getFirst().size(); j++) {
            int numDiagonals = 0;
            for (int[] diagonal : diagonals) {
                int[] check = {i + diagonal[0], j + diagonal[1]};
                if (check[0] >= 0 && check[0] < grid.size() && check[1] >= 0 && check[1] < grid.getFirst().size() && grid.get(check[0]).get(check[1])) {
                    numDiagonals++;
                }
            }
            if (numDiagonals % 2 == 0) {
                row.add(!grid.get(i).get(j));
            }
            else {
                row.add(grid.get(i).get(j));
            }
        }
        newGrid.add(row);
    }

    return newGrid;
}

private boolean comparePattern(ArrayList<ArrayList<Boolean>> grid, ArrayList<ArrayList<Boolean>> pattern) {
    int offset = (grid.size() / 2) - (pattern.size() / 2);
    for (int i = 0; i < pattern.size(); i++) {
        for (int j = 0; j < pattern.getFirst().size(); j++) {
            if (pattern.get(i).get(j) != grid.get(i + offset).get(j + offset)) return false;
        }
    }
    return true;
}

private int countTiles(ArrayList<ArrayList<Boolean>> grid) {
    int total = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.getFirst().size(); j++) {
            if (grid.get(i).get(j)) total++;
        }
    }
    return total;
}