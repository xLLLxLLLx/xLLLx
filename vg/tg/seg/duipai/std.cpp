#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=7e4+10,M=5e4+10,INF=1e9;
struct data{
	int tp,x,y,v,k,rk,id;
}q[N],q1[N],q2[N];
int tr[N],ans[N],w[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

int lowerbit(int x){ return x&(-x); }

void Upd(int x,int y){
	for(;x<M;x+=lowerbit(x)) tr[x]+=y;
}

int Get(int x){
	int ans=0;
	for(;x;x-=lowerbit(x)) ans+=tr[x];
	return ans;
}

void work(int l,int r,int L,int R){
	if(l>r) return ;
	int mid=(L+R)>>1;
	if(L==R){
		fr(i,l,r) if(q[i].tp==2) ans[q[i].rk]=L;
		return ;
	}
	int tot1=0,tot2=0;
	fr(i,l,r){
		if(q[i].tp==1){
			if(q[i].v<=mid){
				q1[++tot1]=q[i];
				Upd(q[i].id,1);
			} else q2[++tot2]=q[i];
		} else if(q[i].tp==3){
			if(q[i].v<=mid){
				q1[++tot1]=q[i];
				Upd(q[i].id,-1);
			} else q2[++tot2]=q[i];
		} else {
			int nm=Get(q[i].y)-Get(q[i].x-1);
			if(nm>=q[i].k) q1[++tot1]=q[i];
			else q[i].k-=nm,q2[++tot2]=q[i];
		}
	}
	fr(i,1,tot1) q[i+l-1]=q1[i];
	fr(i,1,tot2) q[i+l+tot1-1]=q2[i];
	fr(i,l,r) {
		if(q[i].v>mid) continue;
		if(q[i].tp==1) Upd(q[i].id,-1);
		if(q[i].tp==3) Upd(q[i].id,1);
	}
	work(l,l+tot1-1,L,mid),work(l+tot1,r,mid+1,R);
}

int main(){
	int T;read(T);
	fr(o,1,T){
		int n,m;read(n),read(m);
		int tot=0,cnt=0;
		fr(i,1,n){
			int x;read(x);
			w[i]=x;
			q[++tot].tp=1,q[tot].v=x,q[tot].id=i;
		}
		fr(i,1,m){
			char ch;cin>>ch;
			if(ch=='Q') read(q[++tot].x),read(q[tot].y),read(q[tot].k),q[tot].rk=++cnt,q[tot].tp=2;
			else {
				int x,y;read(x),read(y);
				q[++tot].tp=3,q[tot].v=w[x],q[tot].id=x;
				w[x]=y;
				q[++tot].tp=1,q[tot].v=w[x],q[tot].id=x;
			}
		}
		work(1,tot,0,INF);
		fr(i,1,cnt) printf("%d\n",ans[i]);
	}
}
