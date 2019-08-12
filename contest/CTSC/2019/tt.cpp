#include <cstdio>
#include <cctype>
#include <algorithm>
using std::min;
const int SIZE=1<<21;
char ibuf[SIZE],*iS,*iT;
//#define gc() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT?EOF:*iS++):*iS++)
#define gc() getchar()
template <class T>
void read(T &x)
{
    x=0;char c=gc();
    while(!isdigit(c)) c=gc();
    while(isdigit(c)) x=x*10+c-'0',c=gc();
}
const int mod=998244353;
int inline add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
#define mul(x,y) (1ll*(x)*(y)%mod)
int qp(int d,int k){int f=1;while(k){if(k&1)f=mul(f,d);d=mul(d,d),k>>=1;}return f;}
const int N=5e6+1;
int fac[N],inv[N],dp[N],f[N],g[N],invg[N],yuy[N];
int C(int m,int n){return mul(mul(fac[m],inv[n]),inv[m-n]);}
int main()
{
    fac[0]=1;for(int i=1;i<N;i++) fac[i]=mul(fac[i-1],i);
    inv[N-1]=qp(fac[N-1],mod-2);
    for(int i=N-2;~i;i--) inv[i]=mul(inv[i+1],i+1);
    int T,n,m,l,k;read(T);
    for(int o = 1; o <= T; ++o)
    {
        read(n),read(m),read(l),read(k);
        int mi=min(n,min(m,l));
        if(k>mi)
        {
            puts("0");
            continue;
        }
        f[0]=1;
        for(int i=0;i<mi;i++) f[i+1]=mul(f[i],yuy[i]=mul(n-i,mul(m-i,l-i)));
        int fg=1,tot=yuy[0];
        yuy[mi]=0;
        for(int i=1;i<=mi;i++)
        {
            g[i]=add(tot,mod-yuy[i]);
            fg=mul(fg,g[i]);
        }
        // printf("qwq%lld %lld\n", tot, fg);
        invg[mi]=qp(fg,mod-2);
        for(int i=mi-1;~i;i--) invg[i]=mul(invg[i+1],g[i+1]);
        for(int i=1;i<=mi;i++) dp[i]=mul(f[i],invg[i]);
        // if(o == 1) for(int i = 1; i <= mi; ++i) {
        //     printf("%d %lld %lld\n", i, f[i], g[i]);
        // }
        int ans=0;
        for(int i=k;i<=mi;i++)
        {
            if(i-k&1) ans=add(ans,mod-mul(C(i,k),dp[i]));
            else ans=add(ans,mul(C(i,k),dp[i]));
        }
        printf("%d\n",ans);
    }
    return 0;
}
