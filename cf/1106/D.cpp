#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define fi first
#define se second
#define LL long long
using namespace std;
const int N=1e5+10;
struct data{
	bool operator < (const data &B) const {
		if(w!=B.w) return w<B.w;
		else return rk<B.rk;
	}
	LL w;int rk;
};
LL yu[N],v[N];
multiset<data>A;
multiset<data> :: iterator sit;

int main(){
	int n,m;scanf("%d%d",&n,&m);
	LL res=0;
	fr(i,1,n) scanf("%lld",&yu[i]),res+=yu[i];
	fr(i,1,n) {
		scanf("%lld",&v[i]);
		A.insert((data){v[i],i});
	}
	fr(i,1,m){
		int x;LL y;
		scanf("%d%lld",&x,&y);
		LL ans=0;
		if(yu[x]) {
			if(yu[x]<=y){
				y-=yu[x];
				A.erase((data){v[x],x});
				ans+=yu[x]*v[x];
				yu[x]=0;
				if(!y) {
					printf("%lld\n",ans);
					continue;
				}
			} else {
				ans+=y*v[x];
				yu[x]-=y;
				printf("%lld\n",ans);
				continue;
			}
		}
		for(;!A.empty();){
			data pos=(*(A.begin()));
		//	printf("%d %lld %d\n",i,pos.w,pos.rk);
			if(yu[pos.rk]<=y){
				A.erase(pos);
				ans+=yu[pos.rk]*pos.w;
				y-=yu[pos.rk],yu[pos.rk]=0;
				if(!y) break;
			} else {
				ans+=y*pos.w;
				yu[pos.rk]-=y;
				y=0;
				break;
			}
		}
		if(y) {
			fr(j,i,m) printf("0\n");
			return 0;
		} else printf("%lld\n",ans);
	}
	return 0;
}
