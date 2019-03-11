#include<iostream>
#include<cstdio>
#include<cstring>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i<=y;++i)
#define LL long long
using namespace std;
const int N=2e5+10,M=5e4+10;
const int INF=5e4;
struct data{
	int tp,x,y,k,id,rk,v;
}q[N],q1[N],q2[N];
int tot=0;
LL tr1[M],tr2[M],ans[N];

int lowerbit(int x){ return x&(-x); }

void Upd(LL x,LL y){
	LL xs=x;
	for(;x<M;x+=lowerbit(x)) tr1[x]+=y,tr2[x]+=xs*y;
}

LL Get(int x){
	LL as=0,xs=x+1;
	for(;x;x-=lowerbit(x)) as+=xs*tr1[x]-tr2[x];
	return as;
}

void work(int l,int r,LL L,LL R){
	if(l>r||L>R) return ;
	//cout<<l<<" "<<r<<" "<<L<<" "<<R<<endl;
	int mid=(L+R+1)>>1;
	int tot1=0,tot2=0;
	if(L==R){
		fr(i,l,r){
			if(q[i].tp==2) ans[q[i].rk]=L;
		}
		return ;
	}
	fr(i,l,r){
		if(q[i].tp==1){
			if(q[i].v>=mid) {
				q2[++tot2]=q[i];
				Upd(q[i].x,1),Upd(q[i].y+1,-1);
			}
			else q1[++tot1]=q[i];
		} else {
			LL nm=Get(q[i].y)-Get(q[i].x-1);
			if(nm>=q[i].k) q2[++tot2]=q[i];
			else {
				q[i].k-=nm;
				q1[++tot1]=q[i];
			}
		}
	}
	fr(i,1,tot1) q[l+i-1]=q1[i];
	fr(i,1,tot2) q[l+tot1+i-1]=q2[i];
	fr(i,l,r) if(q[i].tp==1&&q[i].v>=mid) Upd(q[i].x,-1),Upd(q[i].y+1,1); 
	work(l,l+tot1-1,L,mid-1),work(l+tot1,r,mid,R);
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	int cnt=0;
	fr(i,1,m){
		int tp,b,c,d;
		scanf("%d%d%d%d",&tp,&b,&c,&d);
		if(tp==2){
			q[++tot].tp=2,q[tot].rk=++cnt,q[tot].x=b,q[tot].y=c,q[tot].k=d;
		} else {
			q[++tot].tp=1,q[tot].x=b,q[tot].y=c,q[tot].id=i,q[tot].v=d;
		}
	}
	/*fr(i,1,tot){
		printf("tp=%d x=%d y=%d id=%d rk=%d v=%d\n",q[i].tp,q[i].x,q[i].y,q[i].id,q[i].rk,q[i].v);
	}*/
	work(1,tot,1,n);
	fr(i,1,cnt) printf("%lld\n",ans[i]);
	return 0;
}
