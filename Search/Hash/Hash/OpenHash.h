//
// Created by 杨志飞 on 15/5/21.
// 开放域寻址法
//

#ifndef HASH_OPENHASH_H
#define HASH_OPENHASH_H
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
using namespace std;
template <class T> class OpenStrHashTable{
    int B, factor;
    string** ht = new string*[B];
    T* value = new T[B];
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
    
    OpenStrHashTable() { }
    
    OpenStrHashTable(int b): B(b) {
        crashcount = 0;
        factor = b;
        while(!isPrime(factor))
            factor--;
    }
    
    void clearcrash() { crashcount = 0; }
    
    void insert(string& str, T val){
        int pos = Hash(str.c_str());
        while(ht[pos] != NULL)
        {
            pos = (pos + 1) % B;
            ++crashcount;
        }
        ht[pos] = &str;
        value[pos] = val;
    }
    
    bool hasKey(string& str) {
        int pos = Hash(str.c_str()), p0 = pos;
        while(ht[pos] != &str) {
            pos = (pos + 1) % B;
            if(pos == p0) return false; //returned to original position, fail
        }
        return true;
    }
    
    T get(string& str) {
        int pos = Hash(str.c_str()), p0 = pos;
        while(ht[pos] != &str) {
            ++crashcount;
            pos = (pos + 1) % B;
            if(pos == p0)
                throw false; //throw an not-exist exception
        }
        return value[pos];
    }
};

#endif //HASH_OPENHASH_H
