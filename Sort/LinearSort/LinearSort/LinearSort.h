//
//  LinearSort.h
//  LinearSort
//
//  Created by 杨志飞 on 15/5/28.
//  Copyright (c) 2015年 杨志飞. All rights reserved.
//

#ifndef LinearSort_LinearSort_h
#define LinearSort_LinearSort_h
#include <cstdio>
#include <cmath>
#include <queue>
#include <vector>
void counting_sort(int a[], int n) {
    int max = a[0], min = a[0], *b, t;
    for (int i = 0; i < n; ++i)
        if (a[i] > max) max = a[i];
        else if (a[i] < min) min = a[i];
    max -= min;
    b = new int[max+1]();
    for (int i = 0; i < n; ++i)
        ++b[a[i]-min];
    t = 0;
    for (int i = 0; i <= max; ++i) {
        while (b[i]--)
            a[t++] = i + min;
    }
    delete [] b;
}

void radix_sort(int a[], int n) {
    //int范围内长度最大是10
    const int power[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    std::queue<int> Q[19]; //-9~9共19个
    int t;
    for (int d = 0; d < 10; ++d) {
        for (int i = 0; i < n; ++i)
            Q[9 + (a[i]/power[d]%10)].push(a[i]);
        t = 0;
        for (int i = 0; i < 19; ++i)
            while (!Q[i].empty()) {
                a[t++] = Q[i].front();
                Q[i].pop();
            }
    }
}

void bucket_sort(int a[], int n) {
    std::vector<int> *bucket;
    int max = a[0], min = a[0], nbucket, t = 0;
    const int lbucket = 10;
    for (int i = 0; i < n; ++i)
        if (a[i] > max) max = a[i];
        else if (a[i] < min) min = a[i];
    nbucket = (max - min) / lbucket + 1;
    bucket = new std::vector<int>[nbucket];
    for (int i = 0; i < n; ++i) {
        bucket[(a[i]-min)/lbucket].push_back(a[i]);
    }
    for (int i = 0; i < nbucket; ++i) {
        sort(bucket[i].begin(), bucket[i].end());
        for (std::vector<int>::iterator j = bucket[i].begin(); j != bucket[i].end(); j++)
            a[t++] = *j;
    }
}

#endif
