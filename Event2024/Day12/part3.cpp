#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>
using namespace std;

int main() {
    int total = 0;
    ifstream infile("../example3.txt");
    vector<string> lines;
    vector<pair<int, int>> targets;
    
    int a, b;
    while (infile >> a >> b) {
        targets.emplace_back(a, b);
    }
    infile.close();
    
    for (auto [fst, snd] : targets) {
        int x = fst / 2;
        int y = snd - (fst - x);
        
        while (y >= 0) {
            // Calculate if meteor is in any firing path
            
            x--;
            y--;
        }
    }

    cout << "Total: " << total << endl;

    return 0;
}
