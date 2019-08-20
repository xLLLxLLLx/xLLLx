#include <bits/stdc++.h>
using namespace std;
const int N = 2010;
struct data {
	int x, y, w;
} a[N];
int f[N], res = 0;

bool cmp(data A, data B) {
	return A.w < B.w;
}

int find(int k) {
	return f[k] == k ? k : f[k] = find(f[k]);
}

int kruskal() {
	int ans = 0;
	sort(a + 1, a + 1 + res, cmp);
	for(int i = 1; i <= 40; ++i) {
		f[i] = i;
	}
	for(int i = 1; i <= res; ++i) {
		int fx = find(a[i].x), fy = find(a[i].y);
		if(fx == fy) {
			continue;
		}
		ans += a[i].w;
		f[fx] = fy;
	}
	return ans;
}

char lx[N];

int main() {
	int sum = 0;
	for(int i = 1; i <= 40; ++i) {
		scanf("%s", lx + 1);
		int len = strlen(lx + 1), now = 0;
		for(int j = 1; j <= len; ++j) {
			int pos = 0;
			for(; j <= len && lx[j] != ','; ++j) {
				if(lx[j] >= '0' && lx[j] <= '9')
					pos = pos * 10 + lx[j] - '0';
			}
			++now;
			sum += pos;
			printf("%d ", pos);
			if(pos && i < now)
				a[++res] = (data){i, now, pos};
		}
		puts("");
	}
	printf("%d %d\n", res, sum / 2 - kruskal());
	return 0;
}