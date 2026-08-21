#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <ranges>
#include <sstream>
#include <vector>
using namespace std;

struct Instruction {
    string command;
    int id = 0;
    pair<int, char> left;
    pair<int, char> right;
};

class Node {
public:
    int rank;
    char symbol;
    int id;
    Node* left;
    Node* right;
    
    Node(const int rank, const char symbol, const int id) {
        this->rank = rank;
        this->symbol = symbol;
        this->id = id;
        this->left = nullptr;
        this->right = nullptr;
    }
};

// "Borrowed" from https://www.geeksforgeeks.org/dsa/insertion-in-binary-search-tree/
static Node* insert(Node* root, vector<int>& depths, const int rank, const char symbol, const int depth = 0) {
    // If tree is empty, create a new node
    if (root == nullptr) {
        depths[depth]++;
        return new Node(rank, symbol, depth);
    }

    // Insert into the left subtree
    if (rank < root->rank) {
        root->left = insert(root->left, depths, rank, symbol, depth + 1);
    }

    // Insert into the right subtree
    else {
        root->right = insert(root->right, depths, rank, symbol, depth + 1);
    }

    return root;
}

// Based on https://www.geeksforgeeks.org/dsa/level-order-tree-traversal/#approach-1-using-queue-iterarive-on-time-and-on-space
static vector<vector<char>> levelOrder(Node* root) {
    if (root == nullptr) return {};
    
    vector<vector<char>> res;
    int currLevel = 0;
    queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        int len = q.size();
        res.emplace_back();
        
        for (int i = 0; i < len; i++) {
            Node* node = q.front();
            q.pop();
            
            //if (currLevel == level) str += node->symbol;
            res[currLevel].push_back(node->symbol);
            
            if (node->left != nullptr) q.push(node->left);
            if (node->right != nullptr) q.push(node->right);
        }
        currLevel++;
    }
    
    return res;
}

static vector<Instruction> parseInput(const string& filename) {
    ifstream infile(filename);
    vector<Instruction> instructions;
    
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string token;
        int temp;
        Instruction in;
        
        getline(ss, token, ' ');
        in.command = token;
        
        getline(ss, token, '=');
        getline(ss, token, ' ');
        in.id = stoi(token);
        
        getline(ss, token, '[');
        getline(ss, token, ',');
        temp = stoi(token);
        getline(ss, token, ']');
        in.left = make_pair(temp, token[0]);
        
        getline(ss, token, '[');
        getline(ss, token, ',');
        temp = stoi(token);
        getline(ss, token, ']');
        in.right = make_pair(temp, token[0]);
        
        instructions.push_back(in);
    }
    infile.close();
    
    return instructions;
}

int main() {
    string output;
    vector<Instruction> instructions = parseInput("../input1.txt");
    
    Node* leftRoot = new Node(instructions[0].left.first, instructions[0].left.second, 0);
    Node* rightRoot = new Node(instructions[0].right.first, instructions[0].right.second, 0);
    vector<int> leftDepths(instructions.size());
    vector<int> rightDepths(instructions.size());
    int leftMax = 0, rightMax = 0;
    int leftDepth = 0, rightDepth = 0;
    
    for (int i = 1; i < instructions.size(); i++) {
        leftRoot = insert(leftRoot, leftDepths, instructions[i].left.first, instructions[i].left.second);
        rightRoot = insert(rightRoot, rightDepths, instructions[i].right.first, instructions[i].right.second);
    }
    
    for (int i = 0; i < leftDepths.size(); i++) {
        if (leftDepths[i] > leftMax) {
            leftDepth = i;
            leftMax = leftDepths[i];
        }
        if (rightDepths[i] > rightMax) {
            rightDepth = i;
            rightMax = rightDepths[i];
        }
    }
    
    auto leftLevels = levelOrder(leftRoot);
    auto rightLevels = levelOrder(rightRoot);
    
    for (auto val : leftLevels[leftDepth]) {
        output += val;
    }
    for (auto val : rightLevels[rightDepth]) {
        output += val;
    }
    
    cout << "Total: " << output << endl;

    return 0;
}
