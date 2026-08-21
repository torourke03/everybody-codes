void main() throws FileNotFoundException {
    double total = 0.0;
    String filename = "input3.txt";
    File inFile = new File("src/" + filename);
    Scanner scnr = new Scanner(inFile);
    double firstGear = 0.0;
    double lastGear = 0.0;
    double multiply = 100.0;
    ArrayList<Integer> midRatios = new ArrayList<>();
    
    firstGear = scnr.nextDouble();
    scnr.nextLine();
    while(scnr.hasNextLine()) {
        String[] splitLine = scnr.nextLine().split("\\|");
        if (splitLine.length == 2) {
            //midRatios.add(Integer.parseInt(splitLine[1]) / Integer.parseInt(splitLine[0]));
            multiply *= Double.parseDouble(splitLine[1]) / Double.parseDouble(splitLine[0]);
        }
        else {
            lastGear = Double.parseDouble(splitLine[0]);
        }
    }
    scnr.close();
    
    total = (firstGear / lastGear * multiply);

    System.out.printf("Output: %f\n", total);
}