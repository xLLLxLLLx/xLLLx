#include <bits/stdc++.h>
#define ll long long
using namespace std;
map<ll, int> v;
vector<int> g;
int kk;
ll p, k;

void fail() {
	printf("-1\n");
	exit(0);
}

ll cal(ll x, ll y) {
	return x * k + y;
}

ll get(ll x) {
	kk = 0;
	ll l = -(p / k) - 10, r =(p / k) + 10, ans = 0, flg = 0;
	for(int o = 1; o <= 64; ++o) {
		ll mid = (l + r) >> 1;
		ll val = cal(mid, x);
		if(val < 0) l = mid + 1;
		else if(val >= k) r = mid - 1;
		else {
			if(mid >= 0 && mid < k) {
				ans = mid, flg = 1;
				kk = 1;
				break;
			} else if(mid < 0) l = mid + 1;
			else r = mid - 1;
			if(!flg && !v.count(mid)) {
				kk = 1, ans = mid;
			}
		}
	}
	v[ans] = 1;
	return ans;
}

int main() {
	scanf("%lld%lld", &p, &k);
	ll pre = p;
	int cnt = 0;
	for(;;) {
		ll pos = get(pre);
		if(!kk) fail();
		g.push_back(pos * k + pre);
		pre = pos;
		if(0 <= pos && pos < k) {
			if(pos) g.push_back(pos);
			break;
		}
	}
	printf("%d\n", (int)g.size());
	for(int i = 0; i < g.size(); ++i) {
		printf("%d ", g[i]);
	}
	puts("");
	return 0;
}