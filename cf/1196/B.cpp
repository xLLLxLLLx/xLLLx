#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
int l[N], r[N];
ll a[N];

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n, k;
		scanf("%d%d", &n, &k);
		int pos = 0;
		ll sum = 0;
		for(int i = 1; i <= n; ++i) {
			scanf("%lld", &a[i]);
			sum += a[i];
			if(sum & 1) {
				l[pos + 1] = r[pos] + 1;
				r[++pos] = i;
				sum = 0;
			}
		}
		if(pos < k) printf("NO\n");
		else {
			ll tmp = 0;
			for(int i = l[k]; i <= n; ++i) {
				tmp += a[i];
			}
			if(tmp & 1) {
				r[k] = n;
				printf("YES\n");
				for(int i = 1; i <= k; ++i) {
					printf("%d ", r[i]);
				}
				puts("");
			} else printf("NO\n");
		}
	}
	return 0;
}