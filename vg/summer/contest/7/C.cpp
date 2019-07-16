#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10, inf = 1e9;
struct data {
	ll tr, tl, sr, s, t, res, minn;
	int rd, ch[2];
	void print() {
		printf("tr=%d tl=%d sr=%d s=%d t=%d res=%d minn=%d ls=%d rs=%d\n", rd,tr,tl,sr,s,t,res,minn,ch[0],ch[1]); 
	}
} t[N];

void up(int x) {
	if(t[x].ch[0]) {
		t[x].tl = t[t[x].ch[0]].tl;
	} else t[x].tl = t[x].t;
	if(t[x].ch[1]) {
		t[x].tr = t[t[x].ch[1]].tr;
		t[x].sr = t[t[x].ch[1]].sr;
	} else {
		t[x].tr = t[x].t;
		t[x].sr = t[x].s;
	}
	t[x].res = 0, t[x].minn = 0;
	if(t[x].ch[0]) {
		t[x].minn = max(t[x].minn, t[t[x].ch[0]].minn);
		t[x].res += t[t[x].ch[0]].res;
		t[x].res += t[t[x].ch[0]].sr * (t[x].t - t[t[x].ch[0]].tr);
		t[x].minn = max(t[x].minn, -t[x].res);
	}
	if(t[x].ch[1]) {
		t[x].res += t[x].s * (t[t[x].ch[1]].tl - t[x].t);
		t[x].minn = max(t[x].minn, -t[x].res);
		t[x].minn = max(t[x].minn, -t[x].res + t[t[x].ch[1]].minn);
		t[x].res += t[t[x].ch[1]].res;
	}
}

void split(int now, int &x, int &y, ll k) {
	if(!now) {
		x = y = 0;
		return ;
	}
	if(t[now].t <= k) {
		x = now, split(t[now].ch[1], t[now].ch[1], y, k);
	} else {
		y = now, split(t[now].ch[0], x, t[now].ch[0], k);
	}
	up(now);
}

int merge(int x, int y) {
	if(!x || !y) return x ^ y;
	if(t[x].rd < t[y].rd) {
		t[x].ch[1] = merge(t[x].ch[1], y);
		up(x);
		return x;
	} else {
		t[y].ch[0] = merge(x, t[y].ch[0]);
		up(y);
		return y;
	}
}

double ask(int x, ll w) {
	if(t[x].ch[0]) {
		if(w <= t[t[x].ch[0]].minn) {
			return ask(t[x].ch[0], w);
		}
		w += t[t[x].ch[0]].res;
		if(w + t[t[x].ch[0]].sr * (t[x].t - t[t[x].ch[0]].tr) <= 0) {
			return t[t[x].ch[0]].tr - (double)w / t[t[x].ch[0]].sr;
		}
		w += t[t[x].ch[0]].sr * (t[x].t - t[t[x].ch[0]].tr);
	}
	if(t[x].ch[1]) {
		if(w + t[x].s * (t[t[x].ch[1]].tl - t[x].t) <= 0) {
			return t[x].t - (double)w / t[x].s;
		}
		w += t[x].s * (t[t[x].ch[1]].tl - t[x].t);
		return ask(t[x].ch[1], w);
	}
	return t[x].t - (double)w / t[x].s;
}

int main() {
	srand(time(NULL));
	int n, root = 0, cnt = 0, dx, dy, dz, dw;
	scanf("%d", &n);
	for(int i = 1, opt; i <= n; ++i) {
		scanf("%d", &opt);
		// printf("root=%d\n", root);
		if(opt == 1) {
			++cnt;
			scanf("%lld%lld", &t[cnt].t, &t[cnt].s);
			t[cnt].tl = t[cnt].tr = t[cnt].t;
			t[cnt].sr = t[cnt].s;
			t[cnt].rd = rand() % inf;
			t[cnt].ch[0] = t[cnt].ch[1] = 0;
			split(root, dx, dy, t[cnt].t);
			root = merge(merge(dx, cnt), dy);
		} else if(opt == 2) {
			int l;
			scanf("%lld", &l);
			split(root, dx, dy, l);
			split(dx, dz, dw, l - 1);
			root = merge(dz, dy);
		} else {
			ll l, r, w;
			scanf("%lld%lld%lld", &l, &r, &w);
			if(!w) {
				printf("%.8f\n", double(l));
				continue;
			}
			split(root, dx, dy, r);
			split(dx, dz, dw, l - 1);
			if(!dw) {
				printf("-1\n");
			} else if(w > t[dw].minn) {
				w += t[dw].res;
				if(w + (r - t[dw].tr) * t[dw].sr <= 0) {
					printf("%.8f\n", t[dw].tr - (double)w / t[dw].sr);
				} else printf("-1\n");
			} else printf("%.8f\n", ask(dw, w));
			root = merge(merge(dz, dw), dy);
		}
	}
	return 0;
}