#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

#define NUM_LOOPS 10
#define BASE_CHANGE 10

int main() {
    int total = 0;
    ifstream infile("../input2.txt");
    ifstream trackFile("../inTrack2.txt");
    string line;
    map<string, vector<int>> devices;
    vector<pair<int, string>> scores;
    string trackStr;
    vector<int> track;
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

    // Get track from
    getline(trackFile, line);
    trackStr = line.substr(1, line.length() - 1);
    char trackChar = line[0];
    string endTrackStr;
    while (getline(trackFile, line)) {
        if (line.at(1) == ' ') {
            trackStr += line.at(line.size() - 1);
            endTrackStr += line.at(0);
        }
        else {
            ranges::reverse(line);
            trackStr += line;
        }
    }
    ranges::reverse(endTrackStr);
    trackStr += endTrackStr + trackChar;
    for (char c : trackStr) {
        if (c == '-') track.push_back(-1);
        else if (c == '=' || c == 'S') track.push_back(0);
        else track.push_back(1);
    }

    cout << "T:";
    for (int x : track) {
        cout << "  " << x;
    }
    cout << endl;

    for (const auto& device : devices) {
        int score = 0;
        int change = BASE_CHANGE;
        cout << device.first << ": ";
        for (int i = 0; i < track.size() * NUM_LOOPS; i++) {
            if (abs(track[i % track.size()]) > 0) {
                change += track[i % track.size()];
            }
            else {
                change += device.second[i % device.second.size()];
            }
            score += change;
            //cout << " " << change;
        }
        cout << score << endl;
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
