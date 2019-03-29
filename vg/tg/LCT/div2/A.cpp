#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ls ch[x][0]
#define rs ch[x][1]
#define LL long long
using namespace std;
const int N=3e5+10;
struct data{
  int fr,to,w;
}a[N];
int ch[N][2],tag[N],v[N],mx[N];
int f[N],w[N],head[N],to[N],nt[N],cnt=0;

struct LCT{
  
  void up(int x){
    mx[x]=max(mx[ls],mx[rs]);
    mx[x]=max(mx[x],v[x]);
  }
  
  void down(int x){
    if(tag[x]){
      swap(ls,rs);
      tag[ls]^=1,tag[rs]^=1;
      tag[x]=0;
    }
  }
  
  void pushdown(int x){
    //printf("x=%d f[x]=%d\n",x,f[x]);
    if(!isroot(x)) pushdown(f[x]);
    down(x);
  }
  
  void reverse(int x){
    access(x),splay(x),tag[x]^=1;
  }
  
  bool isroot(int x){
    return (ch[f[x]][0]!=x)&&(ch[f[x]][1]!=x);
  }
  
  void access(int x){
    for(int i=0;x;i=x,x=f[x]){
      splay(x),rs=i,up(x);
    }
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
    pushdown(x);
    while(!isroot(x)){
      if(!isroot(f[x])) rotate(x);
      rotate(x);
    }
    up(x);
  }
  
  void update(int x,int nw){
    access(x),splay(x);
    v[x]=nw,up(x);
  }
  
  int ask(int x,int y){
    reverse(x),access(y),splay(y);
    return mx[y];
  }
  
}lct;

void read(int &x){
  char ch=getchar();x=0;
  for(;ch<'0'||ch>'9';ch=getchar()) ;
  for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void add(int x,int y){
  to[++cnt]=y,nt[cnt]=head[x],head[x]=cnt;
  to[++cnt]=x,nt[cnt]=head[y],head[y]=cnt;
}

void dfs(int u,int fa){
  //printf("u=%d fa=%d\n",u,fa);
  f[u]=fa;
  for(int i=head[u];i;i=nt[i]){
    if(to[i]!=fa) dfs(to[i],u);
  }
}

void init(){
  memset(head,0,sizeof head);
  memset(mx,0,sizeof mx);
  memset(ch,0,sizeof ch);
  //memset(tag,0,sizeof tag);
  memset(v,0,sizeof v);
}

char lx[15];

int main(){
  //freopen("out","r",stdin);
  int T;read(T);
  fr(o,1,T){
    init();
    cnt=0;
    int n;read(n);
    for(int i=1,x,y,z;i<n;++i){
      read(x),read(y),read(z);
      a[i].fr=x,a[i].to=y,a[i].w=z;
      add(i+n,x),add(i+n,y);
    }
    dfs(1,0);
//    printf("gggx1 f1=%d ch[1][0]=%d ch[1][1]=%d\n",f[1],ch[1][0],ch[1][1]);
    fr(i,1,n) {
  //    printf("x1 f1=%d ch[1][0]=%d ch[1][1]=%d\n",f[1],ch[1][0],ch[1][1]);
      lct.update(i+n,a[i].w);
    }
    for(;;){
      scanf("%s",lx+1);
      if(lx[1]=='Q'){
        int x,y;read(x),read(y);
        //printf("x1 f1=%d ch[1][0]=%d ch[1][1]=%d\n",f[1],ch[1][0],ch[1][1]);
        printf("%d\n",lct.ask(x,y));
      } else if(lx[1]=='C'){
        int x,y;read(x),read(y);
        lct.update(x+n,y);
      } else break;
    }
  }
  return 0;
}
