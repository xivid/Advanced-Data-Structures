#include <iostream>
#include <cstdio>
#include "LinearSort.h"
using namespace std;
int n, *data, *a, *ans;
void gen1(int n) { //重复数据
    for (int i = 0; i < n; i++)
        data[i] = n;
}

void gen2(int n) { //负数数据
    for (int i = 0; i < n; i++)
        data[i] = -10000 + rand()%20000;
}

void gen3(int n) { //顺序数据
    for (int i = 0; i < n; ++i)
        data[i] = i;
}

void gen4(int n) { //逆序数据
    for (int i = 0; i < n; ++i)
        data[i] = n - i;
}

void gen5(int n) { //一般随机数据
    for (int i = 0; i < n; ++i)
        data[i] = 10000 + rand() % 10000;
}

void gen6(int n) { //大数据
    for (int i = 0; i < n; ++i)
        data[i] = ((1+rand()%2)*10000+rand()%1400)*100000 + 10000*(1+rand()%9) + rand()%10000;
}

double test(void (*Sort)(int[], int)) {
    double ret = 0;
    const int TIMES = 3; //测3次取平均值
    for (int i = 1; i <= TIMES; i++) {
        memcpy(a, data, sizeof(int)*n);
        time_t t = clock();
        Sort(a, n);
        t = clock() - t;
        for (int i = 0; i < n; ++i)
            if (a[i] != ans[i]) {
                cout << "Error!" << endl;
                break;
            }
        ret += (double)t/CLOCKS_PER_SEC*1000;
    }
    return ret / TIMES;
}

void test(int DATATYPE) {
    double t[3];
    data = new int[n];
    a = new int[n];
    ans = new int[n];
    switch (DATATYPE) {
        case 1: gen1(n); break;
        case 2: gen2(n); break;
        case 3: gen3(n); break;
        case 4: gen4(n); break;
        case 5: gen5(n); break;
        case 6: gen6(n); break;
        case 7:
            for (int i = 0; i < n; ++i) cin >> data[i];
            break;
    }
    memcpy(ans, data, sizeof(int)*n);
    sort(ans, ans + n);
    cout << "radix_sort time used: " << (t[0] = test(radix_sort)) << "ms" << endl;
    if (DATATYPE != 6 || n <= 10000) {
        cout << "counting_sort time used: " << (t[1] = test(counting_sort)) << "ms" << endl;
        cout << "bucket_sort time used: " << (t[2] = test(bucket_sort)) << "ms" << endl;
    }
    else cout << "counting_sort and bucket_sort uses too much memory." << endl;
    FILE* fp = fopen("input.txt", "w");
    fprintf(fp, "1\n");
    switch (DATATYPE) {
        case 1: fprintf(fp, "重复数据\n"); break;
        case 2: fprintf(fp, "负数数据\n"); break;
        case 3: fprintf(fp, "顺序数据\n"); break;
        case 4: fprintf(fp, "逆序数据\n"); break;
        case 5: fprintf(fp, "一般随机数据\n"); break;
        case 6: fprintf(fp, "长整数数据\n"); break;
        case 7: fprintf(fp, "手动输入的数据\n"); break;
    }
    fprintf(fp, "%d\n基数排序\n%lf\n计数排序\n%lf\n桶排序\n%lf\n", n, t[0], t[1], t[2]);
}

void test(int DATATYPE, int FUNTYPE, int start, int end, int step) {
    FILE* fp = fopen("input.txt", "w");
    double t;
    fprintf(fp, "2\n");
    switch (DATATYPE) {
        case 1: fprintf(fp, "重复数据\n"); break;
        case 2: fprintf(fp, "负数数据\n"); break;
        case 3: fprintf(fp, "顺序数据\n"); break;
        case 4: fprintf(fp, "逆序数据\n"); break;
        case 5: fprintf(fp, "一般随机数据\n"); break;
        case 6: fprintf(fp, "长整数数据\n"); break;
        case 7: fprintf(fp, "手动输入的数据\n"); break;
    }
    switch (FUNTYPE) {
        case 1: fprintf(fp, "计数排序\n"); break;
        case 2: fprintf(fp, "基数排序\n"); break;
        case 3: fprintf(fp, "桶排序\n"); break;
    }
    for (n = start; n <= end; n += step) {
        delete [] data;
        delete [] a;
        delete [] ans;
        data = new int[n];
        a = new int[n];
        ans = new int[n];
        switch (DATATYPE) {
            case 1: gen1(n); break;
            case 2: gen2(n); break;
            case 3: gen3(n); break;
            case 4: gen4(n); break;
            case 5: gen5(n); break;
            case 6: gen6(n); break;
            case 7:
                for (int i = 0; i < n; ++i) cin >> data[i];
                break;
        }
        memcpy(ans, data, sizeof(int)*n);
        sort(ans, ans + n);
        cout << n << " ";
        fprintf(fp, "%d ", n);
        switch (FUNTYPE) {
            case 1: cout << (t = test(counting_sort)); fprintf(fp, "%lf\n", t); break;
            case 2: cout << (t = test(radix_sort)); fprintf(fp, "%lf\n", t); break;
            case 3: cout << (t = test(bucket_sort)); fprintf(fp, "%lf\n", t); break;
        }
        cout << "ms" << endl;
    }
}

int main() {
    srand((unsigned)time(NULL));
    int TESTTYPE, DATATYPE;
    cout << "1. 三种算法横向评测 2. 性能曲线测定" << endl;
    cin >> TESTTYPE;
    cout << "1. 重复数据" << endl;
    cout << "2. 负数数据" << endl;
    cout << "3. 顺序数据" << endl;
    cout << "4. 逆序数据" << endl;
    cout << "5. 一般随机数据" << endl;
    cout << "6. 长整数数据" << endl;
    cout << "7. 自己输入数据" << endl;
    cin >> DATATYPE;
    
    if (TESTTYPE == 1) {
        cout << "数据规模：";
        cin >> n;
        test(DATATYPE);
    }
    else if (TESTTYPE == 2) {
        int FUNTYPE, start, end, step;
        cout << "1. 计数排序" << endl;
        cout << "2. 基数排序" << endl;
        cout << "3. 桶排序" << endl;
        cin >> FUNTYPE;
        cout << "数据规模区间端点和步长：";
        cin >> start >> end >> step;
        test(DATATYPE, FUNTYPE, start, end, step);
    }
    return 0;
}