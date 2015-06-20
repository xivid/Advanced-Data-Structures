#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
#define MAXN 1001

using namespace std;
int L[MAXN][MAXN], dfn[MAXN], low[MAXN];
stack<int> temp;
bool instack[MAXN];
int n, m, cnt;
inline int min(int x, int y) {return x < y ? x : y;}
void tarjan(int u) {
    int v;
    dfn[u] = low[u] = ++cnt;
    temp.push(u);
    instack[u] = true;
    for (int i = 1; i <= L[u][0]; i++) {
        v = L[u][i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (instack[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        cout << "Strong connected component:" << endl;
        while (!temp.empty()) {
            v = temp.top(); temp.pop();
            instack[v] = false;
            cout << v << " ";
            if (v == u) break;
        }
        cout << endl;
    }
}

void StrongCC() {
    //T = None
    memset(dfn, 0, sizeof(dfn));
    cnt = 0;
    for (int i = 1; i <= n; ++i) if (!dfn[i])
            tarjan(i);
}

int main() {
    int u, v;
    memset(L, 0, sizeof(L));
    cout << "Input the number of vertexes and the number of edges: ";
    cin >> n >> m;
    cout << "Input u, v of each edge:" << endl;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        L[u][++L[u][0]] = v;
    }
    StrongCC();
    cnt = 0;

    return 0;
}
/*
6 8
1 3
1 2
2 4
3 4
3 5
5 6
4 6
4 1
 */
