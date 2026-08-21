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
    int pulse{};
    int rollNum{};
};

static vector<Dice> parseInput(const string& filename) {
    ifstream infile(filename);
    vector<Dice> diceList;
    string line;
    
    while (getline(infile, line)) {
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
    infile.close();
    
    return diceList;
}

static int calcNextScore(Dice& dice) {
    int spin = dice.rollNum * dice.pulse;
    dice.facePos = (dice.facePos + spin) % dice.faces.size();
    dice.pulse += spin;
    dice.pulse %= dice.seed;
    dice.pulse += 1 + dice.rollNum + dice.seed;
    dice.rollNum++;
    
    return dice.faces[dice.facePos];
}

int main() {
    constexpr int MAX_SCORE = 10000;
    int total = 0;
    vector diceList = parseInput("../input1.txt");
    int score = 0;
    
    while (score < MAX_SCORE) {
        for (auto & dice : diceList) {
            score += calcNextScore(dice);
        }
        total++;
    }
    
    cout << "Total: " << total << endl;

    return 0;
}
