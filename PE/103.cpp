#include <bits/stdc++.h>
using namespace std;
int a[10], b[10], sum[100];
int maxn = 1e9, now = 0, res = 0;

void work(int dep, int num) {
	if(dep > 7) {
		if(num == 3)sum[++res] = now;
		return ;
	}
	if(7 - dep + 1 < 3 - num || num > 3) return ;
	work(dep + 1, num);
	now += a[dep];
	work(dep + 1, num + 1);
	now -= a[dep];
}

bool check() {
	res = 0, now = 0;
	if(a[1] + a[2] <= a[7]) return false;
	if(a[1] + a[2] + a[3] <= a[6] + a[7]) return false;
	if(a[1] + a[2] + a[3] + a[4] <= a[5] + a[6] + a[7]) return false;
	work(1, 0);
	sort(sum + 1, sum + 1 + res);
	for(int i = 1; i <= res; ++i) {
		if(sum[i] == sum[i + 1])
			return false;
	}
	return true;
}

void dfs(int dep, int last) {
	if(dep > 7) {
		if(check()) {
			int tot = 0;
			for(int i = 1; i <= 7; ++i)
				tot += a[i];
			if(maxn > tot) {
				maxn = tot;
				for(int i = 1; i <= 7; ++i) {
					b[i] = a[i];
					printf("%d ", a[i]);
				}
				puts("");
			}
		}
		return ;
	}
	for(int i = last + 1; i <= 70; ++i) {
		a[dep] = i;
		dfs(dep + 1, i);
	}
}


int main() {
	dfs(1, 10);
	printf("%d\n", maxn);
	for(int i = 1; i <= 7; ++i)
		printf("%d ", b[i]);
	puts("");
	return 0;
}