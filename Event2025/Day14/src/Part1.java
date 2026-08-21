void main() throws FileNotFoundException {
    int total = 0;
    String filename = "input1.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    ArrayList<ArrayList<Boolean>> grid = new ArrayList<>();
    
    while (scnr.hasNextLine()) {
        String line = scnr.nextLine();
        ArrayList<Boolean> row = new ArrayList<>();
        for (int i = 0; i < line.length(); i++) {
            if (line.charAt(i) == '#') row.add(true);
            else row.add(false);
        }
        grid.add(row);
    }
    
    for (int i = 0; i < 10; i++) {
        grid = updateGrid(grid);
        int score = countTiles(grid);
        total += score;
        System.out.println(score);
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

private int countTiles(ArrayList<ArrayList<Boolean>> grid) {
    int total = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.getFirst().size(); j++) {
            if (grid.get(i).get(j)) total++;
        }
    }
    return total;
}