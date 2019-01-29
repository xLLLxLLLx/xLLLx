#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define lson x<<1
#define rson x<<1|1
#define LL long long
using namespace std;
const int N=2e5+10;
struct data{
	int tp;
	LL l,r;
}q[N>>1];
LL a[N],b[N];
LL all[N<<1],sum[N<<2],dis[N<<2],nm[N<<2];

void read(int &x){
	char ch=getchar();x=0;
	int f=0;
	for(;ch<'0'||ch>'9';ch=getchar()) f|=(ch=='-');
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
	if(f) x=-x;
}

void read(LL &x){
	char ch=getchar();x=0;
	int f=0;
	for(;ch<'0'||ch>'9';ch=getchar()) f|=(ch=='-');
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
	if(f) x=-x;
}

void pushup(int x){
	nm[x]=nm[lson]+nm[rson];
	dis[x]=dis[lson]+dis[rson];
	sum[x]=sum[lson]+sum[rson];
	if(nm[lson]&&nm[rson]) sum[x]+=nm[lson]*dis[rson]-dis[lson]*nm[rson];
}

void change(int x,int l,int r,int L,int k){
	if(l==r&&r==L) {
		nm[x]+=k;
		dis[x]+=k*1LL*all[L];
		return ;
	}
	int mid=(l+r)>>1;
	if(mid>=L) change(lson,l,mid,L,k);
	else change(rson,mid+1,r,L,k);
	pushup(x);
//	printf("%d %d %lld\n",l,r,sum[x]);
}

struct node{
	LL tot,dt,num;
};

node find(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) return (node){sum[x],dis[x],nm[x]};
	int mid=(l+r)>>1;
	if(R<=mid) return find(lson,l,mid,L,R);
	else if(L>mid) return find(rson,mid+1,r,L,R);
	else {
		node tmp=find(lson,l,mid,L,R);
		node pos=find(rson,mid+1,r,L,R);
		LL kk=pos.tot+tmp.tot+pos.dt*tmp.num-tmp.dt*pos.num;
		return (node){kk,tmp.dt+pos.dt,tmp.num+pos.num};
	}
}

int main(){
	int n;read(n);
	fr(i,1,n) read(all[i]),a[i]=all[i],b[i]=a[i];
	int m,res=n;read(m);
	fr(i,1,m){
		read(q[i].tp),read(q[i].l),read(q[i].r);
		if(q[i].tp==1){
			a[q[i].l]+=q[i].r;
			all[++res]=a[q[i].l];
		} else {
			all[++res]=q[i].l,all[++res]=q[i].r;
		}
	}
	sort(all+1,all+1+res);
	int now=unique(all+1,all+1+res)-all-1;
	fr(i,1,n) {
		int pos=lower_bound(all+1,all+1+now,b[i])-all;
	//	printf("pos=%d\n",pos);
		change(1,1,now,pos,1);
	}
	fr(i,1,m){
		if(q[i].tp==1){
			int L=lower_bound(all+1,all+1+now,b[q[i].l])-all;
			change(1,1,now,L,-1);
			b[q[i].l]+=q[i].r;
			L=lower_bound(all+1,all+1+now,b[q[i].l])-all;
			change(1,1,now,L,1);
		} else {
			int L=lower_bound(all+1,all+1+now,q[i].l)-all;
			int R=lower_bound(all+1,all+1+now,q[i].r)-all;
	//		printf("L=%d R=%d\n",L,R);
			printf("%lld\n",find(1,1,now,L,R).tot);
		}
	}
	return 0;
}
