#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
ll add[N], a[N];

int main() {
	ll sum = 0;
	int now = 1, n;
	scanf("%d", &n);
	for(int i = 1, tp; i <= n; ++i) {
		scanf("%d", &tp);
		if(tp == 1) {
			int x, y;
			scanf("%d%d", &x, &y);
			add[x] += y;
			sum += 1ll * x * y;
		} else if(tp == 2) {
			int x;
			scanf("%d", &x);
			sum += x, a[++now] = x;
		} else {
			add[now - 1] += add[now];
			sum -= add[now] + a[now];
			add[now] = a[now] = 0;
			now--;
		}
		printf("%.10f\n", double(sum) / double(now));
	}
	return 0;
}