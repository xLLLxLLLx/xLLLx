#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i,n) for (int i = 0; i < (int)(n); i++)
typedef pair <int, int> PII;
typedef unsigned int ui;
const int N = 100005;
const int INF = 0x7FFFFFFF;
const ui mask = (1 << 30) - 1;
int Tc, n, m;
struct Node {
    PII e, sub, cur;
    int o;
    Node *lc, *rc;
}*C, pool[N];
 
struct TPoint {
    int x, y, z;
    TPoint() {}
    TPoint(int x, int y, int z): x(x), y(y), z(z) {}
}a[N];
PII b[N];
 
bool cmp(const TPoint &a, const TPoint &b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y) || (a.x == b.x && a.y == b.y && a.z < b.z);
}
 
bool cmpX(const PII &a, const PII &b) {
    return a.first < b.first || (a.first == b.first && a.second < b.second);
}
 
bool cmpY(const PII &a, const PII &b) {
    return a.second < b.second || (a.second == b.second && a.first < b.first);
}
 
Node *build(PII *b, int l, int r, int o) {
    if (l >= r) return NULL;
    Node *p = C++;
    p->o = o;
    int mid = (l + r) / 2;
    nth_element(b + l, b + mid, b + r, o ? cmpY : cmpX);
    p->e = b[mid];
    p->cur = p->sub = PII(0, 0);
    p->lc = build(b, l, mid, o ^ 1);
    p->rc = build(b, mid + 1, r, o ^ 1);
    return p;
}
 
inline void update(PII &cur, const PII &v) {
    if (v.first > cur.first) {
        cur = v;
    } else if (cur.first == v.first) {
        cur.second = cur.second + v.second;
    }
}
 
void add(Node *p, const PII &e, const PII &v) {
    update(p->sub, v);
    if (e == p->e) {
        update(p->cur, v);
        return;
    } else {
        bool c = p->o ? cmpY(e, p->e) : cmpX(e, p->e);
        if (c) {
            add(p->lc, e, v);
        } else {
            add(p->rc, e, v);
        }
    }
}
 
PII ans;
 
void get(Node *p, const PII &e, int maxx = INF, int maxy = INF) {
    if (!p) return;
    if (p->sub.first < ans.first) return;
    if (maxx <= e.first && maxy <= e.second) {
        update(ans, p->sub);
    } else {
        if (p->e.first <= e.first && p->e.second <= e.second) update(ans, p->cur);
        if (p->o) {
            if (p->e.second <= e.second) get(p->rc, e, maxx, maxy);
            get(p->lc, e, maxx, min(maxy, p->e.second));
        } else {
            if (p->e.first <= e.first) get(p->rc, e, maxx, maxy);
            get(p->lc, e, min(maxx, p->e.first), maxy);
        }
    }
}
 
int main() {
#ifdef cwj
    freopen("E.in", "r", stdin);
#endif
    scanf("%d", &Tc);
    rep (ri, Tc) {
        scanf("%d", &n);
        rep (i, n) {
            scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
            b[i] = make_pair(a[i].y, a[i].z);
        }
        sort(b, b + n);
        m = unique(b, b + n) - b;
        C = pool;
        Node *root = build(b, 0, m, 0);
        sort(a, a + n, cmp);
        rep (i, n) {
            ans = PII(0, 0);
            get(root, PII(a[i].y, a[i].z));
            PII cur;
            if (ans.first == 0) {
                cur.first = 1;
                cur.second = 1;
            } else {
                cur.first = ans.first + 1;
                cur.second = ans.second;
            }
//            printf("cur %d %d %d\n", i, cur.first, cur.second);
            add(root, PII(a[i].y, a[i].z), cur);
        }
        printf("%d %d\n", root->sub.first, root->sub.second & mask);
    }
    return 0;
}