#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e5 + 10;
ll f[N];
vector<int> g;
int p[N], t[N];

void go(int x) {
	int gg = min(p[x], p[x + 1]);
	if(!gg) return ;
	g.push_back(x);
	p[x] -= gg, p[x + 1] -= gg;
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &p[i]);
	}
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	for(int i = 1; i <= n; ++i) {
		f[i] = min(f[max(i - 2, 0)] + p[i], f[max(i - 3, 0)] + max(p[i], p[i - 1]));
		if(f[i] == f[max(i - 3, 0)] + max(p[i], p[i - 1])) t[i] = 1;
	}
	ll ans = min(f[n], f[n - 1]);
	for(int i = n - (ans == f[n - 1]); i >= 1; i -= 2 + t[i]) {
		go(i - 1);
		if(t[i]) go(i - 2);
		go(i);
	}
	printf("%d\n", (int)g.size());
	for(int i = 0; i < g.size(); ++i) {
		printf("%d\n", g[i]);
	}
	return 0;
}