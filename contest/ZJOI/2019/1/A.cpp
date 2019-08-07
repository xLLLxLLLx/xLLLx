#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;

inline void Add(int &x, int y) {
	x += y;
	if(x >= mod) x -= mod;
}

inline void Mul(int &x, int y) {
	x = (int)((long long)x * y % mod);
}

inline int mul(int x, int y) {
  return (long long)x * y % mod;
}

int q_pow(int x, int y) {
	int ans = 1;
	for(; y; y >>= 1) {
		if(y & 1)
			Mul(ans, x);
		Mul(x, x);
	}
	return ans;
}

struct Mask {
	int a[2][3][3], cnt;

	Mask() {
		memset(a, -1, sizeof a);
		a[0][0][0] = 0;
		cnt = 0;
	}

	inline bool operator < (const Mask &C) const {
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 3; ++j)
				for(int k = 0; k < 3; ++k)
					if(a[i][j][k] != C.a[i][j][k])
						return a[i][j][k] < C.a[i][j][k];
		return cnt < C.cnt;
	}

	inline Mask trans(int c) {
		Mask now;
		now.cnt = cnt + (c >= 2);
		memset(now.a, -1, sizeof now.a);
		for(int i = 0; i < 3; ++i)
			for(int j = 0; j < 3; ++j)
				for(int k = 0; k < 3; ++k) {
					if(i + j + k <= c) {
						if(~a[0][k][i]) 
							now.a[0][i][j] = max(now.a[0][i][j], a[0][k][i] + k + (c - (k + i + j)) / 3);
						if(~a[1][k][i])
							now.a[1][i][j] = max(now.a[1][i][j], a[1][k][i] + k + (c - (k + i + j)) / 3);
					}
				}
		if(c >= 2) {
			for(int i = 0; i < 3; ++i)
				for(int j = 0; j < 3; ++j)
					for(int k = 0; k < 3; ++k) {
						if(i + j + k + 2 <= c) {
							if(~a[0][k][i])
								now.a[1][i][j] = max(now.a[1][i][j], a[0][k][i] + k + (c - (k + i + j + 2)) / 3);
						}
					}
		}
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 3; ++j)
				for(int k = 0; k < 3; ++k)
					now.a[i][j][k] = min(now.a[i][j][k], 4);
		now.cnt = min(now.cnt, 7);
		return now;
	}

	bool check() {
		bool f = false;
		for(int i = 0; i < 3; ++i)
			for(int j = 0; j < 3; ++j)
				f |= (a[1][i][j] == 4);
		f |= (cnt == 7);
		return f;
	}
};

const int N = 4010, M = 5;
map <Mask, int> mp;
queue<Mask> q;
int tot = 0, trans[N][M], b[N];

inline void bfs() {
	mp[Mask()] = ++tot, q.push(Mask());
	b[tot] = Mask().check();
	while(!q.empty()) {
		Mask x = q.front(); q.pop();
		for(int i = 0; i < M; ++i) {
			Mask y = x.trans(i);
			if(mp.find(y) == mp.end())
				mp[y] = ++tot, q.push(y), b[tot] = y.check();
			trans[mp[x]][i] = mp[y];
		}
	}
	// printf("tot = %d\n", tot);
	// for(int i = 1; i <= tot; ++i)
	// 	for(int j = 0; j < M; ++j)
	// 		printf("trans[%d][%d]=%d\n", i, j, trans[i][j]);
}

const int K = 510;
int dp[2][N][K];
int jc[K] = {1}, ny[K] = {1}, cnt[K], d[K];

int C(int x, int y) {
	return mul(jc[x], mul(ny[y], ny[x - y]));
}

int main() {
	bfs();
	int n;
	scanf("%d", &n);
	for(int i = 1, x, y; i <= 13; ++i) {
		scanf("%d%d", &x, &y);
		cnt[x]++;
	}
	for(int i = 1; i <= 4 * n; ++i)
		jc[i] = mul(jc[i - 1], i);
	ny[4 * n] = q_pow(jc[4 * n], mod - 2);
	for(int i = 4 * n - 1; i >= 1; --i)
		ny[i] = mul(ny[i + 1], i + 1);
	// for(int i = 0; i <= 4 * n; ++i) {
	// 	printf("%d %d %d\n", jc[i], ny[i], 1ll * jc[i] * ny[i] % mod);
	// }
	dp[0][1][0] = 1;
	int now = 0;
	for(int i = 1; i <= n; ++i) {
		now ^= 1;
		memset(dp[now], 0, sizeof dp[now]);
		for(int j = 1; j <= tot; ++j)
			for(int k = 0; k <= 4 * (i - 1); ++k) {
				for(int c = 0; c <= 4 - cnt[i]; ++c) {
					if(!dp[now ^ 1][j][k]) continue;
					int pos = mul(C(4 - cnt[i], c), mul(C(k + c, c), jc[c]));
					// printf("%d\n", pos);
					Add(dp[now][trans[j][c + cnt[i]]][k + c], mul(pos, dp[now ^ 1][j][k]));
				}
			}
		// for(int j = 1; j <= tot; ++j)
		// 	for(int k = 0; k <= 4 * i; ++k)
		// 		if(dp[now][j][k])
		// 			printf("dp[%d][%d][%d]=%d\n", i, j, k, dp[now][j][k]);
	}
	// for(int i = 1; i <= tot; ++i) {
	// 	if(!b[i]) {
	// 		printf("%d\n", i);
	// 	}
	// }
	for(int j = 1; j <= tot; ++j)
		for(int k = 0; k <= 4 * n - 13; ++k) {
			if(!b[j]) {
				Add(d[k], dp[now][j][k]);
			}
		}
	int ans = 0;
	for(int i = 0; i <= 4 * n - 13; ++i)
		Add(ans, mul(d[i], q_pow(mul(C(4 * n - 13, i), jc[i]), mod - 2)));
	printf("%d\n", ans);
	return 0;
}