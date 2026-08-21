#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <vector>
using namespace std;

#define NUM_LOOPS 100

static vector<pair<int, int>> parseInput(const string& filename) {
    ifstream infile(filename);
    vector<pair<int, int>> snails;
    
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string x, y;
        
        getline(ss, x, '=');
        getline(ss, x, ' ');
        getline(ss, y, '=');
        getline(ss, y, ' ');
        snails.emplace_back(stoi(x) - 1, stoi(y) - 1);
    }
    infile.close();
    
    return snails;
}

int main() {
    int total = 0;
    vector<pair<int, int>> snails = parseInput("../example2.txt");
    vector<int> snailsX;
    for (auto &key: snails | views::keys) {
        snailsX.push_back(key);
    }
    
    /*int i = 1;
    while (true) {
        bool isLinedUp = true;
        for (int j = 0; j < snails.size(); j++) {
            int ringSize = snails[j].first + snails[j].second + 1;
            snailsX[j] = (snailsX[j] + 1) % ringSize;
            if (snailsX[j] != ringSize - 1) isLinedUp = false;
        }
        if (isLinedUp) break;
        
        i++;
    }
    total = i;*/
    
    for (auto snail: snails) {
        cout << snail.first + snail.second + 1 << " ";
    }
    cout << endl;
    
    cout << "Total: " << total << endl;

    return 0;
}
