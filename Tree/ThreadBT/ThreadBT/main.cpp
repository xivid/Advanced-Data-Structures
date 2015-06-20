#include <iostream>
#include "ThreadBT.h"

using namespace std;

int main() {
    PostThreadBT<int> tree;
    BTNode<int> *root = new BTNode<int>(1);
    tree.initialize(root);
    tree.insertLeft(root, new BTNode<int>(2));
    tree.insertRight(root, new BTNode<int>(3));
    tree.insertLeft(root->lc, new BTNode<int>(4));
    tree.insertRight(root->lc->lc, new BTNode<int>(9));
    tree.insertLeft(root->lc->lc, new BTNode<int>(8));
    tree.insertRight(root->lc, new BTNode<int>(5));
    tree.insertRight(root->rc, new BTNode<int>(7));
    tree.insertLeft(root->rc, new BTNode<int>(6));
    tree.PostOrderTraversal();
    return 0;
}
