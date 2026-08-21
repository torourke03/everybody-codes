public static int[] parseInput(String filename) throws FileNotFoundException {
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    
    int[] A = new int[2];
    String line = scnr.nextLine();
    line = line.split("[\\[\\]]")[1];
    A[0] = Integer.parseInt(line.split(",")[0]);
    A[1] = Integer.parseInt(line.split(",")[1]);
    
    scnr.close();
    return A;
}

public static int[] complexAdd(int[] first, int[] second) {
    return new int[] {first[0] + second[0], first[1] + second[1]};
}

public static int[] complexMult(int[] first, int[] second) {
    return new int[] {(first[0] * second[0]) - (first[1] * second[1]), (first[0] * second[1]) + (first[1] * second[0])};
}

public static int[] complexDiv(int[] first, int[] second) {
    return new int[] {first[0] / second[0], first[1] / second[1]};
}

void main(String[] args) throws FileNotFoundException {
    String output = "";
    int[] A = parseInput("input1.txt");
    int[] R = {0, 0};

    for (int i = 0; i < 3; i++) {
        R = complexMult(R, R);
        R = complexDiv(R, new int[] {10, 10});
        R = complexAdd(R, A);
        System.out.println(Arrays.toString(R));
    }
    output = Arrays.toString(R);
    
    System.out.printf("\nOutput: %s\n", output);
}