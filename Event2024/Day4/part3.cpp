#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    long total = 0;
    vector<long> nails;
    ifstream infile("../input3.txt");
    string line;
    while (getline(infile, line)) {
        long val = stol(line);
        nails.push_back(val);
    }
    infile.close();

    sort(nails.begin(), nails.end());
    long median = nails[nails.size() / 2];

    for (long nail : nails) {
        long diff = 0;
        diff = abs(median - nail);
        total += diff;
    }

    cout << "Total: " << total << endl;

    return 0;
}
