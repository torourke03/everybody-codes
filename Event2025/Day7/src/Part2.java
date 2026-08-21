void main() throws FileNotFoundException {
    int total = 0;
    String filename = "input2.txt";
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

    for (int n = 0; n < names.length; n++) {
        String name = names[n];
        boolean isValid = true;
        for (int i = 0; i < name.length() - 1; i++) {
            if (!(rules.containsKey(name.charAt(i)) && rules.get(name.charAt(i)).contains(name.charAt(i + 1)))) {
                isValid = false;
                break;
            }
        }
        if (isValid) {
            total += n + 1;
        }
    }

    System.out.printf("Total: %d\n", total);
}