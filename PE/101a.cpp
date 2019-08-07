#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 20;
double xs[N][N];
ll a[N], b[N], sum = 0;

void cut(int x, int y, int n) {
	double res = xs[y][x] / xs[x][x];
	for(int i = 0; i <= n + 1; ++i) {
		xs[y][i] -= res * xs[x][i];
	}
}

bool check(int n) {
	for(int i = 1; i <= 11; ++i) {
		ll res = 1, pos = 0;
		for(int j = 0; j <= n; ++j) {
			pos += b[j] * res;
			res *= 1ll * i;
		}
		if(pos != a[i]) {
			printf("WAI!!!%d %lld\n", i, pos);
			sum += pos;
			return false;
		}
	}
	return true;
}

void get(int n) {
	for(int i = 0; i <= n; ++i) {
		for(int j = 0; j <= n; ++j) {
			if(j != i && xs[j][i]) {
				cut(i, j, n);
			}
		}
	}
	for(int i = 0; i <= n; ++i) {
		double tmp = xs[i][n + 1] / xs[i][i];
		ll pos = 0;
		if(tmp < 0)
			pos = (long long)(tmp - 0.5);
		else 
			pos = (long long)(tmp + 0.5);
		b[i] = pos;
		cout << pos << " ";
	}
	puts("");
	if(!check(n)) {
		// puts("NO!\n");
	}
	puts("");
}

int main() {
	for(int i = 1; i <= 11; ++i)
		scanf("%lld", &a[i]);
	for(int i = 1; i <= 10; ++i) {
		for(int v = 1; v <= i + 1; ++ v) {
			ll res = 1;
			for(int j = 0; j <= i; ++j) {
				xs[v - 1][j] = res;
				res *= 1ll * v;
			}
			xs[v - 1][i + 1] = a[v];
		}
		get(i);
	}
	printf("%lld\n", sum);
	return 0;
}