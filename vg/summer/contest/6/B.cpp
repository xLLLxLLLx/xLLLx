#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10;
ll dis[N], a[N];
int vis[N], ed[N], vv[10], res = 0, n;

int zh(int y, int x) {
	return x * n + y;
}

void go(int x, int id) {
	// printf("%d %d\n", x, id);
	int num = zh(x, id);
	if(x == 1) {
		ed[num] = id + 1;
		return ;
	}
	vis[num] = res;
	if(!id) {
		int pos = x + a[x], nid = id ^ 1;
		int tmp = zh(pos, nid);
		if(pos > n) {
			dis[num] = a[x];
			return ;
		} else if(vis[tmp] == vis[num]) {
			dis[num] = -1;
			return ;
		} else {
			if(!vis[tmp]) {
				go(pos, nid);
			}
			if(dis[tmp] == -1) dis[num] = -1;
			else dis[num] = dis[tmp] + a[x];
			ed[num] = ed[tmp];
		}
	} else {
		int pos = x - a[x], nid = id ^ 1;
		int tmp = zh(pos, nid);
		if(pos <= 0) {
			dis[num] = a[x];
			return ;
		} else if(vis[num] == vis[tmp]) {
			dis[num] = -1;
			return ;
		} else {
			if(!vis[tmp]) {
				go(pos, nid);
			}
			if(dis[tmp] == -1) dis[num] = -1;
			else dis[num] = dis[tmp] + a[x];
			ed[num] = ed[tmp];
		}
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 2; i <= n; ++i) {
		cin >> a[i];
	}
	for(int i = 2; i <= n; ++i) 
	 for(int j = 0; j < 2; ++j) {
		if(!vis[zh(i, j)]) {
			++res;
			go(i, j);
		}
	}
	for(int i = 1; i < n; ++i) {
		memset(vv, 0, sizeof vv);
		int tt = zh(i + 1, 1);
		ll pos = dis[tt];
		if(ed[tt] == 1) {
			printf("-1\n");
		} else if(ed[tt] == 2){
			cout << pos + i + i << endl;
		} else {
			if(pos == -1) printf("-1\n");
			else cout << pos + i <<endl;
		}
	}
	return 0;
}