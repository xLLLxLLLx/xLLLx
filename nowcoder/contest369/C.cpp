#include<bits/stdc++.h>
#define LL long long
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
const int N=2e5+10;
LL v[N<<1],dp[N];
int Next[N<<1],head[N],To[N<<1];
int n,cnt=0;
LL maxn=0;

void add(int x,int y,LL w){
    To[++cnt]=y,v[cnt]=w,Next[cnt]=head[x],head[x]=cnt;
    To[++cnt]=x,v[cnt]=w,Next[cnt]=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
    LL pos=0;
    for(int i=head[u];i;i=Next[i]){
        if(To[i]==fa) continue;
        dfs(To[i],u);
        LL tmp=dp[To[i]]+v[i];
        maxn=max(maxn,pos+tmp);
        pos=max(pos,tmp);
    }
    dp[u]=pos;
}

int main(){
    scanf("%d",&n);
    LL sum=0;
    fr(i,1,n-1){
        int x,y;LL w;
        scanf("%d%d%lld",&x,&y,&w);
        sum+=w;
        add(x,y,w);
    }
    dfs(1,-1);
    printf("%lld\n",sum*2-maxn);
    return 0;
}
