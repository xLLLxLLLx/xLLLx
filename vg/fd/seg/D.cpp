#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define lson x<<1
#define rson x<<1|1
#define LL long long
using namespace std;
const int N=3e5+10;
int w[N<<2],B1[N<<2],B2[N<<2],E1[N<<2],E2[N<<2];
LL a[N],b[N];

int id(LL x){
	if(x>0) return 1;
	else if(x<0) return -1;
	else return 0;
}

void pushup(int x,int l,int r){
	int mid=(l+r)>>1;
	int szl=(mid-l+1),szr=(r-mid);
	w[x]=max(w[lson],w[rson]);
	B1[x]=B1[lson],B2[x]=B2[lson],E1[x]=E1[rson],E2[x]=E2[rson];
	if(B1[lson]==szl){
		if(E1[lson]) {
			int pos=szl+max(B1[rson],B2[rson]);
			B1[x]=max(B1[x],pos);
		}
		else if(E2[lson]){
			int pos=szl+B2[rson];
			B1[x]=max(B1[x],pos);
		}
		w[x]=max(w[x],B1[x]);
	}
	if(B2[lson]==szl){
		int pos=szl+B2[rson];
		B2[x]=max(B2[x],pos);
		w[x]=max(w[x],B2[x]);
	}
	if(E1[rson]==szr){
		int pos=szr+E1[lson];
		E1[x]=max(E1[x],pos);
		w[x]=max(w[x],E1[x]);
	}
	if(E2[rson]==szr){
		if(B1[rson]){
			int pos=szr+E1[lson];
			E2[x]=max(E2[x],pos);
		} else if(B2[rson]) E2[x]=max(E2[x],szr+max(E1[lson],E2[lson]));
		w[x]=max(w[x],E2[x]);
	}
	w[x]=max(w[x],E1[lson]+max(B1[rson],B2[rson]));
	w[x]=max(w[x],E2[lson]+B2[rson]);
	//printf("x=%d l=%d r=%d B1=%d B2=%d E1=%d E2=%d w=%d\n",x,l,r,B1[x],B2[x],E1[x],E2[x],w[x]);
}

void change(int x,int l,int r,int L,int zz){
	if(l==r&&l==L){
		if(zz) w[x]=1;
		if(zz==1) B1[x]=1,B2[x]=0,E1[x]=1,E2[x]=0;
		else if(zz==-1) B1[x]=0,B2[x]=1,E1[x]=0,E2[x]=1;
		else B1[x]=B2[x]=E1[x]=E2[x]=0;
		//printf("x=%d l=%d r=%d B1=%d B2=%d E1=%d E2=%d w=%d\n",x,l,r,B1[x],B2[x],E1[x],E2[x],w[x]);
		return ;
	}
	int mid=(l+r)>>1;
	if(L<=mid) change(lson,l,mid,L,zz);
	else change(rson,mid+1,r,L,zz);
	pushup(x,l,r);
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%lld",&a[i]);
	fr(i,1,n-1) {
		b[i]=a[i+1]-a[i];
		int pos=id(b[i]);
		change(1,1,n,i,pos);
	//	puts("");
	}
	int m;scanf("%d",&m);
	//puts("");
	fr(i,1,m){
		int l,r;LL x;scanf("%d%d%lld",&l,&r,&x);
		if(l>1) b[l-1]+=x,change(1,1,n,l-1,id(b[l-1]));
		if(r!=n) b[r]-=x,change(1,1,n,r,id(b[r]));
	//	fr(j,1,n-1) printf("%lld ",b[j]);
	//	puts("");
		printf("%d\n",w[1]+1);
	}
	return 0;
}
/*
7
10 2 8 8 4 2 4
7
7 7 20
3 4 75
5 7 14
1 5 10
2 4 14
5 7 51
6 6 67
*/
