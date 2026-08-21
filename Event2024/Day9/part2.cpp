#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// Coin Change algorithm based on https://en.wikipedia.org/wiki/Change-making_problem#Implementation
static vector<vector<int>> getChangeMatrix(const vector<int>& stamps, const int r) {
    vector matrix(stamps.size() + 1, vector(r + 1, 0));
    for (int i = 1; i <= r; i++) {
        matrix[0][i] = INT_MAX;
    }
    return matrix;
}

static int makeChange(const vector<int>& stamps, const int n) {
    vector matrix = getChangeMatrix(stamps, n);
    
    for (int c = 1; c <= stamps.size(); c++) {
        int stamp = stamps[c - 1];
        for (int r = 1; r <= n; r++) {
            // Just use the stamp
            if (stamp == r) matrix[c][r] = 1;
            // Stamp cannot be included. Use the previous solution for making r, excluding stamp
            else if (stamp > r) matrix[c][r] = matrix[c - 1][r];
            // Stamp can be used. Decide which one of the following solutions is the best:
            // Using the previous solution for making r (without using coin).
            // Using the previous solution for making r - coin (without using coin) plus this 1 extra coin.
            else matrix[c][r] = min(matrix[c - 1][r], 1 + matrix[c][r - stamp]);
        }
    }
    
    return matrix[matrix.size() - 1][matrix.at(matrix.size() - 1).size() - 1];
}

int main() {
    int total = 0;
    ifstream infile("../input2.txt");
    vector<int> brightnesses;
    vector stamps = {1, 3, 5, 10, 15, 16, 20, 24, 25, 30};
    
    string line;
    while (getline(infile, line)) {
        brightnesses.push_back(stoi(line));
    }
    infile.close();
    
    for (int x : brightnesses) {
        int minStamps = makeChange(stamps, x);
        cout << minStamps << endl;
        total += minStamps;
    }
    
    cout << "Total: " << total << endl;
    
    return 0;
}
