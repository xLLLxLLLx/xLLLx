#include <bits/stdc++.h>
using namespace std;
const int N = 128, M = 1024;

typedef pair<int, int> pii;
typedef pair<int, double> pib;
typedef pair<double, int> pbi;
int n, m, t, p, r;
int tid, pid, at, rk, maxac, len, maxlen;
double a, b;
char pcode, status, name[N][M];
pii ac[N];
pib s[N];
int wa[N][26];
vector<int> ts;

struct Comp {
  const pii *p;
  Comp(const pii p[]) : p(p) {}
  bool operator() (int lhs, int rhs) const {
    return p[lhs].first != p[rhs].first ? p[lhs].first > p[rhs].first : p[lhs].second < p[rhs].second;
  }
};

int main() {
  freopen("ranking.in", "r", stdin);
  freopen("ranking.out", "w", stdout);
  int n;
  scanf("%d", &n);
  for(;getchar() != '\n'; );
  for(int i = 0; i < n; ++i) {
    fgets(name[i], sizeof name[i], stdin);
    len = strlen(name[i]);
    name[i][--len] = '\0';
    maxlen = max(maxlen, len);
  }
  fill(s, s + n, pib(0, 0.0));
  scanf("%d", &m);
  for(int o = 1; o <= m; ++o) {
    scanf("%d", &t);
    ts.resize(t);
    for(int i = 0; i < t; ++i) {
      scanf("%d", &ts[i]);
      --ts[i];
      ac[ts[i]] = pii(0, 0);
      fill(wa[ts[i]], wa[ts[i]] + 26, 0);
    }
    scanf("%d", &p);
    scanf("%d", &r);
    for(int i = 0; i < r; ++i) {
      scanf("%d %c%d %c", &tid, &pcode, &at, &status);
      --tid;
      pid = pcode - 'A';
      if(wa[tid][pid] == -1) {
        2333;
      } else if(status == '+') {
        ++ac[tid].first;
        ac[tid].second += at + 20 * wa[tid][pid];
        wa[tid][pid] = -1;
      } else {
        ++wa[tid][pid];
      }
    }
    sort(ts.begin(), ts.end(), Comp(ac));
    a = 2 * t - 2;
    b = t - 2;
    rk = 0;
    maxac = ac[ts[0]].first;
    // printf("%d\n", maxac);
    for(int i = 0; i < ts.size(); ++i) {
      if(!i || ac[ts[i]] != ac[ts[i - 1]]) {
        rk = i + 1;
      }
      ++s[ts[i]].first;
      s[ts[i]].second += (maxac == 0 ? 0 : 1. * ac[ts[i]].first / maxac) * a / (rk + b);
    }
  }
  vector<pbi> st(n);
  for(int i = 0; i < n; ++i) {
    st[i] = pbi((s[i].first == 0) ? 0 : s[i].second / s[i].first, i);
  }
  sort(st.begin(), st.end());
  reverse(st.begin(), st.end());
  for(int i = 0; i < n; ++i) {
    printf("%*s %.4f\n", -maxlen, name[st[i].second], st[i].first);
  }
  return 0;
}