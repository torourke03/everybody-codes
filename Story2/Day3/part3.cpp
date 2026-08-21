#include <fstream>
#include <iostream>
#include <queue>
#include <ranges>
#include <sstream>
#include <unordered_set>
#include <vector>
using namespace std;

struct Dice {
    vector<int> faces;
    int facePos{};
    int id{};
    int seed{};
    long pulse{};
    long rollNum{};
};

// Hash function 
struct hashFunction {
    size_t operator()(const pair<int, int> &x) const {
        return x.first ^ x.second;
    }
};

static pair<vector<Dice>, vector<vector<int>>> parseInput(const string& filename) {
    ifstream infile(filename);
    pair<vector<Dice>, vector<int>> result;
    vector<Dice> diceList;
    vector<vector<int>> board;
    string line;
    
    while (getline(infile, line)) {
        if (line.empty()) break;
        stringstream ss(line);
        Dice dice;
        ss >> dice.id;
        
        getline(ss, line, '[');
        getline(ss, line, ']');
        stringstream vec(line);
        while (getline(vec, line, ',')) {
            dice.faces.push_back(stoi(line));
        }
        
        getline(ss, line, '=');
        getline(ss, line);
        dice.seed = stoi(line);
        dice.pulse = dice.seed;
        dice.rollNum = 1;
        dice.facePos = 0;
        
        diceList.push_back(dice);
    }
    
    while (getline(infile, line)) {
        vector<int> row;
        for (char c : line) {
            row.push_back(c - '0');
        }
        board.push_back(row);
    }
    
    infile.close();
    
    return make_pair(diceList, board);
}

static int calcNextScore(Dice& dice) {
    long spin = dice.rollNum * dice.pulse;
    dice.facePos = (dice.facePos + spin) % dice.faces.size();
    dice.pulse += spin;
    dice.pulse %= dice.seed;
    dice.pulse += 1 + dice.rollNum + dice.seed;
    dice.rollNum++;
    
    return dice.faces[dice.facePos];
}

static void runSim(Dice& dice, const vector<vector<int>>& board, unordered_set<pair<int, int>, hashFunction>& visited) {
    queue<pair<int, int>> q;
    // Fill initial spots
    int score = calcNextScore(dice);
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] == score) {
                visited.emplace(i, j);
                q.emplace(i, j);
            }
        }
    }
    
    while (!q.empty()) {
        score = calcNextScore(dice);
        unordered_set<pair<int, int>, hashFunction> nextPos;
        while (!q.empty()) {
            pair<int, int> p = q.front();
            q.pop();
            
            vector adj = {pair(p.first, p.second), 
                          pair(p.first - 1, p.second), pair(p.first + 1, p.second), 
                          pair(p.first, p.second - 1), pair(p.first, p.second + 1)};
            for (auto [fst, snd] : adj) {
                if (fst >= 0 && fst < board.size() && snd >= 0 && snd < board[0].size() && board[fst][snd] == score) {
                    visited.emplace(fst, snd);
                    nextPos.emplace(fst, snd);
                }
            }
        }
        for (auto [fst, snd] : nextPos) {
            q.emplace(fst, snd);
        }
    }
}

static void prettyPicture(const vector<vector<int>>& board, const unordered_set<pair<int, int>, hashFunction>& visited) {
    ofstream outfile("../picture.txt");
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (visited.contains(pair(i, j))) {
                outfile << "#";
            }
            else {
                outfile << ".";
            }
        }
        outfile << endl;
    }
}

int main() {
    int total = 0;
    pair in = parseInput("../input3.txt");
    vector diceList = in.first;
    vector board = in.second;
    unordered_set<pair<int, int>, hashFunction> visited;
    
    for (auto dice : diceList) {
        runSim(dice, board, visited);
    }
    total = visited.size();
    prettyPicture(board, visited);
    
    cout << "Total: " << total << endl;

    return 0;
}
