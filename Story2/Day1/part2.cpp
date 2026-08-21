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

static int calcScore(const vector<vector<bool>>& board, const vector<int>& sequence, const int startCol) {
    int score = 0;
    
    int pos[] = {0, startCol};
        
    auto it = sequence.begin();
    for (int j = 0; j < board.size(); j++) {
        pos[0] = j;
        if (board[pos[0]][pos[1]]) {
            if (pos[1] == 0) pos[1]++;
            else if (pos[1] == board[j].size() - 1) pos[1]--;
            else pos[1] += *it;
            ++it;
        }
    }
    score = max((pos[1] / 2 + 1) * 2 - (startCol / 2 + 1), 0);
    
    return score;
}

int main() {
    int total = 0;
    vector<vector<bool>> board;
    vector<vector<int>> sequences;
    parseInput("../input2.txt", board, sequences);
    
    for (const auto & sequence : sequences) {
        int maxScore = 0;
        for (int i = 0; i < board[0].size(); i += 2) {
            int score = calcScore(board, sequence, i);
            if (score > maxScore) maxScore = score;
        }
        cout << maxScore << endl;
        total += maxScore;
    }
    
    cout << "Total: " << total << endl;

    return 0;
}
