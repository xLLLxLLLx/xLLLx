#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
char lx[N];
int a[N], b[N];

bool check() {
	sort(a + 1, a + 1 + a[0]);
	int pos = 0, tmp = 0;
	int mid = a[0] / 2 + (a[0] & 1);
	for(int i = 1; i <= mid; ++i) {
		pos += a[i];
		if(pos <= tmp) return false;
		tmp += a[a[0] - i + 1];
	}
	int len = (1 << a[0]);
	b[0] = 0;
	for(int i = 0; i < len; ++i) {
		int num = 0, sum = 0;
		for(int j = 1; j <= a[0]; ++j) {
			if((i >> (j - 1)) & 1) {
				num++;
				sum += a[j];
			}
		}
		if(num == mid) b[++b[0]] = sum;
	}
	sort(b + 1, b + 1 + b[0]);
	for(int i = 1; i < b[0]; ++i)
		if(b[i] == b[i + 1]) return false;
	return true;
}

int main() {
	int ans = 0;
	for(int o = 1; o <= 100; ++o) {
		scanf("%s", lx + 1);
		int len = strlen(lx + 1);
		a[0] = 0;
		for(int i = 1; i <= len; ++i) {
			for(; lx[i] < '0' || lx[i] > '9'; i++) ;
			int now = 0;
			for(; lx[i] >= '0' && lx[i] <= '9'; ++i)
				now = now * 10 + (lx[i] - '0');
			a[++a[0]] = now;
		}
		// for(int i = 1; i <= a[0]; ++i)
		// 	printf("%d ", a[i]);
		// puts("");
		if(check()) {
			for(int i = 1; i <= a[0]; ++i)
				ans += a[i];
		}
	}
	printf("%d\n", ans);
	return 0;
}