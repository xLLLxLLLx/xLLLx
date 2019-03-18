#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long

#define lson x<<1
#define rson x<<1|1

using namespace std;
const int N=2e5+10,M=N<<1;
int nm[N<<2];

string s;
int pos,n;

void change(int x,int l,int r,int L,int k){
  if(l==r) {
    nm[x]+=k;
    return ;
  }
  int mid=(l+r)>>1;
  if(L<=mid) change(lson,l,mid,L,k);
  else change(rson,mid+1,r,L,k);
  nm[x]=nm[lson]+nm[rson];
}

int Ask(int x,int l,int r){
  if(l==r) return l;
  int mid=(l+r)>>1;
  if(nm[lson]!=(mid-l+1)) return Ask(lson,l,mid);
  else return Ask(rson,mid+1,r);
}

int idx=0,root=0;
int ch[M][2],f[M],zf[M][2],sz[M],mk[N][2];
LL sum[M],v[M];

#define ls ch[x][0]
#define rs ch[x][1]

void up(int x){
  if(!x) return ;
  sum[x]=sum[ls]+sum[rs]+v[x];
  sz[x]=sz[ls]+sz[rs]+1;
  zf[x][0]=zf[ls][0]+zf[rs][0]+(v[x]>0);
  zf[x][1]=zf[ls][1]+zf[rs][1]+(v[x]<0);
}

int newnode(int& x,LL val,int p){
  x=++idx;
  f[x]=p,ls=rs=0,sz[x]=1;
  sum[x]=v[x]=val;
  zf[x][0]=(val>0),zf[x][1]=(val<0);
  return idx;
}

void init(){
  fr(i,1,n*4) nm[i]=0;
  root=idx=0;
  newnode(root,0,0);
  newnode(ch[root][1],0,root);
  up(ch[root][1]),up(root);
}

int find(int x,int k){
  int gg=sz[ls]+1;
  if(gg>k) return find(ls,k);
  else if(gg==k) return x;
  else return find(rs,k-gg);
}

void rotate(int x){
  int y=f[x],z=f[y];
  int d=(ch[z][1]==y),k=(ch[y][1]==x);
  ch[z][d]=x,f[x]=z;
  ch[y][k]=ch[x][k^1],f[ch[x][k^1]]=y;
  ch[x][k^1]=y,f[y]=x;
  up(y),up(x);
}

void splay(int x,int goal){
  while(f[x]!=goal){
    int y=f[x],z=f[y];
    if(z!=goal)
      (ch[z][1]==y)^(ch[y][1]==x) ? rotate(x) : rotate(y);
    rotate(x);
  }
  if(!goal) root=x;
}

int Fu(int x,int k){
  int nm=zf[ls][1],d=(v[x]<0);
  if(nm>=k) return Fu(ls,k);
  else if(nm+d==k) return x;
  else return Fu(rs,k-d-nm);
}

void print(int x){
  if(!x) return ;
  print(ls);
  printf("fa=%lld ls=%lld rs=%lld v=%lld\n",v[f[x]],v[ls],v[rs],v[x]);
  print(rs);
}

void delet(int pos){
  int L=pos;
  splay(L,0);
  int gg=sz[ch[L][0]];
  int Z=find(root,gg),Y=find(root,gg+2);
  splay(Z,0),splay(Y,Z);
  ch[Y][0]=0;
  up(Y),up(Z);
}

int main(){
  int cse=0;
  while(scanf("%d",&n)==1){
    init();
    printf("Case #%d:\n",++cse);
    fr(o,1,n){
      cin>>s;scanf("%d",&pos);
      if(s=="insert"){
        int val=Ask(1,1,n);
        int L=find(root,pos+1),R=find(root,pos+2);
        splay(L,0),splay(R,L);
        mk[val][0]=newnode(ch[R][0],val,R);
        up(R),up(L);
        int gg=zf[ch[root][0]][0]+(v[root]>0);
        if(zf[root][1]<=gg){
         int zz=sz[root]-1;
         int l=find(root,zz),r=find(root,zz+1);
         splay(l,0),splay(r,l);
         mk[val][1]=newnode(ch[r][0],-val,r);
         up(r),up(l);
        } else {
          gg++;
          int l=Fu(root,gg);
          splay(l,0);
          int pos=sz[ch[l][0]];
          int Z=find(root,pos),Y=find(root,pos+1);
          splay(Z,0),splay(Y,Z);
          mk[val][1]=newnode(ch[Y][0],-val,Y);
          up(Y),up(Z);
        }
        change(1,1,n,val,1);
      }
      if(s=="remove")
        delet(mk[pos][0]),delet(mk[pos][1]),change(1,1,n,pos,-1);
      if(s=="query"){
        int L=mk[pos][0],R=mk[pos][1];
        splay(L,0),splay(R,L);
        printf("%lld\n",sum[ch[R][0]]);
      }
    }
  }
  return 0;
}
