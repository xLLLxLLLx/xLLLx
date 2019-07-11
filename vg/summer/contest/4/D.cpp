#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
char lx[N];
int h[N][N], s[N][N], a[N][N];
int n, m, k;

void fail() {
	printf("NO\n");
	exit(0);
}

void out() {
	printf("YES\n");
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			printf("%d ", a[i][j] + 1);
		}
		puts("");
	}
	exit(0);
}

void revh(int x) {
	for(int i = 1; i <= m; ++i) a[x][i] = 1 - a[x][i];
}

void revs(int x) {
	for(int i = 1; i <= n; ++i) a[i][x] = 1 - a[i][x];
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	int H = 0, S = 0;
	for(int o = 1; o < n * 2; ++o) {
		scanf("%s", lx + 1);
		int len = strlen(lx + 1);
		if(o & 1) {
			++H;
			for(int i = 1; i <= len; ++i) {
				h[H][i] = (lx[i] == 'E');
			}
		} else {
			++S;
			for(int i = 1; i <= len; ++i) {
				s[S][i] = (lx[i] == 'E');
			}
		}
	}
	if(k == 1) {
		int pos = 0, tot = 2 * m * n - m - n;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j < m; ++j) {
				int tmp = (a[i][j] == a[i][j + 1]);
				pos += (tmp != h[i][j]);
			}
		for(int i = 1; i < n; ++i)
			for(int j = 1; j <= m; ++j) {
				int tmp = (a[i][j] == a[i + 1][j]);
				pos += (tmp != s[i][j]);
			}
		if(pos * 4 > tot) fail();
		else out();
	} else if(n <= m) {
		for(int i = 1; i <= n; ++i) {
			for(int j = 2; j <= m; ++j) {
				if(!h[i][j - 1]) {
					a[i][j] = 1 - a[i][j - 1];
				} else {
					a[i][j] = a[i][j - 1];
				}
			}
			if(i > 1) {
				int pos = 0;
				for(int j = 1; j <= m; ++j) {
					int tmp = (a[i][j] == a[i - 1][j]);
					pos += (tmp != s[i - 1][j]);
				}
				// printf("%d %d\n",i ,pos);
				if(pos > m / 2) revh(i);
			}
		}
		out();
	} else {
		for(int j = 1; j <= m; ++j) {
			for(int i = 2; i <= n; ++i) {
				if(!s[i - 1][j]) {
					a[i][j] = 1 - a[i - 1][j];
				} else {
					a[i][j] = a[i - 1][j];
				}
			}
			if(j > 1) {
				int pos = 0;
				for(int i = 1; i <= n; ++i) {
					int tmp = (a[i][j] == a[i][j - 1]);
					pos += (tmp != h[i][j - 1]);
				}
				if(pos > n / 2) revs(j);
			}
		}
		out();
	}
	return 0;
}