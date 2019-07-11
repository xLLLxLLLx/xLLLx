#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int a[N], b[N], na[N], all[N];

void ok() {
	printf("YES\n");
	exit(0);
}

void fail() {
	printf("NO\n");
	exit(0);
}

int main() {
	int n, m, k, res = 0;
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		all[++res] = a[i];
	}
	for(int i = 1; i <= m; ++i) {
		scanf("%d", &b[i]);
		all[++res] = b[i];
	}
	sort(all + 1, all + 1 + res);
	int tot = unique(all + 1, all + 1 + res) - all - 1;
	for(int i = 1; i <= n; ++i) {
		a[i] = lower_bound(all + 1, all + 1 + tot, a[i]) - all;
		na[a[i]]++;
	}
	for(int i = 1; i <= m; ++i) {
		b[i] = lower_bound(all + 1, all + 1 + tot, b[i]) - all;
		na[b[i]]--;
	}
	for(int i = tot; i >= 1; --i) {
		na[i] += na[i + 1];
		if(na[i] > 0) {
			// printf("%d\n", i);
			ok();
		}
	}
	fail();
	return 0;
}