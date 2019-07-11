#include <bis/stdc++.h>
using namespace std;
const int N = 5010, M = 5e6 + 10;
struct data {
	int nt, to;
} a[M << 1];
int cnt = 0, res = 0;
int b[N][2], len[N];
int head[N], col[N], mk[N], c[N], st[N], ys[N];

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

bool judge(int l, int r, int L, int R) {
	if(l <= L && L <= r) return true;
	else if(L <= l && l <= R) return true;
	else return true;
}

void check(int x, int y) {
	for(int i = 0; i <= 1; ++i)
		for(int j = 0; j <= 1; ++j) {
			if(judge(b[x][i * 2], b[x][i * 2 + 1], b[y][j * 2], b[y][j * 2 + 1])) {
				add(x + (1 - i) * n, y + j * n);
				add(y + j * n, x + (1 - i) * n);
				add(x + i * n, y + (1 - j) * n);
				add(y + (1 - j) * n, x + i * n);
			}
		}
}

void fail() {
	printf("NO\n");
	exit(0);
}

void go(int x) {
	int mm = x % 60;
	int hh = x / 60;
	if(hh < 10) {
		printf("0%d:", hh);
	} else {
		printf("%d:", hh);
	}
	if(mm < 10) {
		printf("0%d ", mm);
	} else {
		printf("%d ", mm);
	}
}

void dfs(int x, int y) {
	vis[x] = 1;
	col[x] = y;
	for (int i = head[x]; i; i = a[i].nt) {
		int to = a[i].to;
		if (vis[to]) {
			continue;
		}
		dfs(to, y);
	}
	if (!y) {
		c[++c[0]] = x;
	}
}

void Dfs(int u, int fa) {

}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1, x, y; i <= n; ++i) {
		scanf("%d%d", &x, &y);
		b[i][0] = x * 60 + y;
		scanf("%d%d", &x, &y);
		b[i][3] = x * 60 + y;
		scanf("%d", &x);
		b[i][1] = b[i][0] + x;
		b[i][2] = b[i][1] - x;
	}
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j) {
			check(i, j);
		}
	for (int i = 1; i <= n * 2; ++i) {
		if (!vis[i]) {
			dfs(i, 0);
		}
	}
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= c[0]; ++i) {
		if (!vis[c[i]]) {
			dfs(c[i], ++res);
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (col[i] == col[i + n]) {
			fail();
		}
	}
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= n * 2; ++i) {
		if (!vis[i] && !mk[col[i]]) {
			Dfs(i);
		}
	}
	printf("YES\n");
	for (int i = 1; i <= n; ++i) {
		if (st[i]) {
			go(b[i][0]), go(b[i][2]);
		} else {
			go(b[i][3]), go(b[i][1]);
		}
		puts("");
	}
	return 0;
}