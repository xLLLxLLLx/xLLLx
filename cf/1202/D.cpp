#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n;
		scanf("%d", &n);
		int w;
		for(w = 2; w * (w - 1) / 2 <= n; ++w) ;
		w--;
		printf("1");
		for(int i = 1; i <= w - 2; ++i)
			printf("3");
		for(int i = 1; i <= n - w * (w - 1) / 2; ++i) 
			printf("1");
		printf("337\n");
	}
	return 0;
}