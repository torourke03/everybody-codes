import javafx.util.Pair;

void main() throws FileNotFoundException {
    int total = 0;
    String filename = "input2.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    ArrayList<ArrayList<Integer>> grid = new ArrayList<>();
    HashSet<Pair<Integer, Integer>> explode = new HashSet<>();

    while (scnr.hasNextLine()) {
        String line = scnr.nextLine();
        ArrayList<Integer> row = new ArrayList<>(line.length());
        for (int i = 0; i < line.length(); i++) {
            row.add((int) line.charAt(i) - '0');
        }
        grid.add(row);
    }

    explode.addAll(explodeBarrels(grid, new Pair<>(0, 0)));
    explode.addAll(explodeBarrels(grid, new Pair<>(grid.size() - 1, grid.getFirst().size() - 1)));
    total = explode.size();

    System.out.printf("Total: %d\n", total);
}

private HashSet<Pair<Integer, Integer>> explodeBarrels(ArrayList<ArrayList<Integer>> grid, Pair<Integer, Integer> start) {
    int[][] adj = new int[][] {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    Queue<Pair<Integer, Integer>> q = new LinkedList<>();
    HashSet<Pair<Integer, Integer>> explored = new HashSet<>();
    q.add(start);
    explored.add(start);

    while (!q.isEmpty()) {
        Pair<Integer, Integer> curr = q.poll();
        for (int[] a : adj) {
            Pair<Integer, Integer> check = new Pair<>(curr.getKey() + a[0], curr.getValue() + a[1]);
            if (check.getKey() >= 0 && check.getKey() < grid.size() && check.getValue() >= 0 && check.getValue() < grid.getFirst().size()
                    && !explored.contains(check) && grid.get(check.getKey()).get(check.getValue()) <= grid.get(curr.getKey()).get(curr.getValue())) {
                explored.add(check);
                q.add(check);
            }
        }
    }

    return explored;
}