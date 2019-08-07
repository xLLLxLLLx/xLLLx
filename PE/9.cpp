#include <bits/stdc++.h>
using namespace std;

int main() {
	for(int i = 1; i <= 1000; ++i)
		for(int j = 1; j <= 1000; ++j) {
			int k = 1000 - i - j;
			if(k < 0) break;
			if(i * i + j * j == k * k) {
				printf("%d\n", i * j * k);
			}
		}
	return 0;
}