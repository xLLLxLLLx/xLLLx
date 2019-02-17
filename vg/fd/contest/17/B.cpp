#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define db double
using namespace std;
const int N=1e5+10;
struct data{
	LL A,B;
}qx[N];
struct node{
	LL w;int id;
	bool operator < (const node &C) const {
		return w<C.w;
	}
};
priority_queue<node>q;
int vis[N];
LL k[N],b[N];

bool cmp(data xx,data yy){
	if(xx.A!=yy.A) return xx.A>yy.A;
	return xx.B<yy.B;
}

int main(){
	int n;scanf("%d",&n);
	LL x1,x2;cin>>x1>>x2;
	fr(i,1,n){
		scanf("%lld%lld",&k[i],&b[i]);
		qx[i].A=k[i]*x1+b[i];
		qx[i].B=k[i]*x2+b[i];
	}
	sort(qx+1,qx+1+n,cmp);
	fr(i,1,n) q.push((node){qx[i].B,i});
	fr(i,1,n-1){
		while(!q.empty()&&qx[q.top().id].A>=qx[i].A) {
			q.pop();
		}
		node zz=q.top();
		if(zz.w>qx[i].B) {
			return printf("YES\n"),0;
		}
	}
	printf("NO\n");
	return 0;
}
