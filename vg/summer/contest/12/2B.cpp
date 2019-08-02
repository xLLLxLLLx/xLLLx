#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	if(n > 36) printf("-1\n");
	else {
		int pos = n / 2, gg = n % 2;
		for(int i = 1; i <= pos; ++i) printf("8");
		for(int i = 1; i <= gg; ++i) printf("4");
	}	
	return 0;
}