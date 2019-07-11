#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
struct data {
	int nt, to;
}a[N*N];
int cnt = 0;
int head[N];

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void fail() {
	printf("NO\n");
	exit(0);
}

int main() {
	int n, m;
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &x, &y, &z);
		
	}
	printf("YES\n");
	for(int i = 1; i <= n; ++i) {
		if(!v[i]) v[i]++;
		printf("%d ",v[i]);
	}
	return 0;
}