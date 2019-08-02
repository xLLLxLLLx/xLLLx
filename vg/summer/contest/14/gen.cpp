#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(time(NULL));
	int n = 3 + rand() % 199998, k = rand() % (n - 2) + 2;
	printf("%d %d\n", n, k);
	return 0;
}