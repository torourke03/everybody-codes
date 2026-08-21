import javafx.util.Pair;

void main() throws FileNotFoundException {
    int total = 0;
    String filename = "input3.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    ArrayList<ArrayList<Integer>> grid = new ArrayList<>();
    HashSet<Pair<Integer, Integer>> explode = new HashSet<>();
    HashSet<Pair<Integer, Integer>> bigExplode = new HashSet<>();

    while (scnr.hasNextLine()) {
        String line = scnr.nextLine();
        ArrayList<Integer> row = new ArrayList<>(line.length());
        for (int i = 0; i < line.length(); i++) {
            row.add((int) line.charAt(i) - '0');
        }
        grid.add(row);
    }
    
    for (int i = 0; i < 3; i++) {
        explode = findLargestGroup(grid);
        bigExplode.addAll(explode);
        for (Pair<Integer, Integer> barrel : explode) {
            grid.get(barrel.getKey()).set(barrel.getValue(), Integer.MAX_VALUE);
        }
    }
    total = bigExplode.size();

    System.out.printf("Total: %d\n", total);
}

private HashSet<Pair<Integer, Integer>> findLargestGroup(ArrayList<ArrayList<Integer>> grid) {
    HashSet<Pair<Integer, Integer>> explored = new HashSet<>();
    HashSet<Pair<Integer, Integer>> largestGroup = new HashSet<>();
    
    for (int num = 9; num >= 1; num--) {
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid.getFirst().size(); j++) {
                if (grid.get(i).get(j) == num && !explored.contains(new Pair<>(i, j))) {
                    HashSet<Pair<Integer, Integer>> group = explodeBarrels(grid, new Pair<>(i, j));
                    explored.addAll(group);
                    if (group.size() > largestGroup.size()) {
                        largestGroup = group;
                    }
                }
            }
        }
    }
    
    return largestGroup;
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