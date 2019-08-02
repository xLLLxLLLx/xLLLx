#include<set>
#include<cstdio>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
template<typename T>inline void rd(T&x){int fl=0,ch;while(ch=getchar(),ch<48||57<ch)fl^=!(ch^45);x=(ch&15);while(ch=getchar(),47<ch&&ch<58)x=x*10+(ch&15);if(fl)x=-x;}
template<typename T>inline void pt(T x){if(x<0)putchar('-'),x=-x;if(x>9)pt(x/10);putchar(x%10+48);}
template<typename T>inline void pt(T x,int ch){pt(x),putchar(ch);}
template<typename T>inline T max(const T&x,const T&y){return x<y?y:x;}
template<typename T>inline T min(const T&x,const T&y){return x<y?x:y;}
const int N=10005;
int T,n,m,dis[N],dis2[N],gap[N],dep[N];
struct cmp{
    bool operator()(const int&a,const int&b)const{return dis[a]<dis[b]||(dis[a]==dis[b]&&a<b);}
};
std::set<int,cmp>S;
struct ed{ed*nxt,*rev;int to,w;}*cur[N];
struct gr{
    ed pool[N<<1],*p=pool,*lnk[N];
    void ae(int u,int v,int w){*++p=(ed){lnk[u],0,v,w},lnk[u]=p;}
    void ae2(int u,int v,int w){
//        fprintf(stderr,"E:%lld %lld %lld\n",u,v,w);;
        *++p=(ed){lnk[u],p+1,v,w},lnk[u]=p;
        *++p=(ed){lnk[v],p-1,u,0},lnk[v]=p;
    }
}G,H,I;
void dij(gr&G,int*dis,int s){
    rep(i,1,n)dis[i]=0x3f3f3f3f3f3f3f3fll;dis[s]=0;S.clear();S.insert(s);
    while(!S.empty()){
        int u=*S.begin();S.erase(S.begin());
        for(ed*i=G.lnk[u];i;i=i->nxt)
            if(dis[u]+i->w<dis[i->to]){
                S.erase(i->to);
                dis[i->to]=dis[u]+i->w;
                S.insert(i->to);
            }
    }
}
int dfs(int u,int val){
    if(u==n)return val;
    int v=val;
    for(;cur[u];cur[u]=cur[u]->nxt)
        if(dep[cur[u]->to]==dep[u]-1&&cur[u]->w){
            int f=dfs(cur[u]->to,min(v,cur[u]->w));
            cur[u]->w-=f,cur[u]->rev->w+=f,v-=f;
            if(!v)return val;
        }
    if(!--gap[dep[u]++])dep[1]=n+1;
    ++gap[dep[u]],cur[u]=I.lnk[u];
    return val-v;
}
void solve(){
    rd(n),rd(m);
    rep(i,1,m){
        int u,v,w;rd(u),rd(v),rd(w);
        G.ae(u,v,w),H.ae(v,u,w);
    }
    dij(G,dis,1),dij(H,dis2,n);
    rep(u,1,n-1)
        for(ed*i=G.lnk[u];i;i=i->nxt)
            if(dis[u]+i->w==dis[i->to]&&dis[u]+dis2[u]==dis[n]&&dis[i->to]+dis2[i->to]==dis[n]) {
                I.ae2(u,i->to,i->w);
                printf("%d %d %d\n", u, i -> to, i -> w);
            }
    int res=0;
    for(int i=1;i<=n;i++)cur[i]=I.lnk[i];
    for(gap[0]=n;dep[1]<=n;res+=dfs(1,0x7fffffff));
    pt(res,'\n');
}
void clear(){
    S.clear();
    G.p=G.pool,H.p=H.pool,I.p=I.pool;
    rep(i,1,n)G.lnk[i]=0;
    rep(i,1,n)H.lnk[i]=0;
    rep(i,1,n)I.lnk[i]=0;
    rep(i,0,n)gap[i]=dep[i]=0,cur[i]=0;
}
signed main(){
    rd(T);
    while(T--){
        solve();
        clear();
    }
    return 0;
}