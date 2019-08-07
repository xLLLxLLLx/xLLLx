#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+10;
const int inf = 0x3f3f3f3f;
int n, m;
int v[2*N], x[2*N], ct, al[N], siz[N], h[N], we[N];

inline void add(int u,int V){v[++ct]=V;x[ct]=al[u];al[u]=ct;}

inline int dfs1(int u) {
    siz[u]=1;int mx=0;
    for(int i=al[u];i;i=x[i])
        if(siz[v[i]]==0){siz[u]+=dfs1(v[i]);if(mx<siz[v[i]])mx=siz[v[i]],h[u]=v[i];}
    return siz[u];
}

struct mar {
    int mp[2][2];
    mar(){
        mp[0][0]=mp[0][1]=mp[1][0]=mp[1][1]=-inf;
    }
    mar(int x){
        mp[0][0]=mp[1][1]=0;
        mp[1][0]=mp[0][1]=-inf;
    }
    friend mar operator * (mar a,mar b) {
        mar c;
        for(int i=0;i<2;++i) for(int k=0;k<2;++k) for(int j=0;j<2;++j)
            c.mp[i][j]=max(c.mp[i][j],a.mp[i][k]+b.mp[k][j]);
        return c;
    }
    inline int gmx(){
        return max(max(mp[0][0],mp[0][1]),max(mp[1][0],mp[1][1]));
    }
    inline int* operator [](const int& x){return mp[x];}
};

struct bst {
    int s[N][2], fa[N], st[N], lsiz[N];
    bool book[N];
    int root, tp;
    mar mul[N], w[N];
    bst(){
        w[0]=mul[0]=mar(1);
    }
    inline void ud(const int& x){
        mul[x]=mul[s[x][0]]*w[x]*mul[s[x][1]];
    }
    inline void gtw(const int& x,const int& v) {
        w[x][1][0]+=mul[v].gmx();
        w[x][0][0]=w[x][1][0];
        w[x][0][1]+=max(mul[v][0][0],mul[v][1][0]);
        fa[v]=x;
    }
    inline void ih(){
        for(int i=1;i<=n;i++)
            w[i][0][1]=we[i],w[i][0][0]=w[i][1][0]=0;
    }
    inline bool isr(const int& p){
        return (s[fa[p]][1]!=p)&&(s[fa[p]][0]!=p);
    }
    inline int sbuild(const int& l,const int& r) {
        if(l>r) return 0;
        int tot=0;
        for(int i=l;i<=r;i++) tot+=lsiz[st[i]];
        for(int i=l,ns=lsiz[st[i]];i<=r;i++,ns+=lsiz[st[i]])
            if(2*ns>=tot) {
                int rs=sbuild(l,i-1);
                int ls=sbuild(i+1,r);
                s[st[i]][0]=ls, s[st[i]][1]=rs;
                fa[ls]=st[i], fa[rs]=st[i];
                ud(st[i]);
                return st[i];
            }
    }
    inline int build(int p) {
        for(int t=p;t;t=h[t])book[t]=true;
        for(int t=p;t;t=h[t])
            for(int i=al[t];i;i=x[i])
                if(!book[v[i]])
                    gtw(t,build(v[i]));
        tp=0;
        for(int t=p;t;t=h[t])
            st[++tp]=t,
            lsiz[t]=siz[t]-siz[h[t]];
        return sbuild(1,tp);
    }
    inline void modify(int p,int W) {
        w[p][0][1]+=W-we[p];we[p]=W;
        for(int t=p;t;t=fa[t])
            if(isr(t)&&fa[t]) {
                w[fa[t]][0][0]-=mul[t].gmx();
                w[fa[t]][1][0]=w[fa[t]][0][0];
                w[fa[t]][0][1]-=max(mul[t][0][0],mul[t][1][0]);
                ud(t);
                w[fa[t]][0][0]+=mul[t].gmx();
                w[fa[t]][1][0]=w[fa[t]][0][0];
                w[fa[t]][0][1]+=max(mul[t][0][0],mul[t][1][0]);
            } else ud(t);
    }
}bst;

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&we[i]);
    for(int i=1,u,v;i<n;i++){
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    dfs1(1);
    bst.ih();
    bst.root=bst.build(1);
    for(int i=1,p,w;i<=m;i++) {
        scanf("%d%d",&p,&w);
        bst.modify(p,w);
        printf("%d\n",bst.mul[bst.root].gmx());
    }
    return 0;
}