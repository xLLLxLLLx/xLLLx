#include<bits/stdc++.h>
using namespace std;
cosnt int N = 1e5 + 10;
int a[N], be[N], ed[N];

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	memset(ed, -1, sizeof ed);
	memset(be, 0x3f, sizeof be);
	for(int i = 1; i <= k; ++i) {
		scanf("%d", &a[i]);
		be[a[i]] = min(be[a[i]], i);
		ed[a[i]] = max(ed[a[i]], i);
	}
	int ans = 0;
	for(int i = 1; i <= n; ++i) {
		
	}
	printf("%d\n",ans);
	return 0;
}