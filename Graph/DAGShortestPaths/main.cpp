#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstdlib>
#define MAXN 1001
#define INF 0x7f7f7f7f
using namespace std;

int n, m;
vector<int> vertex[MAXN];
int seq[MAXN], dist[MAXN][MAXN], indegree[MAXN], d[MAXN];
bool toposort() {
    int nodecount = 0, u, size, v;
    memset(seq, 0, sizeof(seq));
    queue<int> Q;
    for (int i = 1; i <= n; ++i)
        if (!indegree[i])
            Q.push(i);
    while(!Q.empty())
    {
        u = Q.front();
        Q.pop();
        seq[++nodecount] = u;
        size = vertex[u].size();
        for (int i = 0; i < size; ++i) {
            v = vertex[u][i];
            --indegree[v];
            if (!indegree[v])
                Q.push(v);
        }
    }
    if (nodecount < n)
        return false;
    return true;
}

bool DAG_SP(int s) {
    if (toposort()) {
        memset(d, 0x7f, sizeof(d));
        d[s] = 0;
        for (int i = 1; i <= n; ++i)
        {
            int u = seq[i], size = vertex[seq[i]].size();
            for (int j = 0; j < size; ++j)
                if (d[u] + dist[u][vertex[u][j]] < d[vertex[u][j]]) //d[u] < INF?
                    d[vertex[u][j]] = d[u] + dist[u][vertex[u][j]];
        }
    }
    else
        return false;
    return true;
}
int main() {
    int u, v, w, s;
    memset(dist, 0x7f, sizeof(dist));
    memset(indegree, 0, sizeof(indegree));
    cout << "Input the number of vertexes and the number of edges: ";
    cin >> n >> m;
    cout << "Input u, v, w of each edge:" << endl;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> w;
        dist[u][v] = w;
        ++indegree[v];
        vertex[u].push_back(v);
    }
    for (int i = 1; i <= n; ++i)
        dist[i][i] = 0;
    cout << "Input source: ";
    cin >> s;
    if (DAG_SP(s)) {
        for (int i = 1; i <= n; ++i) {
            printf("The shortest path from %d to %d is ", s, i);
            if (d[i] == INF)
                puts("INF");
            else
                cout << d[i] << endl;
        }
    }
    else cout << "Cycle(s) exist on this graph." << endl;
    return 0;
}