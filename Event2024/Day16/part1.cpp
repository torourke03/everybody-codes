#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <vector>
using namespace std;

#define CAT_SIZE 3
#define NUM_ROLLS 100

int main() {
    int total = 0;
    string output;
    ifstream infile("../input1.txt");
    vector<int> changes;
    
    string line;
    getline(infile, line);
    stringstream ss(line);
    while (getline(ss, line, ',')) {
        changes.push_back(stoi(line));
    }
    vector wheels(changes.size(), vector<string>());
    getline(infile, line);
    while (getline(infile, line)) {
        for (int i = 0; i < line.length(); i += CAT_SIZE + 1) {
            if (line[i] != ' ') wheels.at(i / (CAT_SIZE + 1)).push_back(line.substr(i, CAT_SIZE));
        }
    }
    infile.close();
    
    for (int i = 0; i < changes.size(); i++) {
        string cat = wheels.at(i).at(changes.at(i) * NUM_ROLLS % wheels.at(i).size());
        output += cat + " ";
    }

    cout << "Output: " << output << endl;

    return 0;
}
