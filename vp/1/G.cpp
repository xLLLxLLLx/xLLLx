#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct data {
	int x, y, id;
} a[N];
struct node {
	int w, id;
} tr[N];
vector<int> g;
int all[N], pr[N];

bool cmp(data A, data B) {
	return A.x == B.x ? A.y < B.y : A.x < B.x;
}

int lower(int x) {
	return x & (-x);
}

void upd(int x, node y) {
	for(; x < N; x += lower(x)) 
		if(tr[x].w < y.w) 
			tr[x] = y;
}

node get(int x) {
	node ans = (node){0, 0};
	for(; x; x -= lower(x))
		if(ans.w < tr[x].w)
			ans = tr[x];
	return ans;
}

void go(int x) {
	if(!x) return ;
	go(pr[x]);
	g.push_back(x);
}

int val[N];

int main() {
	freopen("people.in", "r", stdin);
	freopen("people.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i].x, &a[i].y);
		all[i] = a[i].y;
		a[i].id = i;
	}
	sort(all + 1, all + 1 + n);
	int m = unique(all + 1, all + 1 + n) - all - 1;
	for(int i = 1; i <= n; ++i)
		a[i].y = lower_bound(all + 1, all + 1 + m, a[i].y) - all;
	sort(a + 1, a + 1 + n, cmp);
	int ans = 0, be = 0;
	for(int i = 1; i <= n; ++i) {
		int l = i, r = i;
		for(; r + 1 <= n && a[r + 1].x == a[l].x; r++); 
		for(int j = l; j <= r; ++j) {
			node pos = get(a[j].y - 1);
			val[j] = pos.w + 1;
			pr[a[j].id] = pos.id;
			if(val[j] > ans) {
				ans = val[j];
				be = a[j].id;
			}
		}
		for(int j = l; j <= r; ++j) 
			upd(a[j].y, (node){val[j], a[j].id});
		i = r;
	}
	printf("%d\n", ans);
	go(be);
	sort(g.begin(), g.end());
	for(int i = 0; i < g.size(); ++i)
		printf("%d ", g[i]);
	puts("");
	return 0;
}