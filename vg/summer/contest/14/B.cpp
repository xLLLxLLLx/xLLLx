#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
struct data {
	int nt, to;
} a[N];
int cnt = 0, ans = 0;
int head[N], dp[N], d[N], vis[N];
queue<int> q;

void add(int x, int y) {
	d[x]++, d[y]++;
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void dfs(int u) {
	vis[u] = 1;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		dfs(to);
		ans = max(ans, dp[u] + dp[to] + 1);
		dp[u] = max(dp[u], dp[to] + 1);
	}
}

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	int L = 0;
	for(int i = 1; i <= n; ++i) {
		if(k + (n - k) * i > 2 * (n - 1)) break;
		L = i;
	}
	int pos = 2 * (n - 1) - (k + (n - k) * L), tmp = n - k - pos;
	// printf("%d %d %d\n", L, pos, tmp);
	for(int i = 1; i <= n; ++i) {
		if(i <= k) {
			q.push(i);
			continue;
		}
		if(i == n) L++;
		if(tmp) {
			for(int j = 1; j < L; ++j) {
				int h = q.front(); q.pop();
				add(i, h);
			}
			tmp--;
		} else {
			for(int j = 1; j <= L; ++j) {
				int h = q.front(); q.pop();
				add(i, h);
			}
		}
		q.push(i);
	}	
	dfs(n);
	// printf("%d\n", ans);
	// for(int u = 1; u <= n; ++u) {
	// 	for(int i = head[u]; i; i = a[i].nt) {
	// 		printf("%d %d\n", u, a[i].to);
	// 	}
	// }
	int count = 0, zz = 0, flg = 0;
	for(int i = 1; i <= n; ++i) {
		count += (d[i] == 1);
		zz += (d[i] >= 2);
		if(!vis[i]) {
			flg = 1;
		}
	}
	if(count != k || zz != n - k || flg) printf("WAI!\n");
	else printf("Yes\n");
	return 0;
}