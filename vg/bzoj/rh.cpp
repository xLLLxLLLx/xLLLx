#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <complex>
#define space putchar(' ')
#define enter putchar('\n')
using namespace std;
typedef long long ll;
template <class T>
void read(T &x){
    char c;
    bool op = 0;
    while(c = getchar(), c < '0' || c > '9')
    if(c == '-') op = 1;
    x = c - '0';
    while(c = getchar(), c >= '0' && c <= '9')
    x = x * 10 + c - '0';
    if(op) x = -x;
}
template <class T>
void write(T x){
    if(x < 0) putchar('-'), x = -x;
    if(x >= 10) write(x / 10);
    putchar('0' + x % 10);
}

const int N = 1000005;
const double PI = acos(-1);
typedef complex<double> cp;

int m, n = 1;
double q[N], res[N];
cp f[N], _f[N], g[N], omg[N], inv[N];

void init(){
    for(int i = 0; i < n; i++){
        omg[i] = cp(cos(2 * PI * i / n), sin(2 * PI * i / n));
        inv[i] = conj(omg[i]);
    }
}
void fft(cp *a, cp *omg){
    int lim = 0;
    while((1 << lim) < n) lim++;
    for(int i = 0; i < n; i++){
        int t = 0;
        for(int j = 0; j < lim; j++)
            if(i >> j & 1) t |= 1 << (lim - j - 1);
        if(i < t) swap(a[i], a[t]);
    }
    for(int l = 2; l <= n; l *= 2){
        int m = l / 2;
        for(cp *p = a; p != a + n; p += l)
            for(int i = 0; i < m; i++){
                cp t = omg[n / l * i] * p[m + i];
                p[m + i] = p[i] - t;
                p[i] += t;
            }
    }
}

int main(){

    read(m);
    for(int i = 0; i < m; i++){
        scanf("%lf", &q[i]);
        f[i].real(q[i]);
        _f[m - 1 - i].real(q[i]);
        if(i) g[i].real(1.0 / i / i);
    }
    while(n < 2 * m) n *= 2;
    init();
    fft(f, omg), fft(_f, omg), fft(g, omg);
    for(int i = 0; i < n; i++) {
        f[i] *= g[i], _f[i] *= g[i];
        cout<<f[i].real()<<" "<<_f[i].real()<<endl;
    }
    fft(f, inv), fft(_f, inv);
    for(int i = 0; i < m; i++)
        res[i] = f[i].real() / n - _f[m - 1 - i].real() / n;
    for(int i = 0; i < m; i++)
        printf("%lf\n", res[i]);

    return 0;
}