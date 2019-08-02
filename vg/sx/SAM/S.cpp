#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10;
struct node {
	int fa, mx, ch[26];
} a[N << 1];
int last = 1, cnt = 1;
char lx[N];

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
	scanf("%s", lx + 1);
	int len = strlen(lx + 1);
	ll ans = 0;
	for(int i = 1; i <= len; ++i) {
		insert(lx[i] - 'a');
		ans += a[last].mx - a[a[last].fa].mx;
	}
	printf("%lld\n", ans);
	return 0;
}