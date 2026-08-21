#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define SUB_GRID_SIZE 6
#define GRID_SIZE 8

static int calcGridScore(const vector<string> &grid) {
    vector<string> rowChars;
    vector<string> colChars;
    int score = 0;
    
    for (int i = 2; i < grid.size() - 2; i++) {
        rowChars.push_back(grid[i].substr(0, 2) + grid[i].substr(grid[i].size() - 2, 2));
        colChars.push_back(grid[0].substr(i, 1) + grid[1].substr(i, 1) + grid[grid.size() - 2].substr(i, 1) + grid[grid.size() - 1].substr(i, 1));
    }
    
    for (int i = 0; i < rowChars.size() * colChars.size(); i++) {
        int row = i / rowChars.size();
        int col = i % colChars.size();
        
        for (char rowChar : rowChars[row]) {
            for (char colChar : colChars[col]) {
                if (rowChar == colChar) {
                    //cout << rowChar << ": " << (rowChar - 'A' + 1) << endl;
                    score += (i + 1) * (rowChar - 'A' + 1);
                }
            }
        }
    }
    
    return score;
}

int main() {
    int total = 0;
    ifstream infile("../example3.txt");
    vector<string> input;
    
    string line;
    while (getline(infile, line)) {
        if (!line.empty()) input.push_back(line);
    }
    infile.close();
    
    vector<vector<string>> grids((input.size() / GRID_SIZE) * (input[0].size() + 1) / (GRID_SIZE + 1));
    cout << input[0].size() + 1 << endl;
    cout << grids.size() << endl;
    
    for (int i = 0; i < input.size(); i++) {
        int gridCols = (input[i].size() + 1) / (GRID_SIZE + 1);
        for (int s = 0; s < gridCols; s++) {
            grids[s + (i / GRID_SIZE * gridCols)].push_back(input[i].substr(s * (GRID_SIZE + 1), GRID_SIZE));
            //cout << input[i].substr(s * (GRID_SIZE + 1), GRID_SIZE) << " ";
        }
        //cout << endl;
    }
    
    for (const auto& grid : grids) {
        total += calcGridScore(grid);
    }

    cout << "Total: " << total << endl;

    return 0;
}
