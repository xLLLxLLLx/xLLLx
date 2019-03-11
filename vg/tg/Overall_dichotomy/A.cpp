#include<iostream>
#include<cstdio>
#include<cstring>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i<=y;++i)
#define LL long long
using namespace std;
const int N=2e5+10;
const LL INF=1e9+7;
struct data{
	int tp,x,y,k,id,rk;
	LL v;
}q[N],q1[N],q2[N];
LL ans[N];
int tot=0;
int tr[N];

int lowerbit(int x){ return x&(-x); }

void Upd(int x,int y){
	for(;x<N;x+=lowerbit(x)) tr[x]+=y;
}

int Get(int x){
	if(!x) return 0;
	int ans=0;
	for(;x;x-=lowerbit(x)) ans+=tr[x];
	return ans;
}

void work(int l,int r,LL L,LL R){
	if(l>r) return ;
	//cout<<L<<" "<<R<<endl;
	LL mid=(L+R)>>1;
	int tot1=0,tot2=0;
	if(L==R){
		fr(i,l,r){
			if(q[i].tp==2) ans[q[i].rk]=L;
		}
		return ;
	}
	fr(i,l,r){
		if(q[i].tp==1){
			if(q[i].v<=mid) Upd(q[i].id,1),q1[++tot1]=q[i];
			else q2[++tot2]=q[i];
		} else {
			int nm=Get(q[i].y)-Get(q[i].x-1);
			if(nm>=q[i].k) q1[++tot1]=q[i];//<=M
			else {//>M
				q[i].k-=nm;
				q2[++tot2]=q[i];
			}
		}
	}
	fr(i,1,tot1) q[l+i-1]=q1[i];
	fr(i,1,tot2) q[l+tot1+i-1]=q2[i];
	fr(i,l,r) if(q[i].tp==1&&q[i].v<=mid) Upd(q[i].id,-1);
	work(l,l+tot1-1,L,mid),work(l+tot1,r,mid+1,R);
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,n){
		LL x;
		scanf("%lld",&x);
		q[++tot].tp=1,q[tot].id=i,q[tot].v=x;
	}
	fr(i,1,m){
		++tot;
		scanf("%d%d%d",&q[tot].x,&q[tot].y,&q[tot].k);
		q[tot].tp=2,q[tot].rk=i;
	}
	/*fr(i,1,tot){
		printf("tp=%d x=%d y=%d id=%d rk=%d v=%lld\n",q[i].tp,q[i].x,q[i].y,q[i].id,q[i].rk,q[i].v);
	}*/
	work(1,tot,-INF,INF);
	fr(i,1,m) printf("%lld\n",ans[i]);
	return 0;
}
