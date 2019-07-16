#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
struct data {
	int w, id;
} c[N];
int na[N], nb[N];

bool cmp(data A, data B) {
	return A.w < B.w;
}

int main() {
	int n, x1, x2;
	scanf("%d%d%d" ,&n, &x1, &x2);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &c[i].w);
		c[i].id = i;
	}
	sort(c + 1, c + 1 + n, cmp);
	for(int i = 1; i <= n; ++i) {
		int pos = x1 / c[i].w;
		if(x1 % c[i].w) pos++;
		if(i + pos - 1 > n) {
			continue;
		}
		int tmp = n - (i + pos - 1);
		if(1ll * tmp * c[i + pos].w >= x2) {
			puts("Yes");
			printf("%d %d\n", pos, tmp);
			for(int j = 1; j <= pos; ++j) {
				printf("%d ", c[i + j - 1].id);
			}
			puts("");
			for(int j = i + pos; j <= n; ++j) {
				printf("%d ", c[j].id);
			}
			return 0;
		}
	}
	for(int i = 1; i <= n; ++i) {
		int pos = x2 / c[i].w;
		if(x2 % c[i].w) pos++;
		if(i + pos - 1 > n) {
			continue;
		}
		int tmp = n - (i + pos - 1);
		if(1ll * tmp * c[i + pos].w >= x1) {
			puts("Yes");
			printf("%d %d\n", tmp, pos);
			for(int j = i + pos; j <= n; ++j) {
				printf("%d ", c[j].id);
			}
			puts("");
			for(int j = 1; j <= pos; ++j) {
				printf("%d ", c[i + j - 1].id);
			}
			return 0;
		}
	}
	puts("No");
	return 0;
}