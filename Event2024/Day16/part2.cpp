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
#define NUM_ROLLS 202420242024

static long calcByteCoins(const string& cats) {
    long total = 0;
    map<char, int> counts;
    
    for (char c : cats) {
        counts[c]++;
    }
    for (const auto val: counts | views::values) {
        if (val >= 3) total += val - 2;
    }
    
    return total;
}

static long calcPosN(const vector<long>& changes, const vector<vector<string>>& wheels, const long N) {
    long total = 0;
    vector<long> wheelPos(wheels.size(), 0);
    
    for (int i = 0; i < N; i++) {
        string cats = "";
        for (int j = 0; j < wheels.size(); j++) {
            wheelPos.at(j) = (wheelPos.at(j) + changes.at(j)) % wheels.at(j).size();
            cats += wheels.at(j).at(wheelPos.at(j));
        }
        total += calcByteCoins(cats);
    }
    
    return total;
}

int main() {
    long total = 0;
    ifstream infile("../input2.txt");
    vector<long> changes;
    
    string line;
    getline(infile, line);
    stringstream ss(line);
    while (getline(ss, line, ',')) {
        changes.push_back(stol(line));
    }
    vector wheels(changes.size(), vector<string>());
    getline(infile, line);
    while (getline(infile, line)) {
        for (int i = 0; i < line.length(); i += CAT_SIZE + 1) {
            if (line[i] != ' ') wheels.at(i / (CAT_SIZE + 1)).push_back(line.substr(i, 1) + line.substr(i + 2, 1));
        }
    }
    infile.close();
    
    long spinsPerLoop = wheels.at(0).size();
    for (int i = 1; i < wheels.size(); i++) {
        spinsPerLoop = lcm(spinsPerLoop, wheels.at(i).size());
    }
    cout << spinsPerLoop << endl;
    cout << NUM_ROLLS / spinsPerLoop << endl;
    cout << NUM_ROLLS % spinsPerLoop << endl;
    
    long coinsPerLoop = calcPosN(changes, wheels, spinsPerLoop);
    long remainingCoins = calcPosN(changes, wheels, NUM_ROLLS % spinsPerLoop);
    
    total = coinsPerLoop * (NUM_ROLLS / spinsPerLoop) + remainingCoins;

    cout << "Total: " << total << endl;

    return 0;
}
