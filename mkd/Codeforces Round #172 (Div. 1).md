[TOC]



## [Codeforces Round #172 (Div. 1)](https://codeforces.com/contest/280)

[窝是传送门!](https://codeforces.com/contest/280)

### A.Rectangle Puzzle

超暴力地求出交点 交点构成了一个凸包

直接计算凸包的面积就可以啦～

可以直接按照极角序排序！

~~推式子的方法博主不会~~

![](https://img2018.cnblogs.com/blog/1624986/201904/1624986-20190416200349241-108096118.png)

```c++
#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define db double
using namespace std;
const db PI=acos(-1);
const int N=10;
db kk[N],bb[N];
struct data{ db x,y; }a[N];
struct node{
  db l,r,flg,v;
}zz[N];
db w,h,Arg;
int res=0;

db cross(data A,data B){
  return A.x*B.y-A.y*B.x;
}

bool cmp(data xx,data yy){
  return atan2(xx.y,xx.x)<atan2(yy.y,yy.x);
}

db js(){
  sort(a+1,a+1+res,cmp);
  db ans=0;
  a[res+1]=a[1];
  fr(i,1,res){
    ans+=cross(a[i],a[i+1]);
  }
  return ans/2.0;
}

db jsx(db k,db b,db y){
  return (y-b)/k;
}

db jsy(db k,db b,db x){
  return k*x+b;
}

void init(){
  kk[1]=kk[3]=tan(Arg);
  kk[2]=kk[4]=-1/tan(Arg);
  bb[1]=h/2.0/cos(Arg);
  bb[2]=w/2.0/sin(Arg);
  bb[3]=-bb[1],bb[4]=-bb[2];
  zz[1].l=zz[2].l=-w/2.0;
  zz[1].r=zz[2].r=w/2.0;
  zz[1].flg=zz[2].flg=1;
  zz[1].v=h/2.0,zz[2].v=-h/2.0;
  zz[3].l=zz[4].l=-h/2.0;
  zz[3].r=zz[4].r=h/2.0;
  zz[3].flg=zz[4].flg=0;
  zz[3].v=w/2.0,zz[4].v=-w/2.0;
}

int main(){
  cin>>w>>h>>Arg;
  if(Arg==90){
    printf("%.12f\n",min(h,w)*min(h,w));
    return 0;
  }
  Arg=Arg/180.0*PI;
  db tmp;
  init();
  fr(i,1,4){
    fr(j,1,4){
      if(!zz[j].flg){
        tmp=jsy(kk[i],bb[i],zz[j].v);
        if(tmp>=zz[j].l&&tmp<=zz[j].r) a[++res]=(data){tmp,zz[j].v};
      } else {
        tmp=jsx(kk[i],bb[i],zz[j].v);
        if(tmp>=zz[j].l&&tmp<=zz[j].r) a[++res]=(data){zz[j].v,tmp};
      }
    }
  }
  printf("%.12f\n",js());
  return 0;
}
```

-----

### B.Maximum Xor Secondary

直接按照题意模拟然后用单调栈优化就行了

~~我会说我写的很玄学然后wa了$n^n$发吗QwQ~~

说一下我的~~做法~~乱搞

二进制拆分 

枚举我们要保留的最高位

那么根据这个最高位我们可以将序列分成一段一段

然后扫一遍求最大值即可

复杂度$O(nlog_n)$

```c++
#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define db double
using namespace std;
const int N=1e5+10;
LL a[N];
int q[N];

int main(){
  int n;scanf("%d",&n);
  fr(i,1,n) scanf("%lld",&a[i]);
  LL ans=0;
  rf(i,30,0){
    q[0]=0;
    int res=0;
    fr(j,1,n) if((a[j]>>i)&1) q[++res]=j;
    q[res+1]=n+1;
    fr(j,1,res){
      LL pos=0;
      rf(k,q[j]-1,q[j-1]+1){
        pos=max(pos,a[k]);
        if(pos>=a[q[j]]) break;
        ans=max(ans,pos^a[q[j]]);
      }
      pos=0;
      fr(k,q[j]+1,q[j+1]-1){
        pos=max(pos,a[k]);
        if(pos>=a[q[j]]) break;
        ans=max(ans,pos^a[q[j]]);
      }
    }
  }
  printf("%lld\n",ans);
  return 0;
}
```

----

### C.Game on Tree

好神啊。



```c++
#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define db double
using namespace std;
const int N=1e5+10;
vector<int>g[N];
int dep[N];

void dfs(int u,int fa){
  int len=g[u].size();
  dep[u]=dep[fa]+1;
  fr(i,0,len-1)
    if(g[u][i]!=fa) dfs(g[u][i],u);
}

int main(){
  int n;scanf("%d",&n);
  for(int i=1,x,y;i<n;++i){
    scanf("%d%d",&x,&y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  dfs(1,0);
  db ans=0;
  fr(i,1,n) ans+=1.0/dep[i];
  printf("%.12f\n",ans);
  return 0;
}
```

----

### D - k-Maximum Subsequence Sum

好神啊。



```c++
#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define lson x<<1
#define rson x<<1|1
using namespace std;
const int N=1e5+10;

struct qj{
  int l,r;
  void init(int wz){ l=r=wz; }
};

vector<qj>qx;

int n;

struct data{
  int lmx,rmx,mx,sum;
  
  qj lp,rp,mp;
  
  void init(int wz,int v){
    lmx=rmx=mx=sum=v;
    lp.init(wz),rp.init(wz),mp.init(wz);
  }
};

struct node{
  data mx,mn;
  int tag;
  void rev() { swap(mn,mx); }
}tr[N<<2];

void read(int &x){
  char ch=getchar();x=0;int f=0;
  for(;ch<'0'||ch>'9';ch=getchar()) f|=(ch=='-');
  for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
  if(f) x=-x;
}

data merge(data a,data b){/*woc gang!!*/
  data nw;nw.init(0,0);
  nw.sum=a.sum+b.sum;
  if(a.mx>nw.mx) nw.mx=a.mx,nw.mp=a.mp;
  if(b.mx>nw.mx) nw.mx=b.mx,nw.mp=b.mp;
  if(a.rmx+b.lmx>nw.mx) nw.mx=a.rmx+b.lmx,nw.mp.l=a.rp.l,nw.mp.r=b.lp.r;
  if(a.lmx>nw.lmx) nw.lmx=a.lmx,nw.lp=a.lp;
  if(a.sum+b.lmx>nw.lmx) nw.lmx=a.sum+b.lmx,nw.lp.l=a.lp.l,nw.lp.r=b.lp.r;
  if(b.rmx>nw.rmx) nw.rmx=b.rmx,nw.rp=b.rp;
  if(a.rmx+b.sum>nw.rmx) nw.rmx=a.rmx+b.sum,nw.rp.l=a.rp.l,nw.rp.r=b.rp.r;
  return nw;
}

void up(int x){
  tr[x].mx=merge(tr[lson].mx,tr[rson].mx);
  tr[x].mn=merge(tr[lson].mn,tr[rson].mn);
}

void down(int x){
  //printf("x=%d\n",x);
  if(!tr[x].tag) return ;
  tr[lson].rev(),tr[rson].rev();
  tr[lson].tag^=1,tr[rson].tag^=1;
  tr[x].tag=0;
}

void build(int x,int l,int r){
  if(l==r){
    int v;read(v);
    tr[x].mx.init(l,v);
    tr[x].mn.init(l,-v);
    return ;
  }
  int mid=(l+r)>>1;
  build(lson,l,mid),build(rson,mid+1,r);
  up(x);
  /*puts("");
  printf("x=%d l=%d r=%d ::\n",x,l,r);
  printf("lmx=%d l=%d r=%d\n",tr[x].mx.lmx,tr[x].mx.lp.l,tr[x].mx.lp.r);
  printf("rmx=%d l=%d r=%d\n",tr[x].mx.rmx,tr[x].mx.rp.l,tr[x].mx.rp.r);
  printf("mmx=%d l=%d r=%d\n",tr[x].mx.mx,tr[x].mx.mp.l,tr[x].mx.mp.r);
  puts("");*/
}

void change(int x,int l,int r,int L,int k){
  if(l==r){
   tr[x].mx.init(l,k);
   tr[x].mn.init(l,-k);
   return ; 
  }
  int mid=(l+r)>>1;
  down(x);
  if(L<=mid) change(lson,l,mid,L,k);
  else change(rson,mid+1,r,L,k);
  up(x);
}

void modify(int x,int l,int r,int L,int R){
  if(L<=l&&r<=R){
    tr[x].rev();
    tr[x].tag^=1;
    return ;
  }
  int mid=(l+r)>>1;
  down(x);
  if(L<=mid) modify(lson,l,mid,L,R);
  if(R>mid) modify(rson,mid+1,r,L,R);
  up(x);
}

data Ask(int x,int l,int r,int L,int R){
  if(L<=l&&r<=R) return tr[x].mx;
  int mid=(l+r)>>1;
  down(x);
  if(R<=mid) return Ask(lson,l,mid,L,R);
  else if(L>mid) return Ask(rson,mid+1,r,L,R);
  else {
    data pos=Ask(lson,l,mid,L,R),tmp=Ask(rson,mid+1,r,L,R);
    return merge(pos,tmp);
  }
}

int get(int L,int R,int k){
  int ans=0;
  fr(o,1,k){
    data zz=Ask(1,1,n,L,R);
    if(zz.mx>0){
      ans+=zz.mx;
      modify(1,1,n,zz.mp.l,zz.mp.r);
      qx.push_back((qj){zz.mp.l,zz.mp.r});
    }
  }
  int len=qx.size();
  fr(i,0,len-1) modify(1,1,n,qx[i].l,qx[i].r);
  qx.clear();
  return ans;
}

int main(){
  read(n);
  build(1,1,n);
  int m;read(m);
  fr(o,1,m){
    int tp,x,y,z;
    read(tp);
    if(tp==1){
      read(x),read(y),read(z);      
      printf("%d\n",get(x,y,z));
    } else {
      read(x),read(y);
      change(1,1,n,x,y);
    }
  }
  return 0;
}
```



-----

### E - Sequence Transformation

看不懂。咕咕咕。

 