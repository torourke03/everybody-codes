#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <ranges>
#include <sstream>
#include <vector>
#include <set>
using namespace std;

// Based on https://www.geeksforgeeks.org/dsa/breadth-first-search-or-bfs-for-a-graph/
static int findScore(const set<vector<int>>& branches, const set<vector<int>>& leaves, const vector<int>& start) {
    int score = 0;
    int leavesFound = 0;
    map<vector<int>, int> visited;
    queue<vector<int>> q;
    
    visited[start] = 0;
    q.push(start);
    
    while (!q.empty()) {
        vector v = q.front();
        q.pop();
        
        // Check if the visited node is a leaf, and add the distance to the score
        if (leaves.contains(v)) {
            score += visited[v];
            leavesFound++;
        }
        // If all leaves are found break out of loop
        if (leavesFound >= leaves.size()) break;
        
        vector<vector<int>> adjBranches = {
            {v[0] - 1, v[1], v[2]}, {v[0] + 1, v[1], v[2]},
            {v[0], v[1] - 1, v[2]}, {v[0], v[1] + 1, v[2]},
            {v[0], v[1], v[2] - 1}, {v[0], v[1], v[2] + 1}
        };
        for (const auto& adj : adjBranches) {
            if (branches.contains(adj)) {
                if (!visited.contains(adj)) {
                    visited[adj] = visited[v] + 1;
                    q.push(adj);
                }
            }
        }
    }
    
    return score;
}

int main() {
    int total = 0;
    ifstream infile("../input3.txt");
    vector<vector<pair<char, int>>> instructionSets;
    set<vector<int>> branches;
    set<vector<int>> leaves;
    set<vector<int>> trunk;
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
        for (int i = 0; i < instructionSet.size(); i++) {
            char dir = instructionSet[i].first;
            int dist = instructionSet[i].second;
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
                branches.insert(pos);
                if (pos[0] == 0) trunk.insert(pos);
            }
            if (i == instructionSet.size() - 1) leaves.insert(pos);
        }
    }
    
    total = INT_MAX;
    for (auto t : trunk) {
        int score = findScore(branches, leaves, t);
        if (score < total) total = score;
    }

    cout << "Total: " << total << endl;

    return 0;
}
