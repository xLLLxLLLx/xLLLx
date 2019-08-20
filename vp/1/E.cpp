#include <bits/stdc++.h>
using namespace std;
const int N = 110, M = 32;
struct data {
	data() {
		memset(a, 0, sizeof a);
	}
	void print(int x) {
		for(int i = 0; i < x; ++i) {
			for(int j = 0; j < x; ++j)
				printf("%d ", a[i][j]);
			puts("");
		}
	}
	int a[M][M];
} S;
char lx[N];
int xs[N];
int n, m, mod;

int a[N], b[N];

int add(int x, int y) {
	return (x + y) % mod;
}

void Add(int &x, int y) {
	x = add(x, y);
}

int mul(int x, int y) {
	return 1ll * x * y % mod;
}

bool check(int x, int y) {
	for(int i = 0; i < m; ++i) a[i] = (x >> i) & 1;
	for(int i = 0; i < m; ++i) b[i] = (y >> i) & 1;
	for(int i = 1; i < m; ++i) {
		if(a[i] && a[i - 1] && b[i] && b[i - 1]) return false;
		if(!a[i] && !a[i - 1] && !b[i] && !b[i - 1]) return false;
	}
	return true;
}

int c[N];
void cut() {
	c[0] = xs[0];
	for(int i = xs[0]; i >= 1; --i) {
		c[i] = xs[i] / 2;
		xs[i - 1] += (xs[i] & 1) * 10;
	}
	while(c[0] > 1 && !c[c[0]]) --c[0];
	for(int i = 0; i <= c[0]; ++i)
		xs[i] = c[i];
	// for(int i = c[0]; i >= 1; --i)
	// 	printf("%d", c[i]);
	// puts("");
}

data Mul(data A, data B) {
	data res;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j) {
			res.a[i][j] = 0;
			for(int k = 0; k < n; ++k) 
				Add(res.a[i][j], mul(A.a[i][k], B.a[k][j]));
		}
	return res;
}

int q_pow() {
	data ans;
	for(int i = 0; i < n; ++i)
		ans.a[i][i] = 1;
	for(;xs[0] > 1 || xs[xs[0]]; cut()) {
		if(xs[1] & 1) ans = Mul(ans, S);
		S = Mul(S, S);
		// S.print(n);
	}
	// ans.print(n);
	int pos = 0;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			Add(pos, ans.a[i][j]);
	return pos;
}

void down() {
	xs[1]--;
	for(int i = 1; i <= xs[0]; ++i) {
		if(xs[i] < 0) {
			xs[i + 1]--;
			xs[i] += 10;
		}
	}
	while(xs[0] > 1 && !xs[xs[0]]) xs[0]--;
}

int main() {
	freopen("nice.in", "r", stdin);
	freopen("nice.out", "w", stdout);
	scanf("%s%d%d", lx + 1, &m, &mod);
	int len = strlen(lx + 1);
	xs[0] = len;
	for(int i = len; i >= 1; --i)
		xs[len - i + 1] = lx[i] - '0';
	down();
	n = (1 << m);
	if(xs[0] == 1 && !xs[xs[0]]) {
		return printf("%d\n", n), 0;
	}
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j) {
			if(check(i, j)) S.a[i][j] = 1;
		}
	// S.print(n);
	printf("%d\n", q_pow());
	return 0;
}