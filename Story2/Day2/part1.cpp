#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>
using namespace std;

static vector<int> parseInput(const string& filename) {
    ifstream infile(filename);
    vector<int> balloons;
    string line;
    
    getline(infile, line);
    for (char& c : line) {
        if (c == 'R') balloons.push_back(0);
        else if (c == 'G') balloons.push_back(1);
        else if (c == 'B') balloons.push_back(2);
    }
    infile.close();
    
    return balloons;
}

int main() {
    int total = 0;
    vector balloons = parseInput("../input1.txt");
    int currBalloon = 0;
    int i = 0;
    
    while (i < balloons.size()) {
        // Pop all balloons of same color (number)
        while (i < balloons.size() && balloons[i] == (currBalloon % 3)) {
            i++;
        }
        i++; // Pop one extra balloon
        
        currBalloon++;
    }
    total = currBalloon;
    
    cout << "Total: " << total << endl;

    return 0;
}
