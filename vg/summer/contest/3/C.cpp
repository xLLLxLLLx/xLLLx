#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
struct data {
	int nt, to;
} a[N << 1];
vector<int> g[N];
int maxn = 0, be = 0;
int head[N], d[N], s[N], vis[N], f[N], dep[N], cnt = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void dfs(int x, int y) {
	vis[x] = 1;
	dep[x] = dep[y] + 1, f[x] = y;
	if(dep[x] > maxn) {
		maxn = dep[x], be = x;
	}
	int son = 0;
	for(int i = head[x]; i; i = a[i].nt) {
		int to = a[i].to;
		if(vis[to]) {
			if(to != f[x]) 
				g[x].push_back(to);
			continue;
		}
		++son;
		dfs(to, x);
	}
	if(!son) s[++s[0]] = x;
}

void print() {
	printf("%d\n", d[0]);
	for(int i = 1; i <= d[0]; ++i) {
		printf("%d ", d[i]);
	}
	puts("");
}

void path() {
	printf("PATH\n");
	for(; be; ) {
		d[++d[0]] = be;
		be = f[be];
	}
	print();
}

void get(int x, int y) {
	d[0] = 0;
	if(dep[x] < dep[y]) {
		swap(x, y);
	}
	for(; x != y; x = f[x]) {
		d[++d[0]] = x;
	}
	d[++d[0]] = x;
	print();
}

void cycle(int k) {
	printf("CYCLES\n");
	for(int i = 1; i <= k; ++i) {
		int x = s[i], y = g[s[i]][0], z = g[s[i]][1];
		d[0] = 0;
		if((dep[x] - dep[y] + 1) % 3) {
			get(x, y);
		} else if((dep[x] - dep[z] + 1) % 3) {
			get(x, z);
		} else {
			get(z, y);
		}
	}
}

int main() {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1, x, y; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	dfs(1, 0);
	int pos = n / k;
	if(n % k) pos++;
	if(maxn >= pos) {
		path();
	} else {
		cycle(k);
	}
	return 0;
}