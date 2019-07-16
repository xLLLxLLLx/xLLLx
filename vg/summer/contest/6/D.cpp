#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5050;
int f[N];
ll q[N], p[N];

bool check(int x, int y) {
	if(q[x] % q[y]) return false;
	return p[y] - p[x] == y - x || p[y] < y - x;
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		ll x;
		cin >> x;
		p[i] = 0;
		while(x % 2 == 0) p[i]++, x /= 2;
		q[i] = x;
	}
	memset(f, 0x3f, sizeof f);
	f[0] = 0, q[n] = 1;
	for(int i = 1; i <= n; ++i) {
		f[i] = i;
		for(int j = 0; j < i; ++j) {
			if(check(j, i)) {
				f[i] = min(f[i], f[j] + i - j - 1);
			}
		}
	}
	printf("%d\n", f[n]);
	return 0;
}