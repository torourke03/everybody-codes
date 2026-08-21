#include <fstream>
#include <iostream>
#include <vector>
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
    return (columns.at(0).at(0) * 1000) + (columns.at(1).at(0) * 100) + (columns.at(2).at(0) * 10) + (columns.at(3).at(0));
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
    int total = 0;
    vector<vector<int>> columns;
    ifstream infile("../input1.txt");
    //string line;
    for (int i = 0; i < 4; i++) columns.emplace_back();
    int a, b, c, d;
    while (infile >> a >> b >> c >> d) {
        columns.at(0).push_back(a);
        columns.at(1).push_back(b);
        columns.at(2).push_back(c);
        columns.at(3).push_back(d);
    }
    infile.close();

    printColumns(columns);
    int val = 0;
    for (int i = 0; i < 10; i++) {
        updateDance(columns, i % columns.size());
        printColumns(columns);
        val = getNumber(columns);
        cout << i + 1 << ": " << val << endl;
    }
    total = val;

    cout << "Total: " << total << endl;

    return 0;
}
