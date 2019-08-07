#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
#define N 200050
#define mod 998244353
#define ls ch[p][0]
#define rs ch[p][1]
#define db(x) cerr<<#x<<" = "<<x<<endl
const int inv2=(mod+1)/2;
typedef long long ll;
vector <int> g[N];
int n,du[N],dep[N],fa[N],L,R,w[N];
int siz[N],lf[N],son[N],sz[N],top[N],val[N],S[N];
ll ans[N],mi[N];

ll sub(ll x, ll y) {
    return ((x - y) % mod + mod) % mod;
}

ll qp(ll x,ll y=mod-2) {
    ll re=1;
    for(;y;y>>=1,x=x*x%mod) 
    	if(y&1) 
    		re=re*x%mod; 
    return re;
}
inline void add(int x,int y) {
    g[x].push_back(y);
    g[y].push_back(x);
}
void df1(int x,int y) {
    int i;
    siz[x]=lf[x];
    fa[x]=y;
    sz[x]=1;
    dep[x]=dep[y]+1;
    if(dep[x]&1) w[x]=0;
    else w[x]=n;
    for(i = 0; i < g[x].size(); ++i) {
        int to = g[x][i];
        if(to!=y) {
        df1(to,x);
        siz[x]+=siz[to];
        sz[x]+=sz[to];
        if(dep[x]&1) w[x]=max(w[x],w[to]);
        else w[x]=min(w[x],w[to]);
        if(sz[to]>sz[son[x]]) son[x]=to;
        }
    }
    if(lf[x]) w[x]=x;
    val[x]=sz[x]-sz[son[x]];
}
struct A {
    ll x; int t;
    A() {x=0,t=0;}
    A(ll x_,int t_) {x=x_,t=t_;}
    void operator *= (const ll &u) {
        if(!u) t++;
        else x=x*u%mod;
    }
    void operator /= (const ll &u) {
        if(!u) t--;
        else x=x*qp(u)%mod;
    }
    operator ll() {return t?0:x;}
};
struct Mat {
    ll l,r;
    Mat() {}
    Mat(ll l_,ll r_) {l=l_,r=r_;}
    Mat operator * (const Mat &u) const {
        return Mat(l*u.l%mod,(l*u.r+r)%mod);
    }
}I;
struct Tree {
    int ch[N][2],f[N];
    A dp[N]; 
    Mat F[N];
    int flg,rt;
    bool isrt(int x) {return ch[f[x]][0]!=x&&ch[f[x]][1]!=x;}
    void pushup(int p) {
        F[p]=Mat(-dp[p],dp[p]);
        if(ls) F[p]=F[ls]*F[p];
        if(rs) F[p]=F[p]*F[rs];
    }
    int build(int l,int r) {
        if(l>r) return 0;
        int sum=0,i,p,x=0;
        for(i=l;i<=r;i++) sum+=val[S[i]];
        for(i=l;i<=r;i++) {
            x+=val[S[i]];
            if((x<<1)>=sum) break;
        }
        p=S[i];
        ls=build(l,i-1),rs=build(i+1,r);
        if(ls) f[ls]=p;
        if(rs) f[rs]=p;
        if(!son[p]) {
            if(flg==0) dp[p].x=(p<w[1]);
            else dp[p].x=sub(1,(p>w[1]));
            if(!(dep[p]&1)) dp[p].x=sub(1, dp[p].x);
        }
        pushup(p);
        return p;
    }
    int dfs(int rr) {
    		// printf("x = %d\n", rr);
        int t,i,x;
        for(x=rr;x;x=son[x]) {
            dp[x].x=1;
            for(i=0; i < g[x].size(); ++i) {
                int to = g[x][i];
                if(to!=fa[x]&&to!=son[x]) {
                t=dfs(to);
                f[t]=x;
                dp[x]*=sub(1,F[t].r);
                }
            }
        }
        int tp=0;
        for(x=rr;x;x=son[x]) S[++tp]=x;
        return build(1,tp);
    }
    void init() {
        F[0]=I;
        rt=dfs(1);
    }

    void print() {
        printf("rt = %d\n", rt);
			for(int i = 1; i <= n; ++i) {
				printf("dp[%d]= %lld %lld\n", i, dp[i].x, dp[i].t);
				printf("s[%d] = %lld %lld\n", i, F[i].l, F[i].r);
                printf("fa=%d, ls = %d, rs = %d\n", f[i], ch[i][0], ch[i][1]);
			}
		}

    void UPD(int p,ll x) {
        dp[p]=A(x,0);
        for(;p;p=f[p]) {
            if(isrt(p)) {
                ll gg = sub(1,F[p].r);
                dp[f[p]]/=gg;
            }
            pushup(p);
            if(isrt(p)) {
                ll gg = sub(1, F[p].r);
                dp[f[p]]*=gg;
            }
        }
    }
}T0,T1;
int main() {
    I.l=1,I.r=0;
    scanf("%d%d%d",&n,&L,&R);
    int i,x,y;
    for(mi[0]=i=1;i<=n;i++) mi[i]=mi[i-1]*2%mod;
    for(i=1;i<n;i++) scanf("%d%d",&x,&y),add(x,y),du[x]++,du[y]++;
    for(i=2;i<=n;i++) if(du[i]==1) lf[i]=1;
    df1(1,0);
    T0.flg=0,T1.flg=1,T0.init(),T1.init();
    T0.print(), T1.print();
    for(i=1;i<n;i++) {
        x=w[1]+i-1;
        if(x>w[1]&&x<=n&&lf[x]) T0.UPD(x,inv2);
        x=w[1]-i+1;
        if(x>0&&x<w[1]&&lf[x]) T1.UPD(x,inv2);
        ll v1=sub(1, T0.F[T0.rt].r),v2=T1.F[T1.rt].r;
        ans[i]=(mi[siz[1]]-(mi[siz[1]-1])*(v1*v2%mod))%mod;
        puts("----");
        T0.print(), T1.print();
        printf("%lld\n", ans[i]);
    }
    ans[n]=mi[siz[1]]-1;
    for(i=R;i>=L;i--) {
        ans[i]=(ans[i]-ans[i-1])%mod;
    }
    for(i=L;i<=R;i++) {
        printf("%lld ",(ans[i]+mod)%mod);
    }
    return 0;
}