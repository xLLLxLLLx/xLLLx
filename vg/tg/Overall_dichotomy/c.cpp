//It is made by jump~
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;
typedef long long LL;
const int MAXM = 50011;
int n,m;
int tmp[MAXM],ans[MAXM];
LL c1[MAXM],c2[MAXM];
bool pd[MAXM];
struct ask{
    int id,l,r,val,jilu;
}a[MAXM],zuo[MAXM],you[MAXM];

inline int getint()
{
       int w=0,q=0; char c=getchar();
       while((c<'0' || c>'9') && c!='-') c=getchar(); if(c=='-') q=1,c=getchar(); 
       while (c>='0' && c<='9') w=w*10+c-'0', c=getchar(); return q ? -w : w;
}

inline void add(LL x,LL y){
    int cun=x;
    while(x<=n) {
    c1[x]+=y; c2[x]+=cun*y;
    x+=x&(-x);
    }
}

inline LL sum(LL x){
    LL total=0;
    for(int i=x;i>=1;i-=(i&-i)) total+=(x+1)*c1[i]-c2[i];
    return total;
}

inline void CDQ(int askl,int askr,int l,int r){
    if(askl>askr || l>r) return ;
    cout<<askl<<" "<<askr<<" "<<l<<" "<<r<<endl;
    if(l==r) { for(int i=askl;i<=askr;i++) ans[a[i].jilu]=l; return ; }
    int mid=(l+r+1)/2;
    int nowl=0,nowr=0; LL now;
    for(int i=askl;i<=askr;i++) {
    if(a[i].id==1) {
        if(a[i].val>=mid) add(a[i].l,1),add(a[i].r+1,-1),you[++nowr]=a[i];
        else zuo[++nowl]=a[i];
    }
    else{
        now=sum(a[i].r)-sum(a[i].l-1);
        if(now>=a[i].val) you[++nowr]=a[i];
        else a[i].val-=now,zuo[++nowl]=a[i];
    }
    }
    for(int i=askl;i<=askr;i++) if(a[i].id==1 && a[i].val>=mid) add(a[i].l,-1),add(a[i].r+1,1); //清空
    for(int i=1;i<=nowl;i++) a[askl+i-1]=zuo[i];
    for(int i=1;i<=nowr;i++) a[askl+nowl+i-1]=you[i];
    CDQ(askl,askl+nowl-1,l,mid-1);
    CDQ(askl+nowl,askr,mid,r);
}

inline void work(){
    n=getint(); m=getint();
    for(int i=1;i<=m;i++) { a[i].id=getint(); a[i].l=getint(); a[i].r=getint(); a[i].val=getint(); a[i].jilu=i; if(a[i].id==2) pd[i]=1; }
    CDQ(1,m,1,n);
    for(int i=1;i<=m;i++) if(pd[i]) printf("%d\n",ans[i]);
}

int main()
{
  work();
  return 0;
}
