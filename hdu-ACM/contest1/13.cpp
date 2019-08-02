#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 310;

struct P {
	ll x, y;
	
	P() { x = y = 0; }
	P(ll _x, ll _y) { x = _x, y = _y; }
	
	P operator + (P C) { return P(x + C.x, y + C.y); }
	P operator - (P C) { return P(x - C.x, y - C.y); }

	ll operator * (P C) {
		if(!x && !C.x) return 0ll;
		if(!x) return -y;
		if(!C.x) return C.y;
		if(x * C.y == y * C.x) return 0ll;
		if(1.0 * y / x < 1.0 * C.y / C.x) return 1;
		else return -1;
	}

	bool operator < (P &C) const {
		return x == C.x ? y < C.y : x < C.x;
	}
} a[N], b[N], qa[N], qb[N], ans[N], numa = 0, numb = 0;

void MakeConvex(int &num, int cnt, P *A, P *q) {
	if(!cnt) {
		num = 0;
		return ;
	}
	sort(A + 1, A + 1 + cnt);
	q[num = 1] = A[1];
	for(int i = 2; i <= cnt; ++i) {
		for( ; num >= 2; --num) {
			if((A[i] - q[num - 1]) * (q[num] - q[num - 1]) > 0) {
				break;
			}
		}
		q[++num] = A[i];
	}
}

void merge() {
	if(!na || !nb) {
		int L = max(na, nb);
		for(int i = 1; i <= L; ++i) {
			ans[++len] = na ? qa[i] : qb[i];
		}
		return ;
	}
	ans[++len] = qa[1] + qb[1];
	for(int u = 2, v = 2; u <= na || v <= nb; ) {
		if(u > na) {
			ans[++len] = qa[u - 1] + qb[v++];
		} else if(v > nb) {
			ans[++len] = qa[u++] + qb[v - 1];
		} else {
			P du = qa[u] - qa[u - 1], dv = qb[v] - qb[v - 1];
			if(du * dv < 0) {
				ans[++len] = qa[u++] + qb[v - 1];
			} else {
				ans[++len] = qa[u - 1] + qb[v++];
			}
		}
	}
}

void ok() {
	printf("Successful!\n");
}

void no() {
	printf("Infinite loop!\n");
}

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n, na = 0, nb = 0;
		numa = numb = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) {
			ll x, y, z;
			scanf("%lld%lld%lld", &x, &y, &z);
			if(z == 1) a[++na] = P(x, y);
			else b[++nb] = P(x, y);
		}
		MakeConvex(numa, na, a, qa);
		MakeConvex(numb, nb, b, qb);
		merge();
		for(int i = 1
	}
}