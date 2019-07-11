#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long LL;
const LL mod=998244353;
const int N=1<<20;
LL Pow(LL x,LL y){
    if (!y)
        return 1LL;
    LL xx=Pow(x,y/2);
    xx=xx*xx%mod;
    if (y&1LL)
        xx=xx*x%mod;
    return xx;
}
LL A,B,a[N],b[N],R[N],g[N],n,L;
char str[N];
void read(){
    scanf("%s",str);
    A=strlen(str);
    for (int i=0;i<A;i++)
        a[A-i-1]=str[i]-'0';
    scanf("%s",str);
    B=strlen(str);
    for (int i=0;i<B;i++)
        b[B-i-1]=str[i]-'0';
}
void NTT(LL a[N],int n){
    for (int i=0;i<n;i++)
        if (i<R[i])
            swap(a[i],a[R[i]]);
    for (int d=1,t=n>>1;d<n;d<<=1,t>>=1)
        for (int i=0;i<n;i+=(d<<1))
            for (int j=0;j<d;j++){
                LL tmp=g[t*j]*a[i+j+d]%mod;
                a[i+j+d]=(a[i+j]-tmp+mod)%mod;
                a[i+j]=(a[i+j]+tmp)%mod;
            }
}
int main(){
    read();
    for (n=1,L=0;n<=A+B;n<<=1,L++);
    for (int i=0;i<n;i++)
        R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
    g[0]=1,g[1]=Pow(3,(mod-1)/n);
    printf("%lld %lld\n", g[0], g[1]);
    for (int i=2;i<n;i++)
        g[i]=g[i-1]*g[1]%mod;
    NTT(a,n),NTT(b,n);
    for (int i=0;i<n;i++)
        a[i]=a[i]*b[i]%mod;
    g[0]=1,g[1]=Pow(g[1],mod-2);
    for (int i=2;i<n;i++)
        g[i]=g[i-1]*g[1]%mod;
    NTT(a,n);
    LL Inv=Pow(n,mod-2);
    for (int i=0;i<n;i++)
        a[i]=a[i]*Inv%mod;
    for (int i=0;i<n-1;i++)
        a[i+1]+=a[i]/10,a[i]%=10;
    int d;
    for (d=n-1;d&&!a[d];d--);
    for (int i=d;i>=0;i--)
        putchar(a[i]+'0');
    return 0;
}