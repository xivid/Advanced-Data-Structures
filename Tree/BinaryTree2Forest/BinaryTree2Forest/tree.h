//
//  tree.h
//  BinaryTree2Forest
//
//  Created by 杨志飞 on 15/4/11.
//  Copyright (c) 2015年 杨志飞. All rights reserved.
//

#ifndef BinaryTree2Forest_tree_h
#define BinaryTree2Forest_tree_h

#include <iostream>
#include <vector>

using namespace std;

template<class T> class TreeNode;
template<class T> class BinTree;
template<class T> class Tree;
template<class T> class Forest;

template<class T>
class BinNode
{
    friend class BinTree<T>;
    friend class Tree<T>;
    friend class Forest<T>;
    BinNode<T> *lc, *rc;
    T data;
    
public:
    BinNode();
    BinNode(T d);
    ~BinNode();
};

template<class T> BinNode<T>::BinNode() {lc = rc = NULL; data = T();}
template<class T> BinNode<T>::BinNode(T d) {lc = rc = NULL; data = d;}
template<class T> BinNode<T>::~BinNode() {lc = rc = NULL; data = T();}

template<class T>
class BinTree
{
    friend class Tree<T>;
    friend class Forest<T>;
    BinNode<T> *root;
    int nodeNum;
    void print(BinNode<T>* p, int level);
public:
    BinTree();
    BinTree(int n);
    ~BinTree();
    Forest<T>* toForest();
    void addtoTree(BinNode<T>* r, TreeNode<T>* node, Tree<T>* tree);
    void Print();
};

template<class T> BinTree<T>::BinTree() {root = NULL; nodeNum = 0;}
template<class T> BinTree<T>::BinTree(int n) : nodeNum(n)
{
    T d;
    vector<BinNode<T>*> nodes;
    cout << "Node #1 will be regarded as root." << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << "Input the data of node #" << i << ":" << endl;
        cin >> d;
        nodes.push_back(new BinNode<T>(d));
    }
    int lc, rc;
    for (int i = 1; i <= n; ++i)
    {
        cout << "Input the numbers of left child and right child of node #" << i << "(0 for NULL):" << endl;
        cin >> lc >> rc;
        if (lc)
            nodes[i-1]->lc = nodes[lc-1];
        if (rc)
            nodes[i-1]->rc = nodes[rc-1];
    }
    root = nodes[0];
}
template<class T> BinTree<T>::~BinTree() {root = NULL; nodeNum = 0;}
template<class T> void BinTree<T>::addtoTree(BinNode<T>* r, TreeNode<T>* node, Tree<T>* tree)
{
    if (r->lc)
    {
        TreeNode<T>* tnode = new TreeNode<T>(r->lc->data);
        node->children.push_back(tree->nodeNum++);
        tree->nodes.push_back(tnode);
        addtoTree(r->lc, tnode, tree);
        BinNode<T>* p = r->lc->rc;
        while (p)
        {
            TreeNode<T>* cnode = new TreeNode<T>(p->data);
            node->children.push_back(tree->nodeNum++);
            tree->nodes.push_back(cnode);
            addtoTree(p, cnode, tree);
            p = p->rc;
        }
    }
}
template<class T> Forest<T>* BinTree<T>::toForest()
{
    Forest<T> *forest = new Forest<T>;
    forest->treeNum = 0;
    BinNode<T> *p = root;
    while (p != NULL)
    {
        Tree<T> *tree = new Tree<T>;
        TreeNode<T> *node = new TreeNode<T>(p->data);
        tree->nodes.push_back(node);
        ++tree->nodeNum;
        addtoTree(p, node, tree);
        tree->root = tree->nodes[0];
        
        forest->trees.push_back(tree);
        ++forest->treeNum;
        p = p->rc;
    }
    return forest;
}
template<class T> void BinTree<T>::print(BinNode<T>* p, int level)
{
    if (p)
    {
        print(p->rc, level+1);
        for (int i = 0; i < level; i++)
            putchar('\t');
        cout << p->data << endl;
        print(p->lc, level+1);
    }
}
template<class T> void BinTree<T>::Print()
{
    print(root, 0);
}

template<class T>
class TreeNode
{
    friend class BinTree<T>;
    friend class Tree<T>;
    vector<int> children;
    T data;
    
public:
    TreeNode();
    TreeNode(T d);
    ~TreeNode();
    void addChild(TreeNode<T>* child);
    TreeNode<T>* getChild(int pos);
};

