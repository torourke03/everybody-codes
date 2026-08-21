void main() throws FileNotFoundException {
    final int REPEAT = 1000;
    final int MAX_DIST = 1000;
    int total = 0;
    String filename = "input3.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);

    String line = scnr.nextLine();
    scnr.close();

    for (int i = 0; i < line.length(); i++) {
        if (Character.isLowerCase(line.charAt(i))) {
            // Check left end
            for (int check = i - MAX_DIST; check <= i + MAX_DIST; check++) {
                if (check >= 0 && line.charAt(check % line.length()) == Character.toUpperCase(line.charAt(i))) {
                    total++;
                }
            }
            
            // Check right end
            for (int check = i - MAX_DIST; check <= i + MAX_DIST; check++) {
                int wrappedCheck = check;
                if (check < 0) {
                    wrappedCheck = line.length() + check;
                }
                if (check < line.length() && line.charAt(wrappedCheck) == Character.toUpperCase(line.charAt(i))) {
                    total++;
                }
            }
            
            // Check middle
            for (int check = i - MAX_DIST; check <= i + MAX_DIST; check++) {
                int wrappedCheck = check % line.length();
                if (check < 0) {
                    wrappedCheck = line.length() + check;
                }
                if (line.charAt(wrappedCheck) == Character.toUpperCase(line.charAt(i))) {
                    total += REPEAT - 2;
                }
            }
        }
    }

    System.out.printf("Total: %d\n", total);
}