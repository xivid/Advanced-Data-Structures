#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
#define MAXN 1001

using namespace std;
int L[MAXN][MAXN], dfn[MAXN], low[MAXN], father[MAXN];
bool visited[MAXN];
stack<pair<int, int> > temp;
int n, m, cnt;
inline int min(int x, int y) {return x < y ? x : y;}
void dfs(int v) {
    int w;
    visited[v] = true;
    dfn[v] = ++cnt;
    low[v] = dfn[v];
    for (int i = 1; i <= L[v][0]; i++) {
        w = L[v][i];
        if (!visited[w]) {
            //add(v, w) to T
            if (!((dfn[w] > dfn[v] && visited[w]) || (dfn[w] < dfn[v] && father[v] == w)))
                temp.push(make_pair(v, w));
            father[w] = v;
            dfs(w);
            if (low[w] >= dfn[v]) {
                cout << "Biconnected component:" << endl;
                //print stack
                while (!temp.empty()) {
                    pair<int, int> p = temp.top(); temp.pop();
                    printf("(%d, %d) ", p.first, p.second);
                    if (p.first == v && p.second == w)
                        break;
                }
                cout << endl;
                if (!temp.empty()) cout << "critical point " << v << endl << endl;
            }
            low[v] = min(low[v], low[w]);
        }
        else if (w != father[v]) {
            low[v] = min(low[v], dfn[w]);
            if (!((dfn[w] > dfn[v] && visited[w]) || (dfn[w] < dfn[v] && father[v] == w)))
                temp.push(make_pair(v, w));
        }
    }
}

void Biconnected_Component() {
    //T = None
    memset(visited, false, sizeof(visited));
    memset(father, 0, sizeof(father));
    cnt = 0;
    dfs(1);
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
        L[v][++L[v][0]] = u;
    }
    Biconnected_Component();
    cnt = 0;

    return 0;
}

/*
 8 12
 1 2
 1 3
 2 3
 2 4
 2 5
 4 5
 4 6
 6 7
 6 8
 6 9
 7 8
 8 9
 */