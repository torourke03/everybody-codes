#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <ranges>
#include <vector>
using namespace std;

int main() {
    int total = 0;
    ifstream infile("../input1.txt");
    vector<pair<char, int>> instructions;
    int pos[3] = {0, 0, 0}; // x = -left/+right, y = -down/+up, z = -backward/+forward
    
    string instruction;
    while (getline(infile, instruction, ',')) {
        instructions.emplace_back(instruction[0], stoi(instruction.substr(1, instruction.length() - 1)));
    }
    infile.close();
    
    int maxHeight = 0;
    for (auto i : instructions) {
        char dir = i.first;
        int dist = i.second;
        switch (dir) {
            case 'L':
                pos[0] -= dist;
                break;
            case 'R':
                pos[0] += dist;
                break;
            case 'D':
                pos[1] -= dist;
                break;
            case 'U':
                pos[1] += dist;
                break;
            case 'B':
                pos[2] -= dist;
                break;
            case 'F':
                pos[2] += dist;
                break;
            default:
                cout << "ERROR with instruction: " << dir << dist << endl;
                break;
        }
        if (maxHeight < pos[1]) maxHeight = pos[1];
    }
    
    total = maxHeight;

    cout << "Total: " << total << endl;

    return 0;
}
