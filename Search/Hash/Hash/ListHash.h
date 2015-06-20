//
// Created by 杨志飞 on 15/5/21.
// 拉链法
//

#ifndef HASH_LISTHASH_H
#define HASH_LISTHASH_H
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
using namespace std;
template <class T> class ListStrHashTable{
    int B, factor;
    
    struct node{
        int no; //order in the list
        string* s;
        T value;
        node* next;
        node() : no(0), s(NULL), next(NULL) {}
        node(int NO, string* str, T val) : no(NO), s(str), next(NULL), value(val) {}
    };
    typedef node* hashlist;
    hashlist* ht2 = new hashlist[B];
    
    bool isPrime(int x) {
        if (x == 2)
            return true;
        if (x < 2)
            return false;
        for (int i = 2; i < x; ++i)
            if (x % i == 0)
                return false;
        return true;
    }
    
    unsigned int Hash(const char* s){ //BKDRhash
        unsigned int h = 0;
        while(*s)
            h = h * 31 + *s++;
        return (h & 0x7fffffff) % factor; //factor is the largest prime number smaller than 1280
    }
public:
    int crashcount;
    
    ListStrHashTable() { }
    
    ListStrHashTable(int b): B(b) {
        crashcount = 0;
        factor = b;
        while(!isPrime(factor))
            factor--;
    }
    
    void clearcrash() { crashcount = 0; }
    
    void insert(string &str, T val){
        int pos = Hash(str.c_str());
        node* p = ht2[pos];
        if(p == NULL) ht2[pos] = new node(0, &str, val);
        else { //insert into the list
            ++crashcount;
            while(p->next != NULL) {
                p = p->next;
                ++crashcount;
            }
            p->next = new node(p->no + 1, &str, val);
        }
        
    }
    
    T get(string& str) {
        int pos = Hash(str.c_str());
        node* p = ht2[pos];
        while(p != NULL && p->s != &str) {
            p = p->next;
            ++crashcount;
        }
        if(p == NULL)
            throw false; //not found exception
        return p->value;
    }
    
    bool hasKey(string& str) {
        int pos = Hash(str.c_str());
        node* p = ht2[pos];
        while(p != NULL && p->s != &str) p = p->next;
        if(p == NULL) return false; //not exist
        return true;
    }
};

#endif //HASH_LISTHASH_H
