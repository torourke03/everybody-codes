final static int MIN_LENGTH = 7;
final static int MAX_LENGTH = 11;
static HashSet<String> allNames = new HashSet<>();

public static int calcPermutations(HashMap<Character, HashSet<Character>> rules, char ch, int pos, int total, String name) {
    int curr = total;
    // Base cases
    if (pos >= MAX_LENGTH) {
        //System.out.printf("Max Len Base case: name=%s ch=%c, pos=%d\n", name, ch, pos);
        allNames.add(name);
        return curr + 1;
    }
    if (!rules.containsKey(ch)) {
        if (pos >= MIN_LENGTH) {
            //System.out.printf("No Key Base case:  name=%s ch=%c, pos=%d\n", name, ch, pos);
            allNames.add(name);
            return curr + 1;
        }
        else return 0;
    }
    
    // Add to
    if (pos >= MIN_LENGTH) {
        //System.out.printf("Adding permutation:  name=%s ch=%c, pos=%d\n", name, ch, pos);
        allNames.add(name);
        curr++;
    }
    
    // Recursive case
    for (char c : rules.get(ch)) {
        curr += calcPermutations(rules, c, pos + 1, total, name + c);
    }
    
    return curr;
}

void main() throws FileNotFoundException {
    int total = 0;
    String filename = "input3.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    HashMap<Character, HashSet<Character>> rules = new HashMap<>();
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
        if (isValid && rules.containsKey(name.charAt(name.length() - 1))) {
            calcPermutations(rules, name.charAt(name.length() - 1), name.length(), 0, name);
        }
    }
    total = allNames.size();

    System.out.printf("Total: %d\n", total);
}