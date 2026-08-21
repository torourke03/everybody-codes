import java.util.ArrayList;
import java.util.Comparator;

class SortArrayList implements Comparator<ArrayList<Integer>> {
    public int compare(ArrayList<Integer> arr1, ArrayList<Integer> arr2) {
        for (int i = 0; i < arr1.size(); i++) {
            if (arr1.get(i) < arr2.get(i)) return -1;
            if (arr1.get(i) > arr2.get(i)) return 1;
        }
        return 0;
    }
}

class SortSwords implements Comparator<Node> {
    public int compare(Node n1, Node n2) {
        if (n1.getQuality() < n2.getQuality()) return -1;
        if (n1.getQuality() > n2.getQuality()) return 1;

        SortArrayList s = new SortArrayList();
        if (s.compare(n1.getLevelQualities(), n2.getLevelQualities()) == -1) return -1;
        if (s.compare(n1.getLevelQualities(), n2.getLevelQualities()) == 1) return 1;
        
        if (n1.getId() < n2.getId()) return -1;
        if (n1.getId() > n2.getId()) return 1;
        
        return 0;
    }
}

public class Node {
    private int id;
    private int val;
    private int left;
    private int right;
    private Node child;
    private ArrayList<Integer> levelQualities = new ArrayList<>();

    public Node(int val) {
        this.val = val;
        left = -1;
        right = -1;
        child = null;
    }
    
    public Node(int val, int id) {
        this.id = id;
        this.val = val;
        left = -1;
        right = -1;
        child = null;
    }
    
    public void calcLevelQualities() {
        levelHelper(levelQualities);
    }
    
    private void levelHelper(ArrayList<Integer> levels) {
        String levelStr = "";
        if (left != -1) levelStr += left;
        levelStr += val;
        if (right != -1) levelStr += right;
        levels.add(Integer.parseInt(levelStr));
        if (child != null) {
            child.levelHelper(levels);
        }
    }
    
    public long getQuality() {
        return Long.parseLong(qualHelper(""));
    }
    
    private String qualHelper(String qual) {
        // Base case
        if (child == null) {
            return qual + val;
        }
        // Recursive case
        return child.qualHelper(qual + val);
    }
    
    public void insertValue(int value) {
        if (value < val && left == -1) {
            left = value;
        }
        else if (value > val && right == -1) {
            right = value;
        }
        else if (child == null) {
            child = new Node(value);
        }
        else {
            child.insertValue(value);
        }
    }

    public ArrayList<Integer> getLevelQualities() {
        return levelQualities;
    }

    public int getId() {
        return id;
    }
}
