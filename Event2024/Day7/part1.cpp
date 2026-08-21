#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    int total = 0;
    ifstream infile("../input1.txt");
    string line;
    map<string, vector<int>> devices;
    vector<pair<int, string>> scores;
    while (getline(infile, line)) {
        string token;
        string letter;
        vector<int> changes;
        stringstream ss(line);

        getline(ss, letter, ':');
        while (getline(ss, token, ',')) {
            if (token == "-") changes.push_back(-1);
            else if (token == "=") changes.push_back(0);
            else changes.push_back(1);
        }

        devices[letter] = changes;
    }
    infile.close();

    for (const auto& device : devices) {
        int score = 0;
        int change = 10;
        for (int i = 0; i < 10; i++) {
            change += device.second[i % device.second.size()];
            score += change;
        }
        //cout << device.first << ": " << score << endl;
        pair thisScore = {score, device.first};
        scores.push_back(thisScore);
    }

    sort(scores.begin(), scores.end(), greater<pair<int, string>>());
    for (const auto& score : scores) {
        cout << score.second;
    }
    cout << endl;

    cout << "Total: " << total << endl;

    return 0;
}
