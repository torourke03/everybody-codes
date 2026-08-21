void main() throws FileNotFoundException {
    int total = 0;
    String filename = "input2.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    ArrayList<String> scales = new ArrayList<>();

    while (scnr.hasNextLine()) {
        scales.add(scnr.nextLine().split(":")[1]);
    }

    for (int i = 0; i < scales.size(); i++) {
        for (int j = 0; j < scales.size() - 1; j++) {
            if (i == j) continue;
            for (int k = j + 1; k < scales.size(); k++) {
                if (i == k) continue;
                if (isParents(scales.get(i), scales.get(j), scales.get(k))) {
                    int score = similarityScore(scales.get(i), scales.get(j)) * similarityScore(scales.get(i), scales.get(k));
                    total += score;
                }
            }
        }
    }

    System.out.printf("Total: %d\n", total);
}

private int similarityScore(String scale1, String scale2) {
    int score = 0;

    for (int i = 0; i < scale1.length(); i++) {
        if (scale1.charAt(i) == scale2.charAt(i)) score++;
    }

    return score;
}

private boolean isParents(String child, String parent1, String parent2) {
    for (int i = 0; i < child.length(); i++) {
        if (child.charAt(i) != parent1.charAt(i) && child.charAt(i) != parent2.charAt(i)) {
            return false;
        }
    }
    return true;
}