#include <bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int,int>
#define pdi pair<db,int>
#define mp make_pair
#define pb push_back
#define enter putchar('\n')
#define space putchar(' ')
#define eps 1e-8
#define mo 974711
#define MAXN 1000005
//#define ivorysi
using namespace std;
typedef long long int64;
typedef double db;
template<class T>
void read(T &res) {
    res = 0;char c = getchar();T f = 1;
    while(c < '0' || c > '9') {
    if(c == '-') f = -1;
    c = getchar();
    }
    while(c >= '0' && c <= '9') {
    res = res * 10 + c - '0';
    c = getchar();
    }
    res *= f;
}
template<class T>
void out(T x) {
    if(x < 0) {x = -x;putchar('-');}
    if(x >= 10) {
    out(x / 10);
    }
    putchar('0' + x % 10);
}
int N,M;
db ans;
const db PI = acos(-1.0);
bool dcmp(db a,db b) {
    return fabs(a - b) < eps;
}
struct Point {
    db x,y;
    Point(db _x = 0,db _y = 0) {
        x = _x;y = _y;
    }
    friend Point operator + (const Point &a,const Point &b) {
        return Point(a.x + b.x,a.y + b.y);
    }
    friend Point operator - (const Point &a,const Point &b) {
        return Point(a.x - b.x,a.y - b.y);
    }
    friend Point operator * (const Point &a,const db &d) {
        return Point(a.x * d,a.y * d);
    }
    friend Point operator / (const Point &a,const db &d) {
        return Point(a.x / d,a.y / d);
    }
    friend db operator * (const Point &a,const Point &b) {
        return a.x * b.y - a.y * b.x;
    }
    friend db dot(const Point &a,const Point &b) {
        return a.x * b.x + a.y * b.y;
    }
    db norm() {
        return sqrt(x * x + y * y);
    }
}P[505],conv[505];
void Calc(Point a,Point b,db R) {
    db f = 1;
    if(a * b < 0) f = -1;
    if(max(a.norm(),b.norm()) < R) return;
    db theta = acos(dot(a,b) / (a.norm() * b.norm()));
    db h = fabs(a * b) / (b - a).norm();
    if(h >= R) {ans += f * theta;return;}
    db beta = acos(dot(a - b,Point(-b.x,-b.y)) / ((a - b).norm() * b.norm()));
    db alpha = acos(dot(b - a,Point(-a.x,-a.y)) / ((a - b).norm() * a.norm()));
    db t = asin(h / R);
    db s = 0.0;
    if(t > alpha) s += (t - alpha);
    if(t > beta) s += (t - beta);
    s = min(s,theta);
    ans += f * s;
}
bool check(Point a,Point b) {
    Point c(1,0);
    if(a.y < b.y) swap(a,b);
    return c * a > 0 && b * c > 0 && b * a > 0;
}
void Init() {
    read(N);read(M);
    for(int i = 1 ; i <= N ; ++i) scanf("%lf%lf",&P[i].x,&P[i].y);
    for(int i = 1 ; i <= M ; ++i) scanf("%lf%lf",&conv[i].x,&conv[i].y);
    conv[M + 1] = conv[1];
}
void Solve() {
    for(int i = 1 ; i <= M ; ++i) {
        if(!dcmp(conv[i] * conv[i + 1],0)) {
            for(int j = 1 ; j <= N ; ++j) {
                if(!dcmp(P[j].norm(),0.0)) Calc(conv[i],conv[i + 1],P[j].norm());
            }
        }
    }
    for(int j = 1 ; j <= N ; ++j) {
        if(dcmp(P[j].norm(),0)) {
            bool flag = 1;int t = 0;
            for(int i = 1 ; i <= M ; ++i) {
                if(dcmp((conv[i] - P[j]) * (conv[i + 1] - P[j]),0.0)) {
                    if(dot((conv[i] - P[j]),(conv[i + 1] - P[j])) <= 0) {
                        flag = 0;break;
                    }
                }
                else {
                    if(dcmp(conv[i].y,0)) {
                        if(conv[i].x > 0) ++t;
                    }
                    else t += check(conv[i],conv[i + 1]);
                }
            }
            if(flag && (t & 1)) ans += 2 * PI;
        }
    }
    ans /= 2 * PI;
    printf("%.5lf\n",ans);
}
int main() {
#ifdef ivorysi
    freopen("f1.in","r",stdin);
#endif
    Init();
    Solve();
}