//minamoto
#include<bits/stdc++.h>
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while((ch=getc())<'0'||ch>'9')
    (ch=='-')&&(flag=true);
    for(res=num;(ch=getc())>='0'&&ch<='9';res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
const int N=200005,inf=0x3f3f3f3f;
int n,ver[N],Next[N],head[N],edge[N],tot,ans=-inf,col[N];
inline void add(int u,int v,int e){ver[++tot]=v,Next[tot]=head[u],head[u]=tot,edge[tot]=e;}
inline int fir(multiset<int> &s){return s.size()?*s.rbegin():-inf;}
inline int sec(multiset<int> &s){return s.size()>1?*(++s.rbegin()):-inf;}
#define ls ch[x][0]
#define rs ch[x][1]
int ch[N][2],fa[N],lmx[N],rmx[N],mxs[N],sum[N],len[N],w[N];
multiset<int> chain[N],path[N];
inline bool isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
void init(){for(int i=0;i<=n;++i) lmx[i]=rmx[i]=mxs[i]=-inf;}
void pushup(int x){
    sum[x]=sum[ls]+sum[rs]+len[x];
    int cha=max(w[x],fir(chain[x]));
    int L=max(cha,rmx[ls]+len[x]);
    int R=max(cha,lmx[rs]);
    lmx[x]=max(lmx[ls],sum[ls]+len[x]+R);
    rmx[x]=max(rmx[rs],sum[rs]+L);
    mxs[x]=max(rmx[ls]+len[x]+R,lmx[rs]+L);
    cmax(mxs[x],max(mxs[ls],mxs[rs]));
    cmax(mxs[x],fir(path[x]));
    cmax(mxs[x],fir(chain[x])+sec(chain[x]));
    if(w[x]==0) cmax(mxs[x],max(fir(chain[x]),0));
    printf("x=%d lmx=%d rmx=%d mx=%d ls=%d rs=%d sum=%d\n",x,lmx[x],rmx[x],mxs[x],ls,rs,sum[x]);
}
void rotate(int x){
    int y=fa[x],z=fa[y],d=ch[y][1]==x;
    if(!isroot(y)) ch[z][ch[z][1]==y]=x;
    fa[x]=z,fa[y]=x,fa[ch[x][d^1]]=y,ch[y][d]=ch[x][d^1],ch[x][d^1]=y,pushup(y);
}
void splay(int x){
    for(int y=fa[x],z=fa[y];!isroot(x);y=fa[x],z=fa[y]){
        if(!isroot(y))
        ((ch[y][1]==x)^(ch[z][1]==y))?rotate(x):rotate(y);
        rotate(x);
    }
    pushup(x);
}
void access(int x){
    for(int y=0;x;x=fa[y=x]){
        splay(x);
        if(rs) path[x].insert(mxs[rs]),chain[x].insert(lmx[rs]);
        if(y) path[x].erase(path[x].find(mxs[y])),chain[x].erase(chain[x].find(lmx[y]));
        rs=y,pushup(x);
    }
}
void modify(int x){
    access(x),splay(x);
    col[x]^=1,w[x]=col[x]?(-inf):0;
    pushup(x),ans=mxs[x];
}
void dfs(int u){
    for(int i=head[u];i;i=Next[i]){
        int v=ver[i];
        if(v==fa[u]) continue;
        fa[v]=u,len[v]=edge[i],dfs(v);
        chain[u].insert(lmx[v]),path[u].insert(mxs[v]);
    }
    pushup(u);
}
int main(){
    n=read();init();
    for(int i=1;i<n;++i){
        int u=read(),v=read(),e=read();
        add(u,v,e),add(v,u,e);
    }
    dfs(1),ans=mxs[1];int q=read();
    while(q--){
        char op=getc();int x;
        getc();
        if(op=='A'){
            ans<0?puts("They have disappeared."):printf("%d\n",ans);
        }
        else x=read(),modify(x);
    }
    return 0;
}
