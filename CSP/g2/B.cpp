#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 20;
int len;
ll mx = 1e18, ma, mb;
int a[N], b[N], na[N], nb[N], da[N], db[N];
char lx[N], ly[N];

ll Abs(ll x) {
  if(x < 0) return -x;
  else return x;
}

void dfs(int dep, int lmt) {
  if(dep > len) {
    ll va = 0, vb = 0;
    for(int i = 1; i <= len; ++i) {
      va = (va << 1) + (va << 3) + na[i];
      vb = (vb << 1) + (vb << 3) + nb[i];
    }
    ll pos = Abs(va - vb);
    if(pos < mx || (pos == mx && (va < ma || (va == ma && vb < mb)))) {
      mx = pos, ma = va, mb = vb;
      for(int i = 1; i <= len; ++i) {
        da[i] = na[i];
        db[i] = nb[i];
      }
    } 
    return ;
  }
  int la = na[dep], lb = nb[dep];
  if(na[dep] == -1) na[dep] = lmt ? 0 : 9;
  if(nb[dep] == -1) nb[dep] = lmt ? 9 : 0;
  dfs(dep + 1, lmt);
  na[dep] = la, nb[dep] = lb;
}

int main() {
  int T;
  scanf("%d", &T);
  for(int o = 1; o <= T; ++o) {
    mx = 1e18;
    scanf("%s%s", lx + 1, ly + 1);
    len = strlen(lx + 1);
    for(int i = 1; i <= len; ++i) {
      if(lx[i] == '?') a[i] = -1;
      else a[i] = lx[i] - '0';
      if(ly[i] == '?') b[i] = -1;
      else b[i] = ly[i] - '0';
    }
    for(int i = 1; i <= len; ++i) na[i] = a[i], nb[i] = b[i];
    for(int i = 1; i <= len; ++i) {
      if(a[i] != -1 && b[i] != -1 && a[i] != b[i]) { 
        dfs(i + 1, a[i] > b[i]);
        break;
      }
      if(a[i] == -1 && b[i] == -1) {
        na[i] = 1, nb[i] = 0, dfs(i + 1, 1);
        na[i] = 0, nb[i] = 1, dfs(i + 1, 0);
        na[i] = nb[i] = 0;
      }
      if(a[i] == -1 && b[i] != -1) {
        if(b[i] != 0) na[i] = nb[i] - 1, dfs(i + 1, 0);
        if(b[i] != 9) na[i] = nb[i] + 1, dfs(i + 1, 1);
        na[i] = nb[i];
      }
      if(a[i] != -1 && b[i] == -1) {
        if(a[i] != 0) nb[i] = na[i] - 1, dfs(i + 1, 1);
        if(a[i] != 9) nb[i] = na[i] + 1, dfs(i + 1, 0);
        nb[i] = na[i];
      }
    }
    int flg = 1;
    for(int i = 1; i <= len; ++i) {
      if(na[i] != nb[i]) {
        flg = 0;
        break;
      }
    }
    if(flg) {
      for(int i = 1; i <= len; ++i) {
        da[i] = na[i], db[i] = nb[i];
      }
    }
    printf("Case #%d: ", o);
    for(int i = 1; i <= len; ++i) printf("%d", da[i]);
    printf(" ");
    for(int i = 1; i <= len; ++i) printf("%d", db[i]);
    puts("");
  }
  return 0;
}