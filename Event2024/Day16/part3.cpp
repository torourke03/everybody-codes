#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <ranges>
#include <sstream>
#include <vector>
using namespace std;

#define CAT_SIZE 3
#define NUM_ROLLS 256

static map<pair<int, int>, pair<int, int>> cache;

static int calcByteCoins(const string& cats) {
    int total = 0;
    map<char, int> counts;
    
    for (char c : cats) {
        counts[c]++;
    }
    for (const auto val: counts | views::values) {
        if (val >= 3) total += val - 2;
    }
    
    return total;
}

static pair<int, int> calcNSpins(const vector<int>& changes, const vector<vector<string>>& wheels, const int totalPulls, const int pullNum, const int offset) {
    if (cache.contains(make_pair(pullNum, offset))) return cache[make_pair(pullNum, offset)];
    
    string cats;
    int score = 0;
    for (int i = 0; i < wheels.size(); i++) {
        cats += wheels[i][(pullNum * changes[i] + offset) % wheels[i].size()];
    }
    if (pullNum > 0) score = calcByteCoins(cats);
    
    // Base case
    if (pullNum >= totalPulls) {
        cache[make_pair(pullNum, offset)] = make_pair(score, score);
        return cache[make_pair(pullNum, offset)];
    }
    
    pair low  = calcNSpins(changes, wheels, totalPulls, pullNum + 1, offset - 1);
    pair mid  = calcNSpins(changes, wheels, totalPulls, pullNum + 1, offset);
    pair high = calcNSpins(changes, wheels, totalPulls, pullNum + 1, offset + 1);
    
    cache[make_pair(pullNum, offset)] = make_pair(score + max(low.first, max(mid.first, high.first)), score + min(low.second, min(mid.second, high.second)));
    return cache[make_pair(pullNum, offset)];
}

int main() {
    pair<int, int> total;
    ifstream infile("../input3.txt");
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
            if (line[i] != ' ') wheels.at(i / (CAT_SIZE + 1)).push_back(line.substr(i, 1) + line.substr(i + 2, 1));
        }
    }
    infile.close();
    
    total = calcNSpins(changes, wheels, NUM_ROLLS, 0, 0);

    cout << "Total: " << total.first << " " << total.second << endl;

    return 0;
}
