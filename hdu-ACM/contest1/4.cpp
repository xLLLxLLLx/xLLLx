#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
double t[N];
int l[N], s[N], v[N];

int main() {
	int n;
	while(scanf("%d", &n) == 1) {
		for(int i = 1; i <= n + 1; ++i) {
			scanf("%d", &l[i]);
		}
		for(int i = 1; i <= n + 1; ++i) {
			scanf("%d", &s[i]);
		}
		for(int i = 1; i <= n + 1; ++i) {
			scanf("%d", &v[i]);
			t[i] = 1.0 * s[i] / v[i];
		}
		double ans = 0, sum = 0;
		for(int i = 1; i <= n + 1; ++i) {
			if(i > 1) sum += l[i];
			ans = max(ans, t[i] + 1.0 * sum / v[i]);
		}
		printf("%.10f\n", ans);
	}
	return 0;
}