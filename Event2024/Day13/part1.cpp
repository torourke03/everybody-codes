#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <ranges>
#include <vector>
using namespace std;

static int findDist(const int startHeight, const int endHeight) {
    int dist = min(abs(startHeight - endHeight), abs(startHeight + 10 - endHeight));
    dist = min(dist, abs(startHeight - 10 - endHeight)) + 1;
    return dist;
}

static int getHeight(const vector<string> &lines, const pair<int,int> &pos) {
    if (lines[pos.first][pos.second] == 'S' || lines[pos.first][pos.second] == 'E') return 0;
    if (isdigit(lines[pos.first][pos.second])) return lines[pos.first][pos.second] - '0';
    
    // Failsafe
    return -1;
}

// "Borrowed" from https://www.geeksforgeeks.org/dsa/dijkstras-shortest-path-algorithm-greedy-algo-7/
// adj = vector of (vectors of pairs<node, distance> where node = index of node in the main vector)
static vector<int> dijkstra(vector<vector<pair<int,int>>>& adj, int src) {

    int V = adj.size();

    // Min-heap (priority queue) storing pairs of (distance, node)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<int> dist(V, INT_MAX);

    // Distance from source to itself is 0
    dist[src] = 0;
    pq.emplace(0, src);

    // Process the queue until all reachable vertices are finalized
    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int d = top.first;  
        int u = top.second; 

        // If this distance not the latest shortest one, skip it
        if (d > dist[u])
            continue;

        // Explore all neighbors of the current vertex
        for (auto &p : adj[u]) {
            int v = p.first; 
            int w = p.second; 

            // If we found a shorter path to v through u, update it
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;   
                pq.emplace(dist[v], v);
            }
        }
    }

    // Return the final shortest distances from the source
    return dist;
}

int main() {
    int total = 0;
    ifstream infile("../input1.txt");
    vector<string> lines;
    vector<vector<pair<int,int>>> adjacency;
    vector<pair<int,int>> nodes;
    int start, end;
    
    string line;
    for (int row = 0; getline(infile, line); row++) {
        for (int col = 0; col < line.size(); col++) {
            if (line[col] == 'S') {
                nodes.emplace_back(row, col);
                start = nodes.size() - 1;
            }
            else if (line[col] == 'E') {
                nodes.emplace_back(row, col);
                end = nodes.size() - 1;
            }
            else if (isdigit(line[col])) {
                nodes.emplace_back(row, col);
            }
        }
        lines.push_back(line);
    }
    infile.close();
    ranges::sort(nodes); // Probably not necessary
    
    for (pair node : nodes) {
        auto up_it    = ranges::find(nodes, make_pair(node.first - 1, node.second));
        auto down_it  = ranges::find(nodes, make_pair(node.first + 1, node.second));
        auto left_it  = ranges::find(nodes, make_pair(node.first, node.second - 1));
        auto right_it = ranges::find(nodes, make_pair(node.first, node.second + 1));
        vector<pair<int,int>> adj;
        
        if (up_it != nodes.end()) {
            adj.emplace_back(up_it - nodes.begin(), findDist(getHeight(lines, node), getHeight(lines, *up_it)));
        }
        if (down_it != nodes.end()) {
            adj.emplace_back(down_it - nodes.begin(), findDist(getHeight(lines, node), getHeight(lines, *down_it)));
        }
        if (left_it != nodes.end()) {
            adj.emplace_back(left_it - nodes.begin(), findDist(getHeight(lines, node), getHeight(lines, *left_it)));
        }
        if (right_it != nodes.end()) {
            adj.emplace_back(right_it - nodes.begin(), findDist(getHeight(lines, node), getHeight(lines, *right_it)));
        }
        
        adjacency.emplace_back(adj);
    }
    
    vector dist = dijkstra(adjacency, start);
    total = dist[end];

    cout << "Total: " << total << endl;

    return 0;
}
