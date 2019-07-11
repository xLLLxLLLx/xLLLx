#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 10;
queue<int> q;
int a[N], dis[N];

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	memset(dis, 0x3f, sizeof dis);
	for(int i = 1, x; i <= k; ++i) {
		scanf("%d", &x);
		a[x - n + 1000] = 1;
		dis[x - n + 1000] = 1;
	}
	for(int i = 0; i <= 2000; ++i) {
		if(a[i]) {
			if(i == 1000) {
				return printf("1\n"), 0;
			}
			q.push(i);
		}
	}
	while(!q.empty()) {
		int h = q.front(); q.pop();
		if(h < 1000) {
			for(int i = 1001; i <= 2000; ++i) {
				if(a[i]) {
					int now = h + i - 1000;
					if(now == 1000) {
						return printf("%d\n", dis[h] + 1), 0;
					}
					if(dis[now] > dis[h] + 1) {
						dis[now] = dis[h] + 1;
						q.push(now);
					}
				}
			}
		} else {
			for(int i = 0; i <= 1000; ++i) {
				if(a[i]) {
					int now = h + i - 1000;
					if(now == 1000) {
						return printf("%d\n", dis[h] + 1), 0;
					}
					if(dis[now] > dis[h] + 1) {
						dis[now] = dis[h] + 1;
						q.push(now);
					}
				}
			}
		}
	}
	printf("-1\n");
	return 0;
}