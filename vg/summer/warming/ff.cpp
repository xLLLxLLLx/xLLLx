#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5e5 + 10;
typedef pair <ll, ll> P;
ll L[N], R[N], ys[N], d[N], zx[N], zy[N], tr[N];
P point[N];
vector <int> g[N];
map <P, int> mp;

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

P insert(int x, int y) {
	int pos = gcd(abs(x), abs(y));
	if(pos) {
		x /= pos, y /= pos;
	}
	// printf("%d %d\n", x, y);
	return P(x, y);
}

int lower(int x) {
	return x & (-x);
}

void upd(int x, int y) {
	for(; x; x -= lower(x)) 
		tr[x] += y;
}

int get(int x) {
	int ans = 0;
	for(; x < N; x += lower(x)) 
		ans += tr[x];
	return ans;
}

int main() {
	int n, cnt = 0;
	scanf("%d", &n);
	for(int i = 1, num; i <= n; ++i) {
		// printf("i === %d\n", i);
		scanf("%d", &num);
		L[i] = cnt + 1;
		for(int j = 0; j < num; ++j) {
			scanf("%lld%lld", &zx[j], &zy[j]);
		}
		for(int j = 0; j < num; ++j) {
			point[++cnt] = insert(zx[j] - zx[(j + 1) % num], zy[j] - zy[(j + 1) % num]);
		}
		R[i] = cnt;
	}
	// printf("%d\n", cnt);
	int q;
	scanf("%d", &q);
	for(int o = 1, l, r; o <= q; ++o) {
		scanf("%d%d", &l, &r);
		l = L[l], r = R[r];
		ys[o] = l;
		g[r].push_back(o);
	}
	for(int i = 1; i <= cnt; ++i) {
		if(mp[point[i]]) upd(mp[point[i]], -1);
		mp[point[i]] = i;
		upd(mp[point[i]], 1);
		for(int j = 0; j < g[i].size(); ++j) {
			d[g[i][j]] = get(ys[g[i][j]]);
		}
	}
	for(int i = 1; i <= q; ++i) {
		printf("%d\n", d[i]);
	}
	return 0;
}