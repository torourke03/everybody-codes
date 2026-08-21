void main() throws FileNotFoundException {
    int total = 0;
    String filename = "input3.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    ArrayList<String> scaleList = new ArrayList<>();
    HashMap<Integer, HashSet<Integer>> connections = new HashMap<>();
    HashSet<Integer> searched = new HashSet<>();

    while (scnr.hasNextLine()) {
        scaleList.add(scnr.nextLine().split(":")[1]);
    }

    for (int i = 0; i < scaleList.size(); i++) {
        for (int j = 0; j < scaleList.size() - 1; j++) {
            if (i == j) continue;
            for (int k = j + 1; k < scaleList.size(); k++) {
                if (i == k) continue;
                if (isParents(scaleList.get(i), scaleList.get(j), scaleList.get(k))) {
                    if (!connections.containsKey(i + 1)) connections.put(i + 1, new HashSet<>());
                    if (!connections.containsKey(j + 1)) connections.put(j + 1, new HashSet<>());
                    if (!connections.containsKey(k + 1)) connections.put(k + 1, new HashSet<>());
                    
                    connections.get(i + 1).add(j + 1);
                    connections.get(i + 1).add(k + 1);
                    connections.get(j + 1).add(i + 1);
                    connections.get(j + 1).add(k + 1);
                    connections.get(k + 1).add(i + 1);
                    connections.get(k + 1).add(j + 1);
                }
            }
        }
    }
    
    int maxSize = 0;
    for (int check : connections.keySet()) {
        if (!searched.contains(check)) {
            HashSet<Integer> tree = traverseTree(connections, check);
            searched.addAll(tree);
            if (tree.size() > maxSize) {
                maxSize = tree.size();
                int score = 0;
                for (int scaleNum : tree) {
                    score += scaleNum;
                }
                total = score;
            }
        }
    }

    System.out.printf("Total: %d\n", total);
}

private HashSet<Integer> traverseTree(HashMap<Integer, HashSet<Integer>> connections, int start) {
    Queue<Integer> q = new LinkedList<>();
    HashSet<Integer> explored = new HashSet<>();
    
    explored.add(start);
    q.add(start);
    
    while (!q.isEmpty()) {
        int curr = q.poll();
        
        for (int conn : connections.get(curr)) {
            if (!explored.contains(conn)) {
                explored.add(conn);
                q.add(conn);
            }
        }
    }
    
    return explored;
}

private boolean isParents(String child, String parent1, String parent2) {
    for (int i = 0; i < child.length(); i++) {
        if (child.charAt(i) != parent1.charAt(i) && child.charAt(i) != parent2.charAt(i)) {
            return false;
        }
    }
    return true;
}