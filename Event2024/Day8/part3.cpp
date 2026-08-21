#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

//#define MOD_NUM 5
//#define TOTAL_BLOCKS 160

#define MOD_NUM 10
#define TOTAL_BLOCKS 202400000

int main() {
    long total = 0;
    ifstream infile("../input3.txt");
    string line;

    getline(infile, line);
    long multNum = stol(line);
    infile.close();

    long runningTotal = 1;
    long thickness = 1;
    long layerNum = 1;
    vector<long> layerThickness = {1};
    cout << runningTotal << endl;
    while (runningTotal < TOTAL_BLOCKS) {
        thickness = (thickness * multNum) % MOD_NUM + MOD_NUM;
        layerNum++;
        runningTotal += thickness * (layerNum * 2 - 1);
        layerThickness.push_back(thickness);
        //cout << runningTotal << endl;
    }
    cout << endl;
    
    for (long x : layerThickness) {
        cout << x << " ";
    }
    cout << "\n" << endl;
    
    
    long layerWidth = (layerNum * 2 - 1);
    long currHeight = layerThickness.at(layerThickness.size() - 1);
    long blocksRemove = 0;
    cout << "Remove:";
    for (int i = layerThickness.size() - 2; i >= 0; i--) {
        currHeight += layerThickness.at(i);
        blocksRemove += ((multNum * layerWidth * currHeight) % MOD_NUM);
        if (i > 0) blocksRemove += ((multNum * layerWidth * currHeight) % MOD_NUM);
        //cout << " " << ((multNum * layerWidth * currHeight) % MOD_NUM);
    }
    cout << "\n" << blocksRemove << "\n" << endl;
    
    long blocksUsed = runningTotal - blocksRemove;
    long blocksToBuy = blocksUsed - TOTAL_BLOCKS;
    
    total = blocksToBuy;
    
    cout << "Blocks Used: " << blocksUsed << endl;
    cout << "Blocks to buy: " << blocksToBuy << endl;
    cout << layerWidth << endl;
    cout << layerNum << endl;

    cout << "Total: " << total << endl;

    return 0;
}
