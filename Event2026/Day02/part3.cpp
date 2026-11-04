#include <fstream>
#include <iostream>
#include <ostream>
#include <set>
#include <string>
#include <vector>

std::string traverseAlloys(const int& numAlloys, const std::vector<std::vector<int>>& harderLists, const int currAlloy, std::string currString) {
    std::string nextString = std::to_string(currAlloy) + currString;
    // Base case: nextString is numAlloys long
    if (nextString.size() >= numAlloys) return nextString;

    std::vector<std::string> alloyStrings;
    for (int alloy : harderLists[currAlloy - 1]) {
        std::string alloyString = traverseAlloys(numAlloys, harderLists, alloy, nextString);
        if (alloyString.size() == numAlloys) return alloyString;
    }

    return "";
}

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

    int softestAlloy;
    std::set<int> alloys;
    std::vector<std::vector<int>> harderLists(numAlloys, std::vector<int>());
    for (std::string row : lines) {
        alloys.clear();
        for (int i = 0; i < numAlloys; i++) {
            harderLists[i].clear();
            alloys.insert(i + 1);
        }

        for (int i = 0; i < row.length(); i += 4) {
            if (row[i + 1] == '<') {
                harderLists[row[i] - '0' - 1].push_back(row[i + 2] - '0');
                alloys.erase(row[i + 2] - '0');
            }
            else {
                harderLists[row[i + 2] - '0' - 1].push_back(row[i] - '0');
                alloys.erase(row[i] - '0');
            }
        }
        for (int i : alloys) softestAlloy = i;

        std::string alloyStr = traverseAlloys(numAlloys, harderLists, softestAlloy, "");
        total += std::stol(alloyStr);
    }

    std::cout << "Total: " << total << std::endl;
    return 0;
}
