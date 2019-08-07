#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, M = 4e5 + 10, LOG = 20;
int n, m;
struct data {
	int fr, to, l, h;
} a[M];
struct node {
	int to, w;
};
vector<data> b[N];
int dp[N], dis[N], qx[N][LOG + 1];

void adde(int x, int y, int l, int w) {
	b[x].push_back((data){x, y, l, w});
	b[y].push_back((data){y, x, l, w});
}

bool cmp(data A, data B) {
	return A.l < B.l;
}

typedef pair<int, int> P;
priority_queue<P, vector<P>, greater<P> > que;

void dij() {
	memset(dis, 0x3f, sizeof dis);
	dis[1] = 0;
	que.push(P(0, 1));
	while(!que.empty()) {
		P h = que.top(); que.pop();
		int w = h.first, v = h.second;
		if(w > dis[v]) continue;
		for(int i = 0; i < b[v].size(); ++i) {
			int to = b[v][i].to, val = b[v][i].l;
			if(dis[to] > w + val) {
				dis[to] = w + val;
				que.push(P(dis[to], to));
			}
		}
	}
}

queue<int> Q;

int main() {
	freopen("return.in", "r", stdin);
	freopen("return.out", "w", stdout);
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
			b[i].clear();
		memset(qz, 0, sizeof qz);
		int flg1 = 1, val = 0, flg2 = 1;
		for(int i = 1, x, y, l, h; i <= m; ++i) {
			scanf("%d%d%d%d", &x, &y, &l, &h);
			if(!val) val = h;
			if(h != val) flg1 = 0;
			if(y != x + 1) flg2 = 0;
			a[i] = ((data){x, y, l, h});
			adde(a[i].fr, a[i].to, a[i].l, a[i].h);
		}
		int q, k, s;
		scanf("%d%d%d", &q, &k, &s);
		if(flg1) {
			dij();
			int ans = 0;
			for(int i = 1, x, y; i <= q; ++i) {
				scanf("%d%d", &x, &y);
				x = (x + k * ans - 1) % n + 1;
				y = (y + k * ans) % (s + 1);
				if(y < val) {
					ans = 0;
				} else {
					ans = dis[x];
				}
				printf("%d\n", ans);
			}
		} else if(flg2) {
			for(int i = 1; i <= m; ++i) {
				int u = a[i].fr, v = a[i].to;
				qx[v][0] = a[i].h;
				dis[v] = a[i].l;
			}
			for(int i = 1; i <= n; ++i)
				dis[i] += dis[i - 1];
			for(int j = 1; j <= LOG; ++j) 
				for(int i = 1; i <= n; ++i) {
					if(i - (1 << (j - 1))<0) continue;
					qx[i][j] = min(qx[i][j - 1], qx[i - (1 << (j - 1))][j - 1]);
				}
			int ans = 0;
			for(int i = 1, x, y; i <= q; ++i) {
				scanf("%d%d", &x, &y);
				x = (x + k * ans - 1) % n + 1;
				y = (y + k * ans) % (s + 1);
				int pos = 0;
				for(int i = LOG; i >= 0; --i) {
					if(qx[x][i] > y)
						x = x - (1 << i);
					else {
						pos = max(pos, x - (1 << i));
					}
				}
				if(x == 1) {
					ans = 0;
				} else {
					ans = dis[pos + 1];
				}
				printf("%d\n", ans);
			}
		} else if(n <= 1500) {
			dij();
			int ans = 0;
			for(int i = 1, x, y; i <= q; ++i) {
				scanf("%d%d", &x, &y);
				x = (x + k * ans - 1) % n + 1;
				y = (y + k * ans) % (s + 1);
				memset(dp, -1, sizeof dp);
				Q.push(x);dp[x] = 0;
				while(!Q.empty()) {
					int h = Q.front(); Q.pop();
					for(int i = 0; i < b[h].size(); ++i) {
						int to = b[h][i].to, w = b[h][i].h;
						if(w > y && dp[to] == -1) {
							dp[to] = 0;
							Q.push(to);
						}
					}
				}
				int pos = 2e9;
				for(int i = 1; i <= n; ++i) {
					if(!dp[i]) 
						pos = min(pos, dis[i]);
				}
				ans = pos;
				printf("%d\n", ans);
			}
		}
	}
	return 0;
}