#include <bits/stdc++.h>
using namespace std;

#define N 110000
#define P 1000000007

vector <int> ve[N], ve1[N];
int x[N], y[N];
int sum[N];
bool used[N];
int ans = 1, ans2 = 1;
int n;

int Pow(int x, int y) {
	int ans = 1;
	for (int i = 1; i <= y; i *= 2, x = 1LL * x * x % P)
		if (i & y)
			ans = 1LL * ans * x % P;
	return ans;
}

void dfs_sum(int k) {
	used[k] = true;
	sum[k] = 1;
	for (auto x: ve[k])
		if (!used[x])
			dfs_sum(x), sum[k] += sum[x];
	used[k] = false;
}

int zx;
void dfs_zx(int k, int S) {
	bool ok = (S - sum[k] <= S / 2);
	used[k] = true;
	for (auto x: ve[k]) {
		if (!used[x]) {
			dfs_zx(x, S);
			ok &= (sum[x] <= S / 2);
		}
		
	}
	if (ok)
		zx = k;
	used[k] = false;
}


void dfs_put(int k, int s1, int s2, int prod, pair<int, int> &p, vector <pair<int, int> > &v1, vector <pair<int, int> > &v2) {
	p.first = 1LL * p.first * prod % P;
	p.second++;

	v1[s1].first = 1LL * v1[s1].first * prod % P;
	v1[s1].second++;

	v2[s2].first = 1LL * v2[s2].first * prod % P;
	v2[s2].second++;

	used[k] = true;
	for (int i = 0; i < (int) ve[k].size(); i++) {
		int xx = ve[k][i];
		int id = ve1[k][i];
		if (!used[xx]) {
			dfs_put(xx, s1 + (y[id] == 1 ? 2 : -1), s2 + (y[id] == 1 ? -1 : 2), 1LL * prod * x[id] % P, p, v1, v2);
		}
	}
	used[k] = false;
}

// void pref(vector <int> &X) {
// 	for (int i = 1; i < (int) X.size(); i++) {
// 		X[i] = (X[i] + X[i - 1]) % P;
// 	}
// }

// int Q(int k, int s1, int s2) {
// 	int tmp = 0;
// 	tmp = vv1[k].back();
// 	if (sum[k] - s1 - 1 >= 0)
// 		tmp = (tmp - vv2[k][sum[k] - s1 - 1]) % P;
// 	if (sum[k] - s2 - 1 >= 0)
// 		tmp = (tmp - vv3[k][sum[k] - s2 - 1]) % P;
// 	tmp = (tmp + P) % P;
// 	return tmp;
// }

typedef pair<int, int> pii;
vector <pair<int, int> > prods;
vector <int> offsets;
vector <vector <pair<int, int> > > VV1, VV2; 
	
pair <int, int> cross(pair <int, int> x, pair<int, int> y) {
	return make_pair(1LL * x.first * y.first % P, x.second + y.second);
}

int MM(pair <int, int> x, pair<int, int> y) {
	return 1LL * Pow(x.first, y.second) * Pow(y.first, x.second) % P;
}

