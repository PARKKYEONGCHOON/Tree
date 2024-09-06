#include <iostream>
#include <vector>
using namespace std;

class BTreeNode {
public:
    vector<int> keys;
    vector<BTreeNode*> children;
    bool leaf;

    BTreeNode(bool leaf);
};

class BTree {
private:
    BTreeNode* root;
    int t;

public:
    BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    void insert(int key);
    void insertNonFull(BTreeNode* node, int key);
    void splitChild(BTreeNode* node, int i);
    void inorderTraversal(BTreeNode* node);

    BTreeNode* getRoot() { return root; }
};

BTreeNode::BTreeNode(bool leaf) {
    this->leaf = leaf;
}

void BTree::insert(int key) {
    if (root == nullptr) {
        root = new BTreeNode(true);
        root->keys.push_back(key);
    }
    else {
        if (root->keys.size() == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(false);
            s->children.push_back(root);
            splitChild(s, 0);
            insertNonFull(s, key);
            root = s;
        }
        else {
            insertNonFull(root, key);
        }
    }
}

void BTree::insertNonFull(BTreeNode* node, int key) {
    int i = node->keys.size() - 1;

    if (node->leaf) {
        node->keys.push_back(0);
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
    }
    else {
        while (i >= 0 && key < node->keys[i])
            i--;
        i++;
        if (node->children[i]->keys.size() == 2 * t - 1) {
            splitChild(node, i);
            if (key > node->keys[i])
                i++;
        }
        insertNonFull(node->children[i], key);
    }
}

void BTree::splitChild(BTreeNode* node, int i) {
    BTreeNode* y = node->children[i];
    BTreeNode* z = new BTreeNode(y->leaf);
    node->children.insert(node->children.begin() + i + 1, z);
    node->keys.insert(node->keys.begin() + i, y->keys[t - 1]);

    z->keys.assign(y->keys.begin() + t, y->keys.end());
    y->keys.resize(t - 1);

    if (!y->leaf) {
        z->children.assign(y->children.begin() + t, y->children.end());
        y->children.resize(t);
    }
}

void BTree::inorderTraversal(BTreeNode* node) {
    int i;
    for (i = 0; i < node->keys.size(); i++) {
        if (!node->leaf)
            inorderTraversal(node->children[i]);
        cout << node->keys[i] << " ";
    }
    if (!node->leaf)
        inorderTraversal(node->children[i]);
}

int main() {
    BTree bTree(3);
    int values[] = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int value : values)
        bTree.insert(value);

    bTree.inorderTraversal(bTree.getRoot());  // Output: 5 6 7 10 12 17 20 30
    return 0;
}
