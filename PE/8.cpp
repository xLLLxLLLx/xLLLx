#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1010;
int a[N];

int main() {
	ll maxn = 0;
	for(int i = 1; i <= 1000; ++i) {
		scanf("%1d", &a[i]);
	}
	for(int i = 1; i <= 1000; ++i) {
		if(i + 12 > 1000) break;
		ll pos = 1;
		for(int j = 1; j <= 13; ++j) {
			pos = pos * a[i + j - 1];
		}
		maxn = max(maxn, pos);
	}
	cout << maxn << endl;
	return 0;
}