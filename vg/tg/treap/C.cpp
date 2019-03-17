#include<bits/stdc++.h>
#define REP(i,x,y) for(int i=x;i<=y;++i)
#define LC ch[x][0]
#define RC ch[x][1]
#define SC ch[ch[rt][1]][0]
using namespace std;
 
const int maxn=1000005;
const int INF=(int)(1e9)+100;
int fa[maxn],ch[maxn][2];
int sz[maxn],val[maxn],flip[maxn],all[maxn],vsum[maxn];
int lmx[maxn],rmx[maxn],mx[maxn],vmx[maxn];
int seq[maxn],stk[maxn];
int rt,idx,top;

void read(int &x){
    scanf("%d",&x);
}
 
inline int dir(int x) {return ch[fa[x]][1]==x;}
inline void rep(int x,int v) {
    all[x]=val[x]=vmx[x]=v;
    vsum[x]=sz[x]*v;
    lmx[x]=rmx[x]=mx[x]=max(0,vsum[x]);
}
 
inline void rev(int x) {
    flip[x]^=1;
    swap(LC,RC);
    swap(lmx[x],rmx[x]);
}
 
inline void pd(int x) {
    if(all[x]!=-INF) {
        if(LC) rep(LC,all[x]);
        if(RC) rep(RC,all[x]);
        all[x]=-INF;
    }
    if(flip[x]) {
        if(LC) rev(LC);
        if(RC) rev(RC);
        flip[x]=0;
    }
}
 
inline void pu(int x) {
    sz[x]=sz[LC]+sz[RC]+1;
    vsum[x]=vsum[LC]+vsum[RC]+val[x];
    vmx[x]=max(val[x],max(vmx[LC],vmx[RC]));
    lmx[x]=max(lmx[LC],vsum[LC]+val[x]+lmx[RC]);
    rmx[x]=max(rmx[RC],vsum[RC]+val[x]+rmx[LC]);
    mx[x]=max(rmx[LC]+val[x]+lmx[RC],max(rmx[x],lmx[x]));
    mx[x]=max(mx[x],max(mx[LC],mx[RC]));
}
 
inline void rot(int x) {
    int d=dir(x)^1,p=fa[x];
    pd(p);pd(x);
    ch[p][d^1]=ch[x][d];
    fa[ch[x][d]]=p;
    fa[x]=fa[p];
    if(fa[x]) ch[fa[p]][dir(p)]=x;
    ch[x][d]=p;fa[p]=x;pu(p);
}
 
inline void splay(int x,int goal=0) {
    pd(x);
    while(fa[x]!=goal) {
        pd(fa[fa[x]]);
        pd(fa[x]);pd(x);
        if(fa[fa[x]]==goal) rot(x);
        else if(dir(x)!=dir(fa[x])) rot(x),rot(x);
        else rot(fa[x]),rot(x);
    }
    pu(x);if(goal==0) rt=x;
}
 
inline int rto(int k,int goal=0) {
    int x=rt;pd(x);
    for(;x && k!=sz[LC]+1;) {
        if(k<sz[LC]+1) x=LC;
        else {k-=sz[LC]+1;x=RC;}
        pd(x);
    }
    if(x) splay(x,goal);
    return x;
}
 
inline void newnode(int& x,int v,int p) {
    if(top) x=stk[top--];
    else x=++idx;
    LC=RC=0;sz[x]=1;
    fa[x]=p;val[x]=vsum[x]=vmx[x]=v;
    flip[x]=0;all[x]=-INF;
    lmx[x]=rmx[x]=mx[x]=max(val[x],0);
}
 
void build(int& x,int l,int r,int p) {
    if(l>r) return;
    int mid=(l+r)>>1;
    newnode(x,seq[mid],p);
    build(LC,l,mid-1,x);
    build(RC,mid+1,r,x);
    pu(x);
}
 
inline void init() {
    rt=idx=top=0;
    vmx[0]=-INF;
    newnode(rt,-INF,0); 
    newnode(ch[rt][1],-INF,rt); 
    build(SC,1,seq[0],ch[rt][1]);
    pu(ch[rt][1]);
   // printf("woyilianmengbi??sz=%d\n",sz[rt]);
}
 
void del(int x) {
    if(!x) return;
    stk[++top]=x;
    del(LC);del(RC);
}
 
void print(int x) {
    if(x) {
        pd(x);
        print(LC);
        if(val[x]!=-INF) printf("%d ",val[x]);
        print(RC);
    }
}
 
char op[10];
int main() {
    int n,m,cnt,k,tot,c;
    read(n);read(m);
    seq[0]=0;
    REP(i,1,n) read(seq[++seq[0]]);
    cnt=n;init();
    REP(i,1,m) {
        scanf("%s",op);
        if(strcmp(op,"INSERT")==0) {
            read(k);read(tot);
            seq[0]=0;
            REP(i,1,tot) read(seq[++seq[0]]);
            rto(k+1);rto(k+2,rt);
            build(SC,1,seq[0],ch[rt][1]);   
            pu(ch[rt][1]);pu(rt);
            cnt+=tot;       
        }
        if(strcmp(op,"DELETE")==0) {
            read(k);read(tot);
            rto(k);rto(k+1+tot,rt);
            del(SC);SC=0;
            pu(ch[rt][1]);pu(rt);
            cnt-=tot;
        }
        if(strcmp(op,"MAKE-SAME")==0) {
            read(k);read(tot);read(c);
            rto(k);rto(k+1+tot,rt);
            rep(SC,c);
            pu(ch[rt][1]);pu(rt);
        }
        if(strcmp(op,"REVERSE")==0) {
            read(k);read(tot);
            rto(k);rto(k+1+tot,rt);
            rev(SC);
            pu(ch[rt][1]);pu(rt);
        }
        if(strcmp(op,"GET-SUM")==0) {
            read(k);read(tot);
            rto(k);rto(k+1+tot,rt);
            printf("%d\n",vsum[SC]);
        }
        if(strcmp(op,"MAX-SUM")==0) {
            printf("L=%d R=%d\n",rto(1),rto(cnt+2,rt));
            printf("ww%d\n",cnt);
            if(vmx[SC]<=0) printf("%d\n",vmx[SC]);
            else printf("%d\n",mx[SC]);
        }
    }
    return 0;   
}
