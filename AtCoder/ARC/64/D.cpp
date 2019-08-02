#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
char lx[N];

int main() {
	scanf("%s", lx + 1);
	int len = strlen(lx + 1);
	if(lx[1] == lx[len]) {
		if(len & 1) printf("Second\n");
		else printf("First\n");
	} else {
		if(len & 1) printf("First\n");
		else printf("Second\n");
	}
	return 0;
}