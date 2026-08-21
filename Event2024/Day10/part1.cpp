#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    string runeWord;
    ifstream infile("../input1.txt");
    vector<string> grid;
    vector<string> rowChars;
    vector<string> colChars;
    
    string line;
    while (getline(infile, line)) {
        grid.push_back(line);
    }
    infile.close();
    
    for (int i = 2; i < grid.size() - 2; i++) {
        rowChars.push_back(grid[i].substr(0, 2) + grid[i].substr(grid[i].size() - 2, 2));
        //cout << grid[i].substr(0, 2) + grid[i].substr(grid[i].size() - 2, 2) << endl;
        colChars.push_back(grid[0].substr(i, 1) + grid[1].substr(i, 1) + grid[grid.size() - 2].substr(i, 1) + grid[grid.size() - 1].substr(i, 1));
        //cout << grid[0].substr(i, 1) + grid[1].substr(i, 1) + grid[grid.size() - 2].substr(i, 1) + grid[grid.size() - 1].substr(i, 1) << endl;
    }
    
    for (int i = 0; i < rowChars.size() * colChars.size(); i++) {
        int row = i / rowChars.size();
        int col = i % colChars.size();
        
        cout << row << " " << col << endl;
        
        for (char rowChar : rowChars[row]) {
            for (char colChar : colChars[col]) {
                if (rowChar == colChar) {
                    cout << rowChar << endl;
                    runeWord += rowChar;
                }
            }
        }
    }

    cout << "Total: " << runeWord << endl;

    return 0;
}
