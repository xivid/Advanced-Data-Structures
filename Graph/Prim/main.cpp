#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1000
using namespace std;
int Prim(int d[][MAXN], int n)
{
    int closest[MAXN] = {-1}, k, ans = 0;
    for (int i = 1; i < n; ++i)
        closest[i] = 0;
    for (int i = 1; i < n; ++i)
    {
        k = 1;
        for (int j = 1; j < n; ++j)
            if (closest[j] >= 0 && d[j][closest[j]] < d[k][closest[k]])
                k = j;
        ans += d[k][closest[k]];
        printf("Edge (%d, %d), weight %d added.\n", k+1, closest[k]+1, d[k][closest[k]]);
        for (int j = 1; j < n; ++j)
            if (closest[j] >= 0 && d[j][k] < d[j][closest[j]])
                closest[j] = k;
        closest[k] = -1;
    }
    return ans;
}
int dist[MAXN][MAXN];
int main() {
    int n, m, u, v, d;
    memset(dist, 0x7f, sizeof(dist)); //INFINITY
    printf("Prim MST Algorithm DEMO\n");
    printf("Input the number of vertexes: ");
    cin >> n;
    if (n > MAXN)
        exit(0);
    printf("Input the number of edges: ");
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        printf("Input two endpoints and weight of edge #%d: ", i+1);
        cin >> u >> v >> d;
        dist[u-1][v-1] = dist[v-1][u-1] = d;
    }
    printf("The weight of MST is %d.\n", Prim(dist, n));
    return 0;
}