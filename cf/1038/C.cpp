#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e5+10;
priority_queue<ll>q1,q2;

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) {
		ll x;scanf("%lld",&x);
		q1.push(x);
	}
	fr(i,1,n) {
		ll x;scanf("%lld",&x);
		q2.push(x);
	}
	ll p1=0,p2=0;
	int nw=0;
	for(;;){
		nw^=1;
		if(q1.empty()&&q2.empty()) break;
		if(q1.empty()){
			if(nw) {
				q2.pop();
			} else {
				p2+=q2.top(),q2.pop();
			}
		} else if(q2.empty()){
			if(nw) {
				p1+=q1.top(),q1.pop();
			} else q1.pop();
		} else {
			ll h1=q1.top(),h2=q2.top();
			if(nw){
				if(h1>=h2) p1+=h1,q1.pop();
				else q2.pop();
			} else {
				if(h2>=h1) p2+=h2,q2.pop();
				else q1.pop();
			}
		}
	}
	printf("%lld\n",p1-p2);
	return 0;
}