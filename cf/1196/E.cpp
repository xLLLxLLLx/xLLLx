#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
int a[N], b[N];

void out(int tot) {
	for(int i = 1; i <= tot; ++i) {
		printf("%d %d\n", a[i], b[i]);
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int b, w;
		scanf("%d%d", &b, &w);
		int tot = b + w, now = 0;
		if(b > w) {
			if(b > 3 * w + 1) {
				printf("No\n");
				continue;
			}
			
		} else if(b < w) {
			if(w > 3 * b + 1) {
				printf("No\n");
				continue;
			}
		} else {
			for(int i = 1; i <= b; ++i) {
				a[++now] = i * 2 - 1, b[now] = 1;
				a[++now] = i * 2, b[now] = 1;
			}
		}
		out(tot);
	}
	return 0;
}