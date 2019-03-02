#include<bits/stdc++.h>
#define lson (x<<1)
#define rson (x<<1|1)
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;

const int N=1e5+10,mod=1e9+7;
int tot,n;
int a[N],all[N],qx[N],sy[N];
LL pre[N],nex[N],tr[N];
struct data{
	LL B,D,BC,CD,BCD,SZ;
};
vector<int>ys[N];
vector<data>seg[N];
LL ans=0;

int lowbit(int x){ return x&(-x); }

void UPD(int x,LL y){
	for(;x<N;x+=lowbit(x)) tr[x]+=y;
}

LL Get(int x){
	LL ans=0;
	for(;x;x-=lowbit(x)) ans+=tr[x];
	return ans;
}


void Add(LL &x,LL y){
	x=(x+y+mod)%mod;
}

void Mul(LL &x,LL y){
	x=x*y%mod;
}

LL add(LL x,LL y){
	return (x+y+mod)%mod;
}

LL mul(LL x,LL y){
	return x*y%mod;
}

void pushup(int t,int x,int l,int r){
	int mid=(l+r)>>1;
	seg[t][x].SZ=seg[t][lson].SZ+seg[t][rson].SZ;
	seg[t][x].B=add(seg[t][lson].B,seg[t][rson].B);
	seg[t][x].D=add(seg[t][lson].D,seg[t][rson].D);
	seg[t][x].BC=add(mul(seg[t][lson].B,seg[t][rson].SZ),add(seg[t][lson].BC,seg[t][rson].BC));
	seg[t][x].CD=add(mul(seg[t][rson].D,seg[t][lson].SZ),add(seg[t][lson].CD,seg[t][rson].CD));
	seg[t][x].BCD=add(add(mul(seg[t][rson].CD,seg[t][lson].B),mul(seg[t][lson].BC,seg[t][rson].D)),add(seg[t][lson].BCD,seg[t][rson].BCD));
}

void change(int t,int x,int l,int r,int L,int id,int k){
	if(L==l&&l==r){
		if(k==1) {
			seg[t][x].SZ=1;
			seg[t][x].B=pre[id];
			seg[t][x].D=nex[id];
			seg[t][x].BC=seg[t][x].CD=seg[t][x].BCD=0;
		} else {
			seg[t][x].SZ=seg[t][x].B=seg[t][x].D=seg[t][x].BC=seg[t][x].CD=seg[t][x].BCD=0;
		}
		return ;
	}
	int mid=(l+r)>>1;
	if(L<=mid) change(t,lson,l,mid,L,id,k);
	else change(t,rson,mid+1,r,L,id,k);
	pushup(t,x,l,r);
	//printf("l=%d r=%d B:%lld D:%lld BC:%lld CD:%lld BCD:%lld\n",l,r,seg[t][x].B,seg[t][x].D,seg[t][x].BC,seg[t][x].CD,seg[t][x].BCD);
}

void init(){
	scanf("%d",&n);
	fr(i,1,n) scanf("%d",&a[i]),all[i]=a[i];
	sort(all+1,all+1+n);
	tot=unique(all+1,all+1+n)-all-1;
	fr(i,1,n) {
		a[i]=lower_bound(all+1,all+1+tot,a[i])-all;
		pre[i]=Get(a[i]),UPD(a[i],1);
	}
	memset(tr,0,sizeof tr);
	rf(i,n,1) nex[i]=Get(a[i]),UPD(a[i],1);
	fr(i,1,n){
		ys[a[i]].push_back(i);
		qx[a[i]]++;
		sy[i]=qx[a[i]];
	}
	fr(i,1,tot) fr(j,1,(qx[i])*4) seg[i].push_back((data){0,0,0,0,0});
	fr(i,1,n) change(a[i],1,1,qx[a[i]],sy[i],i,1);
	fr(i,1,tot) Add(ans,seg[i][1].BCD);
}

int main(){
	init();
	int m;scanf("%d",&m);
	fr(i,1,m){
		int q,p,flg=1;
		scanf("%d%d",&q,&p);
		Add(ans,-seg[a[p]][1].BCD);
		if(q==1) flg=-1;
		change(a[p],1,1,qx[a[p]],sy[p],p,flg);
		Add(ans,seg[a[p]][1].BCD);
		printf("%lld\n",ans);
	}
	return 0;
}
