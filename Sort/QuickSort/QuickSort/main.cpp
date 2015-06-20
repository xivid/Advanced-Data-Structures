#include <iostream>
#include <cstdio>
#include "QuickSort.h"
using namespace std;
int n, *data, *a, *ans;
void gen1(int l, int r) { //从中间向两边减小，卡取中
    int m = (l + r) >> 1, x = n;
    data[m] = x--;
    for (int i = 1; i <= m; i++)
    {
        data[m + i] = x--;
        data[m - i] = x--;
    }
    if (!(n%2)) data[n-1] = 1;
}

void gen2(int l, int r) { //每个二分区间的中点为最大值，卡取首和三者取中
    static int x = n;
    if (l <= r) {
        data[(l+r)>>1] = x--;
        gen2(l, ((l+r)>>1) - 1);
        gen2(((l+r)>>1) + 1, r);
    }
}

void gen3(int l, int r) { //顺序数据，卡取首
    for (int i = l; i <= r; ++i)
        data[i] = i;
}

void gen4(int l, int r) { //逆序数据，卡取首
    for (int i = l; i <= r; ++i)
        data[i] = r - i;
}

void gen5(int l, int r) { //随机数据
    for (int i = l; i <= r; ++i)
        data[i] = rand();
}

void gen6(int l, int r) { //重复数据
    for (int i = l; i <= r; ++i)
        data[i] = r;
}

double test(void (*Sort)(int[], int, int)) {
    double ret = 0;
    const int TIMES = 3; //测3次取平均值
    for (int i = 1; i <= TIMES; ++i) {
        memcpy(a, data, sizeof(int)*n);
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

void test(int DATATYPE) {
    double t[7];
    data = new int[n];
    a = new int[n];
    ans = new int[n];
    switch (DATATYPE) {
        case 1: gen1(0, n-1); break;
        case 2: gen2(0, n-1); break;
        case 3: gen3(0, n-1); break;
        case 4: gen4(0, n-1); break;
        case 5: gen5(0, n-1); break;
        case 6: gen6(0, n-1); break;
    }
    memcpy(ans, data, sizeof(int) * n);
    sort(ans, ans+n);
    cout << "STLSort time used: " << (t[0] = test(STLSort)) << "ms" << endl;
    cout << "HeadQSort time used: " << (t[1] = test(HeadQSort)) << "ms" << endl;
    cout << "MidQSort time used: " << (t[2] = test(MidQSort)) << "ms" << endl;
    cout << "RandQSort time used: " << (t[3] = test(RandQSort)) << "ms" << endl;
    cout << "GoldQSort time used: " << (t[4] = test(GoldQSort)) << "ms" << endl;
    cout << "TriMidQSort time used: " << (t[5] = test(TriMidQSort)) << "ms" << endl;
    cout << "DecMidInsQSort time used: " << (t[6] = test(DecMidInsQSort)) << "ms" << endl;
    FILE* fp = fopen("input.txt", "w");
    fprintf(fp, "1\n");
    switch (DATATYPE) {
    	case 1: fprintf(fp, "向两端减小\n"); break;
    	case 2: fprintf(fp, "区间中点最大\n"); break;
    	case 3: fprintf(fp, "顺序数据\n"); break;
    	case 4: fprintf(fp, "逆序数据\n"); break;
    	case 5: fprintf(fp, "随机数据\n"); break;
    	case 6: fprintf(fp, "重复数据\n"); break;
    }
    fprintf(fp, "%d\nSTL Sort\n%lf\n取首快排\n%lf\n取中快排\n%lf\n随机快排\n%lf\n0.618+尾递归快排\n%lf\n三者取中快排\n%lf\n取中+去重+小区间插排\n%lf\n", n, t[0], t[1], t[2], t[3], t[4], t[5], t[6]);
    
}

void test(int DATATYPE, int FUNTYPE, int start, int end, int step) {
    FILE* fp = fopen("input.txt", "w");
    double t;
    fprintf(fp, "2\n");
    switch (DATATYPE) {
        case 1: fprintf(fp, "向两端减小\n"); break;
    	case 2: fprintf(fp, "区间中点最大\n"); break;
    	case 3: fprintf(fp, "顺序数据\n"); break;
    	case 4: fprintf(fp, "逆序数据\n"); break;
    	case 5: fprintf(fp, "随机数据\n"); break;
    	case 6: fprintf(fp, "重复数据\n"); break;
    }
    switch (FUNTYPE) {
            case 1: fprintf(fp, "取首快排\n"); break;
            case 2: fprintf(fp, "取中快排\n"); break;
            case 3: fprintf(fp, "随机快排\n"); break;
            case 4: fprintf(fp, "0.618+尾递归快排\n"); break;
            case 5: fprintf(fp, "三者取中快排\n"); break;
            case 6: fprintf(fp, "取中+去重+小区间插排\n"); break;
    }
    for (n = start; n <= end; n += step) {
        delete [] data;
        delete [] a;
        delete [] ans;
        data = new int[n];
        a = new int[n];
        ans = new int[n];
        switch (DATATYPE) {
            case 1: gen1(0, n-1); break;
            case 2: gen2(0, n-1); break;
            case 3: gen3(0, n-1); break;
            case 4: gen4(0, n-1); break;
            case 5: gen5(0, n-1); break;
            case 6: gen6(0, n-1); break;
        }
        memcpy(ans, data, sizeof(int) * n);
        sort(ans, ans+n);
        cout << n << " ";
        fprintf(fp, "%d ", n);
        switch (FUNTYPE) {
            case 1: cout << (t = test(HeadQSort)); fprintf(fp, "%lf\n", t); break;
            case 2: cout << (t = test(MidQSort)); fprintf(fp, "%lf\n", t); break;
            case 3: cout << (t = test(RandQSort)); fprintf(fp, "%lf\n", t); break;
            case 4: cout << (t = test(GoldQSort)); fprintf(fp, "%lf\n", t); break;
            case 5: cout << (t = test(TriMidQSort)); fprintf(fp, "%lf\n", t); break;
            case 6: cout << (t = test(DecMidInsQSort)); fprintf(fp, "%lf\n", t); break;
        }
        cout << "ms" << endl;
    }
}

int main() {
	srand((unsigned)time(NULL));
	int TESTTYPE, DATATYPE;
	cout << "1. 不同优化横向评测 2. 性能曲线测定" << endl;
	cin >> TESTTYPE;
	cout << "1. 从中间向两边减小的数据（卡取中）" << endl;
	cout << "2. 每个二分区间的中点为最大值的数据（卡取首和三者取中）" << endl;
	cout << "3. 顺序数据（卡取首）" << endl;
	cout << "4. 逆序数据（卡取首）" << endl;
	cout << "5. int范围内随机数据" << endl;
	cout << "6. 所有数字全相同的数据" << endl;
	cin >> DATATYPE;
    if (TESTTYPE == 1) {
        cout << "数据规模：";
        cin >> n;
        test(DATATYPE);
    }
    else if (TESTTYPE == 2) {
        int FUNTYPE, start, end, step;
        cout << "1. 取首快排" << endl;
        cout << "2. 取中快排" << endl;
        cout << "3. 随机快排" << endl;
        cout << "4. 0.618+尾递归快排" << endl;
        cout << "5. 三者取中快排" << endl;
        cout << "6. 取中+去重+小区间插排" << endl;
        cin >> FUNTYPE;
        cout << "测试数据规模区间的端点和步长：";
        cin >> start >> end >> step;
        test(DATATYPE, FUNTYPE, start, end, step);
    }
	return 0;
}