#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 310;
ll ans = 0;
int dis[N][N];
int n;

void Min(int &x, int y) {
  if(x == -1) x = y;
  else x = min(x, y);
}

void floyd(int k) {
  for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= n; ++j)
      if(dis[i][k] != -1 && dis[k][j] != -1)
        Min(dis[i][j], dis[i][k] + dis[k][j]);
}

void work(int l, int r) {
  if(l == r) {
    for(int i = 1; i <= n; ++i)
      for(int j = 1; j <= n; ++j)
        if(i != l && j != l) ans += dis[i][j];
    return ;
  }
  int mid = (l + r) >> 1;
  int w[N][N];
  memcpy(w, dis, sizeof w);
  for(int i = mid + 1; i <= r; ++i)
    floyd(i);
  work(l, mid);
  memcpy(dis, w, sizeof dis);
  for(int i = l; i <= mid; ++i)
    floyd(i);
  work(mid + 1, r);
}

int main() {
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) 
    for(int j = 1; j <= n; ++j)
      scanf("%d", &dis[i][j]);
  work(1, n);
  printf("%lld\n", ans);
  return 0;
}