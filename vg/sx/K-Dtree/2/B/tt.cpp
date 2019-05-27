#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#define mp make_pair
#define pb push_back
using namespace std;

typedef long long li;
template<class T>inline void read(T &x) {
  x = 0;
  T tmp = 1;
  char c = getchar();
  while ((c < '0' || c > '9') && c != '-') c = getchar();
  if (c == '-') tmp = -1, c = getchar();
  while (c >= '0' && c <= '9')
    x = (x << 1) + (x << 3) + c - '0', c = getchar();
  x *= tmp;
}
template<class T>inline void Max(T &x, T y) {
  if (y > x) x = y;
}
template<class T>inline void Min(T &x, T y) {
  if (y < x) x = y;
}

const int N = 1e6 + 10;
const int inf = 1e9;
int n, m, ans, limx, limy;

struct Point {
  int x[2];
}a[N], up[N], down[N];
int ch[N][2], loc, Rt;

inline bool cmp(Point A, Point B) {
  return A.x[loc] < B.x[loc] || (A.x[loc] == B.x[loc] &&
				 A.x[loc ^ 1] < B.x[loc ^ 1]);
}

#define lc ch[rt][0]
#define rc ch[rt][1]

void Update(int rt) {
  if (lc) {
    Min(down[rt].x[0], down[lc].x[0]);
    Min(down[rt].x[1], down[lc].x[1]);
    Max(up[rt].x[0], up[lc].x[0]);
    Max(up[rt].x[1], up[lc].x[1]);
  }
  if (rc) {
    Min(down[rt].x[0], down[rc].x[0]);
    Min(down[rt].x[1], down[rc].x[1]);
    Max(up[rt].x[0], up[rc].x[0]);
    Max(up[rt].x[1], up[rc].x[1]);
  }
}

int Build(int l, int r, int dep) {
  if (l > r) return 0;
  int rt = (l + r) >> 1;
  loc = dep & 1;
  nth_element(a + l + 1, a + rt + 1, a + r + 1, cmp);
  if (l != rt) lc = Build(l, rt - 1, dep + 1);
  if (r != rt) rc = Build(rt + 1, r, dep + 1);
  up[rt] = down[rt] = a[rt];
  Update(rt);
  return rt;
}

void Insert(int now) {
  int rt = Rt, cur = 0;
  while (true) {
    Min(down[rt].x[0], down[now].x[0]);
    Min(down[rt].x[1], down[now].x[1]);
    Max(up[rt].x[0], up[now].x[0]);
    Max(up[rt].x[1], up[now].x[1]);

    if (a[now].x[cur] >= a[rt].x[cur]) {
      if (!rc) {
	rc = now;
	return;
      } else rt = rc;
    } else {
      if (!lc) {
	lc = now;
	return;
      } else rt = lc;
    }

    cur ^= 1;
  }
}

inline int Dist(int rt) {
  int res = 0;
  if (limx < down[rt].x[0]) res += down[rt].x[0] - limx;
  if (limx > up[rt].x[0]) res += limx - up[rt].x[0];
  if (limy < down[rt].x[1]) res += down[rt].x[1] - limy;
  if (limy > up[rt].x[1]) res += limy - up[rt].x[1];
  return res;
}

void Query(int rt) {
  Min(ans, abs(a[rt].x[0] - limx) + abs(a[rt].x[1] - limy));
  int tmpx = lc ? Dist(lc) : inf;
  int tmpy = rc ? Dist(rc) : inf;
  if (tmpx < tmpy) {
    if (tmpx < ans) Query(lc);
    if (tmpy < ans) Query(rc);
  } else {
    if (tmpy < ans) Query(rc);
    if (tmpx < ans) Query(lc);
  }
}

int main(void) {
  read(n), read(m);
  for (int i = 1; i <= n; ++i)
    read(a[i].x[0]), read(a[i].x[1]);
  Rt = Build(1, n, 0);
  
  while (m--) {
    int ty, x, y;
    read(ty), read(x), read(y);
    if (ty == 1) {
      ++n;
      up[n].x[0] = down[n].x[0] = a[n].x[0] = x;
      up[n].x[1] = down[n].x[1] = a[n].x[1] = y;
      Insert(n);
    } else {
      ans = inf;
      limx = x, limy = y;
      Query(Rt);
      printf("%d\n", ans);
    }
  }
  return 0;
}