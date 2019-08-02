#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
int a[N];

int main() {
	int n, x, y;
	cin >> n >> x >> y;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	for(int i = 1; i <= n; ++i) {
		int flg = 1;
		for(int j = max(i - x, 1); j < i; ++j) {
			if(a[j] <= a[i]) {
				flg = 0;
			}
		}
		for(int j = i + 1; j <= min(n, i + y) ; ++j) {
			if(a[j] <= a[i]) {
				flg = 0;
			}
		}
		if(flg) {
			printf("%d\n", i);
			return 0;
		}
	}
	return 0;
}