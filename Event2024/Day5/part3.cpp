#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void updateDance(vector<vector<int>> &columns, int column) {
    int clapNum = columns.at(column).at(0);
    int updateCol = (column + 1) % columns.size();
    int numPasses = (clapNum - 1) / columns.at(updateCol).size();
    int distInCol = (clapNum - 1) % columns.at(updateCol).size();

    if (numPasses % 2 == 0) {
        columns.at(updateCol).insert(columns.at(updateCol).begin() + distInCol, clapNum);
    }
    else {
        columns.at(updateCol).insert(columns.at(updateCol).end() - distInCol, clapNum);
    }

    columns.at(column).erase(columns.at(column).begin());
}

long getNumber(vector<vector<int>> &columns) {
    string num = to_string(columns.at(0).at(0)) + to_string(columns.at(1).at(0)) + to_string(columns.at(2).at(0)) + to_string(columns.at(3).at(0));
    return stol(num);
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

int main() {
    unsigned long total = 0;
    vector<vector<int>> columns;
    ifstream infile("../input3.txt");
    for (int i = 0; i < 4; i++) columns.emplace_back();
    int a, b, c, d;
    while (infile >> a >> b >> c >> d) {
        columns.at(0).push_back(a);
        columns.at(1).push_back(b);
        columns.at(2).push_back(c);
        columns.at(3).push_back(d);
    }
    infile.close();

    long val = 0;
    int i = 0;
    long max = 0;
    printColumns(columns);
    while (true) {
        updateDance(columns, i % columns.size());
        val = getNumber(columns);
        if (val > max) {
            max = val;
            cout << "New max: " << max << endl;
        }
        i++;
    }

    return 0;
}
