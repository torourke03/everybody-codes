#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

void findAllFruits(map<int, vector<string>> &fruitDists, map<string, vector<string>> tree, set<string> explored, string node, int depth, string path) {
    explored.insert(node);

    if (node == "@") {
        fruitDists[depth].push_back(path + node);
        return;
    }

    for (const auto& branch : tree[node]) {
        if (!explored.contains(branch)) {
            findAllFruits(fruitDists, tree, explored, branch, depth + 1, path + node.at(0));
        }
    }

    //return fruitDist;
}

int main() {
    int total = 0;
    ifstream infile("../input2.txt");
    string line;
    map<string, vector<string>> tree;
    while (getline(infile, line)) {
        string token;
        string root;
        vector<string> branches;
        stringstream ss(line);

        getline(ss, root, ':');
        while (getline(ss, token, ',')) {
            branches.push_back(token);
        }

        tree[root] = branches;
    }
    infile.close();

    for (const auto& node : tree) {
        cout << node.first << ": ";
        for (const auto& branch : node.second) {
            cout << branch << " ";
        }
        cout << endl;
    }

    set<string> explored;
    map<int, vector<string>> fruitDists;
    findAllFruits(fruitDists, tree, explored, "RR", 0, "");

    for (const auto& node : fruitDists) {
        cout << node.first << ": ";
        for (const auto& branch : node.second) {
            cout << branch << " ";
        }
        cout << endl;
    }

    cout << "Total: " << total << endl;

    return 0;
}
