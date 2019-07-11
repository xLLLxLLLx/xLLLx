#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10, LOG = 18;
int st[N][LOG + 1], a[N];
int n;
map<int, ll> mp;
map<int, ll> :: iterator sit;

int gcd(int A, int B) {
	return B ? gcd(B, A % B) : A;
}

int get(int l, int r) {
	int k = log((double)(r - l + 1)) / log(2.0);
	return gcd(st[l][k], st[r - (1 << k) + 1][k]);
}

int Bet(int v, int B) {
	int l = B, r = n, ans = B;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(get(B, mid) % v) {
			r = mid - 1;
		} else {
			ans = mid;
			l = mid + 1;
		}
	}
	return ans;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			st[i][0] = a[i];
		}
		for(int j = 1; j <= LOG; ++j) {
			for(int i = 1; i <= n; ++i) {
				if(i + (1 << j) > n + 1) {
					break;
				}
				st[i][j] = gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
			}
		}
		for(int i = 1; i <= n; ++i) {
			// printf("i==%d\n", i);
			int r = i - 1, now = st[i][0];
			for(; r != n;) {
				r++;
				now = get(i, r);
				int pos = Bet(now, r);
				// printf("qwq%d %d %d\n", now, r, pos);
				mp[now] += pos - r + 1;
				r = pos;
			}
		}
		// printf("!!!!!%d\n", get(2, 5));
		int Q;
		scanf("%d", &Q);
		printf("Case #%d:\n", o);
		for(int i = 1, l, r; i <= Q; ++i) {
			scanf("%d%d", &l, &r);
			int pos = get(l, r);
			printf("%d %lld\n", pos, mp[pos]);
		}
		mp.clear();
	}
	return 0;
}