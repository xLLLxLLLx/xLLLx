#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int a[N], vis[N], b[N];

int main() {
	int n;
	scanf("%d", &n);
	int cnt = 0, res = 0, tot = 0;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		if(a[i] > 0) {
			vis[a[i]]++;
		} else if(a[i] == 0) {
			res++, tot++;
		} else {
			a[i] = -a[i];
			if(vis[a[i]]) vis[a[i]]--;
			else {
				if(!res) return printf("No\n"), 0;
				else b[++b[0]] = a[i], res--;
			}
		}
	}
	printf("Yes\n");
	for(int i = b[0] + 1; i <= tot; ++i) b[i] = 1;
	for(int i = 1; i <= tot; ++i) {
		printf("%d ", b[i]);
	}
	return 0;
}