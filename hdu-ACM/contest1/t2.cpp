#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10, LOG = 29;
int qz[N][LOG + 1], pos[N][LOG + 1];

void insert(int id, int x) {
	for(int i = 0; i <= LOG; ++i)
		qz[id][i] = qz[id - 1][i], pos[id][i] = pos[id - 1][i];
	int now = id;
	for(int i = LOG; i >= 0; --i) {
		if((x >> i) & 1) {
			if(!qz[id][i]) {
				qz[id][i] = x;
				pos[id][i] = now;
				break;
			} else {
				if(now > pos[id][i]) {
					swap(x, qz[id][i]);
					swap(now, pos[id][i]);
				}
				x ^= qz[id][i];
			}
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n, m;
		scanf("%d%d", &n, &m);
		for(int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			insert(i, x);
		}
		int ans = 0;
		for(int o = 1, tp; o <= m; ++o) {
			scanf("%d", &tp);
			if(tp == 0) {
				int l, r;
				scanf("%d%d", &l, &r);
				l ^= ans, r ^= ans;
				l = l % n + 1, r = r % n + 1;
				swap(l, r);
				if(l > r) swap(l, r);
				int now = 0;
				for(int i = LOG; i >= 0; --i) {
					if((!((now >> i) & 1)) && pos[r][i] >= l) now ^= qz[r][i];
				}
				ans = now;
				printf("%d\n", ans);
			} else {
				int x;
				scanf("%d", &x);
				++n;
				insert(n, x ^ ans);
			}
		}
	}
	return 0;
}