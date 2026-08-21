void main(String[] args) throws FileNotFoundException {
    String output;
    File inFile = new File("src/input3.txt");
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

    for (String direction : directions) {
        int dist = Integer.parseInt(direction.substring(1));
        pos = 0;
        if (direction.charAt(0) == 'L') {
            for (int j = 0; j < dist; j++) {
                if (pos == 0) pos = names.size() - 1;
                else pos--;
            }
        } else {
            pos = (pos + dist) % names.size();
        }
        Collections.swap(names, 0, pos);
        System.out.println(names.getFirst());
    }

    output = names.getFirst();

    System.out.printf("\nOutput: %s\n", output);
}