#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;

namespace PAM {
	int len[N], fail[N], Next[N][26];
	int cnt;
	void init() {
		cnt = 2;
		len[1] = -1, fail[1] = 1;
		len[2] = 0, fail[2] = 1;
		memset(Next, 0, sizeof Next);
	}

	void build(char *s, int n) {
		init();
		s[0] = '*';
		int x = 1;
		for(int i = 1; i <= n; ++i) {
			for(; s[i - len[x] - 1] != s[i]; x = fail[x]) ;
			int c = s[i] - 'a';
			if(Next[x][c]) {
				x = Next[x][c];
			} else {
				int y = Next[x][c] = ++cnt;
				len[y] = len[x] + 2;
				if(len[y] == 1) {
					fail[y] = 2;
				} else {
					x = fail[x];
					for(; s[i - len[x] - 1] != s[i]; x = fail[x]);
					fail[y] = Next[x][c];
				}
				x = y;
			}
		}
	}
}

char s[N], ss[N];
int len[N];

void Manachar(char *s, int n) {
	for(int i = 0; i <= n + 1; ++i)
		len[i] = 0;
	int mx = 1;
	for(int i = 1; i <= n; ++i) {
		len[i] = max(1, min(mx + len[mx] - i, len[mx * 2 - i]));
		for(; s[i - len[i]] == s[i + len[i]]; ++len[i]);
			if(i + len[i] > mx + len[mx])
				mx = i;
	}
}

int solve(char *s, int n) {
	ss[0] = '#', ss[1] = '*';
	for(int i = 1; i <= n; ++i) {
		ss[i << 1] = s[i];
		ss[i << 1 | 1] = '*';
	}
	ss[n * 2 + 2] = '$';
	Manachar(ss, n * 2 + 1);
	int ans = 0;
	for(int i = 1; i <= n * 2 + 1; ++i) {
		printf("%d %d\n", i, len[i] - 1);
		ans = max(ans, len[i] - 1);
	}
	return ans;
}

bool check(int l, int r) {
	l <<= 1, r <<= 1;
	int mid = (l + r) >> 1;
	return len[mid] >= (r - l) / 2;
}

int main() {
	while(scanf("%s", s + 1) != EOF) {
		int n = strlen(s + 1);
		PAM::build(s, len);
		solve(s, n);

	}
	return 0;
}