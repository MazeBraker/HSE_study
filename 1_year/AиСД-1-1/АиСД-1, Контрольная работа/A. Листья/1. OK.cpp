#include <iostream>
#include <string>

struct node {
    int val;
    node *left, *right;

    node(int i) : val(i), left(NULL), right(NULL) {};
};

node *addnode(int val) {
    return new node(val);
}

node *addtree(node *root, int value) {
    if (!root) {
        root = addnode(value);
        return root;
    }
    if (value >= root->val) {}
    else if (!root->left) {
        root->left = addnode(value);
    } else {
        addtree(root->left, value);
    }
    if (value > root->val) {
        !root->right ? (root->right = addnode(value)) :
        addtree(root->right, value);
    }
    return root;
}

void printLeaves(node *root) {
    if (root) {
        printLeaves(root->left);
        if (!root->left && !root->right)
            std::cout << root->val << " ";
        printLeaves(root->right);
    }
}

int main() {
    int n;
    std::cin >> n;
    int num;
    std::cin >> num;
    node *tree = NULL;
    if (n != 0) {
        tree = new node(num);
    }
    for (int i = 1; i < n; i++) {
        std::cin >> num;
        addtree(tree, num);
    }
    printLeaves(tree);
    return 0;
}