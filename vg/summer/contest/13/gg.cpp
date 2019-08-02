#include<string.h>
#include<stdlib.h>
#include<stdio.h>
//#include<assert.h>
#include<algorithm>
//#include<iostream>
using namespace std;

int n,a,b,p;
#define maxn 2011
const int mod=998244353;
int cp[maxn][maxn],str[maxn],ans[maxn];

int powmod(int a,int b)
{
    int ans=1;
    while (b)
    {
        if (b&1) ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}

int list1p[maxn],listp[maxn];
int main()
{
    scanf("%d%d%d",&n,&a,&b); p=1ll*a*powmod(b,mod-2)%mod;
    cp[0][0]=1;
    list1p[0]=1; for (int i=1;i<=n;i++) list1p[i]=list1p[i-1]*1ll*(mod+1-p)%mod;
    listp[0]=1; for (int i=1;i<=n;i++) listp[i]=listp[i-1]*1ll*p%mod;
    for (int i=1;i<=n;i++)
    {
        cp[i][0]=1;
        for (int j=1;j<=i;j++) cp[i][j]=list1p[j]*1ll*cp[i-1][j]%mod+listp[i-j]*1ll*cp[i-1][j-1]%mod,
        cp[i][j]-=cp[i][j]>=mod?mod:0;
    }
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= i; ++j)
            printf("%d %d %lld\n", i, j, cp[i][j]);
    str[1]=1;
    for (int i=2;i<=n;i++)
    {
        str[i]=1;
        for (int j=1;j<i;j++) str[i]-=str[j]*1ll*cp[i][j]%mod,str[i]+=str[i]<0?mod:0;
    }
    for(int i = 1; i <= n; ++i)
        printf("%d %lld\n", i, str[i]);
    ans[0]=ans[1]=0;
    for (int i=2;i<=n;i++)
    {
        ans[i]=(str[i]*1ll*cp[i][i]%mod)*i*(i-1)%mod*((mod+1)>>1)%mod;
        for (int j=1;j<i;j++) ans[i]+=str[j]*1ll*cp[i][j]%mod*(1ll*j*(j-1)%mod*((mod+1)>>1)%mod
        +1ll*j*(i-j)%mod+ans[j]+ans[i-j])%mod,ans[i]-=ans[i]>=mod?mod:0;
        ans[i]=1ll*ans[i]*powmod(mod+1-str[i]*1ll*cp[i][i],mod-2)%mod;
        printf("%d %lld\n", i, ans[i]);
    }
    printf("%d\n",ans[n]);
    return 0;
}