import java.awt.*;

void main() throws FileNotFoundException {
    int total = 0;
    String filename = "input1.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    String[] instructions;
    HashSet<Point> walls = new HashSet<>();

    instructions = scnr.nextLine().split(",");
    scnr.close();
    
    Point pos = new Point(0, 0);
    Point dir = new Point(-1, 0);
    for (String instr : instructions) {
        char turn = instr.charAt(0);
        int dist = Integer.parseInt(instr.substring(1));
        // Surely this turning works :)
        if (Math.abs(dir.x) > 0) {
            if (turn == 'L') {
                dir.y = dir.x;
            }
            else {
                dir.y = -dir.x;
            }
            dir.x = 0;
        }
        else {
            if (turn == 'L') {
                dir.x = -dir.y;
            }
            else {
                dir.x = dir.y;
            }
            dir.y = 0;
        }
        
        for (int i = 0; i < dist; i++) {
            pos.x += dir.x;
            pos.y += dir.y;
            walls.add(new Point(pos.x, pos.y));
        }
    }
    walls.remove(pos);
    
    total = findDist(walls, new Point(), pos);
    
    System.out.printf("Total: %d\n", total);
}

private int findDist(HashSet<Point> walls, Point start, Point end) {
    ArrayList<Point> adj = new ArrayList<>(4);
    adj.add(new Point(-1, 0));
    adj.add(new Point(1, 0));
    adj.add(new Point(0, -1));
    adj.add(new Point(0, 1));
    Queue<Point> q = new LinkedList<>();
    HashMap<Point, Integer> explored = new HashMap<>();
    q.add(start);
    explored.put(start, 0);
    
    int dist = 0;
    while (!q.isEmpty()) {
        Point p = q.poll();
        if (p.equals(end)) {
            dist = explored.get(p);
            break;
        }
        
        for (Point a : adj) {
            Point check = new Point(p.x + a.x, p.y + a.y);
            if (!explored.containsKey(check) && !walls.contains(check)) {
                explored.put(check, explored.get(p) + 1);
                q.add(check);
            }
        }
    }
    
    return dist;
}