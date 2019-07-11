#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	for(int i = 60; i >= 0; --i) {
		if(n & (1ll << i)) {
			printf("%d\n", i);
		}
	}
	return 0;
}