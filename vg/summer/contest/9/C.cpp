#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
ll a[N], b[N];
vector<int> g[N];
int c[N], now[N];

void fail() {
	puts("No");
	exit(0);
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
	}
	sort(a + 1, a + 1 + n);
	for(int i = 2; i <= n; ++i) {
		for(int j = 60; j >= 0; --j) {
			if((a[i] >> j) & 1) {
				g[j].push_back(i);
				break;
			}
		}
	}
	for(int i = 0; i <= 60; ++i) {
		now[i] = 1;
	}
	b[1] = a[1];
	ll pos = a[1];
	for(int i = 2; i <= n; ++i) {
		for(int j = 60; j >= 0; --j) {
			c[j] = (pos >> j) & 1;
		}
		int flg = 0;
		for(int j = 0; j <= 60; ++j) {
			if(!c[j]) {
				// printf("nn!\n");
				if(g[j].size() >= now[j]) {
					flg = 1;
					b[i] = a[g[j][now[j] - 1]];
					now[j]++;
					break;
				}
			}
		}
		if(!flg) fail();
		pos ^= b[i];
	}
	puts("Yes");
	for(int i = 1; i <= n; ++i) {
		printf("%lld ", b[i]);
	}
	return 0;
}