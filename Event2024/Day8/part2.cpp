#include <fstream>
#include <iostream>
using namespace std;

#define MOD_NUM 1111
#define TOTAL_BLOCKS 20240000

int main() {
    long total = 0;
    ifstream infile("../input2.txt");
    string line;

    getline(infile, line);
    long multNum = stol(line);
    infile.close();

    long runningTotal = 1;
    long thickness = 1;
    long layerNum = 1;
    cout << runningTotal << endl;
    while (runningTotal < TOTAL_BLOCKS) {
        thickness = (thickness * multNum) % MOD_NUM;
        layerNum++;
        runningTotal += thickness * (layerNum * 2 - 1);
        cout << runningTotal << endl;
    }
    cout << endl;
    
    long blocksNeeded = runningTotal - TOTAL_BLOCKS;
    long layerWidth = (layerNum * 2 - 1);
    total = blocksNeeded * layerWidth;
    
    cout << blocksNeeded << endl;
    cout << layerWidth << endl;

    cout << "Total: " << total << endl;

    return 0;
}
