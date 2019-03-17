#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long

#define ls ch[x][0]
#define rs ch[x][1]

using namespace std;
const int N=5e5+10,M=4e6+10,inf=1e4;
int top=0,idx=0,cnt=0,root;
int s[M],ch[N][2],f[N],tag[N],add[N],fz[N],q[N];
int vmx[N],v[N],lmx[N],sum[N],sz[N],rmx[N],mx[N];//weihu

void up(int x){
  if(!x) return ;
  sum[x]=sum[ls]+sum[rs]+v[x];
  sz[x]=sz[ls]+sz[rs]+1;
  vmx[x]=max(v[x],max(vmx[ls],vmx[rs]));
  lmx[x]=max(lmx[ls],sum[ls]+v[x]+lmx[rs]);
  rmx[x]=max(rmx[rs],sum[rs]+v[x]+rmx[ls]);
  mx[x]=max(max(max(mx[ls],mx[rs]),max(lmx[x],rmx[x])),v[x]+rmx[ls]+lmx[rs]);
  //printf("xxx%d\n",mx[x]);
}

void rec(int x,int val){
  tag[x]=1,add[x]=val;
  v[x]=vmx[x]=val;
  sum[x]=val*sz[x];
  lmx[x]=rmx[x]=mx[x]=max(val*sz[x],0);
}

void rev(int x){
  fz[x]^=1;
  swap(ls,rs);
  swap(lmx[x],rmx[x]);
}

void down(int x){
  //printf("???x=%d\n",x);
  if(tag[x]){
    if(ls) rec(ls,add[x]);
    if(rs) rec(rs,add[x]);
    tag[x]=0;
  }
  if(fz[x]){
    if(ls) rev(ls);
    if(rs) rev(rs);
    fz[x]=0;
  }
}

void newnode(int &x,int val,int p){
  if(top) x=q[top--];
  else x=++idx;
  sz[x]=1;
  ls=rs=0;
  f[x]=p,v[x]=vmx[x]=sum[x]=val;
  lmx[x]=rmx[x]=mx[x]=max(sum[x],0);
  tag[x]=fz[x]=add[x]=0;
}

void build(int &x,int l,int r,int p){
  if(l>r) return ;
  int mid=(l+r)>>1;
  newnode(x,s[mid],p);
  build(ls,l,mid-1,x),build(rs,mid+1,r,x);
  up(x);
}

void init(){
  vmx[0]=-inf;
  newnode(ch[0][1],-inf,0);
  root=ch[0][1];
  newnode(ch[root][0],-inf,root);
  build(ch[ch[root][0]][1],1,s[0],ch[root][0]);
	up(ch[root][0]);up(root);
}

void print(int x){
  if(!x) return ;
  print(ls);
  printf("%d l=%d r=%d %d sz=%d f=%d\n",v[x],v[ls],v[rs],sum[x],sz[x],v[f[x]]);
  print(rs);
}

void rotate(int x){
  int y=f[x],z=f[y];
  down(x),down(y);
  int k=(ch[z][1]==y),d=(ch[y][1]==x);
  ch[z][k]=x,f[x]=z;
  ch[y][d]=ch[x][d^1],f[ch[x][d^1]]=y;
  ch[x][d^1]=y,f[y]=x;
  up(y),up(x);
}

void splay(int x,int goal){
  down(x);
  while(f[x]!=goal){
    int y=f[x],z=f[y];
    if(z!=goal)
      (y==ch[z][0])^(x==ch[y][0]) ? rotate(x):rotate(y);
    rotate(x);
  }
  up(x);
  if(!goal) root=x;
}

int find(int x,int k){  
  down(x);
  int gg=sz[ls]+1;
 // printf("%d %d %d %d %d\n",x,ls,rs,k,gg);
  if(gg>k) return find(ls,k);
  else if(gg<k) return find(rs,k-gg);
  else return x;
}

void del(int x){
  if(!x) return ;
  q[++top]=x;
  del(ls),del(rs);
}


int main(){
  int n,m;scanf("%d%d",&n,&m);
  fr(i,1,n) scanf("%d",&s[++s[0]]);
  init();
  string S;
  int cnt=n;
  fr(o,1,m){
    cin>>S;
    int pos,tot,c;
    if(S=="INSERT"){
      s[0]=0;
      scanf("%d%d",&pos,&tot);
      fr(i,1,tot) scanf("%d",&s[++s[0]]);
      int L=find(root,pos+1),R=find(root,pos+2);
      splay(L,0),splay(R,L);
      build(ch[R][0],1,s[0],R);
      up(R),up(L);
      cnt+=tot;
    }
    if(S=="DELETE"){
      scanf("%d%d",&pos,&tot);
      int L=find(root,pos),R=find(root,pos+tot+1);
      splay(L,0),splay(R,L);
      del(ch[R][0]);
      ch[R][0]=0;
      up(R),up(L);
      cnt-=tot;
    }
    if(S=="MAKE-SAME"){
      scanf("%d%d%d",&pos,&tot,&c);
      int L=find(root,pos),R=find(root,pos+tot+1);
      splay(L,0),splay(R,L);
      rec(ch[R][0],c);
      down(ch[R][0]);
      up(R),up(L);
    }
    if(S=="REVERSE"){
      scanf("%d%d",&pos,&tot);
      int L=find(root,pos),R=find(root,pos+tot+1);
      splay(L,0),splay(R,L);
      rev(ch[R][0]);
      down(ch[R][0]);
      up(R),up(L);
    }
    if(S=="GET-SUM"){
      scanf("%d%d",&pos,&tot);
      int L=find(root,pos),R=find(root,pos+tot+1);
      splay(L,0),splay(R,L);
      printf("%d\n",sum[ch[R][0]]);
    }
    if(S=="MAX-SUM"){
      int L=find(root,1),R=find(root,cnt+2);
      splay(L,0),splay(R,L);
      if(vmx[ch[R][0]]>=0) printf("%d\n",mx[ch[R][0]]);
      else printf("%d\n",vmx[ch[R][0]]);
    }
  }
  return 0;
}

