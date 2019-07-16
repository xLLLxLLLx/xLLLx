#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
const int N=100010,M=700;
int s,tt,cnt,ans;
bool in[N];
int head[N],to[N],nxt[N],fa[N],bel[N],sz[N],lz[N],f[M][M],la[N],pa[N],a[N];
inline int gi() {
    int x=0,o=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=='-'?o=-1:0,ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return o*x;
}
inline int dfs(int x) {
    int d=1,ch=0;
    for(int i=head[x];i;i=nxt[i]) {
        int y=to[i];
        fa[y]=x,d=max(d,dfs(y)+1);
        if(bel[y]) bel[x]=bel[y],++ch;
    }
    if(d>s||ch>1) {
        la[bel[x]=++cnt]=x,d=1;
        for(int i=head[x];i;i=nxt[i]) pa[la[bel[to[i]]]]=x;
    }
    ++sz[bel[x]];
    return d;
}
inline void add(int x,int t) {
    int y=bel[x],z=sz[y],*v=f[y]+z;
    if(y&&a[x]>=-z&&a[x]<z) v[a[x]]+=t;
    if(a[x]-lz[y]<0) ans+=t;
}
inline void upd(int x,int t) {
    int y=bel[x],z=sz[y],*v=f[y]+z;
    if(t==1) ans-=v[--lz[y]];
    else ans+=v[lz[y]++];
    if(lz[y]==-z||lz[y]==z) {
    for(int i=x;bel[i]==bel[x];i=fa[i]) a[i]-=lz[y];
    for(int i=-z;i<z;i++) v[i]=0;
    lz[y]=0;
    for(int i=x;bel[i]==bel[x];i=fa[i])
        if(in[i]&&a[i]>=-z&&a[i]<z) ++v[a[i]];
    }
}
inline void F(int x,int t) {
    if(in[x]) add(x,-1);
    a[x]+=t;
    if(in[x]) add(x,1);
}
inline void modify(int x) {
    int y=fa[x],t=(in[x]^=1)?1:-1;
    add(x,t);
    while(y&&!bel[y]) F(y,t),y=fa[y];
    if(!y) return;x=bel[y];
    while(bel[y]==x) F(y,t),y=fa[y];
    while(y) upd(y,t),y=pa[y];
}
int main() {
    int n,m;
    cin>>n>>m,s=sqrt(n)+1e-9;
    for(int i=2,x;i<=n;i++)
    to[++tt]=i,nxt[tt]=head[x=gi()],head[x]=tt;
    for(int i=1;i<=n;i++) a[i]=gi(),in[i]=1;
    dfs(1);
    for(int i=1;i<=cnt;i++) {
    int *v=f[i]+sz[i];
    for(int j=la[i];bel[j]==bel[la[i]];j=fa[j])
        if(a[j]>=-sz[i]&&a[j]<sz[i]) ++v[a[j]];
    }
    while(m--) modify(abs(gi())),printf("%d ",ans);
    return 0;
}