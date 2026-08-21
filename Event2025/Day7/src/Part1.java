void main() throws FileNotFoundException {
    String output = "";
    String filename = "input1.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    Map<Character, HashSet<Character>> rules = new HashMap<>();
    String[] names;

    names = scnr.nextLine().split(",");
    scnr.nextLine();
    while (scnr.hasNextLine()) {
        String line = scnr.nextLine();
        char c = line.charAt(0);
        String[] after = line.substring(4).split(",");
        HashSet<Character> second = new HashSet<>();
        for (String s : after) {
            second.add(s.charAt(0));
        }
        rules.put(c, second);
    }
    scnr.close();
    
    for (String name : names) {
        boolean isValid = true;
        for (int i = 0; i < name.length() - 1; i++) {
            if (!(rules.containsKey(name.charAt(i)) && rules.get(name.charAt(i)).contains(name.charAt(i + 1)))) {
                isValid = false;
                break;
            }
        }
        if (isValid) {
            output = name;
            break;
        }
    }
    
    System.out.printf("Total: %s\n", output);
}