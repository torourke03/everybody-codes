#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>
using namespace std;

static void parseInput(const string& filename, vector<vector<bool>>& board, vector<vector<int>>& sequences) {
    ifstream infile(filename);
    
    string line;
    while (getline(infile, line)) {
        if (line[0] == '*' || line[0] == '.') {
            vector row(line.length(), false);
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '*') row[i] = true;
            }
            board.push_back(row);
        }
        else if (line[0] == 'R' || line[0] == 'L') {
            vector sequence(line.length(), 0);
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == 'L') sequence[i] = -1;
                else sequence[i] = 1;
            }
            sequences.push_back(sequence);
        }
    }
    infile.close();
}

int main() {
    int total = 0;
    vector<vector<bool>> board;
    vector<vector<int>> sequences;
    parseInput("../input1.txt", board, sequences);
    
    for (int i = 0; i < sequences.size(); i++) {
        int pos[] = {0, 2 * i};
        
        auto it = sequences[i].begin();
        for (int j = 0; j < board.size(); j++) {
            pos[0] = j;
            if (board[pos[0]][pos[1]]) {
                if (pos[1] == 0) pos[1]++;
                else if (pos[1] == board[j].size() - 1) pos[1]--;
                else pos[1] += *it;
                ++it;
            }
        }
        int score = max((pos[1] / 2 + 1) * 2 - (i + 1), 0);
        cout << score << endl;
        total += score;
    }
    
    cout << "Total: " << total << endl;

    return 0;
}
