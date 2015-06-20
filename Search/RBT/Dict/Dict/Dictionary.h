//
// Created by 杨志飞 on 15/5/20.
//

#ifndef RBT_DICTIONARY_H
#define RBT_DICTIONARY_H
#include "RedBlackTree.h"

template<class Key, class Value> class Dict {
    RBTree<Key, Value> tree;
public:
    Value& operator [](Key key) {
        try {
            return tree.get(key);
        } catch(bool) {
            tree.insert(key, *(new Value));
            return tree.get(key);
        }
    }
    void pop(Key key) { tree.pop(key); }
};
#endif //RBT_DICTIONARY_H
