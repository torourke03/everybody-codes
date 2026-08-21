#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

#define NUM_LOOPS 2024
#define BASE_CHANGE 10

static char getCharAtPos(const vector<string> &map, const int x, const int y) {
    if (x < 0 || x >= map.size() || y < 0 || y >= map[x].size()) return ' ';
    return map[x][y];
}

static vector<int> parseTrack(const string& filename) {
    ifstream infile(filename);
    string line;
    vector<string> trackGrid;
    string trackStr;
    vector<int> track;
    int pos[2] = {0, 0}; // +x = down, +y = right in file
    int dir[2] = {0, 1};
    
    while (getline(infile, line)) {
        trackGrid.push_back(line);
    }
    infile.close();
    
    while (true) {
        // Update position and add to trackStr
        pos[0] += dir[0];
        pos[1] += dir[1];
        trackStr += trackGrid[pos[0]][pos[1]];
        
        if (getCharAtPos(trackGrid, pos[0], pos[1]) == 'S') break;
        
        // Determine next direction, if ahead is empty check left and right
        if (getCharAtPos(trackGrid, pos[0] + dir[0], pos[1] + dir[1]) == ' ') {
            if (abs(dir[0]) > 0) {
                dir[0] = 0;
                if (getCharAtPos(trackGrid, pos[0], pos[1] - 1) != ' ') dir[1] = -1;
                else dir[1] = 1;
            }
            else {
                dir[1] = 0;
                if (getCharAtPos(trackGrid, pos[0] - 1, pos[1]) != ' ') dir[0] = -1;
                else dir[0] = 1;
            }
        }
    }
    
    for (char c : trackStr) {
        if (c == '-') track.push_back(-1);
        else if (c == '+') track.push_back(1);
        else track.push_back(0);
    }
    
    return track;
}

static long calcScore(const vector<int> &track, const vector<int> &plan) {
    long score = 0;
    int change = BASE_CHANGE;
    for (int i = 0; i < track.size() * NUM_LOOPS; i++) {
        if (abs(track[i % track.size()]) > 0) {
            change += track[i % track.size()];
        }
        else {
            change += plan[i % plan.size()];
        }
        score += change;
    }
    return score;
}

int main() {
    int total = 0;
    ifstream infile("../input3.txt");
    string trackFileName = "../inTrack3.txt";
    vector<pair<int, string>> scores;
    string trackStr;
    vector<int> track;
    vector<int> rivalPlan;

    // Get rival's plan
    string token;
    getline(infile, token, ':');
    while (getline(infile, token, ',')) {
        if (token == "-") rivalPlan.push_back(-1);
        else if (token == "=") rivalPlan.push_back(0);
        else rivalPlan.push_back(1);
    }
    infile.close();
    for (int x : rivalPlan) {
        cout << x << " ";
    }
    cout << endl;
    
    // Get track
    track = parseTrack(trackFileName);
    for (int x : track) {
        cout << x << " ";
    }
    cout << endl;
    
    // Calculate rival's score
    long rivalScore = calcScore(track, rivalPlan);
    cout << "Rival's score: " << rivalScore << endl;
    
    // Calculate scores for each permutation of the plans
    vector plan = {-1, -1, -1, 0, 0, 0, 1, 1, 1, 1, 1};
    ranges::sort(plan);
    long score;
    int i = 0;
    do {
        score = calcScore(track, plan);
        if (score > rivalScore) total++;
        if (i % 100 == 0) cout << i << endl;
        i++;
    } while (ranges::next_permutation(plan).found);
    
    cout << "Total: " << total << endl;

    return 0;

    // Get track from
    /*getline(trackFile, line);
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

    return 0;*/
}
