#include <climits>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    int total = 0;
    ifstream infile("../example1.txt");
    vector<pair<int, int>> stars;
    string line;
    
    for (int i = 0; getline(infile, line); i++) {
        for (int j = 0; j < line.length(); j++) {
            if (line[j] == '*') stars.emplace_back(i, j);
        }
    }
    infile.close();
    
    vector<bool> visited(stars.size(), false);
    total += stars.size();
    for (int i = 0; i < stars.size(); i++) {
        visited[i] = true;
        int minDist = INT_MAX;
        int index = -1;
        for (int j = 0; j < stars.size(); j++) {
            if (!visited[j] && i != j) {
                int dist = abs(stars[i].first - stars[j].first) + abs(stars[i].second - stars[j].second);
                if (dist < minDist) {
                    minDist = dist;
                    index = j;
                }
            }
        }
        
        if (index >= 0) {
            visited[index] = true;
            total += minDist;
        }
    }

    cout << "Total: " << total << endl;

    return 0;
}
