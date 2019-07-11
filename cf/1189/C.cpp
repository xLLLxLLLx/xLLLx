#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N], b[N];

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &b[i]);
	}
	sort(b + 1, b + 1 + n);
	for(int i = 1; i <= n; ++i) {
		
	}
	for(int i = 2; i < n; ++i) {
		if(a[i] >= a[i - 1] + a[i + 1]) {
			printf("NO\n");
			return 0;
		}
	}
	if(a[2] + a[n] <= a[1] || a[1] + a[n - 1] <= a[n]) {
		return printf("NO\n"), 0;
	} 
	printf("YES\n");
	for(int i = 1; i <= n; ++i) {
		printf("%d ", a[i]);
	}
	return 0;
}