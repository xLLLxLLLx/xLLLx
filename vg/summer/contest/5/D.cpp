#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
int a[N];

int main() {
	int n, d, b;
	scanf("%d%d%d", &n, &d, &b);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	ll sum = 0;
	int ans1 = 0, ans2 = 0;
	for(int i = 1, j = 1; i <= (n + 1) / 2; ++i) {
		for(; j <= min(i * (d + 1), n); ++j) sum += a[j];
		if(sum >= b) sum -= b;
		else ans1++;
	}
	reverse(a + 1, a + 1 + n);
	sum = 0;
	for(int i = 1, j = 1; i <= n / 2; ++i) {
		for(; j <= min(i * (d + 1), n); ++j) sum += a[j];
		if(sum >= b) sum -= b;
		else ans2++;
	}
	printf("%d\n", max(ans1, ans2));
	return 0;
}