void solve(int q, int h) {

	if (q == h)
		return ;

	int mid = (q + h) / 2;
	pii prodl = make_pair(1, 0);
	int offsetl = 0, lengthl = 0;
	for (int i = q; i <= mid; i++)
		offsetl += offsets[i], prodl = cross(prodl, prods[i]), lengthl += VV1[i].size();
	vector <pii> VV1l(lengthl, make_pair(1, 0)), VV2l(lengthl, make_pair(1, 0));
	for (int i = q; i <= mid; i++) {
		for (int j = 0; j < (int) VV1[i].size(); j++)
			VV1l[j - offsets[i] + offsetl] = cross(VV1l[j - offsets[i] + offsetl], VV1[i][j]), 
			VV2l[j - offsets[i] + offsetl] = cross(VV2l[j - offsets[i] + offsetl], VV2[i][j]);
	}

	pii prodr = make_pair(1, 0);
	int offsetr = 0, lengthr = 0;
	for (int i = mid + 1; i <= h; i++)
		offsetr += offsets[i], prodr = cross(prodr, prods[i]), lengthr += VV1[i].size();
	vector <pii> VV1r(lengthr, make_pair(1, 0)), VV2r(lengthr, make_pair(1, 0));
	for (int i = mid + 1; i <= h; i++) {
		for (int j = 0; j < (int) VV1[i].size(); j++)
			VV1r[j - offsets[i] + offsetr] = cross(VV1r[j - offsets[i] + offsetr], VV1[i][j]), 
			VV2r[j - offsets[i] + offsetr] = cross(VV2r[j - offsets[i] + offsetr], VV2[i][j]);
	}

	ans = 1LL * ans * MM(prodl, prodr) % P;
	pii sum1 = make_pair(1, 0), sum2 = make_pair(1, 0);
	int now = 0;
	for (int i = lengthl - 1; i >= 0; i--) {
		while (now < lengthr && i + now - offsetl - offsetr < 0)
			sum1 = cross(sum1, VV1r[now]),
			sum2 = cross(sum2, VV2r[now]),
			now++;
		ans2 = 1LL * ans2 * MM(sum1, VV1l[i]) % P;
		ans2 = 1LL * ans2 * MM(sum2, VV2l[i]) % P;
	}


	solve(q, mid);
	solve(mid + 1, h);
	// for (int i = q; i <= h; i++)
	// 	for (int j = i + 1; j <= h; j++) {
	// 		ans = 1LL * ans * Pow(prods[i].first, prods[j].second) % P * Pow(prods[j].first, prods[i].second) % P;
	// 		for (int a = 0; a < (int) VV1[i].size(); a++)
	// 			for (int b = 0; b < (int) VV1[j].size(); b++) {
	// 				if (a + b - offsets[i] - offsets[j] < 0) {
	// 					ans2 = 1LL * ans2 * Pow(VV1[i][a].first, VV1[j][b].second) % P * Pow(VV1[j][b].first, VV1[i][a].second) % P;
	// 					ans2 = 1LL * ans2 * Pow(VV2[i][a].first, VV2[j][b].second) % P * Pow(VV2[j][b].first, VV2[i][a].second) % P;
	// 				}
	// 			}
	// 	}
}

void dfs(int k) {
	dfs_sum(k);
	dfs_zx(k, sum[k]);
	// printf("!! %d %d\n", k, zx);
	k = zx;

	dfs_sum(k);

	used[k] = true;
	
	prods.clear();
	offsets.clear();
	VV1.clear();
	VV2.clear();

	for (int i = 0; i < (int) ve[k].size(); i++) {
		int xx = ve[k][i];
		int id = ve1[k][i];
		if (!used[xx]) {
			auto PROD = make_pair(1, 0);
			vector <pair<int, int> > vv1(3 * sum[xx] + 1, make_pair(1, 0));
			vector <pair<int, int> > vv2(3 * sum[xx] + 1, make_pair(1, 0));

			dfs_put(xx, sum[xx] + (y[id] == 1 ? 2 : -1), sum[xx] + (y[id] == 1 ? -1 : 2), x[id], PROD, vv1, vv2);

			prods.push_back(PROD);
			VV1.push_back(vv1);
			VV2.push_back(vv2);
			offsets.push_back(sum[xx]);

		}
	}

	prods.push_back(make_pair(1, 1));
	VV1.push_back(vector <pair<int, int> >(1, make_pair(1, 1)));
	VV2.push_back(vector <pair<int, int> >(1, make_pair(1, 1)));
	offsets.push_back(0);

	solve(0, VV1.size() - 1);


	for (auto x: ve[k]) {
		if (!used[x])
			dfs(x);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d%d%d", &u, &v, &x[i], &y[i]);
		ve[u].push_back(v);
		ve1[u].push_back(i);
		ve[v].push_back(u);
		ve1[v].push_back(i);
	}
	dfs(1);
	ans = 1LL * ans * Pow(ans2, P - 2) % P;
	printf("%d\n", (ans + P) % P);
}