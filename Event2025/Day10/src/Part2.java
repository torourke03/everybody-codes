import javafx.util.Pair;

private final ArrayList<Pair<Integer, Integer>> knightMoves = new ArrayList<>(8);

void main() throws FileNotFoundException {
    final int NUM_MOVES = 20;
    int total = 0;
    String filename = "input2.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    ArrayList<String> board = new ArrayList<>();
    int numRows = 0, numCols = 0;
    HashSet<Pair<Integer, Integer>> sheep = new HashSet<>();
    HashSet<Pair<Integer, Integer>> hideouts = new HashSet<>();
    HashSet<Pair<Integer, Integer>> moves = new HashSet<>();
    
    knightMoves.add(new Pair<>(-2, -1));
    knightMoves.add(new Pair<>(-2, 1));
    knightMoves.add(new Pair<>(2, -1));
    knightMoves.add(new Pair<>(2, 1));
    knightMoves.add(new Pair<>(-1, -2));
    knightMoves.add(new Pair<>(1, -2));
    knightMoves.add(new Pair<>(-1, 2));
    knightMoves.add(new Pair<>(1, 2));
    int row = 0;
    while (scnr.hasNextLine()) {
        String line = scnr.nextLine();
        board.add(line);
        for (int col = 0; col < line.length(); col++) {
            if (line.charAt(col) == 'D') moves.add(new Pair<>(row, col));
            if (line.charAt(col) == 'S') sheep.add(new Pair<>(row, col));
            if (line.charAt(col) == '#') hideouts.add(new Pair<>(row, col));
        }
        row++;
    }
    numRows = board.size();
    numCols = board.getFirst().length();
    
    for (int i = 0; i < NUM_MOVES; i++) {
        moves = findNextMoves(numRows, numCols, moves);
        int score = eatSheep(moves, sheep, hideouts);
        sheep = moveSheep(sheep);
        total += score;
        System.out.println(score);
    }

    System.out.printf("Total: %d\n", total);
}

public HashSet<Pair<Integer, Integer>> findNextMoves(int rows, int cols, HashSet<Pair<Integer, Integer>> currMoves) {
    HashSet<Pair<Integer, Integer>> moves = new HashSet<>();
    
    for (Pair<Integer, Integer> currMove : currMoves) {
        for (Pair<Integer, Integer> knightMove : knightMoves) {
            Pair<Integer, Integer> nextMove = new Pair<>(currMove.getKey() + knightMove.getKey(), currMove.getValue() + knightMove.getValue());
            if (!moves.contains(nextMove) && nextMove.getKey() >= 0 && nextMove.getKey() < rows
                    && nextMove.getValue() >= 0 && nextMove.getValue() < cols) {
                moves.add(nextMove);
            }
        }
    }

    return moves;
}

public int eatSheep(HashSet<Pair<Integer, Integer>> moves, HashSet<Pair<Integer, Integer>> sheep, HashSet<Pair<Integer, Integer>> hideouts) {
    int total = 0;
    
    for (Pair<Integer, Integer> move : moves) {
        if (sheep.contains(move) && !hideouts.contains(move)) {
            total++;
            sheep.remove(move);
        }
        if (sheep.contains(new Pair<>(move.getKey() - 1, move.getValue())) && !hideouts.contains(move)) {
            total++;
            sheep.remove(new Pair<>(move.getKey() - 1, move.getValue()));
        }
    }
    
    return total;
}

public HashSet<Pair<Integer, Integer>> moveSheep(HashSet<Pair<Integer, Integer>> sheep) {
    HashSet<Pair<Integer, Integer>> newSheep = new HashSet<>();
    
    for (Pair<Integer, Integer> s : sheep) {
        newSheep.add(new Pair<>(s.getKey() + 1, s.getValue()));
    }
    
    return newSheep;
}

public void printMoves(ArrayList<String> board, HashSet<Pair<Integer, Integer>> moves) {
    for (int i = 0; i < board.size(); i++) {
        StringBuilder out = new StringBuilder();
        for (int j = 0; j < board.get(i).length(); j++) {
            if (moves.contains(new Pair<>(i, j))) out.append('X');
            else out.append('.');
        }
        System.out.println(out);
    }
    System.out.println();
}