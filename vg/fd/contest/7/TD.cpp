#include<bits/stdc++.h>
#define LL long long
#define fr(i,x,y) for(LL i=x;i<=y;++i)
#define rf(i,x,y) for(LL i=x;i<=y;++i)
#define bug(x); cout<<#x<<"="<<x<<endl;
using namespace std;
const int N=1e6+10,M=1e3+10;
LL rx[N],cx[N],r[M],c[M];

priority_queue<LL,vector<LL> >q1,q2;

int main(){
	int n,m;LL k,p;
	cin>>n>>m>>k>>p;
	fr(i,1,n) fr(j,1,m) {
		LL x;cin>>x;
		c[j]+=x,r[i]+=x;
	}
	fr(i,1,n) q1.push(r[i]);
	fr(i,1,k){
		LL pos=q1.top();q1.pop();
		rx[i]=rx[i-1]+pos;
		pos-=m*p;
		q1.push(pos);
	}
	fr(i,1,m) q2.push(c[i]);
	fr(i,1,k){
		LL pos=q2.top();q2.pop();
		cx[i]=cx[i-1]+pos;
		pos-=n*p;
		q2.push(pos);
	}
	LL maxn=-1e17;
	maxn=max(maxn,rx[k]),maxn=max(maxn,cx[k]);
	fr(i,1,k-1){
		LL pos=-(i)*1LL*(k-i)*1LL*p;
		pos+=rx[i]+cx[k-i];
		maxn=max(maxn,pos);
	}
	cout<<maxn<<endl;
	return 0;
}
