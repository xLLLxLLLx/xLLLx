#include<iostream>
#include<algorithm>
#include<cstdio>
#define LL long long
#define fr(i,x,y) for(int i=x;i<=y;++i)
using namespace std;
const int MAXA=1e6;
const long long MAXN=1e18;
int n,m,x,y,fl,topp=0;
int first[MAXA<<1],go[MAXA<<1],nxt[MAXA<<1],tot=1,na[MAXA<<1];
long long tree[MAXA<<3],val[MAXA],f[MAXA];
int dfn[MAXA],df[MAXA],top[MAXA],dep[MAXA],fa[MAXA],son[MAXA],siz[MAXA];
int add(int x,int y,long long z){
    nxt[++tot]=first[x]; first[x]=tot; val[tot]=z; go[tot]=y; return 0;
}

long long che(long long x,long long y){
    if(x>MAXN/y) return MAXN+MAXN;
    return x*y;
}

int predfs(int x,int father){
    fa[x]=father;dep[x]=dep[father]+1;
    for(int i=first[x];i;i=nxt[i])
	if(go[i]!=father){
	    f[go[i]]=val[i];
	    na[i]=na[i^1]=go[i];
	    siz[x]+=predfs(go[i],x);
	    if(siz[go[i]]>siz[son[x]]) son[x]=go[i];
	}
    return ++siz[x];
}

void dfs(int x,int father){
    dfn[x]=++topp;
    df[topp]=x;
    top[son[x]]=top[x];
    if(son[x]) dfs(son[x],x);
    for(int i=first[x];i;i=nxt[i])
	if(go[i]!=father&&go[i]!=son[x]){
	    top[go[i]]=go[i];
	    dfs(go[i],x);
	}
}

long long build(int x,int l,int r){
    int mid=(l+r)>>1;
    if(l==r) return tree[x]=f[df[l]];
    return tree[x]=che(build(x<<1,l,mid),build(x<<1|1,mid+1,r));
}

long long ask(int x,int l,int r,int ll,int rr){
  //  printf("$%d %d %d %d %d\n",x,l,r,ll,rr);
    if(l>=ll&&r<=rr) return tree[x];
    if(r<ll||l>rr) return 1;
    int mid=(l+r)>>1;
    return che(ask(x<<1,l,mid,ll,rr),ask(x<<1|1,mid+1,r,ll,rr));
}

long long ad(int x,int l,int r,int pos,long long vall){
    if(!(l<=pos&&r>=pos)) return tree[x];
    if(l==r) return tree[x]=vall;
    int mid=(l+r)>>1;
    return tree[x]=che(ad(x<<1,l,mid,pos,vall),ad(x<<1|1,mid+1,r,pos,vall));
}

long long hld(int x,int y){
    //printf("x=%d y=%d\n",x,y);
    if(dep[top[x]]>dep[top[y]]||top[x]==top[y]&&dep[x]>dep[y]) swap(x,y);
    if(top[x]==top[y]) return ask(1,2,n,dfn[x]+1,dfn[y]);
    return che(ask(1,2,n,dfn[top[y]],dfn[y]),hld(x,fa[top[y]]));
}

int solve(){
    long long sum=0;
    scanf("%d",&fl);
    if(fl==1){
	scanf("%d%d",&x,&y);
	scanf("%lld",&sum);
	LL zz=hld(x,y);
	cout<<"zz="<<zz<<endl;
	printf("%lld\n",sum/zz);
	
    }
    else{
    
	scanf("%d%lld",&x,&sum);val[x*2]=sum;
	printf("xxxx\n");
	cout<<na[x*2]<<endl;
	printf("xxxxx\n");
	ad(1,2,n,dfn[na[x*2]],sum);
    }
    return 0;
}

int main(){
    long long z; top[1]=1;
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++){
	scanf("%d%d%lld",&x,&y,&z);
	add(x,y,z);
	add(y,x,z);
    }
    LL w=1922256435501153944;
    predfs(1,0);
    dfs(1,0);
   	fr(i,1,n) printf("i=%d dfn=%d f=%lld na=%d\n",i,dfn[i],f[i],na[i]);
    build(1,2,n);
    for(;m;m--) solve();
    return 0;
}

/*
10 10
1 2 2295009248763120479
1 3 399659560414065867
1 4 107083965476434530
1 5 3232674836331837600
3 6 1922256435501153944
6 7 1376528839436636255
3 8 751083395312294616
6 9 212914859058387090
1 10 1355026447415503530
2 7 449300082769305144
2 2 32007718507314160
2 6 198168225945338382
2 1 2079295697350577860
2 3 1290988004281051208
1 10 10 3644359774272971390
1 9 2 375078876147630710
1 6 3 988925204434906890
1 3 5 683543888820667930
1 10 1 704658150478852056
*/
