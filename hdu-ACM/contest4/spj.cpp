#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
int vis[N];
string lx;

int main() {
	ll sum = 0;
	int k, maxn = 0;
	scanf("%d", &k);
	for(int i = 1; i <= k; ++i) {
		getline(cin, lx);
		int len = lx.size();
		for(int i = 0; i < len; ++i) {
			int pos = 0;
			for(; lx[i] < '0' || lx[i] > '9'; ++i) ;
			for(; lx[i] >= '0' && lx[i] <= '9'; ++i) 
				pos = pos * 10 + (lx[i] - '0');
			sum += pos, vis[pos] = 1;
			maxn = max(maxn, pos);
		}
	}
	printf("%d %lld\n", maxn, sum);
	if(1ll * maxn * (maxn + 1) / 2 != sum) {
		return printf("WAI!\n"), 0;
	} 
	for(int i = 1; i <= maxn; ++i) {
		if(!vis[i]) 
			return printf("WAI!!\n"), 0;
	}
	printf("%d %d\n", maxn, k);
	return 0;
}