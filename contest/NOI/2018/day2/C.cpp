#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
multiset<int> s;
multiset<int> :: iterator it;
int a[N], p[N], b[N], c[N];

int get(int x) {
	int pos;
	it = s.lower_bound(x);
	if(it == s.end()) {
		pos = *s.rbegin();
	} else if(it == s.begin()) {
		pos = *s.begin();
	} else {
		it--;
		pos = *it;
	}
	return pos;
}

int main() {
	freopen("dragon.in", "r", stdin);
	freopen("dragon.out", "w", stdout);
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		s.clear();
		int n, m;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		int flg = 1;
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &p[i]);
			if(p[i] != 1) flg = 0;
		}
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &c[i]);
		}
		for(int i = 1; i <= m; ++i) {
			scanf("%d", &b[i]);
			s.insert(b[i]);
		}
		if(flg) {
			int maxn = 0, pos;
			for(int i = 1; i <= n; ++i) {
				int pos = get(a[i]);
				int tmp = a[i] / pos;
				if(a[i] % pos) tmp++;
				maxn = max(maxn, tmp);
				s.erase(s.find(pos));
				s.insert(c[i]);
			}
			printf("%d\n", maxn);
		} else {
			puts("-1");
		}
	}
	return 0;
}