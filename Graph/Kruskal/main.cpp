#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1001
#define MAXM 1000001
using namespace std;

struct Edge
{
    int u, v, w;
} E[MAXM];
bool cmp(const Edge& a, const Edge& b) {return a.w < b.w;}

int p[MAXN];
inline void Makeset(int x) {p[x] = x;}
int Find(int x) {return p[x] == x ? x : p[x] = Find(p[x]); }
inline void Union(int x, int y)
{
    x = Find(x); y = Find(y);
    if (x != y)
        p[x] = y;
}
int Kruskal(Edge e[], int m, int n)
{
    int ans = 0, min = 1;
    for (int i = 1; i <= n; ++i)
        Makeset(i);
    sort(e + 1, e + m + 1, cmp);
    for (int i = 1; i < n; ++i)
    {
        while(Find(e[min].u) == Find(e[min].v))
            ++min;
        ans += e[min].w;
        printf("Edge (%d, %d) with weight %d added.\n", e[min].u, e[min].v, e[min].w);
        Union(e[min].u, e[min].v);
    }
    return ans;
}

int main() {
    int n, m;
    cout << "Input the number of vertexes: ";
    cin >> n;
    cout << "Input the number of edges: ";
    cin >> m;
    for (int i = 1; i <= m; ++i)
    {
        cout << "Input the two endpoints and weight of edge #" << i << ": ";
        cin >> E[i].u >> E[i].v >> E[i].w;
    }

    cout << "The weight of MST is " << Kruskal(E, m, n) << endl;
    return 0;
}