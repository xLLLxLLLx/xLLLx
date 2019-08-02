#include <bits/stdc++.h>
using namespace std;
const int N = 110;
struct data {
	int d, m, y, id;
} a[N];

bool cmp(data A, data B) {
	if(A.y != B.y) return A.y > B.y;
	if(A.m != B.m) return A.m > B.m;
	return A.d > B.d;
}

int main() {
	freopen("king.in", "r", stdin);
	freopen("king.out", "w", stdout);
	int d, m, y;
	cin >> d >> m >> y;
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		a[i].id = i;
		scanf("%d%d%d", &a[i].d, &a[i].m, &a[i].y);
	}
	sort(a + 1, a + 1 + n, cmp);
	for(int i = 1; i <= n; ++i) {
		if(a[i].y + 18 < y) {
			return printf("%d\n", a[i].id), 0;
		} else if(a[i].y + 18 == y) {
			if(a[i].m < m) {
				return printf("%d\n", a[i].id), 0;
			} else if(a[i].m == m) {
				if(d >= a[i].d) {
					return printf("%d\n", a[i].id), 0;
				}
			}
		}
	}
	printf("-1\n");
	return 0;
}