/*just try it*/
#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ls ch[x][0]
#define rs ch[x][1]
#define LL long long
using namespace std;
const int N=1e5+10,inf=112333333;
struct data{
  int nt,to,z;
}a[N<<1];
multiset<int>pt[N],cl[N];
int cnt=0,ans=0;
int ch[N][2],lmx[N],rmx[N],mx[N],sum[N];
int head[N],w[N],f[N],col[N],len[N];

void read(int &x){
  char ch=getchar();x=0;bool f=0;
  for(;ch<'0'||ch>'9';ch=getchar()) f|=(ch=='-') ;
  for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
  if(f) x=-x;
}

struct LCT{
  
  int fir(multiset<int> &s){
    return s.size() ? *s.rbegin() : -inf;
  }
  
  int sec(multiset<int> &s){
    return s.size()>1 ? *(++s.rbegin()) : -inf;
  }
  
  void Max(int &x,int y){
    x=max(x,y);
  }
  
  void up(int x){
    sum[x]=sum[ls]+sum[rs]+len[x];
    int G=max(w[x],fir(cl[x]));
    int L=max(G,rmx[ls]+len[x]);
    int R=max(G,lmx[rs]);
//    printf("x=%d len=%d G=%d L=%d R=%d\n",x,len[x],G,L,R);
    lmx[x]=max(lmx[ls],sum[ls]+len[x]+R);
    rmx[x]=max(rmx[rs],sum[rs]+L);
//    mx[x]=L+R;
    mx[x]=max(R+rmx[ls]+len[x],L+lmx[rs]);
    Max(mx[x],max(mx[ls],mx[rs]));
    Max(mx[x],fir(pt[x]));
    Max(mx[x],fir(cl[x])+sec(cl[x]));
    if(!w[x]) Max(mx[x],max(fir(cl[x]),0));
//    printf("x=%d lmx=%d rmx=%d mx=%d ls=%d rs=%d sum=%d\n",x,lmx[x],rmx[x],mx[x],ls,rs,sum[x]);
  }
  
  bool isroot(int x){
    return (ch[f[x]][0]!=x)&&(ch[f[x]][1]!=x);
  }
  
  void rotate(int x){
    int y=f[x],z=f[y];
    int k=(ch[z][1]==y),d=(ch[y][1]==x);
    if(!isroot(y)) ch[z][k]=x;
    f[x]=z;
    ch[y][d]=ch[x][d^1],f[ch[x][d^1]]=y;
    ch[x][d^1]=y,f[y]=x;
    up(y),up(x);
  }
  
  void splay(int x){
    while(!isroot(x)){
      int y=f[x],z=f[y];
      if(!isroot(y)) 
        (ch[z][1]==y)^(ch[y][1]==x) ? rotate(x) : rotate(y);
      rotate(x);
    }
    up(x);
  }
  
  void access(int x){
    for(int i=0;x;i=x,x=f[x]){
      splay(x);
      if(rs) cl[x].insert(lmx[rs]),pt[x].insert(mx[rs]); 
      if(i) cl[x].erase(cl[x].find(lmx[i])),pt[x].erase(pt[x].find(mx[i]));
      rs=i,up(x);
    }
  }
  
  void change(int x){
    access(x),splay(x);
    col[x]^=1;
    if(!col[x]) w[x]=0;
    else w[x]=-inf;
//    printf("xxx\n");
    up(x);
//    printf("xxxx\n");
    ans=mx[x];
  }
  
  void init(int n){
    fr(i,0,n) lmx[i]=rmx[i]=mx[i]=-inf;
  }
  
}lct;

void add(int x,int y,int z){
  a[++cnt].to=y,a[cnt].z=z,a[cnt].nt=head[x],head[x]=cnt;
  a[++cnt].to=x,a[cnt].z=z,a[cnt].nt=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
  f[u]=fa;
  for(int i=head[u];i;i=a[i].nt){
    if(a[i].to==fa) continue;
    len[a[i].to]=a[i].z,dfs(a[i].to,u);
    cl[u].insert(lmx[a[i].to]),pt[u].insert(mx[a[i].to]);
  }
  lct.up(u);
}

int main(){
  int n;read(n);
  lct.init(n);
  for(int i=1,x,y,z;i<n;++i){
    read(x),read(y),read(z);
    add(x,y,z);
  }
  dfs(1,0);
  ans=mx[1];
  int m;read(m);
  fr(i,1,m){
    char ch=getchar();
    for(;ch<'A'||ch>'Z';) ch=getchar();
//    cout<<ch<<endl;
    if(ch=='A'){
      if(ans<0) printf("They have disappeared.\n");
      else printf("%d\n",ans);
    } else {
      int x;read(x);
      lct.change(x);
    }
  }
  return 0;
}
/*
 x=3 lmx=1 rmx=0 mx=0 ls=0 rs=0 sum=1
 x=2 lmx=1 rmx=0 mx=0 ls=0 rs=0 sum=1
 x=1 lmx=1 rmx=1 mx=2 ls=0 rs=0 sum=0
 2
 x=1 lmx=1 rmx=1 mx=2 ls=0 rs=0 sum=0
 x=1 lmx=1 rmx=1 mx=2 ls=0 rs=0 sum=0
 x=1 lmx=1 rmx=1 mx=2 ls=0 rs=0 sum=0
 x=1 lmx=1 rmx=1 mx=2 ls=0 rs=0 sum=0
 2
 x=2 lmx=1 rmx=0 mx=0 ls=0 rs=0 sum=1
 x=2 lmx=1 rmx=0 mx=0 ls=0 rs=0 sum=1
 x=1 lmx=1 rmx=1 mx=2 ls=0 rs=0 sum=0
 x=1 lmx=1 rmx=2 mx=2 ls=0 rs=2 sum=1
 x=1 lmx=1 rmx=1 mx=0 ls=0 rs=0 sum=0
 x=2 lmx=1 rmx=2 mx=2 ls=1 rs=0 sum=1
 x=2 lmx=1 rmx=2 mx=0 ls=1 rs=0 sum=1
 0
 x=3 lmx=1 rmx=0 mx=0 ls=0 rs=0 sum=1
 x=3 lmx=1 rmx=0 mx=0 ls=0 rs=0 sum=1
 x=2 lmx=-1061109566 rmx=-1061109566 mx=-1061109567 ls=0 rs=0 sum=1
 x=1 lmx=1 rmx=2 mx=0 ls=0 rs=2 sum=1
 x=1 lmx=1 rmx=0 mx=0 ls=0 rs=3 sum=1
 x=1 lmx=-1061109566 rmx=-1061109566 mx=-1061109567 ls=0 rs=0 sum=0
 x=3 lmx=1 rmx=0 mx=0 ls=1 rs=0 sum=1
 x=3 lmx=-1061109566 rmx=-1061109565 mx=-1061109567 ls=1 rs=0 sum=1
 They have disappeared.
 * */
