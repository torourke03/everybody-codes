#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>
using namespace std;

#define REPEAT 100000

static vector<int> parseInput(const string& filename) {
    ifstream infile(filename);
    string line;
    
    getline(infile, line);
    vector<int> balloons(line.length() * REPEAT);
    for (int i = 0; i < REPEAT; i++) {
        for (int j = 0; j < line.length(); j++) {
            if (line[j] == 'R') balloons[i * line.length() + j] = 0;
            else if (line[j] == 'G') balloons[i * line.length() + j] = 1;
            else if (line[j] == 'B') balloons[i * line.length() + j] = 2;
        }
    }
    infile.close();
    
    return balloons;
}

int main() {
    int total = 0;
    vector balloons = parseInput("../input3.txt");
    int currBolt = 0;
    int balloonsLeft = balloons.size();
    auto start = balloons.begin();
    auto mid = balloons.begin() + balloonsLeft / 2;
    
    while (!balloons.empty()) {
        if (*start == currBolt % 3 && balloonsLeft % 2 == 0) {
            *mid = -1;
            ++mid;
            balloonsLeft--;
        }
        else if (balloonsLeft % 2 == 0) {
            ++mid;
        }
        balloonsLeft--;
        currBolt++;
        if (balloonsLeft > 0) {
            do {
                ++start;
            } while (*start == -1);
        }
        else break;
    }
    total = currBolt;
    
    cout << "Total: " << total << endl;

    return 0;
}
