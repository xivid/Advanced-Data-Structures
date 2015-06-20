#include <iostream>
#include <cstring>
#define MAXN 1000
using namespace std;

int dist[MAXN][MAXN];
int sp[MAXN][MAXN];
inline int min(int x, int y) {return x < y ? x : y;}
bool Floyed(int sp[][MAXN], int dist[][MAXN], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; ++j)
                sp[i][j] = dist[i][j];
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (sp[i][k] < 0x7f7f7f7f && sp[k][j] < 0x7f7f7f7f)
                    sp[i][j] = min(sp[i][j], sp[i][k] + sp[k][j]);
    for (int i = 0; i < n; ++i)
        if (sp[i][i] < 0)
            return false;
    return true;
}

int main() {
    int n, m, u, v, w;
    memset(dist, 0x7f, sizeof(dist)); //INF
    memset(sp, 0, sizeof(sp));
    cout << "Input number of nodes and number of edges: ";
    cin >> n >> m;
    cout << "Input " << m << " edges(u, v, w):" << endl;
    for (int i = 0; i < m; ++i)
    {
        cin >> u >> v >> w;
        dist[u-1][v-1] = w;
        //dist[v-1][u-1] = w; //non-direct
    }
    for (int i = 0; i < n; ++i)
        dist[i][i] = 0;

    if(Floyed(sp, dist, n))
    {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j){
                cout << "The shortest path from " << i + 1 << " to " << j + 1 << " is ";
                if (sp[i][j] == 0x7f7f7f7f) cout << "INF" << endl;
                else cout << sp[i][j] << endl;
            }
    }
    else
        printf("There exists cycle(s) with negative weight.\n");
    return 0;
}