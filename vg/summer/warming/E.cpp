#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3010;
multiset<int> s;
int f[N][N];

int main() {
	int n, m, a, b;
	ll g, x, y, z;
	cin >> n >> m >> a >> b >> g >> x >> y >> z;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) {
			f[i][j] = g;
			g = (g * x % z + y) % z;
		}
	// for(int i = 1; i <= n; ++i) {
	// 	for(int j = 1; j <= m; ++j) {
	// 		printf("%d ", f[i][j]);
	// 	}
	// 	puts("");
	// }
	ll ans = 0;
	for(int i = 1; i <= n - a + 1; ++i) {
		if(i > 1) {
			if(i & 1) {
				for(int j = 1; j <= b; ++j) {
					s.erase(s.find(f[i - 1][j]));
					s.insert(f[i + a - 1][j]);
				}
			} else {
				for(int j = m - b + 1; j <= m; ++j) {
					s.erase(s.find(f[i - 1][j]));
					s.insert(f[i + a - 1][j]);
				}
			}
		} else {
			for(int j = i; j <= i + a - 1; ++j)
				for(int k = 1; k <= b; ++k) {
					s.insert(f[j][k]);
				}
		}
		ans += *s.begin();
		if(i & 1) {
			for(int k = b + 1; k <= m; ++k) {
				for(int j = i; j <= i + a - 1; ++j) {
					s.erase(s.find(f[j][k - b]));
					s.insert(f[j][k]);
				}
				ans += *s.begin();
			}
		} else {
			for(int k = m - b; k >= 1; --k) {
				for(int j = i; j <= i + a - 1; ++j) {
					s.erase(s.find(f[j][k + b]));
					s.insert(f[j][k]);
				}
				ans += *s.begin();
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}