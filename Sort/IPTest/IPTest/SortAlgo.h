//
//  SortAlgo.h
//  IPTest
//
//  Created by 杨志飞 on 15/6/4.
//  Copyright (c) 2015年 杨志飞. All rights reserved.
//

#ifndef IPTest_SortAlgo_h
#define IPTest_SortAlgo_h

//#define OUTPUT_LENGTH
//#define OUTPUT_DETAIL
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>

template<class T>
void radix_sort(T a[], int l, int r) {
    //int范围内长度最大是10
    const long long power[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000ll, 100000000000ll, 1000000000000ll};
    std::queue<T> Q[19]; //-9~9共19个
    int t;
    for (int d = 0; d < 13; ++d) {
        for (int i = l; i <= r; ++i)
            Q[9 + (a[i]/power[d]%10)].push(a[i]);
        t = 0;
        for (int i = 0; i < 19; ++i)
            while (!Q[i].empty()) {
                a[t++] = Q[i].front();
                Q[i].pop();
            }
    }
}

template<class T>
void HeadQSort(T a[], int l, int r) {
    int tl = l, tr = r;
    T m = a[l];
#ifdef OUTPUT_LENGTH
    std::cout << "sort (" << l << ", " << r << ", " << (r-l+1) << "): " << std::endl;
#ifdef OUTPUT_DETAIL
    for (int i = l; i <= r; ++i) std::cout << a[i] << ' ';
    std::cout << std::endl;
#endif
#endif
    while (tl <= tr) {
        while (a[tl] < m) tl++;
        while (a[tr] > m) tr--;
        if (tl <= tr) {
            if (tl != tr) {T t = a[tl]; a[tl] = a[tr]; a[tr] = t; }
            ++tl, --tr;
        }
    }
    if (tr > l) HeadQSort(a, l, tr);
    if (tl < r) HeadQSort(a, tl, r);
}

template<class T>
void MidQSort(T a[], int l, int r) {
    T m = a[(l+r)>>1];
    int tl = l, tr = r;
#ifdef OUTPUT_LENGTH
    std::cout << "sort (" << l << ", " << r << ", " << (r-l+1) << "): " << std::endl;
#ifdef OUTPUT_DETAIL
    for (int i = l; i <= r; ++i) std::cout << a[i] << ' ';
    std::cout << std::endl;
#endif
#endif
    while (tl <= tr) {
        while (a[tl] < m) tl++;
        while (a[tr] > m) tr--;
        if (tl <= tr) {
            if (tl != tr) {T t = a[tl]; a[tl] = a[tr]; a[tr] = t; }
            ++tl, --tr;
        }
    }
    if (tr > l) MidQSort(a, l, tr);
    if (tl < r) MidQSort(a, tl, r);
}

template<class T>
inline T& mid(T& a, T& b, T& c) {return a > b ? (b > c ? b : (c > a ? a : c)) : (b < c ? b : (c < a ? a : c)); }

template<class T>
void TriMidQSort(T a[], int l, int r) {
    T m = mid(a[l], a[(l+r)>>1], a[r]);
    int tl = l, tr = r;
#ifdef OUTPUT_LENGTH
    std::cout << "sort (" << l << ", " << r << ", " << (r-l+1) << "): " << std::endl;
#ifdef OUTPUT_DETAIL
    for (int i = l; i <= r; ++i) std::cout << a[i] << ' ';
    std::cout << std::endl;
#endif
#endif
    while (tl <= tr) {
        while (a[tl] < m) tl++;
        while (a[tr] > m) tr--;
        if (tl <= tr) {
            if (tl != tr) {T t = a[tl]; a[tl] = a[tr]; a[tr] = t; }
            ++tl, --tr;
        }
    }
    if (tr > l) TriMidQSort(a, l, tr);
    if (tl < r) TriMidQSort(a, tl, r);
}

template<class T>
void GoldQSort(T a[], int l, int r) {
#ifdef OUTPUT_LENGTH
    std::cout << "sort (" << l << ", " << r << ", " << (r-l+1) << "): " << std::endl;
#ifdef OUTPUT_DETAIL
    for (int i = l; i <= r; ++i) std::cout << a[i] << ' ';
    std::cout << std::endl;
#endif
#endif
    while (l < r) {
        T m = a[l + (int)((r-l)*0.618)];
        int tl = l, tr = r;
        while (tl <= tr) {
            while (a[tl] < m) tl++;
            while (a[tr] > m) tr--;
            if (tl <= tr) {
                if (tl != tr) {T t = a[tl]; a[tl] = a[tr]; a[tr] = t; }
                ++tl, --tr;
            }
        }
        if (tr > l) GoldQSort(a, l, tr);
        l = tl; //if (tl < r) GoldQSort(a, tl, r);
    }
}

template<class T>
void RandQSort(T a[], int l, int r) {
    T m = a[l + rand() % (r-l+1)];
    int tl = l, tr = r;
#ifdef OUTPUT_LENGTH
    std::cout << "sort (" << l << ", " << r << ", " << (r-l+1) << "): " << std::endl;
#ifdef OUTPUT_DETAIL
    for (int i = l; i <= r; ++i) std::cout << a[i] << ' ';
    std::cout << std::endl;
#endif
#endif
    while (tl <= tr) {
        while (a[tl] < m) tl++;
        while (a[tr] > m) tr--;
        if (tl <= tr) {
            if (tl != tr) {T t = a[tl]; a[tl] = a[tr]; a[tr] = t; }
            ++tl, --tr;
        }
    }
    if (tr > l) RandQSort(a, l, tr);
    if (tl < r) RandQSort(a, tl, r);
}

template<class T>
void DecMidInsQSort(T a[], int l, int r) {
#ifdef OUTPUT_LENGTH
    std::cout << "sort (" << l << ", " << r << ", " << (r-l+1) << "): " << std::endl;
#ifdef OUTPUT_DETAIL
    for (int i = l; i <= r; ++i) std::cout << a[i] << ' ';
    std::cout << std::endl;
#endif
#endif
    if (r - l < 6) { //size < 7, insertion sort
        for (int i = l; i < r; ++i) {
            int tl = l, tr = i;
            T t = a[i+1];
            while (tl <= tr) {
                T x = a[(tl+tr) >> 1];
                if (t < x) tr = ((tl+tr)>>1) - 1;
                else	   tl = ((tl+tr)>>1) + 1;
            }
            for (int j = i; j >= tl; --j) a[j+1] = a[j];
            a[tl] = t;
        }
        return;
    }
    T m = a[(l+r)>>1];
    int tl = l, tr = r;
    while (tl <= tr) {
        while (a[tl] < m) tl++;
        while (a[tr] > m) tr--;
        if (tl <= tr) {
            if (tl != tr) {T t = a[tl]; a[tl] = a[tr]; a[tr] = t; }
            ++tl, --tr;
        }
    }
    for (int i = l; i <= tr; i++) if (a[i] == m) {
        T t = a[i];
        a[i] = a[tr];
        a[tr--] = t;
    }
    for (int i = r; i >= tl; --i) if (a[i] == m) {
        T t = a[i];
        a[i] = a[tl];
        a[tl++] = t;
    }
    if (tr > l) DecMidInsQSort(a, l, tr);
    if (tl < r) DecMidInsQSort(a, tl, r);
}

template<class T>
void STLSort(T a[], int l, int r) {
    std::sort(a + l, a + r + 1);
}

#endif
