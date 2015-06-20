#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <queue>
#define MAXN 10001
using namespace std;

bool vis[MAXN];
void Dijkstra(int dist[][MAXN], int d[MAXN], int u, int n)
{
    int v;
    memset(vis, false, sizeof(vis));
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > Q;
    for (int i = 1; i <= n; ++i)
        d[i] = 0x7f7f7f7f;
    d[u] = 0;
    Q.push(make_pair(0, u));
    for (int i = 1; i <= n; ++i)
    {
        while (!Q.empty())
        {
            v = Q.top().second;
            Q.pop();
            if (!vis[v])
            {
                vis[v] = true;
                for (int j = 1; j <= n; ++j)
                    if (dist[v][j] < 0x7f7f7f7f && dist[v][j] + d[v] < d[j])
                    {
                        d[j] = d[v] + dist[v][j];
                        Q.push(make_pair(d[j], j));
                    }
                break;
            }
        }
    }
}
int d[MAXN], dist[MAXN][MAXN];
int main() {
    int n, m, u, v, w;
    memset(dist, 0x7f, sizeof(dist)); //INF
    memset(d, 0, sizeof(d));
    cout << "Input number of nodes and number of edges: ";
    cin >> n >> m;
    cout << "Input " << m << " edges(u, v, w):" << endl;
    for (int i = 0; i < m; ++i)
    {
        cin >> u >> v >> w;
        dist[u][v] = w;
    }
    for (int i = 1; i <= n; ++i)
        dist[i][i] = 0;

    cout << "Specify the source: ";
    while(cin >> u) {
        Dijkstra(dist, d, u, n);
        for (int i = 1; i <= n; ++i)
            if (d[i] == 0x7f7f7f7f)
                printf("The shortest path from %d to %d is INF\n", u, i);
            else printf("The shortest path from %d to %d is %d\n", u, i, d[i]);
    }
    return 0;
}