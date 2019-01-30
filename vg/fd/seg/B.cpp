#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define lson x<<1
#define rson x<<1|1
#define bug(x); cout<<#x<<"="<<x<<endl;
#define de(x); cout<<#x<<"="<<x<<" ";
#define xxxx cout<<endl;
using namespace std;
const int N=35010,M=55;
int a[N],b[N];
int f[M][N],v[N<<2],add[N<<2];

void build(int x,int l,int r,int nw){
	if(l==r){
		v[x]=f[nw][l];
		return ;
	}
	int mid=(l+r)>>1;
	build(lson,l,mid,nw),build(rson,mid+1,r,nw);
	add[x]=0;
	v[x]=max(v[lson],v[rson]);
}

void pushdown(int x){
	if(!add[x]) return ;
	v[lson]+=add[x];
	v[rson]+=add[x];
	add[lson]+=add[x],add[rson]+=add[x];
	add[x]=0;
}

void change(int x,int l,int r,int L,int R,int z){
	//printf("%d %d %d %d %d %d\n",x,l,r,L,R,z);
	if(L>R) return ;
	if(L<=l&&r<=R){
		v[x]+=z;
		add[x]+=z;
		return ;
	}
	int mid=(l+r)>>1;
	pushdown(x);
	if(L<=mid) change(lson,l,mid,L,R,z);
	if(R>mid) change(rson,mid+1,r,L,R,z);
	v[x]=max(v[lson],v[rson]);
	//printf("zz%d %d %d %d\n",x,l,r,v[x]);
}

int find(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) return v[x];
	pushdown(x);
	int mid=(l+r)>>1,ans1=0,ans2=0;
	if(L<=mid) ans1=find(lson,l,mid,L,R);
	if(R>mid) ans2=find(rson,mid+1,r,L,R);
	return max(ans1,ans2);
}

int main(){
	int n,k;scanf("%d%d",&n,&k);
	fr(i,1,n) scanf("%d",&a[i]);
	fr(i,1,k){
//		printf("i===%d\n",i);
		fr(j,1,n){
			int l=max(i-1,b[a[j]]);
			b[a[j]]=j;
			if(l>j-1) continue;
			change(1,0,n,l,j-1,1);
			f[i][j]=find(1,0,n,0,j-1);
	//		xxxx
		}
		memset(b,0,sizeof b);
		build(1,0,n,i);
	}
	//fr(i,1,k) fr(j,1,n) printf("%d %d %d\n",i,j,f[i][j]);
	printf("%d\n",f[k][n]);
	return 0;
}
