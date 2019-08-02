#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 4e5 + 10;
int a[N], all[N], num[N];

int main() {
	int n, I;
	cin >> n >> I;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		all[i] = a[i];
	}
	sort(all + 1, all + 1 + n), sort(a + 1, a + 1 + n);
	int m = unique(all + 1, all + 1 + n) - all - 1;
	for(int i = 1; i <= n; ++i) {
		a[i] = lower_bound(all + 1, all + 1 + m, a[i]) - all;
	}
	int k = 1, pos = 8 * I / n;
	for(int i = 1; i <= pos; ++i) {
		k *= 2;
		if(k >= n) {
			puts("0");
			return 0;
		}
	}
	int maxn = n;
	int r = 0, res = 0;
	for(int i = 1; i <= n; ++i) {
		while(r < n && res + (num[a[r + 1]] == 0) <= k) {
			r++;
			if(!num[a[r]]) res++;
			num[a[r]]++;
		}
		maxn = min(maxn, i - 1 + n - r);
		num[a[i]]--;
		if(!num[a[i]]) res--;
	}
	printf("%d\n", maxn);
	return 0;
}