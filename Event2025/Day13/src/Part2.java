import javafx.util.Pair;

void main() throws FileNotFoundException {
    final int NUM_TURNS = 20252025;
    int total = 0;
    String filename = "input2.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    ArrayList<Pair<Integer, Integer>> wheel = new ArrayList<>();
    ArrayList<Integer> rangeSizes = new ArrayList<>();
    Deque<Pair<Integer, Integer>> tempStack = new ArrayDeque<>();
    Deque<Integer> tempSizes = new ArrayDeque<>();
    int wheelSize = 1;

    wheel.add(new Pair<>(1, 1));
    rangeSizes.add(1);
    for (int i = 0; scnr.hasNextLine(); i++) {
        String[] line = scnr.nextLine().split("-");
        if (i % 2 == 0) {
            wheel.add(new Pair<>(Integer.parseInt(line[0]), Integer.parseInt(line[1])));
            rangeSizes.add(Integer.parseInt(line[1]) - Integer.parseInt(line[0]) + 1);
        }
        else {
            tempStack.offerFirst(new Pair<>(Integer.parseInt(line[1]), Integer.parseInt(line[0])));
            tempSizes.offerFirst(Integer.parseInt(line[1]) - Integer.parseInt(line[0]) + 1);
        }
        
        wheelSize += Integer.parseInt(line[1]) - Integer.parseInt(line[0]) + 1;
    }
    while (!tempStack.isEmpty()) {
        wheel.add(tempStack.pollFirst());
        rangeSizes.add(tempSizes.pollFirst());
    }

    int dist = NUM_TURNS % wheelSize;
    int i = 0;
    while (dist >= rangeSizes.get(i)) {
        dist -= rangeSizes.get(i);
        i++;
    }
    
    Pair<Integer, Integer> range = wheel.get(i);
    if (range.getKey() < range.getValue()) {
        total = range.getKey() + dist;
    }
    else {
        total = range.getKey() - dist;
    }

    System.out.printf("Total: %d\n", total);
}
