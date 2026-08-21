#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define MAX_DIFF 100

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
    ifstream infile("../input3.txt");
    vector<int> brightnesses;
    vector stamps = {1, 3, 5, 10, 15, 16, 20, 24, 25, 30, 37, 38, 49, 50, 74, 75, 100, 101};
    
    string line;
    while (getline(infile, line)) {
        brightnesses.push_back(stoi(line));
    }
    infile.close();
    
    for (int x : brightnesses) {
        int low = 0, high = 0;
        if (x % 2 == 0) {
            low = x / 2;
            high = x / 2;
        }
        else {
            low = x / 2;
            high = x / 2 + 1;
        }
        
        int minStamps = INT_MAX;
        cout << x << ": " << endl;
        while (high - low <= MAX_DIFF) {
            int lowStamps = makeChange(stamps, low);
            int highStamps = makeChange(stamps, high);
            //cout << "low = " << low << ", lowStamps = " << lowStamps << ", high =  " << high << ", highStamps = " << highStamps << ", total = " << lowStamps + highStamps << endl;
            
            if (lowStamps + highStamps < minStamps) {
                //cout << "Found lower stamp total: " << lowStamps << " + " << highStamps << " = " << lowStamps + highStamps << endl;
                minStamps = lowStamps + highStamps;
            }
            low--;
            high++;
        }
        cout << minStamps << endl;
        total += minStamps;
    }
    
    cout << "Total: " << total << endl;
    
    return 0;
}
