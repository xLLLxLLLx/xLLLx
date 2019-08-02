#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5e5 + 10;
vector<int> g;
int b[N];

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n, m;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= 3 * n; ++i) {
			b[i] = 0;
		}
		g.clear();
		for(int i = 1, x, y; i <= m; ++i) {
			scanf("%d%d", &x, &y);
			if(!b[x] && !b[y]) {
				g.push_back(i);
				b[x] = b[y] = 1;
			}
		}
		if(g.size() >= n) {
			puts("Matching");
			for(int i = 0; i < n; ++i) {
				printf("%d ", g[i]);
			}
			puts("");
		} else {
			int pos = 0;
			puts("IndSet");
			for(int i = 1; i <= 3 * n; ++i) {
				if(!b[i]) {
					pos++;
					printf("%d ", i);
				}
				if(pos == n) {
					puts("");
					break;
				}
			}
		}
	}
	return 0;
}