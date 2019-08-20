#include <bits/stdc++.h>
using namespace std;
const int N = 110, M = 1e5 + 10;
int pr[N], flg[M], a[N][N], b[N];

void init() {
	for(int i = 2; i < M; ++i) {
		if(!flg[i]) pr[++pr[0]] = i;
		if(pr[0] >= 100) return ;
		for(int j = 1; j <= pr[0]; ++j) {
			if(i * pr[j] >= M) break;
			flg[i * pr[j]] = 1;
			if(i % pr[j] == 0) break;
		}
	}
}

void up() {
	b[0]++;
	for(int i = 1; i <= b[0]; ++i) {
		b[i] *= 2;
	}
	for(int i = 1; i <= b[0]; ++i) {
		b[i + 1] += b[i] / 10;
		b[i] %= 10;
	}
	while(b[0] > 1 && !b[b[0]]) --b[0];
}

void q_pow(int x) {
	for(int i = 1; i <= x; ++i) {
		up();
	}
}

void down() {
	b[1]--;
	for(int i = 1; i <= b[0]; ++i) {
		if(b[i] < 0) {
			b[i + 1] --;
			b[i] += 10;
		}
	}
	while(b[0] > 1 && !b[b[0]]) --b[0];
}

int ans = 0;
int n, m;

void Swap(int x, int y) {
	for(int i = 1; i <= m; ++i)
		swap(a[x][i], a[y][i]);
}

void cut(int x, int y) {
	for(int i = 1; i <= m; ++i)
		a[y][i] ^= a[x][i];
}

void go() {
	int pos = 1;
	for(int i = 1; i <= m; ++i) {
		if(pos > n) break;
		for(int k = pos; k <= n; ++k) {
			if(a[k][i]) {
				Swap(pos, k);
				for(int j = 1; j <= n; ++j)
					if(j != pos && a[j][i]) {
						for(int l = 1; l <= m; ++l)
							a[j][l] ^= a[pos][l];
					}
				++pos;
				break;
			}
		}
	}
	// printf("%d\n", pos);
	ans = m - pos + 1;
}

int main() {
	freopen("rsa.in", "r", stdin);
	freopen("rsa.out", "w", stdout);
	init();
	scanf("%d%d", &n, &m);
	for(int i = 1, x; i <= m; ++i) {
		scanf("%d", &x);
		for(int j = 1; j <= n; ++j) {
			while(x % pr[j] == 0) {
				x /= pr[j];
				a[j][i] ^= 1;
			}
		}
	}
	go();
	b[0] = b[1] = 1;
	q_pow(ans), down();
	for(int i = b[0]; i >= 1; --i)
		printf("%d", b[i]);
	puts("");
	return 0;
}