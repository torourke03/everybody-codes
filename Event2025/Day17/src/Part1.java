import java.awt.*;

void main() throws FileNotFoundException {
    final int RADIUS = 10;
    int total = 0;
    String filename = "input1.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    ArrayList<String> map = new ArrayList<>();
    Point volcano = new Point();
    
    for (int i = 0; scnr.hasNextLine(); i++) {
        String line = scnr.nextLine();
        map.add(line);
        if (line.indexOf('@') >= 0) volcano = new Point(i, line.indexOf('@'));
    }
    scnr.close();
    
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map.getFirst().length(); j++) {
            if (Math.powExact(volcano.x - i, 2) + Math.powExact(volcano.y - j, 2) <= RADIUS * RADIUS && map.get(i).charAt(j) != '@') {
                total += map.get(i).charAt(j) - '0';
                //System.out.print(map.get(i).charAt(j) - '0');
            }
        }
        //System.out.println();
    }
    
    System.out.printf("Total: %d\n", total);
}