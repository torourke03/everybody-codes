#include <fstream>
#include <iostream>
#include <queue>
#include <ranges>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

static long eni(const long N, const long EXP, const long MOD) {
    long total = 0;
    long score = 1;
    long loopSize = 0;
    long loopStart = 0;
    long loopValue = 0;
    long skipVal = 0;
    bool isLooping = false;
    vector<long> scores;
    
    for (long i = 0; i < EXP; i++) {
        score = score * N % MOD;
        //total += score;
        
        // Check if scores are looping
        auto it = find(scores.begin(), scores.end(), score);
        if (it != scores.end()) {
            loopStart = distance(scores.begin(), it);
            loopSize = i - loopStart;
            for (long j = loopStart; j < i; j++) {
                loopValue += scores[j];
            }
            for (long j = 0; j < loopStart; j++) {
                total += scores[j];
            }
            isLooping = true;
            score = scores[i - 1];
            break;
        }
        scores.push_back(score);
    }
    
    if (isLooping) {
        long numLoops = (EXP - loopStart) / loopSize;
        skipVal = loopStart + (numLoops * loopSize);
        total += loopValue * numLoops;
        //score = scores[skipVal - 1];
    
        for (long i = skipVal; i < EXP; i++) {
            score = score * N % MOD;
            total += score;
        }
    }
    
    return total;
}

int main() {
    long total = 0;
    ifstream infile("../input3.txt");
    vector<vector<long>> variables;
    
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        vector<long> v;
        while (getline(ss, line, '=')) {
            getline(ss, line, ' ');
            v.push_back(stol(line));
        }
        variables.push_back(v);
    }
    infile.close();
    
    for (auto v : variables) {
        long first = eni(v[0], v[3], v[6]);
        long second = eni(v[1], v[4], v[6]);
        long third = eni(v[2], v[5], v[6]);
        long sum = first + second + third;
        if (sum > total) total = sum;
    }
    
    cout << "Total: " << total << endl;

    return 0;
}
