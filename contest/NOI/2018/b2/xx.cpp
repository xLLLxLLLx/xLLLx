#include<bits/stdc++.h>
#define N 50004
#define V 1800000
#define mid (l+r>>1)
#define il inline
#define re return
#define mx(xx,yy) xx<yy?xx=yy:0
using namespace std;
typedef long long ll;
const ll inf=-1e17;
int T,n,m,D,f[N],dep[N],lg[N*2],to[N],hd[N],lk[N],
fa[18][N*2],siz[N],son[N],top[N],dfn[N],cnt,st[N],tot,
rt[N],c[V][2];
ll Dep[N],ans,tmx,tnow,add,mx0[V],mx1[V],tmp,ww;
struct sig{int u;ll w;}t1,t2;
struct dat{int u;sig v;};
vector<dat>s2[N];
il int lca(int u,int v){
    if(u==v)re u;
    if(dfn[u]>dfn[v])swap(u,v);
    register int d=lg[dfn[v]-dfn[u]];
    return min(fa[d][dfn[u]],fa[d][dfn[v]-(1<<d)+1]);
}
il ll dis(int u,int v){re u&&v?Dep[u]+Dep[v]-2*Dep[lca(u,v)]:inf;}
il ll dis(sig u,sig v){re dis(u.u,v.u)+u.w+v.w;}
il void upd(sig u,sig v){(tnow=dis(u,v))>tmx?t1=u,t2=v,tmx=tnow:0;}
struct mxd{
    sig a,b;int no;
    il void ini(){a.u=b.u=0;}
    il void uni(mxd &c){
        if(!a.u)re a=c.a,b=c.b,c.ini();
        t1=a,t2=c.a,tmx=dis(a,t2);
        upd(a,c.b),upd(b,c.a),upd(b,c.b);
        mx(ans,(tmx>>1)-Dep[no]);
        upd(a,b),upd(c.a,c.b);
        a=t1,b=t2,c.ini();
    }
}d[N],ad;
il int nxt(int u,int v){
    for(;top[u]^top[v];u=f[top[u]])
    if(f[top[u]]==v)re top[u];
    re son[v];
}
void dfs(int x){
    dep[x]=dep[f[x]]+1,Dep[x]+=Dep[f[x]];
    mx(D,dep[x]);
    fa[0][++cnt]=x,dfn[x]=cnt;
    for(register int s,i=lk[x];i;i=hd[i]){
        dfs(s=to[i]);
        fa[0][++cnt]=x,siz[x]+=siz[s];
        siz[s]>siz[son[x]]?son[x]=s:0;
    }
}
bool cmp(dat a,dat b){re dfn[a.u]<dfn[b.u];}
int u,v,w,i;
il void upd(int x,int y){mx(ans,mx0[c[x][0]]+mx1[c[y][1]]-add);}
il void pu(int k){
    mx0[k]=mx0[c[k][mx0[c[k][0]]<mx0[c[k][1]]]];
    mx1[k]=mx1[c[k][mx1[c[k][0]]<mx1[c[k][1]]]];
}
void ins(int &k,int l,int r,int d){
    if(!k)k=++cnt,c[k][0]=c[k][1]=0,mx0[k]=mx1[k]=inf;
    l<r?d>mid?ins(c[k][1],mid+1,r,d):ins(c[k][0],l,mid,d),pu(k),upd(k,k),0:
    (mx(mx0[k],tmp),mx(mx1[k],tmx));
}
void del(int &k,int l,int r,int lim){
    l>lim?k=0:0;
    if(l<=lim&&r>lim)del(c[k][0],l,mid,lim),del(c[k][1],mid+1,r,lim),pu(k);
}
void uni(int &x,int y,int l,int r){
    x&&y?l<r?upd(x,y),upd(y,x),
    uni(c[x][0],c[y][0],l,mid),uni(c[x][1],c[y][1],mid+1,r),pu(x),0:
    (mx(mx0[x],mx0[y]),mx(mx1[x],mx1[y])):(x|=y);
}
il void ins(int x){tmx=tmp+Dep[w],add=Dep[x],ins(rt[x],1,D,dep[w]);}
int main(){
    mx0[0]=mx1[0]=inf;
    for(scanf("%d",&T);T--;){
        scanf("%d",&n),ans=inf,D=cnt=0;
        for(i=1;i<=n;i++)
        lk[i]=son[i]=top[i]=rt[i]=0,siz[i]=1,d[i].no=i,s2[i].clear();
        for(i=1;i<n;i++)scanf("%d%d%d",&u,&v,&w),
        f[v]=u,Dep[v]=w,to[i]=v,hd[i]=lk[u],lk[u]=i;
        lg[0]=-1,dfs(1);
        for(i=1;i<=n;i++)!top[i]?top[i]=i:0,top[son[i]]=top[i];
        for(i=1;i<n<<1;i++)lg[i]=lg[i-1]+!(i&i-1);
        for(i=0;1<<i+1<cnt;i++)
        for(int j=1;j<=cnt-(1<<i+1)+1;j++)
        fa[i+1][j]=min(fa[i][j],fa[i][j+(1<<i)]);
        for(scanf("%d",&m),cnt=0;m--;){
            scanf("%d%d%lld",&u,&v,&ww),w=lca(u,v),tmp=dis(u,v)-ww;
            if(u^w)s2[nxt(u,w)].push_back((dat){u,(sig){v,tmp+Dep[u]-ww}}),ins(u);
            if(v^w)s2[nxt(v,w)].push_back((dat){v,(sig){u,tmp+Dep[v]-ww}}),ins(v);
        }
        for(i=n;i>2;i--)
        add=Dep[f[i]],del(rt[i],1,D,dep[i]-2),uni(rt[f[i]],rt[i],1,D);
        for(i=2;i<=n;i++)if(s2[i].size()>1){
            sort(s2[i].begin(),s2[i].end(),cmp);
            for(auto j:s2[i]){
                u=j.u,ad.ini(),ad.a=j.v,d[u].uni(ad);
                if(tot){
                    if(st[tot]==u)continue;
                    for(v=0,w=lca(u,st[tot]);dep[w]<dep[st[tot]];)
                    v?d[st[tot]].uni(d[v]),0:0,v=st[tot--];
                    if(v)d[w].uni(d[v]);
                    w^st[tot]?st[++tot]=w:0;
                }
                st[++tot]=u;
            }
            for(;tot>1;tot--)d[st[tot-1]].uni(d[st[tot]]);
            if(tot)d[st[1]].ini(),tot=0;
        }
        ans<-1e15?puts("F"):printf("%lld\n",ans);
    }
}

