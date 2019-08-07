#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 25;
ll a[N][N];

int main() {
	for(int i = 1; i <= 20; ++i)
		for(int j = 1; j <= 20; ++j) 
			scanf("%lld", &a[i][j]);
	ll maxn = 0;
	for(int i = 1; i <= 20; ++i)
		for(int j = 1; j <= 20; ++j) {
			ll pos = 1;
			int x = i, y = j, flg = 1;
			for(int t = 1; t <= 4; ++t) {
				pos *= a[x][y];
				x++, y++;
				if(x > 20 || y > 20) {
					flg = (t == 4);
					break;
				}
			}
			if(flg) {
				maxn = max(maxn, pos);
			}
		}
	printf("%lld\n", maxn);
	return 0;
}