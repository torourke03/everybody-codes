#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <vector>
#include <set>
using namespace std;

int main() {
    int total = 0;
    ifstream infile("../input2.txt");
    vector<vector<pair<char, int>>> instructionSets;
    set<vector<int>> visited;
    vector pos = {0, 0, 0}; // x = -left/+right, y = -down/+up, z = -backward/+forward
    
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string token;
        vector<pair<char, int>> instructionSet;
        while (getline(ss, token, ',')) {
            instructionSet.emplace_back(token[0], stoi(token.substr(1, token.length() - 1)));
        }
        instructionSets.push_back(instructionSet);
    }
    infile.close();
    
    for (const auto& instructionSet : instructionSets) {
        pos[0] = 0;
        pos[1] = 0;
        pos[2] = 0;
        for (auto i : instructionSet) {
            char dir = i.first;
            int dist = i.second;
            for (int j = 0; j < dist; j++) {
                switch (dir) {
                    case 'L':
                        pos[0] --;
                        break;
                    case 'R':
                        pos[0] ++;
                        break;
                    case 'D':
                        pos[1] --;
                        break;
                    case 'U':
                        pos[1] ++;
                        break;
                    case 'B':
                        pos[2] --;
                        break;
                    case 'F':
                        pos[2] ++;
                        break;
                    default:
                        cout << "ERROR with instruction: " << dir << dist << endl;
                        break;
                }
                visited.insert(pos);
            }
        }
    }
    
    total += visited.size();

    cout << "Total: " << total << endl;

    return 0;
}
