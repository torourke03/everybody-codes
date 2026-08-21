void main() throws FileNotFoundException {
    int total = 1;
    String filename = "input1.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    ArrayList<String> scales = new ArrayList<>();
    int childScale;
    
    while (scnr.hasNextLine()) {
        scales.add(scnr.nextLine().substring(2));
    }
    
    childScale = findChild(scales);
    for (int i = 0; i < scales.size(); i++) {
        if (i == childScale) continue;
        total *= similarityScore(scales.get(childScale), scales.get(i));
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

private int findChild(ArrayList<String> scales) {
    int numCandidates = scales.size();
    ArrayList<Boolean> candidates = new ArrayList<>(numCandidates);
    for (int i = 0; i < numCandidates; i++) candidates.add(true);
    
    for (int i = 0; i < scales.getFirst().length(); i++) {
        for (int j = 0; j < scales.size(); j++) {
            boolean isCandidate = false;
            for (int k = 0; k < scales.size(); k++) {
                if (j == k) continue;
                if (scales.get(j).charAt(i) == scales.get(k).charAt(i)) {
                    isCandidate = true;
                }
            }
            if (!isCandidate) {
                candidates.set(j, false);
                numCandidates--;
            }
        }
        if (numCandidates <= 1) break;
    }
    
    int index = -1;
    for (int i = 0; i < scales.size(); i++) {
        if (candidates.get(i)) index = i;
    }
    
    return index;
}