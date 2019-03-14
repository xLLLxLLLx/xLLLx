#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e4+10,M=1e6+10;
struct Query{ int id,l,r,T; }q[N];
struct Change{ int x,nw,od; }c[N];
int pre[N],B[N],nm[M],d[N],a[N],ans=0;

bool cmp(Query xx,Query yy){
    if(B[xx.l]==B[yy.l]){
        if(B[xx.r]==B[yy.r]) return xx.T<yy.T;
        else return xx.r<yy.r;
    } else return xx.l<yy.l;
}

void Upd(int x,int flg){
   // printf("GG %d %d\n",x,flg);
    if(nm[x]) ans--;
    nm[x]+=flg;
    if(nm[x]) ans++;
}

void Go(int sit,int x,int y,int l,int r){
  //  printf("gg%d %d %d %d %d\n",sit,x,y,l,r);
    if(sit>=l&&sit<=r) Upd(x,-1),Upd(y,1);
    a[sit]=y;
}

int main(){
    int n,m;scanf("%d%d",&n,&m);
    int sz=pow(n,0.666666);
    fr(i,1,n) scanf("%d",&pre[i]),a[i]=pre[i],B[i]=i/sz+1;
    int T=0,cnt=0;
    fr(i,1,m){
        char ch;cin>>ch;
        int x,y;scanf("%d%d",&x,&y);
        if(ch=='Q') q[++cnt]=(Query){cnt,x,y,T};
        else c[++T]=(Change){x,y,pre[x]},pre[x]=y;
    }
    sort(q+1,q+1+cnt,cmp);
    /*fr(i,1,cnt){
        printf("id=%d l=%d r=%d T=%d\n",q[i].id,q[i].l,q[i].r,q[i].T);
    }*/
    int l=1,r=0;T=0;
    fr(i,1,cnt){
        while(q[i].T>T) T++,Go(c[T].x,c[T].od,c[T].nw,l,r);
        while(q[i].T<T) Go(c[T].x,c[T].nw,c[T].od,l,r),T--;
        while(l<q[i].l) Upd(a[l],-1),l++;
        while(l>q[i].l) l--,Upd(a[l],1);
        while(r<q[i].r) r++,Upd(a[r],1);
        while(r>q[i].r) Upd(a[r],-1),r--;
        d[q[i].id]=ans;
    }
    fr(i,1,cnt) printf("%d\n",d[i]);
    return 0;
}
