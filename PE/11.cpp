#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 25;
ll a[N][N];

int main() {
	for(int i = 1; i <= 20; ++i)
		for(int j = 1; j <= 20; ++j) 
			scanf("%lld", &a[i][j]);
	for(int i = 1; i <= 20; ++i) {
		for(int j = 1; j <= 20; ++j)
			printf("%lld ", a[i][j]);
		puts("");
	}
	ll maxn = 0;
	for(int i = 1; i <= 20; ++i)
		for(int j = 1; j <= 20; ++j) {
			ll pos = 1;
			int x = i, y = j, flg = 1;
			for(int t = 1; t <= 4; ++t) {
				pos *= a[x][y];
				if(x > 20 || y > 20) {
					flg = 0;
					break;
				}
				x++, y++;
			}
			if(flg) {
				maxn = max(maxn, pos);
				if(pos == 40304286) {
					printf("%d %d\n", i, j);
				}
			}
		}
	for(int i = 1; i <= 20; ++i)
		for(int j = 1; j <= 20; ++j) {
			int flg = 1;
			ll pos = 1;
			for(int t = 0; t < 4; ++t) {
				int yy = j + t;
				if(yy > 20) {
					flg = 0;
				}
				pos = pos * a[i][yy];
			}
			if(flg) maxn = max(maxn, pos);
			pos = 1, flg = 1;
			for(int t = 0; t < 4; ++t) {
				int xx = i + t;
				if(xx > 20) {
					flg = 0;
				}
				pos = pos * a[xx][j];
			}
			if(flg) maxn = max(maxn, pos);
			if(flg && pos == 51267216) {
				printf("%d %d\n", i, j);
			}
		}
	printf("%lld\n", maxn);
	return 0;
}