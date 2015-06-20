/* 散列查找问题（要求应用)
 * 填充因子、数据规模与分布对查找性能影响
 * 完成一个具体的查找实例
 */
#include "OpenHash.h"
#include "ListHash.h"
#include "AVLTree.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
using namespace std;
FILE* fp;
const char Surname[24][8] = {"An", "Bai", "Cai", "Deng", "Fan", "Guo", "Han", "Ji", "Kuang", "Li", "Mu", "Nan", "Ou", "Piao", "Qian", "Sun", "Wu", "Wang", "Yang", "Yu", "Zhang", "Zhao", "Zheng", "Zhou"};
const char Given[24][15] = {"Alice", "Bob", "Cindy", "Dan", "Einstein", "Faham", "God", "Helen", "Ivan", "Jack", "Keven", "Linda", "Mary", "Nancy", "Oliver", "Percy", "Qiqi", "Ran", "Sandy", "Tank", "Urban", "Vanon", "Wilfred", "Zack"};
void demo1(int n, double lf) {
    //generate strings containing only three characters 'a', 'b' and 'c'
    fp = fopen("test1.txt", "w");
    string *v = new string[n + 10];
    time_t t1;
    AVLTree<string, bool> used;
    OpenStrHashTable<int> openhash(ceil((double)n / lf));
    ListStrHashTable<int> listhash(ceil((double)n / lf));
    cout << "Generating data:" << endl;
    for (int i = 1; i <= n; ) {
        string s;
        int len = ceil(log(n)/log(3)) + rand() % 7 - 3; // min length satisfying(3^len>n) +- 3
        if (len <= 0) len = 1;
        for (int j = 1; j <= len; ++j)
            s += (rand()%3 + 'a');
        if (used.hasKey(s)) {
            //cout << "duplicate key:" << s << endl;
            continue;
        }
        else {
            fprintf(fp, "%s\n", s.c_str());
            v[i++] = s;
            used.insert(s, true);
        }
    }
    cout << "Generation finished." << endl;
    
    cout << "Inserting all (key = string, value = length) pairs to OpenStrHashTable..." << endl;
    t1 = clock();
    openhash.clearcrash();
    for (int i = 1; i <= n; i++)
        openhash.insert(v[i], v[i].length());
    t1 = clock() - t1;
    cout << "Crashes: " << openhash.crashcount << ", Time used: " << (double)t1/CLOCKS_PER_SEC << endl;
    
    cout << "Searching all keys in OpenStrHashTable..." << endl;
    t1 = clock();
    openhash.clearcrash();
    for (int i = 1; i <= n; i++)
        openhash.get(v[i]);
    //cout << v[i] << ": " << openhash.get(v[i]) << endl;
    t1 = clock() - t1;
    cout << "Crashes: " << openhash.crashcount << ", Time used: " << (double)t1/CLOCKS_PER_SEC << endl;
    
    cout << "Inserting all (key = string, value = length) pairs to ListStrHashTable..." << endl;
    listhash.clearcrash();
    t1 = clock();
    for (int i = 1; i <= n; i++)
        listhash.insert(v[i], v[i].length());
    t1 = clock() - t1;
    cout << "Crashes: " << listhash.crashcount << ", Time used: " << (double)t1/CLOCKS_PER_SEC << endl;
    
    cout << "Searching all keys in ListStrHashTable..." << endl;
    t1 = clock();
    listhash.clearcrash();
    for (int i = 1; i <= n; i++)
        listhash.get(v[i]);
    //cout << v[i] << ": " << listhash.get(v[i]) << endl;
    t1 = clock() - t1;
    cout << "Crashes: " << listhash.crashcount << ", Time used: " << (double)t1/CLOCKS_PER_SEC << endl;
}

