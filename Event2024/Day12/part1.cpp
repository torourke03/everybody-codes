#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>
using namespace std;

#define FIRST_POSITION 4

int main() {
    int total = 0;
    ifstream infile("../input1.txt");
    vector<string> lines;
    vector<pair<int, int>> targets;
    
    string line;
    getline(infile, line);
    while (getline(infile, line)) {
        if (line[0] != '=') lines.insert(lines.begin(), line);
    }
    infile.close();
    
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] == 'T') {
                int segmentVal = (i + j - FIRST_POSITION) % 3 + 1;
                int power = (i + j - FIRST_POSITION) / 3 + 1;
                total += power * segmentVal;
            }
        }
    }

    cout << "Total: " << total << endl;

    return 0;
}
