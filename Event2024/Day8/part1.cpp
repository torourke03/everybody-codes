#include <fstream>
#include <iostream>
#include <climits>
#include <complex>
using namespace std;

int main() {
    long total = 0;
    ifstream infile("../input1.txt");
    string line;

    getline(infile, line);
    long num = stol(line);
    infile.close();

    long layerNum = static_cast<long>(sqrt(num)) + 1;
    long neededBlocks = (layerNum * layerNum) - num;
    long width = layerNum * 2 - 1;
    
    cout << layerNum << endl;
    cout << neededBlocks << endl;
    cout << width << endl;
    
    total = neededBlocks * width;

    cout << "Total: " << total << endl;

    return 0;
}
