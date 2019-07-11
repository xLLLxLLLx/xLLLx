#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
	int x, y;
	cin >> x >> y;
	if(x > y) {
		return printf("0\n"), 0;
	}
	x--;
	if(x < 0) x++;
	ll ans = 0;
	for(int i = 1; i <= y; ++i) {
		ans += (long long)(y / i - x / i);
	}	
	cout<<ans<<endl;
	return 0;
}