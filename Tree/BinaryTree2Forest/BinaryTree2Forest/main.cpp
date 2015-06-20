#include "tree.h"
#include <string>

int main()
{
    int choice, n;
    printf("1. Binary Tree to Forest\n2. Forest to Binary Tree\nPlease choose:");
    cin >> choice;
    if (choice == 1)
    {
        cout << "Input number of nodes in the binary tree:" << endl;
        cin >> n;
        BinTree<string> bintree(n);
        bintree.toForest()->Print();
        cout << "Convert back to binary tree:" << endl;
        bintree.toForest()->toBinTree()->Print();
    }
    else if (choice == 2)
    {
        cout << "Input number of trees in forest:" << endl;
        cin >> n;
        Forest<string> forest(n);
        forest.toBinTree()->Print();
        cout << "Convert back to forest:" << endl;
        forest.toBinTree()->toForest()->Print();
    }
    return 0;
}