#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <ranges>
#include <sstream>
#include <vector>
using namespace std;

#define NUM_ROUNDS 20

static long getTermiteCount(map<string, vector<string>>& termiteMap, const int& rounds, const string& start) {
    map<string, long> termiteCounts;
    termiteCounts[start] = 1;
    long total = 0;
    
    for (int n = 0; n < rounds; n++) {
        map<string, long> nextTermiteCounts;
        for (const auto& termiteCount : termiteCounts) {
            for (const string& child : termiteMap[termiteCount.first]) {
                nextTermiteCounts[child] += termiteCount.second;
            }
        }
        termiteCounts.clear();
        //int count = 0;
        for (const auto& termiteCount : nextTermiteCounts) {
            termiteCounts[termiteCount.first] = termiteCount.second;
            //count += termiteCount.second;
        }
        //cout << count << endl;
    }
    
    for (const auto& termiteCount : termiteCounts) {
        total += termiteCount.second;
    }
    
    return total;
}

int main() {
    long total = 0;
    ifstream infile("../input3.txt");
    map<string, vector<string>> termiteMap;
    
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string token;
        string parent;
        vector<string> children;
        
        getline(ss, parent, ':');
        
        while (getline(ss, token, ',')) {
            children.push_back(token);
        }
        termiteMap[parent] = children;
        //termiteCounts[parent] = 0;
    }
    infile.close();
    
    long max = 0, min = LONG_MAX;
    for (const auto &key: termiteMap | views::keys) {
        long count = getTermiteCount(termiteMap, NUM_ROUNDS, key);
        cout << key << ": " << count << endl;
        if (count < min) min = count;
        if (count > max) max = count;
    }
    
    total = max - min;

    cout << "Total: " << total << endl;

    return 0;
}
