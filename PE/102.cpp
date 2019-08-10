#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 110;
struct data {
	ll x, y;
} b[N];
ll a[N];
char lx[N];

ll cross(data A, data B) {
	return (A.x * B.y) - (A.y * B.x);
}

int main() {
	int ans = 0;
	for(int i = 1; i <= 1000; ++i) {
		scanf("%s", lx + 1);
		int len = strlen(lx + 1), now = 0;
		for(int i = 1; i <= len; ++i) {
			int pos = 0, f = 0;
			for(;lx[i] < '0' || lx[i] > '9';++i)
				if(lx[i] == '-') f = 1;
			for(;lx[i] >= '0' && lx[i] <= '9'; ++i)
				pos = pos * 10 + (lx[i] - '0');
			if(f) pos = -pos;
			a[++now] = pos;
		}
		for(int i = 1; i <= now; i += 2)
			b[i / 2 + 1] = (data) {a[i], a[i + 1]};
		int flg = 1;
		for(int i = 1; i <= 3; ++i) {
			ll tmp = 1;
			for(int j = 1; j <= 3; ++j) {
				if(i == j) continue;
				tmp *= cross((data){b[j].x - b[i].x, b[j].y - b[i].y}, (data){-b[i].x, -b[i].y});
			}
			if(tmp >= 0) flg = 0;
		}
		printf("%d\n", flg);
		ans += flg;
	}
	printf("%d\n", ans);
	return 0;
}