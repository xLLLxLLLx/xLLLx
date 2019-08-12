#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
set<int> s;
int a[N];
char lx[N];

int main() {
	int n;
	scanf("%d%s", &n, lx + 1);
	for(int i = 1; i <= 10; ++i) s.insert(i);
	for(int i = 1; i <= n; ++i) {
		if(lx[i] == 'L') {
			int pos = *s.begin();
			a[pos] = 1;
			s.erase(pos);
		} else if(lx[i] == 'R') {
			int pos = *s.rbegin();
			a[pos] = 1;
			s.erase(pos);
		} else {
			int pos = lx[i] - '0' + 1;
			s.insert(pos);
			a[pos] = 0;
		}
	}
	for(int i = 1; i <= 10; ++i)
		printf("%d", a[i]);
	puts("");
	return 0;
}