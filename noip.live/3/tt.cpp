#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int a[N], b[N];

int main() {
	int n;
	while(scanf("%d", &n) == 1 && n) {
		for(int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		for(int i = 1; i <= n; ++i) 
			scanf("%d", &b[i]);
		sort(a + 1, a + 1 + n), sort(b + 1, b + 1 + n);
		int lt = 1, res = 0;
		// for(int i = 1; i <= n; ++i) {
		// 	printf("%d ", a[i]);
		// }
		// puts("");
		// for(int i = 1; i <= n; ++i) {
		// 	printf("%d ", b[i]);
		// }
		// puts("");
		for(int i = 1; i <= n; ++i) {
			// printf("quq%d %d\n", lt, i);
			while(lt <= n && a[lt] < b[i]) 
				lt++, res--;
			// printf("qwq%d %d\n", lt, i);
			if(lt <= n) {
				if(a[lt] > b[i]) res++;
				else {
					if(lt < n && a[lt + 1] > b[i] && i != n && a[lt + 1] <= b[i + 1]) lt++;
				}
				lt++;
			}
		}
		printf("%d\n", res * 200);
	}
	return 0;
}