template<class T> TreeNode<T>::TreeNode() {data = T();}
template<class T> TreeNode<T>::TreeNode(T d) {data = d;}
template<class T> TreeNode<T>::~TreeNode() {children.clear(); data = T(); }

template<class T>
class Tree
{
    friend class BinTree<T>;
    vector<TreeNode<T>*> nodes;
    TreeNode<T> *root;
    int nodeNum;
public:
    Tree();
    Tree(int n);
    ~Tree();
    void Delete(TreeNode<T> *p);
    BinTree<T>* toBinTree();
    void print(TreeNode<T>* p, int level);
    void Print();
};

template<class T> Tree<T>::Tree() {root = NULL; nodeNum = 0;}
template<class T> Tree<T>::Tree(int n) : nodeNum(n)
{
    T data;
    int no;
    cout << "Node #1 is regarded as root." << endl;
    for (int i = 1; i <= n; ++i)
    {
        cout << "Input the data of node #" << i << ":" << endl;
        cin >> data;
        nodes.push_back(new TreeNode<T>(data));
    }
    for (int i = 1; i <= n; ++i)
    {
        cout << "Input the numbers of the children of node #" << i << "(end with 0):" << endl;
        cin >> no;
        while (no)
        {
            if (no > 0 && no <= n)
                nodes[i-1]->children.push_back(no-1);
            else
                cout << "Invalid number! Try again." << endl;
            cin >> no;
        }
    }
    root = nodes[0];
}
template<class T> Tree<T>::~Tree()
{
    Delete(root);
    nodes.clear();
    nodeNum = 0;
}
template<class T> void Tree<T>::Delete(TreeNode<T>* p)
{
    for (int i = 0; i < p->children.size(); ++i)
        Delete(nodes[p->children[i]]);
    delete p;
}
template<class T> void Tree<T>::print(TreeNode<T>* p, int level)
{
    int size = (int)p->children.size();
    for (int i = size - 1; i >= size/2; --i)
        print(nodes[p->children[i]], level+1);
    for (int j = 0; j < level; j++)
        putchar('\t');
    cout << p->data << endl;
    for (int i = size/2 - 1; i >= 0; --i)
        print(nodes[p->children[i]], level+1);
}
template<class T> void Tree<T>::Print()
{
    print(root, 0);
}
template<class T> BinTree<T>* Tree<T>::toBinTree()
{
    BinTree<T>* bt = new BinTree<T>;
    vector<BinNode<T>*> btnodes;
    bt->nodeNum = nodeNum;
    for (int i = 0; i < nodeNum; ++i)
        btnodes.push_back(new BinNode<T>(nodes[i]->data));
    bt->root = btnodes[0];
    for (int i = 0; i < nodeNum; ++i)
    {
        int childNum = (int)nodes[i]->children.size();
        if (childNum)
        {
            btnodes[i]->lc = btnodes[nodes[i]->children[0]];
            BinNode<T> *p = btnodes[i]->lc;
            for (int j = 1; j < childNum; ++j)
            {
                p->rc = btnodes[nodes[i]->children[j]];
                p = p->rc;
            }
        }
    }
    return bt;
}

template<class T>
class Forest
{
    friend class BinTree<T>;
    vector<Tree<T>*> trees;
    int treeNum;
public:
    Forest();
    Forest(int n);
    ~Forest();
    BinTree<T>* toBinTree();
    void Print();
};
template<class T> Forest<T>::Forest() {treeNum = 0;}
template<class T> Forest<T>::Forest(int n) : treeNum(n)
{
    int num;
    for (int i = 1; i <= n; ++i)
    {
        cout << "Input the number of nodes in tree #" << i << ":" << endl;
        cin >> num;
        while (num < 1)
        {
            cout << "Illegal number! Try again." << endl;
            cin >> num;
        }
        trees.push_back(new Tree<T>(num)); //index starting from 0
    }
}
template<class T> Forest<T>::~Forest() {}
template<class T> BinTree<T>* Forest<T>::toBinTree()
{
    BinTree<T>* tree = trees[0]->toBinTree();
    BinNode<T>* p = tree->root;
    for (int i = 1; i < treeNum; ++i)
    {
        p->rc = trees[i]->toBinTree()->root;
        p = p->rc;
    }
    return tree;
}
template<class T> void Forest<T>::Print()
{
    for (int i = 0; i < treeNum; ++i)
    {
        cout << "Tree #" << i+1 << ":" << endl;
        trees[i]->Print();
        cout << endl;
    }
}


#endif
