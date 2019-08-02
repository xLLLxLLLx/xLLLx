#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 110, mod = 998244353;
ll f[N][N][N];
int a[N], b[N], vis[N], pa[N], pb[N];

int dfs(int x, int l, int r){
  if(f[x][l][r] != -1) return 0;
  f[x][l][r] = 0;
  if(l == r) {
  	f[x][l][r] = 1;
  	if(a[x] != b[l]) {
  		if(a[x] && b[l]) {
  			f[x][l][r] = 0;
  		} else if(a[x] && pb[a[x]]) {
  			f[x][l][r] = 0;
  		} else if(b[l] && pa[b[l]]) {
  			f[x][l][r] = 0;
  		}
  	}
  	return 0;
  }
  if(r + 1 == l) f[x][l][r] = 1;
  if(r < l) return 0;
  if(a[x]) {
  	if(pb[a[x]]) {
  		if(pb[a[x]] < l || pb[a[x]] > r) {
  			f[x][l][r] = 0;
  		} else {
  			dfs(x + 1, l, pb[a[x]] - 1);
  			dfs(x + pb[a[x]] - l + 1, pb[a[x]] + 1, r);
  			f[x][l][r] = f[x + 1][l][pb[a[x]] - 1] * f[x + pb[a[x]] - l + 1][pb[a[x]] + 1][r] % mod;
  		}
  		return 0;
  	}
  	int maxn = l;
  	for(int i = l; i <= r; ++i) {
  		if(pa[b[i]]) {
  			if(pa[b[i]] < x || pa[b[i]] > x + r - l) break;
  			maxn = max(maxn, l + pa[b[i]] - x);
  		}
  		if(b[i]) continue;
  		if(i < maxn) continue;
  		dfs(x + 1, l, i - 1);
  		dfs(x + i - l + 1, i + 1, r);
  		f[x][l][r] = (f[x][l][r] + f[x + 1][l][i - 1] * f[x + i - l + 1][i + 1][r]) % mod;
  	}
  	return 0;
  }
    
  int maxx = l;
      
  for(int i=l;i<=r;i++){
    if(pa[b[i]]){
        if(pa[b[i]] < x || pa[b[i]] > x + r - l)break;
        maxx = max(maxx, l + pa[b[i]] - x);
    }
    if(i < maxx)continue;
    dfs(x + 1, l, i - 1);
    dfs(x + i - l + 1, i + 1, r);
    f[x][l][r] = (f[x][l][r] + f[x + 1][l][i - 1] * f[x + i - l + 1][i + 1][r]) % mod;
  }
    
  return 0;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		memset(vis, 0, sizeof vis);
		memset(pa, 0, sizeof pa);
		memset(pb, 0, sizeof pb);
		memset(f, -1, sizeof f);
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			if(a[i]) {
				vis[a[i]] = 1;
				pa[a[i]] = i;
			}
		}
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &b[i]);
			if(b[i]) {
				vis[b[i]] = 1;
				pb[b[i]] = i;
			}
		}
		dfs(1, 1, n);
		// for(int i = 1; i <= n; ++i)
		// 	for(int j = 1; j <= n; ++j)
		// 		for(int k = 1; k <= n; ++k) {
		// 			if(dp[i][j][k] != -1) printf("dp[%d][%d][%d]=%d\n", i, j, k, dp[i][j][k]);
		// 		}
		ll ans = f[1][1][n];
		int cnt = 0;
		for(int i = 1; i <= n; ++i) {
			cnt += (vis[i] == 0);
		}
		for(int i = 1; i <= cnt; ++i) {
			ans = 1ll * ans * i % mod;
		}
		printf("%lld\n", ans);
	}
	return 0;
}