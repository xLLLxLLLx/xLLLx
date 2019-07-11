#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct data {
	int w, id;
} a[N], b[N], s[N];

bool cmp(data A, data B) {
	return A.w < B.w;
}

bool comp(data A, data B) {
	return A.id < B.id;
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &s[i].w);
		s[i].id = i;
	}
	sort(s + 1, s + 1 + n, cmp);
	int pos = (n + 2) / 3;
	for(int i = 1; i <= pos; ++i) {
		a[i].w = i - 1;
		b[i].w = s[i]. w - a[i].w;
	}
	for(int i = pos + 1; i <= 2 * pos; ++i) {
		b[i].w = i - 1;
		a[i].w = s[i].w - b[i].w;
	}
	for(int i = 2 * pos + 1; i <= n; ++i) {
		b[i].w = n - i;
		a[i].w = s[i].w - b[i].w;
	}
	for(int i = 1; i <= n; ++i) {
		a[i].id = b[i].id = s[i].id;
	}
	sort(a + 1, a + 1 + n, comp);
	sort(b + 1, b + 1 + n, comp);
	printf("YES\n");
	for(int i = 1; i <= n; ++i) {
		printf("%d ", a[i].w);
	}
	puts("");
	for(int i = 1; i <= n; ++i) {
		printf("%d ", b[i].w);
	}
	return 0;
}