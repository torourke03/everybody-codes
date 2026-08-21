import javafx.util.Pair;

void main() throws FileNotFoundException {
    final long NUM_TURNS = 202520252025L;
    long total = 0;
    String filename = "input3.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    ArrayList<Pair<Long, Long>> wheel = new ArrayList<>();
    ArrayList<Long> rangeSizes = new ArrayList<>();
    Deque<Pair<Long, Long>> tempStack = new ArrayDeque<>();
    Deque<Long> tempSizes = new ArrayDeque<>();
    long wheelSize = 1;

    wheel.add(new Pair<>(1L, 1L));
    rangeSizes.add(1L);
    for (int i = 0; scnr.hasNextLine(); i++) {
        String[] line = scnr.nextLine().split("-");
        if (i % 2 == 0) {
            wheel.add(new Pair<>(Long.parseLong(line[0]), Long.parseLong(line[1])));
            rangeSizes.add(Long.parseLong(line[1]) - Long.parseLong(line[0]) + 1);
        }
        else {
            tempStack.offerFirst(new Pair<>(Long.parseLong(line[1]), Long.parseLong(line[0])));
            tempSizes.offerFirst(Long.parseLong(line[1]) - Long.parseLong(line[0]) + 1);
        }

        wheelSize += Long.parseLong(line[1]) - Long.parseLong(line[0]) + 1;
    }
    while (!tempStack.isEmpty()) {
        wheel.add(tempStack.pollFirst());
        rangeSizes.add(tempSizes.pollFirst());
    }

    long dist = NUM_TURNS % wheelSize;
    int i = 0;
    while (dist >= rangeSizes.get(i)) {
        dist -= rangeSizes.get(i);
        i++;
    }

    Pair<Long, Long> range = wheel.get(i);
    if (range.getKey() < range.getValue()) {
        total = range.getKey() + dist;
    }
    else {
        total = range.getKey() - dist;
    }

    System.out.printf("Total: %d\n", total);
}
