#include <bits/stdc++.h>
#define ll long long
#define ls x << 1
#define rs x << 1 | 1
using namespace std;
const int N = 1e5 + 10, M = 50;
int da = 0, db = N * 4 - 1;
int tr[N << 2][M + 1], len[N << 2];

void merge(int x, int y, int z) {
	len[x] = 0;
	int ny = 1, nz = 1;
	while((ny <= len[y] || nz <= len[z]) && len[x] < M) {
		if(ny > len[y] || tr[z][nz] > tr[y][ny]) tr[x][++len[x]] = tr[z][nz++];
		else tr[x][++len[x]] = tr[y][ny++];
	}
}

void build(int x, int l, int r) {
	if(l == r) {
		int val;
		scanf("%d", &val);
		tr[x][len[x] = 1] = val;
		return ;
	}
	int mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
	merge(x, ls, rs);
}

void Ask(int x, int l, int r, int L, int R) {
	if(L <= l && r <= R) {
		merge(da, db, x);
		for(int i = 1; i <= len[da]; ++i) 
			tr[db][i] = tr[da][i];
		len[db] = len[da];
		return ;
	}
	int mid = (l + r) >> 1;
	if(L <= mid) Ask(ls, l, mid, L, R);
	if(R > mid) Ask(rs, mid + 1, r, L, R);
}

int main() {
	// freopen("in11", "r", stdin);
	int n, q;
	while(scanf("%d%d", &n, &q) == 2) {
		for(int i = 1; i <= n * 4; ++i) {
			len[i] = 0;
			for(int j = 1; j <= M; ++j) {
				tr[i][j] = 0;
			}
		}
		build(1, 1, n);
		for(int o = 1, l, r; o <= q; ++o) {
			len[da] = len[db] = 0;
			int flg = 0;
			scanf("%d%d", &l, &r);
			Ask(1, 1, n, l, r);
			for(int i = 1; i <= len[da] - 2; ++i) {
				if(tr[da][i] < tr[da][i + 1] + tr[da][i + 2]) {
					printf("%lld\n", 1ll * tr[da][i] + 1ll * tr[da][i + 1] + 1ll * tr[da][i + 2]);
					flg = 1;
					break;
				}
			}
			if(!flg) puts("-1");
		}
	}
}