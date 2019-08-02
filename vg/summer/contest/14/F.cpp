#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
struct node {
	int u, v, l, r;
	bool operator < (const node & C) const {
		return l > C.l;
	}
};
struct data {
	int nt, to, r;
} a[N * 10];
int head[N][2], L[N][2], cnt = 0;
priority_queue<node> q;

void add(int x, int y, int r, int opt) {
	a[++cnt].to = y, a[cnt].r = r;
	a[cnt].nt = head[x][opt], head[x][opt] = cnt;
}

void insert(int u, int v, int l, int r) {
	q.push((node){u, v, l, r});
}

void go(int u, int l, int r, int opt) {
	L[u][opt] = max(L[u][opt], r);
	for(int i = head[u][opt]; i; i = a[i].nt) {
		insert(u, a[i].to, l, a[i].r);
	}
	head[u][opt] = 0;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	if(n == 1) {
		return printf("0\n"), 0;
	}
	for(int i = 1; i <= m; ++i) {
		int u, v, l, r;
		scanf("%d%d%d%d", &u, &v, &l, &r);
		r--;
		int pos = r - l;
		insert(u, v, l, r - (pos & 1));
		insert(v, u, l, r - (pos & 1));
		insert(u, v, l + 1, r - (!(pos & 1)));
		insert(v, u, l + 1, r - (!(pos & 1)));
	}
	memset(L,255,sizeof(L));
  L[1][0]=0;
	while(!q.empty()) {
		node h = q.top(); q.pop();
		if(h.l > h.r) {
			continue;
		}
		int opt = h.l & 1;
		if(L[h.u][opt] >= h.l) {
			if(h.v == n) {
				printf("%d\n", h.l + 1);
				return 0;
			} 
			go(h.v, h.l + 1, h.r + 1, opt ^ 1);
		} else {
			add(h.u, h.v, h.r, opt);
		}
	}
	puts("-1");
	return 0;
}