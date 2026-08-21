import javafx.util.Pair;

void main() throws FileNotFoundException {
    final int NUM_MOVES = 4;
    int total = 0;
    String filename = "input1.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    ArrayList<String> board = new ArrayList<>();
    Pair<Integer, Integer> start = null;
    
    int row = 0;
    while (scnr.hasNextLine()) {
        String line = scnr.nextLine();
        board.add(line);
        for (int col = 0; col < line.length(); col++) {
            if (line.charAt(col) == 'D') {
                start = new Pair<>(row, col);
            }
        }
        row++;
    }

    HashSet<Pair<Integer, Integer>> moves = findAllMoves(board, start, NUM_MOVES);
    for (Pair<Integer, Integer> move : moves) {
        if (board.get(move.getKey()).charAt(move.getValue()) == 'S') {
            total++;
        }
    }
    
    System.out.printf("Total: %d\n", total);
}

public HashSet<Pair<Integer, Integer>> findAllMoves(ArrayList<String> board, Pair<Integer, Integer> start, int numMoves) {
    final ArrayList<Pair<Integer, Integer>> knightMoves = new ArrayList<>(8);
    knightMoves.add(new Pair<>(-2, -1));
    knightMoves.add(new Pair<>(-2, 1));
    knightMoves.add(new Pair<>(2, -1));
    knightMoves.add(new Pair<>(2, 1));
    knightMoves.add(new Pair<>(-1, -2));
    knightMoves.add(new Pair<>(1, -2));
    knightMoves.add(new Pair<>(-1, 2));
    knightMoves.add(new Pair<>(1, 2));
    
    HashSet<Pair<Integer, Integer>> moves = new HashSet<>();
    HashSet<Pair<Integer, Integer>> prevMoves = new HashSet<>();
    moves.add(start);
    prevMoves.add(start);
    
    for (int i = 0; i < numMoves; i++) {
        HashSet<Pair<Integer, Integer>> nextMoves = new HashSet<>();
        for (Pair<Integer, Integer> prevMove : prevMoves) {
            for (Pair<Integer, Integer> knightMove : knightMoves) {
                Pair<Integer, Integer> nextMove = new Pair<>(prevMove.getKey() + knightMove.getKey(), prevMove.getValue() + knightMove.getValue());
                if (!moves.contains(nextMove) && nextMove.getKey() >= 0 && nextMove.getKey() < board.size() 
                            && nextMove.getValue() >= 0 && nextMove.getValue() < board.getFirst().length()) {
                    nextMoves.add(nextMove);
                    moves.add(nextMove);
                }
            }
        }
        prevMoves = nextMoves;
    }
    
    return moves;
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