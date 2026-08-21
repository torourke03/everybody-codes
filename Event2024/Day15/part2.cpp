#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <ranges>
#include <vector>
#include <set>
using namespace std;

// Based on https://www.geeksforgeeks.org/dsa/breadth-first-search-or-bfs-for-a-graph/
static map<pair<int, int>, int> findDist(const vector<string>& maze, const set<pair<int, int>>& herbs, const pair<int, int>& start, const int startVal) {
    map<pair<int, int>, int> distances;
    int herbsFound = 0;
    map<pair<int, int>, int> visited;
    queue<pair<int, int>> q;
    
    visited[start] = startVal;
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
                if (maze[adj.first][adj.second] != '#' && maze[adj.first][adj.second] != '~') { // Is not wall
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

static int findMinDist(const vector<string>& maze, const map<char, set<pair<int, int>>>& herbTypes, const pair<int, int>& start, const string& order) {
    map<pair<int, int>, int> currDistances;
    currDistances[start] = 0;
    for (int i = 0; i < order.length(); i++) {
        map<pair<int, int>, int> nextDistances;
        for (auto nextHerb : herbTypes.at(order[i])) {
            nextDistances[nextHerb] = INT_MAX;
        }
        for (auto currDist : currDistances) {
            map nextHerbDists = findDist(maze, herbTypes.at(order[i]), currDist.first, currDist.second);
            for (auto nextHerb : nextHerbDists) {
                nextDistances[nextHerb.first] = min(nextDistances[nextHerb.first], nextHerb.second);
            }
        }
        
        currDistances = nextDistances;
    }
    
    return currDistances[start];
}

int main() {
    int total = 0;
    ifstream infile("../input2.txt");
    vector<string> maze;
    pair<int, int> start;
    map<char, set<pair<int, int>>> herbTypes;
    
    string line;
    for (int i = 0; getline(infile, line); i++) {
        for (int j = 0; j < line.length(); j++) {
            if (i == 0 && line[j] == '.') start = make_pair(0, j);
            if (isalpha(line[j])) herbTypes[line[j]].insert(make_pair(i, j));
        }
        maze.push_back(line);
    }
    infile.close();
    
    string herbOrder;
    for (const auto &key: herbTypes | views::keys) {
        herbOrder += key;
    }
    ranges::sort(herbOrder);
    herbTypes['.'].insert(start);
    
    //int test = findMinDist(maze, herbTypes, start, "ACB.");
    //cout << test << endl;
    
    total = INT_MAX;
    do {
        cout << herbOrder << ".: ";
        int minDist = findMinDist(maze, herbTypes, start, herbOrder + '.');
        cout << minDist << endl;
        if (minDist < total) total = minDist;
    } while (ranges::next_permutation(herbOrder).found);

    cout << "Total: " << total << endl;

    return 0;
}
