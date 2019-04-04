#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10;
struct data{
	int l,r,id;
}d[N],c[N];
struct node{
	int ss,r;
};
struct Gei{
	int r,id;
	bool operator < (const Gei &C) const{
		return r<C.r;
	}
};
vector<node>v[N];
priority_queue<Gei>Q;
int qz[N],hz[N],ans[N];
int a[N],mk[N];

bool cmp(data xx,data yy){
	if(xx.l!=yy.l) return xx.l<yy.l;
	else return xx.r<yy.r;
}

int main(){
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	fr(i,1,n) {
		int x;scanf("%d",&x);
		mk[x]=i;
	}
	fr(i,1,m) scanf("%d",&a[i]);
//	fr(i,1,m) printf("%d %d\n",i,a[i]);
	memset(qz,-1,sizeof qz),memset(hz,-1,sizeof hz);
	fr(i,1,m){
		int sit=mk[a[i]];
		if(sit==1) qz[sit]=i;
		else qz[sit]=qz[sit-1];
		if(qz[sit]!=-1) v[sit].push_back((node){i,qz[sit]});
	}
	int res=0;
	rf(i,m,1){
		int sit=mk[a[i]];
		if(sit==n) hz[sit]=i;
		else hz[sit]=hz[sit+1];
		if(hz[sit]!=-1){
			if(sit==1){
				c[++res].l=i,c[res].r=hz[sit];
				continue;
			}
			int len=v[sit-1].size();
			if(!len||v[sit-1][len-1].r<hz[sit]) continue;
			int l=0,r=len-1,tt=-1;
			while(l<=r){
				int mid=(l+r)>>1;
				if(v[sit-1][mid].r>=hz[sit]) r=mid-1,tt=mid;
				else l=mid+1;
			}
			c[++res].l=i,c[res].r=v[sit-1][tt].ss;
		}
	}
	//fr(i,1,m) printf("%d %d\n",qz[i],hz[i]);
	fr(i,1,q) scanf("%d%d",&d[i].l,&d[i].r),d[i].id=i;
	sort(c+1,c+1+res,cmp),sort(d+1,d+1+q,cmp);
	int head=1,tail=0,lt=0;
	fr(i,1,res){
		//printf("zz%d %d\n",c[i].l,c[i].r);
		while(lt+1<=q&&d[lt+1].l<=c[i].l) lt++,Q.push((Gei){d[lt].r,d[lt].id});
		while(Q.size()&&Q.top().r>=c[i].r){
			Gei h=Q.top();Q.pop();
			ans[h.id]=1;
		}
	}
	fr(i,1,q) printf("%d",ans[i]);
	return 0;
}