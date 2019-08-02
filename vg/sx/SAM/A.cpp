#include <bits/stdc++.h>
using namespace std;
const int N = 2010;
struct node {
	int fa, mx,ch[26];
} a[N << 1];
int d[N][N], cnt, last;
char lx[N];

void init() {
	cnt = last = 1;
	memset(a, 0, sizeof a);
}

void insert(int x) {
	int p = last, np = ++cnt;
	a[np].mx = a[p].mx + 1;
	for(; p && !a[p].ch[x]; p = a[p].fa) 
		a[p].ch[x] = np;
	if(!p) {
		a[np].fa = 1;
	} else {
		int q = a[p].ch[x];
		if(a[q].mx == a[p].mx + 1) {
			a[np].fa = q;
		} else {
			int nq = ++cnt;
			a[nq] = a[q];
			a[nq].mx = a[p].mx + 1;
			a[np].fa = a[q].fa = nq;
			for(; p && a[p].ch[x] == q; p = a[p].fa)
				a[p].ch[x] = nq;
		}
	}
	last = np;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1, m; o <= T; ++o) {
		scanf("%s%d", lx + 1, &m);
		int len = strlen(lx + 1);
		for(int i = 1; i <= len; ++i) {
			init();
			for(int j = i; j <= len; ++j) {
				insert(lx[j] - 'a');
				d[i][j] = d[i][j - 1] + a[last].mx - a[a[last].fa].mx;
			}
		}
		for(int i = 1, l, r; i <= m; ++i) {
			scanf("%d%d", &l, &r);
			printf("%d\n", d[l][r]);
		}
	}
	return 0;
}