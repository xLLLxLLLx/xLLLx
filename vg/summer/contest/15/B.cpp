#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N], all[N], num[N];

int main() {
	int n, now = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		now += (a[i] == 0);
		all[i] = a[i];
	}
	sort(a + 1, a + 1 + n), sort(all + 1, all + 1 + n);
	int m = unique(all + 1, all + 1 + n) - all - 1;
	for(int i = 1; i <= n; ++i) {
		int pos = lower_bound(all + 1, all + 1 + m, a[i]) - all;
		num[pos]++;
	}
	int res = 0, tot = 0, be = 0;
	for(int i = 1; i <= m; ++i) {
		if(num[i] >= 2) {
			res++;
			tot += num[i];
			be = i;
		}
	}
	int pos = 0;
	if(now >= 2 || res >= 2 || res * 2 < tot) return printf("cslnb\n"), 0;
	else if(res){
		if(be > 1 && all[be - 1] == all[be] - 1) return printf("cslnb\n"), 0;
		else {
			for(int i = 1; i <= n; ++i) {
				if(a[i] == all[be]) {
					a[i]--, pos = 1;
					break;
				}
			}
		}
	}
	for(int i = 1; i <= n; ++i) {
		pos ^= ((a[i] - i + 1) & 1);
	}
	if(pos & 1) printf("sjfnb\n");
	else printf("cslnb\n");
	return 0;
}