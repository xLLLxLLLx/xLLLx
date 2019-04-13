#include<iostream>
#include<cstdio>
using namespace std;
#define MOD 998244353
#define MAX 4040
void add(int &x,int y){x+=y;if(x>=MOD)x-=MOD;}
int jc[MAX],jv[MAX],inv[MAX],n,k,tot[MAX];
int C(int n,int m){return 1ll*jc[n]*jv[m]%MOD*jv[n-m]%MOD;}
int main()
{
    scanf("%d%d",&k,&n);
    jc[0]=jv[0]=inv[0]=inv[1]=1;
    for(int i=2;i<=n+k;++i)inv[i]=1ll*inv[MOD%i]*(MOD-MOD/i)%MOD;
    for(int i=1;i<=n+k;++i)jc[i]=1ll*jc[i-1]*i%MOD;
    for(int i=1;i<=n+k;++i)jv[i]=1ll*jv[i-1]*inv[i]%MOD;
    for(int i=1;i<=k;++i)tot[i+1]+=1,tot[i+k+1]-=1;
    for(int i=1;i<=k+k;++i)tot[i]+=tot[i-1];
    for(int i=2;i<=k+k;++i)
    {
        int cnt=(tot[i]+1)/2,ans=0;
       // printf("%d\n",cnt);
        for(int j=0,d=1;j<=cnt&&j+j<=n;++j,d=MOD-d)
            add(ans,1ll*d*C(cnt,j)%MOD*C(n-2*j+k-1,k-1)%MOD);
        printf("%d\n",ans);
    }
    return 0;
}