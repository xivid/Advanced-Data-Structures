#include <iostream>
#include <cstdlib>
#include <queue>
#define MAXM 1000001
#define MAXN 1001
#define INF 0x7f7f7f7f
using namespace std;

int n, m;
int u[MAXM], v[MAXM], w[MAXM], Next[MAXM];
int first[MAXN], d[MAXN];
bool inQueue[MAXN];

bool spfa(int s)
{
    queue<int> Q;
    memset(inQueue, false, sizeof(inQueue));
    memset(d, 0x7f, sizeof(d));
    d[s] = 0;
    Q.push(s);
    inQueue[s] = true;

    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        inQueue[s] = false;
        for (int e = first[u]; e; e = Next[e])
            if (d[u] + w[e] < d[v[e]]){
                d[v[e]] = d[u] + w[e];
                if (!inQueue[v[e]]) {
                    Q.push(v[e]);
                    inQueue[v[e]] = true;
                }
        }
    }

    for (int e = 1; e <= m; ++e)
        if (d[v[e]] > d[u[e]] + w[e]) //fail due to negative circle
            return false;

    return true;
}

int main() {
    int s;
    memset(Next, 0, sizeof(Next));
    memset(first, 0, sizeof(first));
    cout << "Input number of vertexes and number of edges: ";
    cin >> n >> m;
    cout << "Input the u, v, w of " << m << " edges:" << endl;
    for (int i = 1; i <= m; ++i)
    {
        cin >> u[i] >> v[i] >> w[i];
        Next[i] = first[u[i]];
        first[u[i]] = i;
    }
    cout << "Input source: ";
    while(cin >> s)
    {
        if (spfa(s))
        {
            for (int i = 1; i <= n; ++i)
                if (d[i] != INF)
                    printf("The shortest path from %d to %d is %d\n", s, i, d[i]);
                else
                    printf("The shortest path from %d to %d is INF\n", s, i);
        }
        else
            cout << "There exists negative cycle(s)." << endl;
    }
    return 0;
}