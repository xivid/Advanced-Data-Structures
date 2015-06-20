//
//  main.cpp
//  DSLib
//
//  Created by 杨志飞 on 15/6/4.
//  Copyright (c) 2015年 杨志飞. All rights reserved.
//

#include <iostream>
#include "DataStructure.h"
using namespace std;
int main(int argc, const char * argv[]) {
    {
        PriorityQueue<int, int> queue(100);
        queue.push(30, 12);
        queue.push(20, 8);
        queue.push(12, 9);
        queue.push(80, -4);
        while (!queue.isempty()) {
            cout << queue.peek() << endl;
            queue.pop();
        }
    }
    {
        SkipList<string> skiplist(100, 1<<30);
        skiplist.insert(10, "asdf");
        skiplist.insert(11, "abcdefg");
        skiplist.insert(12, "abddcdefg");
        skiplist.insert(13, "abewscdefg");
        skiplist.print();
    }
    {
        SparseMatrix sparsematrix(5, 5, 7);
        sparsematrix.insert(1, 2, 888);
        sparsematrix.insert(2, 3, 666);
        SparseMatrix rev(sparsematrix.reverse());
        rev.printmatrix();
    }
    {
        string origin("Python大法好");
        string enc = HuffmanTree::encode(origin.c_str(), (unsigned)origin.length());
        cout << enc << endl;
        cout << HuffmanTree::decode(enc.c_str(), (unsigned)enc.length()) << endl;
    }
    {
        PreThreadBT<int> tree;
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
        tree.PreOrderTraversal();
    }
    {
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
    }
    {
        BinTree<string> bintree(10); //会要求输入10个节点
        Forest<string> *forest = bintree.toForest();
        forest->Print();
        cout << "Convert back to binary tree:" << endl;
        bintree = *forest->toBinTree();
        bintree.Print();
    }
    {
        Forest<string> forest(10); //会要求输入10个节点
        forest.toBinTree()->Print();
        cout << "Convert back to forest:" << endl;
        forest.toBinTree()->toForest()->Print();
    }
    {
        AVLTree<int, int> tree; //key, value
        tree.insert(3, 10);
        tree.insert(9, 20);
        tree.search(3);
    }
    {
        RBTree<int, int> tree; //key, value
        tree.insert(3, 10);
        tree.insert(9, 20);
        cout << tree.get(3) << endl;
    }
    {
        class People {
            string name, province;
            int age;
            bool sex; //true: MALE, false: FEMALE
        public:
            People() {province = "abd";}
            People(People const& p) {*this = p;}
            People(string Name, string Province, int Age, bool Sex): name(Name), province(Province), age(Age), sex(Sex) {}
            string getProvince() { return province; }
            string getName() { return name; }
        };
        Dict<string, People> Family;
        bool MALE = true, FEMALE = false;
        Family["Father"] = People("Yang Dejun", "Shandong", 45, MALE);
        Family["Mother"] = People("Zhang Shuying", "Shandong", 44, FEMALE);
        Family["Son"] = People("Yang Zhifei", "Shandong", 19, MALE);
        Family["Daughter"] = People("Yang Yifei", "Shandong", 3, FEMALE);
        cout << "The daughter " << Family["Daughter"].getName() << " is from " << Family["Daughter"].getProvince() << " province." << endl;
    }
    string s[] = {"abc", "def", "ghi"};
    {
        ListStrHashTable<int> listhash(100);
        listhash.insert(s[0], 0);
        listhash.insert(s[1], 1);
        listhash.insert(s[2], 2);
        cout << listhash.get(s[1]) << endl;
    }
    {
        OpenStrHashTable<int> openhash(100);
        openhash.insert(s[0], 0);
        openhash.insert(s[1], 1);
        openhash.insert(s[2], 2);
        cout << openhash.get(s[1]) << endl;
    }
    return 0;
}
