#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
    std::string filename = "input.txt";
    if (argc == 2) filename = argv[1];
    std::ifstream inFile(filename);
    int total = 0;
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    std::map<int, int> alloyScores;
    for (std::string row : lines) {
        alloyScores.clear();
        alloyScores = {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}};
        for (int i = 0; i < row.length(); i += 4) {
            if (row[i + 1] == '<') {
                alloyScores[row[i + 2] - '0']++;
            }
            else {
                alloyScores[row[i] - '0']++;
            }
        }
        for (auto alloy : alloyScores) {
            total += alloy.first * std::pow(10, alloy.second);
        }
    }

    std::cout << "Total: " << total << std::endl;
    return 0;
}
