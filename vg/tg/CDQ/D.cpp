#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
struct data{
	int x,y,z;
}qx[N],gg[N];
int n,m;
int ys[N],vis[N],a[N];
LL tr[N],ans[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

int lowerbit(int x){ return x&(-x); }

LL Get(int x){
	LL ans=0;
	if(!x) return 0LL;
	for(;x;x-=lowerbit(x)) ans+=tr[x];
	return ans;
}

void Upd(int x,int k){
	for(;x<N;x+=lowerbit(x)) tr[x]+=k;
}

void Qk(int x){
	for(;x<N;x+=lowerbit(x)) tr[x]=0;
}

void cdq(int l,int r){
	int mid=(l+r)>>1;
	if(l==r) return ;
	cdq(l,mid),cdq(mid+1,r);
	int pos=l-1,nw=l;
	//printf("l=%d r=%d\n",l,r);
	fr(i,mid+1,r){
		while(pos+1<=mid&&qx[pos+1].y<qx[i].y){
			pos++,gg[nw++]=qx[pos],Upd(qx[pos].z,1);
		}
		gg[nw++]=qx[i];
		ans[qx[i].x]+=(pos-l+1)-Get(qx[i].z-1);
	}
	fr(i,pos+1,mid) gg[nw++]=qx[i];
	fr(i,l,pos) Qk(qx[i].z);
	pos=mid+1;
	rf(i,r,mid+1){
		while(pos-1>=l&&qx[pos-1].y>qx[i].y){
			pos--,Upd(qx[pos].z,1);
		}
		ans[qx[i].x]+=Get(qx[i].z-1);
	}
	fr(i,pos,mid) Qk(qx[i].z);
	fr(i,l,r) qx[i]=gg[i];
}

int main(){
	read(n),read(m);
	fr(i,1,n) scanf("%d",&a[i]),ys[a[i]]=i;
	int cz=n+1;
	fr(i,1,m){
		int x;scanf("%d",&x);
		vis[x]=1;
		qx[--cz].y=ys[x],qx[cz].z=x,qx[cz].x=cz;
	}
	fr(i,1,n) if(!vis[i]) qx[--cz].y=ys[i],qx[cz].z=i,qx[cz].x=cz;
	cdq(1,n);
	/*fr(i,1,n){
		printf("mdans=%lld\n",ans[i]);
	}*/
	fr(i,1,n) ans[i]+=ans[i-1];
	rf(i,n,n-m+1) printf("%lld\n",ans[i]);
	return 0;
}
