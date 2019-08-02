#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n;
int use[N], a[N];

int gcd(int A, int B) {
	return B ? gcd(B, A % B) : A;
}

void dfs(int dep, int fi, int se) {
	if(dep == n + 1) {
		if(fi == 1 && se == 1) {
			puts("YES");
			for(int i = 1; i <= n; ++i) {
				printf("%d ", use[i]);
			}
			puts("");
			exit(0);
		}
		return ;
	}
	int nfi = gcd(fi, a[dep]), nse = gcd(se, a[dep]);
	if(nfi != fi) {
		use[dep] = 1;
		dfs(dep + 1, nfi, se);
	}
	use[dep] = 2;
	dfs(dep + 1, fi, nse);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	dfs(1, 0, 0);
	puts("NO");
	return 0;
}