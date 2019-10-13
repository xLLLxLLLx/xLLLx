#include <cstring>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int maxn = 3e5 + 10;
typedef pair<int,int> pii;
int n, q, u, v;
int x, y, z;
int indg[maxn], a[maxn], cnt, dfn[maxn];
vector<int> E[maxn];
int dis[1010][1010];
bool visited[1010];
queue<int> Q;
void dfs(int x, int f){
    dfn[x] = ++cnt;
    a[cnt] = x;
    for(auto i = E[x].begin(); i != E[x].end(); i++){
        if(*i != f) dfs(*i, x);
    }
}
void query1(int x, int y, int z){
    int stck[3], ans[3];
    stck[0] = dfn[x], stck[1] = dfn[y], stck[2] = dfn[z];
    sort(stck, stck+3);
    int mid1 = (stck[1] - stck[0] - 1) >> 1;
    int mid2 = (stck[2] - stck[1] - 1) >> 1;
    ans[0] = stck[0] + mid1;
    ans[1] = mid1 + mid2 + 1;
    ans[2] = mid2 + (n - ans[2] + 1);
    int ansx, ansy, ansz;
    if(x == a[stck[0]]) ansx = ans[0];
    if(x == a[stck[1]]) ansx = ans[1];
    if(x == a[stck[2]]) ansx = ans[2];
    if(y == a[stck[0]]) ansy = ans[0];
    if(y == a[stck[1]]) ansy = ans[1];
    if(y == a[stck[2]]) ansy = ans[2];
    if(z == a[stck[0]]) ansz = ans[0];
    if(z == a[stck[1]]) ansz = ans[1];
    if(z == a[stck[2]]) ansz = ans[2];
    printf("%d %d %d\n", ansx, ansy, ansz);
}
void BFS(int x){
    Q.push(x);
    visited[x] = true;
    while(!Q.empty()){
        int y = Q.front();
        //int len = Q.front().second;
        Q.pop();
        for(auto i = E[y].begin(); i != E[y].end(); i++){
            if(!visited[*i]){
                visited[*i] = true;
                dis[x][*i] = dis[x][y] + 1;
                Q.push(*i);
            }
        }
    }
}
void query(int x, int y, int z){
    int ansx = 0, ansy = 0, ansz = 0;
    pii tmp[3];
    for(int i = 1; i <= n; i++){
        tmp[0] = make_pair(dis[x][i], x);
        tmp[1] = make_pair(dis[y][i], y);
        tmp[2] = make_pair(dis[z][i], z);
        sort(tmp, tmp+3);
        if(tmp[0].first == tmp[1].first) continue;
        if(tmp[0].second == x) ansx++;
        if(tmp[0].second == y) ansy++;
        if(tmp[0].second == z) ansz++;
    }
    printf("%d %d %d\n", ansx, ansy, ansz);
}
int main(){
    scanf("%d", &n);
    for(int i = 1; i < n; i++){
        scanf("%d%d", &u, &v);
        E[u].push_back(v);
        E[v].push_back(u);
        indg[u]++, indg[v]++;
    }
    if(n <= 1000){
        scanf("%d", &q);
        for(int i = 1; i <= n; i++){
            memset(visited, 0, sizeof(visited));
            BFS(i);
        }
        //cerr << "OK<" << endl;
        for(int i = 1; i <= q; i++){
            scanf("%d%d%d", &x, &y, &z);
            query(x, y, z);
        }
        return 0;
    }else{
        int rt = 1;
        for(int i = 1; i <= n; i++)
            if(indg[i] == 2){rt = i; break;}
        dfs(rt, 0);
        scanf("%d", &q);
        for(int i = 1; i <= q; i++){
            scanf("%d%d%d", &x, &y, &z);
            query1(x, y, z);
        }
    }
    return 0;
}