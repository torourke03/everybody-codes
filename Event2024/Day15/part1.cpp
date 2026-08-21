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
static map<pair<int, int>, int> findDist(const vector<string>& maze, const set<pair<int, int>>& herbs, const pair<int, int>& start) {
    map<pair<int, int>, int> distances;
    int herbsFound = 0;
    map<pair<int, int>, int> visited;
    queue<pair<int, int>> q;
    
    visited[start] = 0;
    q.push(start);
    
    while (!q.empty()) {
        pair v = q.front();
        q.pop();
        
        // Check if the visited node is a herb, and add the distance to the distances map
        if (herbs.contains(v)) {
            distances[v] = visited[v];
            herbsFound++;
        }
        // If all herbs are found break out of loop
        if (herbsFound >= herbs.size()) break;
        
        vector<pair<int, int>> adjPos = {
            {v.first - 1, v.second}, {v.first + 1, v.second},
            {v.first, v.second - 1}, {v.first, v.second + 1},
        };
        for (const auto& adj : adjPos) {
            if (adj.first >= 0 && adj.first < maze.size() && adj.second >= 0 && adj.second < maze[adj.first].size()) { // In maze bounds
                if (maze[adj.first][adj.second] != '#') { // Is not wall
                    if (!visited.contains(adj)) { // Is not visited
                        visited[adj] = visited[v] + 1;
                        q.push(adj);
                    }
                }
            }
        }
    }
    
    return distances;
}

int main() {
    int total = 0;
    ifstream infile("../input1.txt");
    vector<string> maze;
    pair<int, int> start;
    set<pair<int, int>> herbs;
    
    string line;
    for (int i = 0; getline(infile, line); i++) {
        for (int j = 0; j < line.length(); j++) {
            if (i == 0 && line[j] == '.') start = make_pair(0, j);
            if (line[j] == 'H') herbs.insert(make_pair(i, j));
        }
        maze.push_back(line);
    }
    infile.close();
    
    map scores = findDist(maze, herbs, start);
    
    total = INT_MAX;
    for (auto score : scores) {
        if (score.second < total) total = score.second;
    }
    total *= 2;

    cout << "Total: " << total << endl;

    return 0;
}
