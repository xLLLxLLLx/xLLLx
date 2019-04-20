#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e6+10;
struct data{
    int nt,to;
}a[N<<1];
int n,m,sz=0,cnt=0,tp=0;
int head[N],q[N],cen[N],col[N],nm[N];

void add(int x,int y){
    a[++cnt].to=y,a[cnt].nt=head[x],head[x]=cnt;
    a[++cnt].to=x,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs(int u,int v){
    int lt=tp;
    for(int i=head[u];i;i=a[i].nt){
        if(a[i].to==v) continue;
        dfs(a[i].to,u);
        if(tp-lt>=m){
            sz++;cen[sz]=u;
            while(tp>lt) col[q[tp--]]=sz;
        }
    }
    q[++tp]=u;
}

int main(){
    scanf("%d%d",&n,&m);
    if(n%m) return printf("NO\n"),0;
    if(m==1) return printf("YES\n"),0;
    for(int i=1,x,y;i<n;++i){
        scanf("%d%d",&x,&y);
        add(x,y);
    }
    dfs(1,0);
    if(tp) return printf("NO\n"),0;
    fr(i,1,n){
    	if(!col[i]) return printf("NO\n"),0;
    	else nm[col[i]]++;
    }
    fr(i,1,n/m) if(nm[i]!=m) return printf("NO\n"),0;
    printf("YES\n");
    return 0;
}