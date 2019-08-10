#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
int cnt = 0;
int ch[N][30];
string s[N];
ll d[N], a[N];
char lx[N];
 
vector<int> g[N];
int fail[N], vis[N], vs[N], deg[N];
void insert(int x) {
	int len = s[x].size();
	int fa = 0;
	for(int i = 0; i < len; ++i) {
		int pos = s[x][i] - 'a' + 1;
		if(!ch[fa][pos]) ch[fa][pos] = ++cnt;
		fa = ch[fa][pos];
	}
	vis[fa]++;
}
 
void reinsert(int x) {
	int len = s[x].size();
	int fa = 0;
	for(int i = len - 1; i >= 0; --i) {
		int pos = s[x][i] - 'a' + 1;
		if(!ch[fa][pos]) {
			ch[fa][pos] = ++cnt;
			memset(ch[cnt], 0, sizeof ch[cnt]);
		}
		fa = ch[fa][pos];
	}
	vis[fa]++;
}
 
queue<int> q;
 
void build() {
	int fa = 0;
	for(int i = 1; i <= 26; ++i) {
		if(ch[fa][i]) 
			q.push(ch[fa][i]);
	}
	while(!q.empty()) {
		int h = q.front(); q.pop();
		for(int i = 1; i <= 26; ++i) {
			int f = fail[h];
			if(!ch[h][i]) ch[h][i] = ch[f][i];
			else {
				while(f && !ch[f][i]) f = fail[f];
				q.push(ch[h][i]);
				fail[ch[h][i]] = ch[f][i];
			}
		}
		vis[h] += vis[fail[h]];
	}
}
 
void search(ll *t) {
	// puts("xxxx");
	int len = strlen(lx + 1);
	int fa = 0;
	for(int i = 1; i <= len; ++i) {
		int x = lx[i] - 'a' + 1;
		// printf("%d\n", x);
		while(fa && !ch[fa][x]) fa = fail[fa];
		if(ch[fa][x]) {
			fa = ch[fa][x];
			t[i] += vis[fa];
		}
	}
}
int n;

void init() {
	memset(vis, 0, sizeof vis);
	cnt = 0, memset(ch[0], 0, sizeof ch[0]);
	memset(fail, 0, sizeof fail);
}
 
int main() {
	scanf("%s", lx + 1);
	int len = strlen(lx + 1);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		cin >> s[i];
		insert(i);	
	}
	build();
	search(d);
	
	init();
	
	for(int i = 1; i <= n; ++i) {
		reinsert(i);
	}
	build();
	reverse(lx + 1, lx + 1 + len);
	search(a);
 	ll ans = 0;
 	for(int i = 1; i <= len; ++i) {
 		ans += a[i] * d[len - i];
 	}
	printf("%lld\n", ans);
	return 0;
}