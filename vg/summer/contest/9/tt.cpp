#include <bits/stdc++.h>
using namespace std;
int a[10];

int main() {
	int x = 7;
	for(int i = 1; i <= 8; ++i) a[i] = 3;
	a[9] = 10;
	int *v = a + x;
	for(int i = 1; i <= 9; ++i) cout<<v[i]<<endl;
	return 0;
}