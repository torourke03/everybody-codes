#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>
using namespace std;

#define NUM_PASSES 10000

static void rotateLeft(vector<string>& lines, const int row, const int col) {
    const char temp = lines[row - 1][col - 1]; // Store TL
    
    lines[row - 1][col - 1] = lines[row - 1][col]; // TOP TO TL
    lines[row - 1][col] = lines[row - 1][col + 1]; // TR TO TOP
    lines[row - 1][col + 1] = lines[row][col + 1]; // RIGHT TO TR
    lines[row][col + 1] = lines[row + 1][col + 1]; // BR TO RIGHT
    lines[row + 1][col + 1] = lines[row + 1][col]; // BOT TO BR
    lines[row + 1][col] = lines[row + 1][col - 1]; // BL TO BOT
    lines[row + 1][col - 1] = lines[row][col - 1]; // LEFT TO BL
    lines[row][col - 1] = temp; // TL TO LEFT
}

static void rotateRight(vector<string>& lines, const int row, const int col) {
    const char temp = lines[row][col - 1]; // Store LEFT
    
    lines[row][col - 1] = lines[row + 1][col - 1]; // BL TO LEFT
    lines[row + 1][col - 1] = lines[row + 1][col]; // BOT TO BL
    lines[row + 1][col] = lines[row + 1][col + 1]; // BR TO BOT
    lines[row + 1][col + 1] = lines[row][col + 1]; // RIGHT TO BR
    lines[row][col + 1] = lines[row - 1][col + 1]; // TR TO RIGHT
    lines[row - 1][col + 1] = lines[row - 1][col]; // TOP TO TR
    lines[row - 1][col] = lines[row - 1][col - 1]; // TL TO TOP
    
    lines[row - 1][col - 1] = temp; // LEFT TO TL
}

static string checkSolution(const vector<string>& lines) {
    int leftCarrot[2];
    int rightCarrot[2];
    
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].length(); j++) {
            if (lines[i][j] == '>') {
                leftCarrot[0] = i;
                leftCarrot[1] = j;
            }
            if (lines[i][j] == '<') {
                rightCarrot[0] = i;
                rightCarrot[1] = j;
            }
        }
    }
    
    return lines[leftCarrot[0]].substr(leftCarrot[1] + 1, rightCarrot[1] - leftCarrot[1] - 1);
}

int main() {
    string output;
    ifstream infile("../input3.txt");
    vector<string> lines;
    string instructions;
    
    string line;
    getline(infile, instructions);
    getline(infile, line);
    while (getline(infile, line)) {
        lines.push_back(line);
    }
    infile.close();
    
    
    int instr = 0;
    for (int i = 1; i < lines.size() - 1; i++) {
        for (int j = 1; j < lines[i].length() - 1; j++) {
            if (instructions[instr % instructions.length()] == 'L') {
                rotateLeft(lines, i, j);
            }
            else {
                rotateRight(lines, i, j);
            }
            instr++;
        }
    }
    
    for (auto l : lines) {
        cout << l << endl;
    }

    cout << "Total: " << output << endl;

    return 0;
}
