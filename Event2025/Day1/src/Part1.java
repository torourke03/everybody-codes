void main(String[] args) throws FileNotFoundException {
    String output;
    File inFile = new File("src/input1.txt");
    Scanner scnr = new Scanner(inFile);
    ArrayList<String> names;
    ArrayList<String> directions;
    int pos = 0;
    
    String line = scnr.nextLine();
    names = new ArrayList<>(Arrays.asList(line.split(",")));
    scnr.nextLine();
    line = scnr.nextLine();
    directions = new ArrayList<>(Arrays.asList(line.split(",")));
    scnr.close();
    
    for (int i = 0; i < directions.size(); i++) {
        String direction = directions.get(i);
        int dist = Integer.parseInt(direction.substring(1));
        if (direction.charAt(0) == 'L') {
            pos = Math.max(0, pos - dist);
        }
        else {
            pos = Math.min(names.size() - 1, pos + dist);
        }
        System.out.println(pos + " " + names.get(pos));
    }
    
    output = names.get(pos);

    System.out.printf("\nOutput: %s\n", output);
}