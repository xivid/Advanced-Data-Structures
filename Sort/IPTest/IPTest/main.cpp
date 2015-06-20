//
//  IPTest.cpp
//  QuickSort
//
//  Created by 杨志飞 on 15/6/4.
//  Copyright (c) 2015年 杨志飞. All rights reserved.
//
#include <iostream>
#include <cstdio>
#include "SortAlgo.h"
using namespace std;
long long a[2400000], ans[2400000], data[2400000];
int n = 0;
double test(void (*Sort)(long long[], int, int)) {
    double ret = 0;
    const int TIMES = 3; //测3次取平均值
    for (int i = 1; i <= TIMES; ++i) {
        memcpy(a, data, sizeof(long long)*n);
        time_t t = clock();
        Sort(a, 0, n-1);
        t = clock() - t;
        for (int i = 0; i < n; ++i)
            if (a[i] != ans[i]) {
                cout << "i=" << i << ", a[i]=" << a[i] << ", ans[i]=" << ans[i] << endl;
                cout << "Error!" << endl;
                break;
            }
        ret += (double)t/CLOCKS_PER_SEC*1000;
    }
    return ret / TIMES;
}
int main() {
    long long tmp;
    n = 0;
    FILE* fp = fopen("IPInfo.txt", "r");
    if (fp == NULL) {cout << "Cannot open file." << endl; return 0;}
    while (fscanf(fp, "%lld", &tmp) != EOF) {
        data[n++] = tmp;
    }
    fclose(fp);
    double t[8];
    cout << "n = " << n << endl;
    memcpy(ans, data, sizeof(long long) * n);
    sort(ans, ans+n);
    cout << "STLSort time used: " << (t[0] = test(STLSort)) << "ms" << endl;
    cout << "HeadQSort time used: " << (t[1] = test(HeadQSort)) << "ms" << endl;
    cout << "MidQSort time used: " << (t[2] = test(MidQSort)) << "ms" << endl;
    cout << "RandQSort time used: " << (t[3] = test(RandQSort)) << "ms" << endl;
    cout << "GoldQSort time used: " << (t[4] = test(GoldQSort)) << "ms" << endl;
    cout << "TriMidQSort time used: " << (t[5] = test(TriMidQSort)) << "ms" << endl;
    cout << "DecMidInsQSort time used: " << (t[6] = test(DecMidInsQSort)) << "ms" << endl;
    cout << "RadixSort time used: " << (t[7] = test(radix_sort)) << "ms" << endl;
    fp = fopen("input.txt", "w");
    fprintf(fp, "1\nIPInfo.txt\n");
    fprintf(fp, "%d\nSTL Sort\n%lf\n取首快排\n%lf\n取中快排\n%lf\n随机快排\n%lf\n0.618+尾递归快排\n%lf\n三者取中快排\n%lf\n取中+去重+小区间插排\n%lf\n基数排序\n%lf\n", n, t[0], t[1], t[2], t[3], t[4], t[5], t[6], t[7]);
    return 0;
}