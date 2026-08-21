public static long[] parseInput(String filename) throws FileNotFoundException {
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);

    long[] A = new long[2];
    String line = scnr.nextLine();
    line = line.split("[\\[\\]]")[1];
    A[0] = Long.parseLong(line.split(",")[0]);
    A[1] = Long.parseLong(line.split(",")[1]);

    scnr.close();
    return A;
}

public static long[] complexAdd(long[] first, long[] second) {
    return new long[] {first[0] + second[0], first[1] + second[1]};
}

public static long[] complexMult(long[] first, long[] second) {
    return new long[] {(first[0] * second[0]) - (first[1] * second[1]), (first[0] * second[1]) + (first[1] * second[0])};
}

public static long[] complexDiv(long[] first, long[] second) {
    return new long[] {first[0] / second[0], first[1] / second[1]};
}

public static boolean checkEngrave(long[] point) {
    long[] result = new long[] {0, 0};
    for (long i = 0; i < 100; i++) {
        result = complexMult(result, result);
        result = complexDiv(result, new long[] {100000, 100000});
        result = complexAdd(result, point);
        if (Math.abs(result[0]) > 1000000 || Math.abs(result[1]) > 1000000) {
            //System.out.println(Arrays.toString(result));
            return false;
        }
    }

    //System.out.println(Arrays.toString(result));
    return true;
}

void main(String[] args) throws IOException {
    int total = 0;
    long[] A = parseInput("example2.txt");
    long[] end = new long[] {A[0] + 1000, A[1] + 1000};
    HashSet<ArrayList<Integer>> engrave = new HashSet<>();
    
    for (long i = A[0]; i <= end[0]; i += 10) {
        for (long j = A[1]; j <= end[1]; j += 10) {
            if (checkEngrave(new long[] {i, j})) {
                total++;
                ArrayList<Integer> arr = new ArrayList<>(2);
                arr.add((int)i);
                arr.add((int)j);
                engrave.add(arr);
            }
        }
    }

    FileWriter myWriter = new FileWriter("src/output.txt");
    for (long i = A[0]; i <= end[0]; i += 10) {
        for (long j = A[1]; j <= end[1]; j += 10) {
            ArrayList<Integer> arr = new ArrayList<>(2);
            arr.add((int)i);
            arr.add((int)j);
            if (engrave.contains(arr)) {
                myWriter.write('#');
            }
            else {
                myWriter.write('.');
            }
        }
        myWriter.write("\n");
    }
    myWriter.close();

    System.out.printf("\nOutput: %d\n", total);
}