void demo2(int n, double lf) {
    //generate random strings
    fp = fopen("test2.txt", "w");
    string *v = new string[n + 10];
    time_t t1;
    AVLTree<string, bool> used;
    OpenStrHashTable<int> openhash(ceil((double)n / lf));
    ListStrHashTable<int> listhash(ceil((double)n / lf));
    cout << "Generating data:" << endl;
    for (int i = 1; i <= n; ) {
        string s;
        int len = ceil(log(n)/log(3)) + rand() % 15; // min length satisfying(3^len>n) +- 3
        for (int j = 1; j <= len; ++j)
            s += (33 + rand()%(127-33));
        if (used.hasKey(s)) {
            //cout << "duplicate key:" << s << endl;
            continue;
        }
        else {
            fprintf(fp, "%s", s.c_str());
            v[i++] = s;
            used.insert(s, true);
        }
    }
    cout << "Generation finished." << endl;
    
    cout << "Inserting all (key = string, value = length) pairs to OpenStrHashTable..." << endl;
    t1 = clock();
    openhash.clearcrash();
    for (int i = 1; i <= n; i++)
        openhash.insert(v[i], v[i].length());
    t1 = clock() - t1;
    cout << "Crashes: " << openhash.crashcount << ", Time used: " << (double)t1/CLOCKS_PER_SEC << endl;
    
    cout << "Searching all keys in OpenStrHashTable..." << endl;
    t1 = clock();
    openhash.clearcrash();
    for (int i = 1; i <= n; i++)
        openhash.get(v[i]);
    //cout << v[i] << ": " << openhash.get(v[i]) << endl;
    t1 = clock() - t1;
    cout << "Crashes: " << openhash.crashcount << ", Time used: " << (double)t1/CLOCKS_PER_SEC << endl;
    
    cout << "Inserting all (key = string, value = length) pairs to ListStrHashTable..." << endl;
    listhash.clearcrash();
    t1 = clock();
    for (int i = 1; i <= n; i++)
        listhash.insert(v[i], v[i].length());
    t1 = clock() - t1;
    cout << "Crashes: " << listhash.crashcount << ", Time used: " << (double)t1/CLOCKS_PER_SEC << endl;
    
    cout << "Searching all keys in ListStrHashTable..." << endl;
    t1 = clock();
    listhash.clearcrash();
    for (int i = 1; i <= n; i++)
        listhash.get(v[i]);
    //cout << v[i] << ": " << listhash.get(v[i]) << endl;
    t1 = clock() - t1;
    cout << "Crashes: " << listhash.crashcount << ", Time used: " << (double)t1/CLOCKS_PER_SEC << endl;
}

