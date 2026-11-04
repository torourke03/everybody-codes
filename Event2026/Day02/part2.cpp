#include <cmath>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
    std::string filename = "input.txt";
    if (argc == 2) filename = argv[1];
    std::ifstream inFile(filename);
    long total = 0;
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    int numAlloys = 0;
    for (int i = 0; i < lines[0].length(); i++) {
        if (lines[0][i] - '0' >= 0 && lines[0][i] - '0' <= 9) numAlloys = std::max(numAlloys, lines[0][i] - '0');
    }

    std::vector<int> alloyScores(numAlloys, 0);
    std::vector<int> alloyCounts(numAlloys, 0);
    std::vector<int> missingIndexes;
    for (std::string row : lines) {
        for (int i = 0; i < numAlloys; i++) {
            alloyScores[i] = 0;
            alloyCounts[i] = 0;
        }
        missingIndexes.clear();

        for (int i = 0; i < row.length(); i += 4) {
            if (row[i + 1] == '<') {
                alloyScores[row[i + 2] - '0' - 1]++;
            }
            else {
                alloyScores[row[i] - '0' - 1]++;
            }
            alloyCounts[row[i] - '0' - 1]++;
            alloyCounts[row[i + 2] - '0' - 1]++;
        }

        for (int i = 0; i < alloyCounts.size(); i++) {
            if (alloyCounts[i] < numAlloys - 1) missingIndexes.push_back(i);
        }
        if (alloyScores[missingIndexes[0]] > alloyScores[missingIndexes[1]]) alloyScores[missingIndexes[0]]++;
        else alloyScores[missingIndexes[1]]++;

        for (int i = 0; i < alloyScores.size(); i++) {
            total += (i + 1) * std::pow(10, alloyScores[i]);
        }
    }

    std::cout << "Total: " << total << std::endl;
    return 0;
}
