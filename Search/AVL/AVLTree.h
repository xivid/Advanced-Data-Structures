//
// Created by 杨志飞 on 15/5/9.
//

#ifndef AVL_AVLTREE_H
#define AVL_AVLTREE_H
#include <iostream>
template<typename T, typename V> class AVLTree;
template<typename T, typename V> class AVLNode {
    friend class AVLTree<T, V>;
    AVLNode<T, V> *lc, *rc, *fa;
    T key;
    int value, bf; //times of occurrence, balance factor
    AVLNode() {lc = rc = fa = NULL; value = 1; bf = 0;}
    AVLNode(T d, V v): key(d) {lc = rc = fa = NULL; value = v; bf = 0;}
};
template<typename T, typename V> class AVLTree {
    AVLNode<T, V>* root;
    AVLNode<T, V>* get(T data) {
        //show the information of the corresponding node
        AVLNode<T, V> *p = root;
        while (p) {
            if (p->key > data)
                p = p->lc;
            else if (p->key < data)
                p = p->rc;
            else
                return p;
        }
        return NULL;
    }
    void rotate_left(AVLNode<T, V>* &p) {
        //need to change the value of p and balance factor of *p
        AVLNode<T, V>* n = p->rc; //new root
        n->fa = p->fa; //or null
        if (p == root) {
            root = n;
        } else {
            if (p == p->fa->lc)
                p->fa->lc = n;
            else
                p->fa->rc = n;
        }
        p->fa = n;
        p->rc = n->lc;
        if (n->lc)
            n->lc->fa = p;
        n->lc = p;
        if (p->bf == n->bf) {
            p->bf += 1 - n->bf;
            n->bf += 2;
        }
        else {
            p->bf += 1 + (n->bf < 0);
            ++n->bf;
        }
        p = n;
    }
    void rotate_right(AVLNode<T, V>* &p) {
        AVLNode<T, V>* n = p->lc; //new root
        n->fa = p->fa;
        if (p == root)
            root = n;
        else {
            if (p == p->fa->lc)
                p->fa->lc = n;
            else
                p->fa->rc = n;
        }
        p->fa = n;
        p->lc = n->rc;
        if (n->rc)
            n->rc->fa = p;
        n->rc = p;
        if (p->bf == n->bf) {
            p->bf -= 1 + n->bf;
            n->bf -= 2;
        }
        else {
            p->bf -= 1 + (n->bf > 0);
            --n->bf;
        }
        p = n;
    }
    void InOrderPrint(AVLNode<T, V>* p, int level) {
        if (p) {
            InOrderPrint(p->rc, level + 1);
            for (int i = 0; i < level; ++i)
                std::cout << '\t';
            std::cout << p->key << ',' << p->value << '[' << p->bf << ']' << std::endl;
            InOrderPrint(p->lc, level + 1);
        }
    }
public:
    AVLTree() {root = NULL;}
    bool hasKey(T key) {
        return (get(key) != NULL);
    }
    AVLNode<T, V>* search(T key) {
        //show the information of the corresponding node
        AVLNode<T, V> *p = root;
        int level = 0;
        while (p) {
            if (p->key > key)
                p = p->lc, ++level;
            else if (p->key < key)
                p = p->rc, ++level;
            else {
                std::cout << "key: " << p->key << ", value: " << p->value << ", level: " << level << std::endl;
                return p;
            }
        }
        return NULL;
    }
    void update(T key, V value) {
        AVLNode<T, V> *p = get(key);
        if (p) {
            p->value = value;
        }
        else
            std::cout << "Update failed: no such node." << std::endl;
    }
    void insert(T key, V value) {
        if (root == NULL) {
            root = new AVLNode<T, V>(key, value);
        }
        else {
            AVLNode<T, V> *p = root, *n;
            while (p) {
                if (key < p->key) {
                    if (p->lc)
                        p = p->lc;
                    else {
                        n = p->lc = new AVLNode<T, V>(key, value);
                        p->lc->fa = p;
                        break;
                    }
                }
                else if (key > p->key) {
                    if (p->rc)
                        p = p->rc;
                    else {
                        n = p->rc = new AVLNode<T, V>(key, value);
                        p->rc->fa = p;
                        break;
                    }
                }
                else {
                    p->value = value;
                    return;
                }
            }
            ///re-balance if:
            ///1) n is the subtree of p, and the height of n increases by 1
            ///2) n is a new child of p (can also seen as circumstance 1)
            ///after rotation, n becomes the root and the height of the whole part remains unchanged
            do {
                if (n == p->lc) {
                    //Left Rotation
                    if (p->bf == 1) {
                        p->bf = 2;
                        if (n->bf == -1) //为防止过右,若n已右倾,则先将n左旋
                            rotate_left(n);
                        rotate_right(p);
                        break;
                    }
                    else if (p->bf == -1) {
                        p->bf = 0;
                        break;
                    }
                    p->bf = 1;
                }
                else { //n == p->rc
                    if (p->bf == -1) {
                        p->bf = -2;
                        if (n->bf == 1)
                            rotate_right(n);
                        rotate_left(p);
                        break;
                    }
                    else if (p->bf == 1) {
                        p->bf = 0;
                        break;
                    }
                    p->bf = -1;
                }
                n = p;
                p = p->fa;
            } while(p);
        }
    }
    void pop(T key) { //delete by 1 time
        AVLNode<T, V> *x = get(key), *n, *p, *z;
        if (x) {
            if (x->value > 1)
                --x->value;
            else {
                if (x == root && !(x->lc || x->rc)) {//x is root and x is a leaf
                    root = NULL;
                    delete x;
                } else { //z := the node to be deleted
                    if (!(x->lc || x->rc)) { //x is a leaf
                        z = n = x;
                        p = x->fa;
                    }
                    else {
                        if ((x->lc == NULL) ^ (x->rc == NULL)) //x has only one subtree(which must be a leaf)
                            z = x->lc ? x->lc : x->rc; //z := subtree(x)
                        else {
                            z = x->lc;
                            while (z->rc)
                                z = z->rc; //in-order predecessor
                        }
                        x->key = z->key;
                        x->value = z->value;
                        n = z;
                        p = z->fa;
                    }
                    //n is the subtree of p whose height decreases by 1
                    int B;
                    AVLNode<T, V> *S;
                    do { //re-balance
                        if (n == p->lc) {
                            if (p->bf == -1) {
                                p->bf = -2;
                                S = p->rc; //sibling, in case it changes in rotation
                                B = S->bf; //in case it changes
                                if (B == 1)
                                    rotate_right(S);
                                rotate_left(p);
                                if (B == 0)
                                    break;
                            }
                            else if (p->bf == 0) {
                                p->bf = -1;
                                break;
                            }
                            p->bf = 0;
                        } else { //n == p->rc
                            if (p->bf == 1) {
                                p->bf = 2;
                                S = p->lc;
                                B = S->bf;
                                if (B == -1)
                                    rotate_left(S);
                                rotate_right(p);
                                if (B == 0)
                                    break;
                            }
                            else if (p->bf == 0) {
                                p->bf = 1;
                                break;
                            }
                            p->bf = 0;
                        }
                        n = p;
                        p = p->fa;
                    } while (p);
                    //delete z
                    p = z->fa;
                    n = z->lc ? z->lc : (z->rc ? z->rc : NULL);
                    if (n)
                        n->fa = p;
                    if (z == p->lc)
                        p->lc = n; //or null
                    else
                        p->rc = n;
                    delete z;
                }
            }
        }
        else
            std::cout << "Deletion failed: no such node." << std::endl;
    }
    void print() {
        std::cout << "The AVL Tree is: " << std::endl;
        if (root)
            InOrderPrint(root, 0);
        else
            std::cout << "Empty!" << std::endl;
    }

};
#endif //AVL_AVLTREE_H
