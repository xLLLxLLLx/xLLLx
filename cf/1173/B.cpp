#include<bits/stdc++.h>
using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	int pos=(n+1)/2+((n+1)&1);
	printf("%d\n", pos);
	for(int i = 1; i <= n; ++i) {
		if(i<=pos) printf("1 %d\n", i);
		else {
			printf("%d %d\n",i-pos+1,pos);
		}
	}
	return 0;
}