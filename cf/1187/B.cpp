#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, M = 30;
vector<int> g[M];
int a[M];
char lx[N], ll[N];

int main() {
	int T, len;
	scanf("%d%s", &len, lx + 1);
	for(int i = 1; i <= len; ++i) {
		int pos = lx[i] - 'a' + 1;
		g[pos].push_back(i);
	}
	cin>>T;
	for(int o = 1; o <= T; ++o) {
		memset(a, 0, sizeof a);
		scanf("%s", ll + 1);
		int tot = strlen(ll + 1);
		for(int i = 1; i <= tot; ++i) {
			int pos = ll[i] - 'a' + 1;
			a[pos]++;
		}
		int maxn = 0;
		for(int i = 1; i <= 26; ++i) {
			if(!a[i]) {
				continue;
			}
			// printf("%d %d %d\n",o, i,a[i]);
			int num = g[i].size();
			int tmp = a[i] / num * len;
			int pos = a[i] % num;
			if(!pos) {
				tmp -= len;
				tmp += g[i][num - 1];
			} else {
				tmp += g[i][pos - 1];
			}
			maxn = max(maxn, tmp);
		}
		printf("%d\n", maxn);
	}
	return 0;
}