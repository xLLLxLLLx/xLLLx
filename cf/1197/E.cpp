#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
struct data {
	int x, y;
} a[N];

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i].x, &a[i].y);
	}
	
	return 0;
}