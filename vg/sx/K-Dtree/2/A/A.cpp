#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const ll inf=1e17;
const int N=5e4+10,M=10;
struct data{
	int a[M],c[2];
}s[N],sc[N],q;
struct node{
	int a[M];
	ll dis;
	bool operator < (const node &C) const {
		return dis<C.dis;
	}
}gg;
priority_queue<node>Q;
int n,k,pd;

bool cmp(data A,data B){
	if(A.a[pd]!=B.a[pd]) return A.a[pd]<B.a[pd];
	fr(i,pd+1,k) {
		if(A.a[i]!=B.a[i]) return A.a[i]<B.a[i];
	}
	fr(i,1,pd-1) {
		if(A.a[i]!=B.a[i]) return A.a[i]<B.a[i];
	}
}

ll dist(data A,data B){
	ll d=0;
	fr(i,1,k) {
		d+=1ll*(A.a[i]-B.a[i])*(A.a[i]-B.a[i]);
	}
	return d;
}

int build(int l,int r,int pos){
	int mid=(l+r)>>1;
	pd=pos,nth_element(s+l,s+mid,s+r+1,cmp);
	if(l<mid) {
		s[mid].c[0]=build(l,mid-1,pos%k+1);
	} else s[mid].c[0]=0;
	if(r>mid) {
		s[mid].c[1]=build(mid+1,r,pos%k+1);
	} else s[mid].c[1]=0;
	return mid;
}

void work(int now,int pos){
	if(!now) return ;
	ll d=dist(s[now],q);
	if(d<Q.top().dis) {
		Q.pop();
		node tt;
		fr(i,1,k) {
			tt.a[i]=s[now].a[i];
		}
		tt.dis=d;
		Q.push(tt);
	}
	ll pd=s[now].a[pos]-q.a[pos];
	if(pd>=0) {
		work(s[now].c[0],pos%k+1);
		if(pd*pd<Q.top().dis) {
			work(s[now].c[1],pos%k+1);
		}
	} else {
		work(s[now].c[1],pos%k+1);
		if(pd*pd<Q.top().dis) {
			work(s[now].c[0],pos%k+1);
		}
	}
}

int main(){
	while(scanf("%d%d",&n,&k)==2) {
		fr(i,1,n) fr(j,1,k) {
			scanf("%d",&s[i].a[j]);
		}
		int now=build(1,n,1);
		int T,m;
		scanf("%d",&T);
		gg.dis=inf;
		fr(o,1,T) {
			fr(i,1,k) {
				scanf("%d",&q.a[i]);
			}
			scanf("%d",&m);
			fr(i,1,m) {
				Q.push(gg);
			}
			work(now,1);
			int tmp=0;
			while(!Q.empty()) {
				tmp++;
				fr(i,1,k) {
					sc[tmp].a[i]=Q.top().a[i];
				}
				Q.pop();
			}
			printf("the closest %d points are:\n",m);
			rf(i,tmp,1) {
				fr(j,1,k) {
					printf("%d",sc[i].a[j]);
					if(j!=k) printf(" ");
					else printf("\n");
				}
			}
		}
	}
	return 0;
}