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

static int calcSnailScore(const int startX, const int startY) {
    int ringSize = startX + startY + 1;
    int x = startX, y = startY;
    
    for (int i = 0; i < NUM_LOOPS; i++) {
        x = (x + 1) % ringSize;
        if (y == 0) y = ringSize - 1;
        else y--;
    }
    
    return (x + 1) + (100 * (y + 1));
}

int main() {
    int total = 0;
    vector<pair<int, int>> snails = parseInput("../input1.txt");
    
    for (auto [fst, snd] : snails) {
        int ringSize = fst + snd + 1;
        int x = (fst + NUM_LOOPS) % ringSize;
        int y = ringSize - x - 1;
        int sum = (x + 1) + (NUM_LOOPS * (y + 1));
        total += sum;
        cout << x << " " << y << " " << sum << endl;
    }
    
    cout << "Total: " << total << endl;

    return 0;
}
