#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
struct data {
	int c, t, id;
} a[N];
int tr[N], jump[N], d[N], mn[N];

int lower(int x) {
	return x & (-x);
}

void upd(int x, int y) {
	for(; x < N; x += lower(x)) 
		tr[x] = min(tr[x], y);
}

int get(int x) {
	int ans = N;
	for(; x; x -= lower(x)) 
		ans = min(ans, tr[x]);
	return ans;
}

void dpd(int x, int y) {
	for(; x; x -= lower(x))
		jump[x] = min(jump[x], y);
}

int got(int x) {
	int ans = N;
	for(; x < N; x += lower(x))
		ans = min(ans, jump[x]);
	return ans;
}

bool cmp(data A, data B) {
	return A.c > B.c;
}

int main() {
	freopen("codecoder.in", "r", stdin);
	freopen("codecoder.out", "w", stdout);
	memset(mn, 0x3f, sizeof mn);
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i].c, &a[i].t);
		a[i].id = i;
	}
	for(int i = 0; i < N; ++i)
		tr[i] = jump[i] = N;
	sort(a + 1, a + 1 + n, cmp);
	for(int i = 1; i <= n; ++i) {
		d[a[i].id] = n - i;
		int pos = get(a[i].t);
		upd(a[i].t, i);
		if(pos == N) {
			mn[i] = i;
			dpd(i, i);
			continue;
		}
		int tmp = got(pos);
		mn[i] = tmp;
		dpd(i, tmp);
	}
	for(int i = n; i >= 1; --i)
		mn[i] = min(mn[i], mn[i + 1]);
	for(int i = 1; i <= n; ++i)
		d[a[i].id] += i - mn[i];
	for(int i = 1; i <= n; ++i) {
		printf("%d\n", d[i]);
	}
	return 0;
}