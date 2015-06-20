//
// Created by 杨志飞 on 15/5/20.
//

#ifndef RBT_REDBLACKTREE_H
#define RBT_REDBLACKTREE_H

#include <iostream>

using namespace std;

template<class Key, class Value>
class RBTree {
private:
    static const bool RED = true, BLACK = false;

    class RBNode {
        friend class RBTree;

        RBNode *lc, *rc;
        Key key;
        Value value;
        bool color;

        RBNode() { }

        RBNode(Key k, Value v, bool c) : key(k), value(v), color(c) { lc = rc = NULL; }
    };

    RBNode *root;
    int BlackHeight;

    //Helper methods
    bool isRed(RBNode *const r) {
        return r == NULL ? false : r->color == RED;
    }

    void colorFlip(RBNode *r) {
        r->color = !r->color;
        r->lc->color = !r->lc->color; //nulptr?
        r->rc->color = !r->rc->color;
    }

    void leftRotate(RBNode *&r) {
        RBNode *h = r->rc;
        h->color = r->color;
        r->color = RED;
        r->rc = h->lc;
        h->lc = r;
        r = h;
    }

    void rightRotate(RBNode *&r) {
        RBNode *h = r->lc;
        h->color = r->color;
        r->color = RED;
        r->lc = h->rc;
        h->rc = r;
        r = h;
    }

    void moveRedLeft(RBNode* &r) {
        colorFlip(r);
        if (isRed(r->rc->lc)) {
            rightRotate(r->rc);
            leftRotate(r);
            colorFlip(r);
        }
    }

    void moveRedRight(RBNode* &r) {
        colorFlip(r);
        if (isRed(r->lc->lc)) {
            rightRotate(r);
            colorFlip(r);
        }
    }

    void fixUp(RBNode* &r) {
        if (isRed(r->rc))
            leftRotate(r);
        if (isRed(r->lc) && isRed(r->lc->lc))
            rightRotate(r);
        if (isRed(r->lc) && isRed(r->rc))
            colorFlip(r);
    }
    RBNode* getMin(RBNode* r) {
        while (r->lc)
            r = r->lc;
        return r;
    }

    void popMin(RBNode* &r) {
        if (r->lc == NULL) {
            r = NULL;
            return;
        }
        if (!isRed(r->lc) && !isRed(r->lc->lc))
            moveRedLeft(r);
        popMin(r->lc);
        fixUp(r);
    }

    //Operation methods
    void insert(RBNode *&r, Key key, Value val) {
        if (r == NULL)
            r = new RBNode(key, val, RED);

        if (isRed(r->lc) && isRed(r->rc))
            colorFlip(r);

        if (key == r->key)
            r->value = val;
        else if (key < r->key)
            insert(r->lc, key, val);
        else
            insert(r->rc, key, val);

        if (isRed(r->rc))
            leftRotate(r);

        if (isRed(r->lc) && isRed(r->lc->lc))
            rightRotate(r);
    }

    void pop(RBNode* &r, Key key) {
        if (key < r->key) {
            //if (!r->lc)
                //throw false;
            if (!isRed(r->lc) && !isRed(r->lc->lc))
                moveRedLeft(r);
            pop(r->lc, key);
        }
        else {
            if (isRed(r->lc))
                rightRotate(r);
            if (key == r->key && r->rc == NULL) {
                delete r;
                r = NULL;
                return;
            }
            //if (key > r->key && r->rc == NULL)
                //throw false;
            if (!isRed(r->rc) && !isRed(r->rc->lc))
                moveRedRight(r);
            if (key == r->key) {
                RBNode* min = getMin(r->rc);
                r->value = min->value;
                r->key = min->key;
                popMin(r->rc);
            } else
                pop(r->rc, key);
        }
        fixUp(r);
    }

    //For demo
    void InOrderPrint(RBNode *p, int level) {
        if (p) {
            InOrderPrint(p->rc, level + 1);
            for (int i = 0; i < level; ++i)
                cout << '\t';
            cout << p->key << '[' << p->value << ']' << (isRed(p) ? "*" : "") << endl;
            InOrderPrint(p->lc, level + 1);
        }
    }

public:
    RBTree() {
        root = NULL;
        BlackHeight = 0;
    }

    Value &get(Key key) {
        RBNode *p = root;
        int level = 0; //for demo
        while (p) {
            if (p->key == key) {
                cout << "Found at level " << level << endl;
                return p->value;
            }
            p = p->key < key ? p->rc : p->lc;
        }
        throw false;
    }

    void insert(Key key, Value val) {
        insert(root, key, val);
        if (root->color == RED) {
            root->color = BLACK; //the 2-3-4 tree grows higher up one level
            ++BlackHeight;
        }
    }

    void pop(Key key) {
        pop(root, key);
        if (root)
            root->color = BLACK;
    }

    bool contains(Key key) {
        try {
            get(key);
        } catch(bool) {
            return false;
        }
        return true;
    }

    void print() {
        cout << "The Red Black Tree is: " << endl;
        if (root)
            InOrderPrint(root, 0);
        else
            cout << "Empty!" << endl;
    }
};

#endif //RBT_REDBLACKTREE_H
