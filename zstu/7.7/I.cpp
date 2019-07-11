#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5e5 + 10;
struct data {
	int x, y;
	ll w;
}a[N];
int f[N], cnt = 0;

bool cmp(data A, data B) {
	return A.w < B.w;
}

int find(int k) {
	return k == f[k] ? k : f[k] = find(f[k]);
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) f[i] = i;
	for(int i = 1; i <= m; ++i) {
		scanf("%d%d%lld", &a[i].x, &a[i].y, &a[i].w);
	}
	sort(a + 1, a + 1 + m, cmp);
	int cnt = 0;
	ll ans = 0;
	for(int i = 1; i <= m; ++i) {
		int fx = find(a[i].x), fy = find(a[i].y);
		if(fx != fy) {
			f[fx] = fy;
			ans += a[i].w;
		}
	}
	cout<<ans<<endl;
	return 0;
}