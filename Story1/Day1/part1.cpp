#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <vector>
using namespace std;

static long eni(const int N, const int EXP, const int MOD) {
    int score = 1;
    vector<int> remainList;
    string result;
    
    for (int i = 0; i < EXP; i++) {
        score = score * N % MOD;
        remainList.push_back(score);
    }
    
    for (const int & it : std::views::reverse(remainList)) {
        result += to_string(it);
    }
    
    return stol(result);
}

int main() {
    long total = 0;
    ifstream infile("../input1.txt");
    vector<vector<int>> variables;
    
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        vector<int> v;
        while (getline(ss, line, '=')) {
            getline(ss, line, ' ');
            v.push_back(stoi(line));
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
