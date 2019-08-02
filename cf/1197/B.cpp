#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int a[N];

int main() {
	int n;
	scanf("%d", &n);
	int maxn = 0, be = 0, sum = 0;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		if(a[i] > maxn) {
			maxn = a[i];
			be = i;
			sum = 1;
		} else if(a[i] == maxn) {
			sum++;
		}
	}
	if(sum > 1) printf("No\n");
	else {
		for(int i = 1; i < be; ++i) {
			if(a[i] <= a[i - 1]) return printf("No\n"), 0;
		}
		for(int i = be + 1; i <= n; ++i) {
			if(a[i] >= a[i - 1]) return printf("No\n"), 0;
		}
		puts("Yes");
	}
	return 0;
}