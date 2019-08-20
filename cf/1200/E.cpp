#include <bits/stdc++.h>
using namespace std;
string ll, lx;

int main() {
	int T;
	scanf("%d", &T);
	ll = "";
	for(int o = 1; o <= T; ++o) {
		cin >> lx;
		int len1 = ll.size(), len2 = lx.size(), flg = 0;
		for(int i = 0; i < len2; ++i) {
			if(ll[len1 - 1] == lx[i]) {
				int pos = len1 - 1, tmp = ;
				for(pos >= 0 && tmp >= 0) {

				}
			}
		}
		if(!flg) {
			ll += lx;
		}
	}
	cout << ll << endl;
	return 0;
}