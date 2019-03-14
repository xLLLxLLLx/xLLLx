#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e3+10;
struct data{
    int nt,to;
}a[N<<1];
int n,m,sz=0,cnt=0,tp=0;
int head[N],q[N],cen[N],col[N];

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
    for(int i=1,x,y;i<n;++i){
        scanf("%d%d",&x,&y);
        add(x,y);
    }
    dfs(1,0);
    while(tp) col[q[tp--]]=sz;
    fr(i,1,n) if(!col[i]) return printf("0\n"),0;
    printf("%d\n",sz);
    fr(i,1,n) printf("%d ",col[i]);
    puts("");
    fr(i,1,sz) printf("%d ",cen[i]);
    return 0;
}
