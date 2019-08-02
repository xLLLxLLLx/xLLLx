#include <bits/stdc++.h>
#define ll long long 
using namespace std;
const int N = 3010;
int n, m, a, b, g, x, y, z;
int val[N][N], f[N][N], q[N];

void init() {
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			val[i][j] = g;
			// printf("%d ", val[i][j]); 
			g = (1ll * g * x % z + y) % z;
		}
		// puts("");
	}
}

int main() {
	cin >> n >> m >> a >> b >> g >> x >> y >> z;
	init();
	for(int i = 1; i <= n; ++i) {
		int l = 1, r = 0;
		for(int j = 1; j <= m; ++j) {
			while(l <= r && q[l] <= j - b) l++;
			while(l <= r && val[i][q[r]] >= val[i][j]) r--;
			q[++r] = j;
			f[i][j] = val[i][q[l]];
		}
	}
	ll ans = 0;
	for(int j = b; j <= m; ++j) {
		int l = 1, r = 0;
		for(int i = 1; i <= n; ++i) {
			while(l <= r && q[l] <= i - a) l++;
			while(l <= r && f[q[r]][j] >= f[i][j]) r--;
			q[++r] = i;
			if(i >= a) {
				ans += f[q[l]][j];
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}