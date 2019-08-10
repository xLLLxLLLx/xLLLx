#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10, M = 15;
struct data {
	int be, ed;
};
queue<int> q;
int a[M][M];
int trans[M][M], vis[M];

void Min(int &x, int y) {
	if(x == -1) x = y;
	else x = min(x, y);
}

void go(int x, int y) {
	memset(trans, -1, sizeof trans);
	memset(vis, 0, sizeof vis);
	q.push(0);
	vis[0] = 1;
	while(!q.empty()) {
		int h = q.front(); q.pop();
		int pos = (h + x) % 10, tmp = (h + y) % 10;
		if(!vis[pos]) {
			vis[pos] = 1;
			q.push(pos);
		}
		if(!vis[tmp]) {
			vis[tmp] = 1;
			q.push(tmp);
		}
		trans[h][pos] = trans[h][tmp] = 1;
	}
	for(int k = 0; k <= 9; ++k)
		for(int i = 0; i <= 9; ++i)
			for(int j = 0; j <= 9; ++j) {
				if(trans[i][k] == -1 || trans[k][j] == -1) continue;
				Min(trans[i][j], trans[i][k] + trans[k][j]);
			}
}

char lx[N];
int b[N];

int main() {
	scanf("%s", lx + 1);
	int len = strlen(lx + 1);
	for(int i = 1; i <= len; ++i)
		b[i] = lx[i] - '0';
	for(int i = 0; i < 10; ++i) 
		for(int j = 0; j < 10; ++j) {
			go(i, j);
			for(int k = 2; k <= len; ++k) {
				if(trans[b[k - 1]][b[k]] == -1) {
					a[i][j] = -1;
					break;
				} else {
					a[i][j] += trans[b[k - 1]][b[k]] - 1;
				}
			}
		}
	for(int i = 0; i <= 9; ++i) {
		for(int j = 0; j <= 9; ++j) {
			printf("%d ", a[i][j]);
		}
		puts("");
	}
	return 0;
}