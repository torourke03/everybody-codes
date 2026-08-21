void main() throws FileNotFoundException {
    int total = 0;
    String filename = "input1.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    Map<Character, Integer> mentors = new HashMap<>();

    String line = scnr.nextLine();
    scnr.close();
    
    mentors.put('A', 0);
    for (int i = 0; i < line.length(); i++) {
        char c = line.charAt(i);
        if (c == 'A' || c == 'a') {
            if (Character.isUpperCase(c)) {
                mentors.put(c, mentors.get(c) + 1);
            }
            else {
                total += mentors.get(Character.toUpperCase(c));
            }
        }
    }
    
    System.out.printf("Total: %d\n", total);
}