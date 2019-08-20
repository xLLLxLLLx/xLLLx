#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10, M = 6010;
struct data {
	string s;
	int len;
	data() {
		s = "";
	}
} a[M];
char lx[N];

bool cmp(data A, data B) {
	int x = A.len, y = B.len;
	for(int i = 0; i < min(x, y); ++i) {
		if(A.s[i] > B.s[i]) return false;
		if(A.s[i] < B.s[i]) return true;
	}
	return x <= y;
}

int main() {
	freopen("22.in", "r", stdin);
	scanf("%s", lx + 1);
	int len = strlen(lx + 1), now = 0;
	for(int i = 1; i <= len; ++i) {
		++now;
		for(;i <= len && lx[i] < 'A' || lx[i] > 'Z'; ++i);
		for(;i <= len && lx[i] >= 'A' && lx[i] <= 'Z'; ++i)
			a[now].s += lx[i], a[now].len++;
		cout << a[now].s << endl;
	}
	printf("now = %d\n", now);
	sort(a + 1, a + 1 + now, cmp);
	ll ans = 0;
	for(int i = 1; i <= now; ++i) {
		int pos = 0;
		for(int j = 0; j < a[i].len; ++j) {
			pos += a[i].s[j] - 'A' + 1;
		}
		ans += 1ll * i * pos;
	}
	printf("%lld\n", ans);
	return 0;
}