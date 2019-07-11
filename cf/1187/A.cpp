#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
	cin>>T;
	for(int i = 1; i <= T; ++i) {
		int n, s, t;
		cin>>n>>s>>t;
		if(s > t) {
			swap(s, t);
		}
		int pos = s + t - n;
		printf("%d\n", t - pos + 1);
	}
	return 0;
}