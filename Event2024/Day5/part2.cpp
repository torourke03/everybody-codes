#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

void updateDance(vector<vector<int>> &columns, int column) {
    int clapNum = columns.at(column).at(0);
    int updateCol = (column + 1) % columns.size();

    if (clapNum <= columns.at(updateCol).size()) {
        columns.at(updateCol).insert(columns.at(updateCol).begin() + clapNum - 1, clapNum);
    }
    else {
        columns.at(updateCol).insert(columns.at(updateCol).end() - (clapNum - columns.at(updateCol).size()) + 1, clapNum);
    }

    columns.at(column).erase(columns.at(column).begin());
}

int getNumber(vector<vector<int>> &columns) {
    string num = to_string(columns.at(0).at(0)) + to_string(columns.at(1).at(0)) + to_string(columns.at(2).at(0)) + to_string(columns.at(3).at(0));
    return atoi(num.c_str());
}

void printColumns(vector<vector<int>> &columns) {
    cout << "------------" << endl;
    for (vector col : columns) {
        for (int row : col) {
            cout << row << " ";
        }
        cout << endl;
    }
    cout << "------------" << endl;
}

int fakeGetNumber(vector<vector<int>> &columns, int i) {
    switch (i) {
        case 0:
            return 6345;
        case 1:
            return 6245;
        case 2:
            return 6285;
        case 3:
            return 5284;
        case 4:
            return 6584;
        case 5:
            return 6254;
        case 6:
            return 6285;
        case 7:
            return 5284;
        case 8:
            return 6584;
        case 9:
            return 6254;
        default:
            return -1;
    }
}

int main() {
    unsigned long total = 0;
    vector<vector<int>> columns;
    ifstream infile("../input2.txt");
    for (int i = 0; i < 4; i++) columns.emplace_back();
    int a, b, c, d;
    while (infile >> a >> b >> c >> d) {
        columns.at(0).push_back(a);
        columns.at(1).push_back(b);
        columns.at(2).push_back(c);
        columns.at(3).push_back(d);
    }
    infile.close();

    vector<int> numbers;
    int val = 0;
    bool isLooping = false;
    map<int, int> counts;
    int i = 0;
    while (!isLooping) {
        updateDance(columns, i % columns.size());
        val = getNumber(columns);
        counts[val]++;

        numbers.push_back(val);

        i++;
        if (counts[val] >= 2024) {
            break;
        }
    }

    cout << i << endl;
    cout << val << endl;

    total = (unsigned long) i * (unsigned long) val;

    cout << "Total: " << total << endl;

    return 0;
}
