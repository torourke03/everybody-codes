#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
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

static pair<vector<Dice>, vector<int>> parseInput(const string& filename) {
    ifstream infile(filename);
    pair<vector<Dice>, vector<int>> result;
    vector<Dice> diceList;
    vector<int> track;
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
    
    getline(infile, line);
    for (char c : line) {
        track.push_back(c - '0');
    }
    infile.close();
    
    return make_pair(diceList, track);
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

int main() {
    int total = 0;
    pair in = parseInput("../input2.txt");
    vector diceList = in.first;
    vector track = in.second;
    vector finished(diceList.size(), false);
    vector progress(diceList.size(), 0);
    int numFinished = 0;
    int numDice = finished.size();
    
    while (numFinished < numDice) {
        for (int i = 0; i < diceList.size(); i++) {
            if (!finished[i]) {
                int score = calcNextScore(diceList[i]);
                if (score == track[progress[i]]) {
                    progress[i]++;
                    if (progress[i] == track.size()) {
                        finished[i] = true;
                        numFinished++;
                        cout << i + 1 << ",";
                    }
                }
            }
        }
        total++;
    }
    cout << endl;
    
    cout << "Total: " << total << endl;

    return 0;
}
