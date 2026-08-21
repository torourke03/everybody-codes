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
    Node* parent; // If parent == nullptr, this is the root
    
    Node(const int rank, const char symbol, const int id, Node* parent) {
        this->rank = rank;
        this->symbol = symbol;
        this->id = id;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = parent;
    }
};

// "Borrowed" from https://www.geeksforgeeks.org/dsa/insertion-in-binary-search-tree/
static Node* insert(Node* root, Node* parent, const int rank, const char symbol, const int id, const int depth = 0) {
    // If tree is empty, create a new node
    if (root == nullptr) {
        return new Node(rank, symbol, id, parent);
    }

    // Insert into the left subtree
    if (rank < root->rank) {
        root->left = insert(root->left, root, rank, symbol, id, depth + 1);
    }

    // Insert into the right subtree
    else {
        root->right = insert(root->right, root, rank, symbol, id, depth + 1);
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

// Level Order search, returns vector of parents and which side to swap
static vector<pair<Node*, char>> findByID(Node* root, const int id) {
    if (root == nullptr) return {};
    
    vector<pair<Node*, char>> swaps;
    queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        int len = q.size();
        
        for (int i = 0; i < len; i++) {
            Node* node = q.front();
            q.pop();
        
            if (node->left != nullptr) {
                if (node->left->id == id) swaps.emplace_back(node, 'L');
                q.push(node->left);
            }
            if (node->right != nullptr) {
                if (node->right->id == id) swaps.emplace_back(node, 'R');
                q.push(node->right);
            }
        }
    }
    
    return swaps;
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
        
        if (token == "ADD") {
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
        }
        else if (token == "SWAP") {
            getline(ss, token);
            in.id = stoi(token);
            
            in.left = make_pair(-1, '\0');
            in.right = make_pair(-1, '\0');
        }
        
        instructions.push_back(in);
    }
    infile.close();
    
    return instructions;
}

int main() {
    string output;
    vector<Instruction> instructions = parseInput("../input3.txt");
    
    Node* root = new Node(-1, '\0', 0, nullptr);
    
    for (auto & instruction : instructions) {
        if (instruction.command == "ADD") {
            root->left = insert(root->left, root, instruction.left.first, instruction.left.second, instruction.id);
            root->right = insert(root->right, root, instruction.right.first, instruction.right.second, instruction.id);
        }
        else if (instruction.command == "SWAP") {
            vector<pair<Node*, char>> swaps = findByID(root, instruction.id);
            if (swaps.size() != 2) {
                cout << "ERROR: swaps.size() = " << swaps.size() << endl;
                return -1;
            }
            pair<Node*, char> firstParent = swaps[0];
            pair<Node*, char> secondParent = swaps[1];
            Node* firstChild;
            Node* secondChild;
            if (firstParent.second == 'L') firstChild = firstParent.first->left;
            else firstChild = firstParent.first->right;
            if (secondParent.second == 'L') secondChild = secondParent.first->left;
            else secondChild = secondParent.first->right;
            
            Node* temp = firstChild;
            if (firstParent.second == 'L') firstParent.first->left = secondChild;
            else firstParent.first->right = secondChild;
            if (secondParent.second == 'L') secondParent.first->left = temp;
            else secondParent.first->right = temp;
        }
    }
    
    auto leftLevels = levelOrder(root->left);
    auto rightLevels = levelOrder(root->right);
    int leftMax = 0, rightMax = 0;
    int leftDepth = 0, rightDepth = 0;
    
    for (int i = 0; i < leftLevels.size(); i++) {
        auto level = leftLevels[i];
        if (level.size() > leftMax) {
            leftDepth = i;
            leftMax = level.size();
        }
    }
    cout << endl;
    for (int i = 0; i < rightLevels.size(); i++) {
        auto level = rightLevels[i];
        if (level.size() > rightMax) {
            rightDepth = i;
            rightMax = level.size();
        }
    }
    
    for (auto val : leftLevels[leftDepth]) {
        output += val;
    }
    for (auto val : rightLevels[rightDepth]) {
        output += val;
    }
    
    cout << "Total: " << output << endl;

    return 0;
}
