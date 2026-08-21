#include <climits>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int total = 0;
    vector<int> nails;
    ifstream infile("../input2.txt");
    string line;
    int smallest = INT_MAX;
    while (getline(infile, line)) {
        int val = stoi(line);
        if (val < smallest) {
            smallest = val;
        }
        nails.push_back(val);
    }
    infile.close();

    for (int nail : nails) {
        int diff = nail - smallest;
        total += diff;
    }

    cout << "Total: " << total << endl;

    return 0;
}
