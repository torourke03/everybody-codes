#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <ranges>
#include <set>
#include <vector>
using namespace std;

// Based on https://www.geeksforgeeks.org/dsa/breadth-first-search-or-bfs-for-a-graph/
static map<pair<int, int>, int> findDist(const vector<string>& maze, const pair<int, int>& start, const int startVal) {
    map<pair<int, int>, int> visited;
    queue<pair<int, int>> q;
    
    visited[start] = startVal;
    q.push(start);
    
    while (!q.empty()) {
        pair v = q.front();
        q.pop();
        
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
    
    return visited;
}

int main() {
    int total = INT_MAX;
    ifstream infile("../input3.txt");
    vector<string> maze;
    set<pair<int, int>> trees;
    map<pair<int, int>, int> totalDists;
    
    string line;
    for (int i = 0; getline(infile, line); i++) {
        maze.push_back(line);
        for (int j = 0; j < line.length(); j++) {
            if (line[j] == 'P') trees.insert(make_pair(i, j));
        }
    }
    infile.close();
    
    for (auto tree : trees) {
        map distMap = findDist(maze, tree, 0);
        for (auto dist : distMap) {
            if (!trees.contains(dist.first)) totalDists[dist.first] += dist.second;
        }
    }
    
    for (auto val: totalDists | views::values) {
        if (val < total) total = val;
    }

    cout << "Total: " << total << endl;

    return 0;
}
