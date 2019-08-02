#include <bits/stdc++.h>
using namespace std;
queue<int> q;

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	int m = (n - 1) / k, yu = (n - 1) % k;
	if(!yu) printf("%d\n", m * 2);
	else if(yu == 1) printf("%d\n", m * 2 + 1);
	else printf("%d\n", m * 2 + 2);
	int now = k + 1;
	for(int i = 2; i <= k + 1; ++i) printf("1 %d\n", i), q.push(i);
	for(;;) {
		now++;
		if(now > n) break;
		printf("%d %d\n", now, q.front());
		q.pop(), q.push(now);
	}
	return 0;
}