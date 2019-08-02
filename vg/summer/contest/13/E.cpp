#include <bits/stdc++.h>
using namespace std;
const int N = 310;
char sr[15];
string F[N], S[N], T[N];

bool cmp(string a, string b) {
	if(a.size() != b.size()) return a.size() > b.size();
	else return a > b;
}

bool change(string &a, string b) {
	if(a == "" || cmp(a, b)) {
		a = b;
		return true; 
	} else return false;
}

void init() {
	F[15] = 'x', F[51] = 'y', F[85] = 'z';
	int pos = (1 << 8) - 1;
	for(;;) {
		int ok = 0;
		for(int i = 0; i <= pos; ++i) {
			if(T[i] != "") {
				ok |= change(F[i], '(' + T[i] + ')');
			}
		}
		for(int i = 0; i <= pos; ++i) {
			if(F[i] != "") ok |= change(F[pos ^ i], '!' + F[i]);
		}
		for(int i = 0; i <= pos; ++i) {
			if(F[i] != "") ok |= change(S[i], F[i]);
		}
		for(int i = 0; i <= pos; ++i) 
			for(int j = 0; j <= pos; ++j) {
				if(S[i] != "" && F[j] != "") {
					ok |= change(S[i & j], S[i] + '&' + F[j]);
				}
			}
		for(int i = 0; i <= pos; ++i) {
			if(S[i] != "") ok |= change(T[i], S[i]);
		}
		for(int i = 0; i <= pos; ++i)
			for(int j = 0; j <= pos; ++j) {
				if(T[i] != "" && S[j] != "") {
					ok |= change(T[i | j], T[i] + '|' + S[j]);
				}
			}
		if(!ok) break;
	}
}

int main() {
	init();
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%s", sr + 1);
		int len = strlen(sr + 1), pos = 0;
		for(int j = 1; j <= len; ++j) {
			pos = pos * 2 + (sr[j] == '1');
		}
		// printf("%d\n", pos);
		cout << T[pos] << endl;
	}
	return 0;
}