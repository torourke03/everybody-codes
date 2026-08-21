#include <fstream>
#include <iostream>
#include <map>
#include <ranges>
#include <vector>
#include <queue>
#include <set>
using namespace std;

// Based on https://www.geeksforgeeks.org/dsa/breadth-first-search-or-bfs-for-a-graph/
static map<pair<int, int>, int> findDist(const vector<string>& maze, const set<pair<int, int>>& trees, const pair<int, int>& start, const int startVal) {
    map<pair<int, int>, int> distances;
    int treesFound = 0;
    map<pair<int, int>, int> visited;
    queue<pair<int, int>> q;
    
    visited[start] = startVal;
    q.push(start);
    
    while (!q.empty()) {
        pair v = q.front();
        q.pop();
        
        // Check if the visited node is a herb, and add the distance to the distances map
        if (trees.contains(v)) {
            distances[v] = visited[v];
            treesFound++;
        }
        // If all herbs are found break out of loop
        if (treesFound >= trees.size()) break;
        
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
    ifstream infile("../input2.txt");
    vector<string> maze;
    pair<int, int> startLeft, startRight;
    set<pair<int, int>> trees;
    
    string line;
    for (int i = 0; getline(infile, line); i++) {
        maze.push_back(line);
        if (line[0] == '.') startLeft = make_pair(i, 0);
        if (line[line.length() - 1] == '.') startRight = make_pair(i, line.length() - 1);
        for (int j = 0; j < line.length(); j++) {
            if (line[j] == 'P') trees.insert(make_pair(i, j));
        }
    }
    infile.close();
    
    map treeDistsLeft = findDist(maze, trees, startLeft, 0);
    map treeDistsRight = findDist(maze, trees, startRight, 0);
    for (auto t: treeDistsLeft) {
        int dist = min(t.second, treeDistsRight[t.first]);
        if (dist > total) total = dist;
    }

    cout << "Total: " << total << endl;

    return 0;
}
