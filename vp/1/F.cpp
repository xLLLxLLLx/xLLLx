#include <bits/stdc++.h>
using namespace std;
const int N = 2010;
const double eps = 1e-6;
struct data {
	int nt, to;
	double w;
} a[N << 1];
int head[N], cnt = 0;
struct node {
	double x, y;
} b[N], tmp;
int f[N];
double R[N];

void add(int x, int y, double w) {
	a[++cnt].to = y;
	a[cnt].w = w;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

double cross(node A, node B) {
	return A.x * B.y - A.y * B.x;
}

double pf(double x) {
	return x * x;
}

double Dis(int x, int y) {
	return pf(b[x].x - b[y].x) + pf(b[x].y - b[y].y);
}

bool check(int x, int y) {
	return sqrt(Dis(x, y)) - (R[x] + R[y]) <= -eps;
}

double dis[N], inf = 1e100;

int main() {
	freopen("out.in", "r", stdin);
	freopen("out.out", "w", stdout);
	int n;
	scanf("%d", &n);
	double r;
	for(int i = 1; i <= n; ++i) {
		cin >> b[i].x >> b[i].y >> R[i];
	}
	cin >> tmp.x >> tmp.y >> r;
	for(int i = 1; i <= n; ++i) {
		b[i].x -= tmp.x;
		b[i].y -= tmp.y;
		R[i] += r;
	}
	for(int i = 1; i <= n; ++i) 
	 for(int j = i + 1; j <= n; ++j) {
		if(check(i, j)) {
			double res1 = b[i].x * b[i].x + b[i].y * b[i].y;
			double res2 = b[j].x * b[j].x + b[j].y * b[j].y;
			double pos = acos((res1 + res2 - Dis(i, j)) / (2.0 * sqrt(res1) * sqrt(res2)));
			int bo = (cross(b[i], b[j]) >= 0);
			add(i, j, bo ? pos : -pos);
			add(j, i, bo ? -pos : pos);
		}
	}
	for(int o = 1; o <= n; ++o) {
		for(int u = 1; u <= n; ++u) {
			for(int i = head[u]; i; i = a[i].nt) {
				int to = a[i].to;
				if(dis[to] - (dis[u] + a[i].w) > eps) {
					dis[to] = dis[u] + a[i].w;
				}
			}
		}
	}
	for(int u = 1; u <= n; ++u) {
		for(int i = head[u]; i; i = a[i].nt) {
			int to = a[i].to;
			if(dis[to] - (dis[u] + a[i].w) > eps) {
				return printf("NO\n"), 0;
			}
		}
	}
	puts("YES");
	return 0;
}