struct People {
    string name;
    string tel;
};
void demo3(int n, double lf) {
    //generate a contact book
    fp = fopen("test3.txt", "w");
    People* v = new People[n + 10];
    time_t t1;
    AVLTree<string, bool> used;
    OpenStrHashTable<People*> openhash(ceil((double)n / lf));
    ListStrHashTable<People*> listhash(ceil((double)n / lf));
    cout << "Generating data:" << endl;
    for (int i = 1; i <= n; ) {
        string name;
        name += Given[rand()%24];
        name += " ";
        name += Surname[rand()%24];
        if (used.hasKey(name)) {
            continue;
            //cout << "duplicate key:" << name << endl;
            //used.print();
            //break;
        }
        else {
            char TEL[13] = "13000000000";
            TEL[1] += rand() % 6;
            for(int j = 2; j < 11; ++j)
                TEL[j] += rand() % 10;
            v[i].name = name;
            v[i++].tel += TEL;
            fprintf(fp, "%s\n%s\n", name.c_str(), TEL);
            used.insert(name, true);
        }
    }
    cout << "Generation finished." << endl;
    
    cout << "Inserting all (key = string, value = People*) pairs to OpenStrHashTable..." << endl;
    t1 = clock();
    openhash.clearcrash();
    for (int i = 1; i <= n; i++)
        openhash.insert(v[i].name, v + i);
    t1 = clock() - t1;
    cout << "Crashes: " << openhash.crashcount << ", Time used: " << (double)t1/CLOCKS_PER_SEC << endl;
    
    cout << "Searching all keys in OpenStrHashTable..." << endl;
    t1 = clock();
    openhash.clearcrash();
    for (int i = 1; i <= n; i++)
        openhash.get(v[i].name);
    //cout << v[i] << ": " << openhash.get(v[i]) << endl;
    t1 = clock() - t1;
    cout << "Crashes: " << openhash.crashcount << ", Time used: " << (double)t1/CLOCKS_PER_SEC << endl;
    
    cout << "Inserting all (key = string, value = People*) pairs to ListStrHashTable..." << endl;
    listhash.clearcrash();
    t1 = clock();
    for (int i = 1; i <= n; i++)
        listhash.insert(v[i].name, v + i);
    t1 = clock() - t1;
    cout << "Crashes: " << listhash.crashcount << ", Time used: " << (double)t1/CLOCKS_PER_SEC << endl;
    
    cout << "Searching all keys in ListStrHashTable..." << endl;
    t1 = clock();
    listhash.clearcrash();
    for (int i = 1; i <= n; i++)
        listhash.get(v[i].name);
    //cout << v[i] << ": " << listhash.get(v[i]) << endl;
    t1 = clock() - t1;
    cout << "Crashes: " << listhash.crashcount << ", Time used: " << (double)t1/CLOCKS_PER_SEC << endl;
}
void demo4() {
    FILE *fp;
    double t1;
    int n = 0;
    if ((fp = fopen("NodeInfo.txt", "r")) == NULL) {
        cout << "Cannot open NodeInfo.txt" << endl;
        return;
    }
    string* nodeinfo = new string[2400000];
    char t[100];
    while (fgets(t, 100, fp) > 0) nodeinfo[n++] = t;
    fclose(fp);
    OpenStrHashTable<int> openhash(ceil((double)n / 0.8));
    ListStrHashTable<int> listhash(ceil((double)n / 0.8));
    
    cout << "Inserting all (key = string, value = int) pairs to OpenStrHashTable..." << endl;
    t1 = clock();
    openhash.clearcrash();
    for (int i = 0; i < n; ++i) {
        openhash.insert(nodeinfo[i], i);
    }
    t1 = clock() - t1;
    cout << "Crashes: " << openhash.crashcount << ", Time used: " << (double)t1/CLOCKS_PER_SEC << endl;
    ///----
    cout << "Searching all keys in OpenStrHashTable..." << endl;
    t1 = clock();
    openhash.clearcrash();
    for (int i = 0; i < n; ++i) {
        try {
             if (openhash.get(nodeinfo[i]) != i) cout << "open " << i << ":" << openhash.get(nodeinfo[i]) << endl;
        }catch(bool) {cout << "not found!" << endl;}
    }
    t1 = clock() - t1;
    cout << "Crashes: " << openhash.crashcount << ", Time used: " << (double)t1/CLOCKS_PER_SEC << endl;
    
    ////////////
    cout << "Inserting all (key = string, value = int) pairs to ListStrHashTable..." << endl;
    listhash.clearcrash();
    t1 = clock();
    for (int i = 0; i < n; ++i) {
        listhash.insert(nodeinfo[i], i);
    }
    t1 = clock() - t1;
    cout << "Crashes: " << listhash.crashcount << ", Time used: " << (double)t1/CLOCKS_PER_SEC << endl;
    ///----
    cout << "Searching all keys in ListStrHashTable..." << endl;
    t1 = clock();
    listhash.clearcrash();
    for (int i = 0; i < n; ++i) {
        try {
            if (listhash.get(nodeinfo[i]) != i) cout << "list " << i << ":" << listhash.get(nodeinfo[i]) << endl;
        }catch(bool) {cout << "not found!" << endl;}
    }
    t1 = clock() - t1;
    cout << "Crashes: " << listhash.crashcount << ", Time used: " << (double)t1/CLOCKS_PER_SEC << endl;
}
int main() {
    int dataSize;
    double loadFactor;
    cout << "Input dataSize:" << endl;
    cin >> dataSize;
    cout << "Input load factor:" << endl;
    cin >> loadFactor;
    cout << "dataSize = " << dataSize << ", loadFactor = " << loadFactor << endl;
    srand((unsigned)time(NULL));
    cout << "Distribution 1: Similar strings" << endl;
    demo1(dataSize, loadFactor);
    cout << "Distribution 2: Random strings" << endl;
    demo2(dataSize, loadFactor);
    cout << "Distribution 3: Randomly combined contactbook" << endl;
    demo3(100, loadFactor);
    cout << "Distribution 4: Given 200MB data" << endl;
    demo4();
    return 0;
}
