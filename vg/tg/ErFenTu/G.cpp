#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 25, M = 10;
char s[5] = {'S', 'M', 'L', 'X', 'T'};
char lx[N];
int n, a[N][M], nm[M], now[M], vis[M], mx[M][N];

int zh(char ch) {
	for(int i = 0; i < 5; ++i) {
		if(ch == s[i]) return i;
	}
}

bool dfs(int x) {
	for(int i = 0; i < 5; ++i) {
		if(!a[x][i] || vis[i]) continue;
		if(now[i] + 1 >= nm[i]) vis[i] = 1;
		if(nm[i] > now[i]) {
			mx[i][++now[i]] = x;
			return true;
		} else {
			for(int j = 1; j <= now[i]; ++j) {
				if(dfs(mx[i][j])) {
					mx[i][j] = x;
					return true;
				}
			}
		}
	}
	return false;
}

bool check() {
	for(int i = 1; i <= n; ++i) {
		memset(vis, 0, sizeof vis);
		if(!dfs(i)) 
			return false;
	}
	return true;
}

int main() {
	for(;;) {
		scanf("%s", lx + 1);
		if(lx[1] != 'S') break;
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) {
			scanf("%s", lx + 1);
			int L = zh(lx[1]), R = zh(lx[2]);
			for(int j = L; j <= R; ++j) {
				a[i][j] = 1;
			}
		}
		for(int i = 0; i < 5; ++i)
			scanf("%d", &nm[i]);
		if(check())
			puts("T-shirts rock!");
		else 
			puts("I'd rather not wear a shirt anyway...");
		scanf("%s", lx + 1);
		memset(a, 0, sizeof a);
		memset(mx, 0, sizeof mx);
		memset(now, 0, sizeof now);
	}
	return 0;
}