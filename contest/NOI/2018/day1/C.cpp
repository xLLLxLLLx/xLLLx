#include <bits/stdc++.h>
#define ll long long

const int N = 2e6 + 10, M = 30;
char lx[N], s[N];
int n;
int a[N], id[N], sa[N], rk[N], nm[N], h[N];

void Sort() {
	memset(nm,0,sizeof nm);
	for(int i = 1; i <= n; ++i)
    nm[rk[i]]++;
	for(int i = 1; i <= max(M,n); ++i) 
    nm[i] += nm[i-1];
	for(int i = n; i >= 1; --i) 
    sa[nm[rk[id[i]]]--] = id[i];
}

void Geth() {
	int H = 0;
	for(int i = 1; i <= n; ++i){
		if(H) H--;
		int j = sa[rk[i] - 1];
		for(; a[i+H] == a[j+H]; ++H);
		h[rk[i]] = H;
	}
}

bool cmp(int x, int y, int j) {
	return id[x] == id[y] && id[x + j] == id[y + j];
}

int main() {
	scanf("%s", lx + 1);
	int T;
	scanf("%d", &T);
	for(int o = 1, l, r; o <= T; ++o) {
		scanf("%s%d%d", s + 1, &l, &r);
		int len1 = r - l + 1;
		int len2 = strlen(s + 1);
		n = len1 + len2 + 1;
		for(int i = 1; i <= len1; ++i)
			a[i] = lx[l + i - 1] - 'a' + 1;
		a[len1 + 1] = 27;
		for(int i = 1; i <= len2; ++i)
			a[len1 + i + 1] = s[i] - 'a' + 1;
		for(int i = 1; i <= n; ++i)
			id[i] = i, rk[i] = a[i];
		Sort();
		for(int j = 1, p = 0; p < n; j <<= 1) {
			p = 0;
			for(int i = n - j + 1; i <= n; ++i) 
	      id[++p] = i;
			for(int i = 1; i <= n; ++i) 
	      if(sa[i] > j) 
	        id[++p] = sa[i] - j;
			Sort(), swap(id, rk);
			p = 0;
			for(int i = 1; i <= n; ++i) 
	      rk[sa[i]] = cmp(sa[i], sa[i-1], j) ? p : ++p;
		}
		Geth();
		int now = 0, flg = 0;
		ll ans = 0;
		for(int i = 1; i <= n; ++i) {
			int pos = sa[i];
			now = 
			if(pos > len1 + 1) {

			} else if(pos <= len1) {
				
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}