#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e2+7;
const int mod = 1e9+7;
typedef long long ll;
struct node{
    int len;
    ll v[maxn][maxn];
};
int n,x,ar[maxn],m;
ll inv[maxn];

node mul(node& n1,node& n2){
    node ans;
    memset(ans.v,0,sizeof(ans.v));
    for(int i=0;i<=n1.len;i++){
        for(int j=0;j<=n1.len;j++){
            for(int k=0;k<=n1.len;k++){
                ans.v[i][j] = (ans.v[i][j] + 1LL*n1.v[i][k]*n2.v[k][j]%mod)%mod;
            }
        }
    }
    ans.len=n1.len;
    return ans;
}
node no;
void prin(node no){
    for(int i=0;i<=no.len;i++){
        for(int j=0;j<=no.len;j++)cout<<no.v[i][j]<<" ";cout<<endl;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    x=0;
    for(int i=1;i<=n;i++)scanf("%d",ar+i);
    for(int i=1;i<=n;i++){
        if(ar[i]==0){
            x++;
        }
    }
    inv[1]=1;
    for(int i=2;i<=n;i++)inv[i] = 1LL*inv[mod%i]*(mod-mod/i)%mod;
    for(int i=1;i<=n;i++)assert(1LL*inv[i]*i%mod==1);
    int a=0;
    for(int i=1;i<=x;i++){
        if(ar[i]==0)a++;
    }
    no.len=x;
    memset(no.v,0,sizeof(no.v));
    for(int i=0;i<=x;i++){
        ll a1=i,b1=x-i,a2=x-i,b2=n-2*x+i;
        if(a1<0)continue;
        if(a2<0)continue;
        if(b1<0)continue;
        if(b2<0)continue;
        if(i>0){
            no.v[i][i-1] = a1*b2%mod*2%mod*inv[n]%mod*inv[n-1]%mod;
        }
        if(i<x){
            no.v[i][i+1] = b1*a2%mod*2%mod*inv[n]%mod*inv[n-1]%mod;
        }
        no.v[i][i] += b1*a1%mod*2%mod*inv[n]%mod*inv[n-1]%mod;
        no.v[i][i] += a2*b2%mod*2%mod*inv[n]%mod*inv[n-1]%mod;
        no.v[i][i] += a1*a2%mod*2%mod*inv[n]%mod*inv[n-1]%mod;
        no.v[i][i] += b1*b2%mod*2%mod*inv[n]%mod*inv[n-1]%mod;
        no.v[i][i] += a1*(a1-1)%mod%mod*inv[n]%mod*inv[n-1]%mod;
        no.v[i][i] += a2*(a2-1)%mod%mod*inv[n]%mod*inv[n-1]%mod;
        no.v[i][i] += b1*(b1-1)%mod%mod*inv[n]%mod*inv[n-1]%mod;
        no.v[i][i] += b2*(b2-1)%mod%mod*inv[n]%mod*inv[n-1]%mod;
        no.v[i][i] %= mod;
    }
   	for(int i=0;i<=x;++i) for(int j=0;j<=x;++j){
   		printf("a[%d][%d]=%lld\n",i,j,no.v[i][j]*n%mod*(n-1)%mod*inv[2]%mod);
    }
    node ans;
    memset(ans.v,0,sizeof(ans.v));
    for(int i=0;i<=x;i++)ans.v[i][i]=1;
    ans.len=x;
    while(m){
        if(m&1)ans = mul(ans,no);
        m/=2;
        no = mul(no,no);
    }
    printf("%lld\n",ans.v[a][x]);

    return 0;
}