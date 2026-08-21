#include <fstream>
#include <iostream>
#include <queue>
#include <ranges>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

static long eni(const long N, const long EXP, const long MOD) {
    long score = 1;
    long loopSize = 0;
    long loopStart = 0;
    long skipVal = 0;
    bool isLooping = false;
    vector<long> scores;
    deque<long> remainList;
    string result;
    
    for (long i = 0; i < EXP; i++) {
        score = score * N % MOD;
        remainList.push_back(score);
        if (i >= 5) remainList.pop_front();
        
        // Check if scores are looping
        auto it = find(scores.begin(), scores.end(), score);
        if (it != scores.end() && i >= 5) {
            loopStart = distance(scores.begin(), it);
            loopSize = i - loopStart;
            isLooping = true;
            break;
        }
        scores.push_back(score);
    }
    
    if (isLooping) {
        long numLoops = (EXP - loopStart) / loopSize;
        skipVal = loopStart + (numLoops * loopSize);
    
        for (long i = skipVal + 1; i < EXP; i++) {
            score = score * N % MOD;
            remainList.push_back(score);
            if (remainList.size() >= 5) remainList.pop_front();
        }
    }
    
    long numRemains = min(5ul, remainList.size());
    for (long i = 0; i < numRemains; i++) {
        result += to_string(remainList.back());
        remainList.pop_back();
    }
    
    return stol(result);
}

int main() {
    long total = 0;
    ifstream infile("../input2.txt");
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
        long sum = eni(v[0], v[3], v[6]) + eni(v[1], v[4], v[6]) + eni(v[2], v[5], v[6]);
        if (sum > total) total = sum;
    }
    
    cout << "Total: " << total << endl;

    return 0;
}
