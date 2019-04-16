#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=32,M=2e5+10;
int q[N],qz[M];

bool insert(int x){
	rf(i,N-1,0){
		if((x>>i)&1){
			if(!q[i]){
				q[i]=x;
				return true;
			} else x^=q[i];
		}
	}
	return false;
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%d",&qz[i]);
	fr(i,1,n) qz[i]^=qz[i-1];
	int ans=0;
	if(!qz[n]) return printf("-1\n"),0;
	rf(i,n,1){
		if(insert(qz[i])) ans++;
	}
	cout<<ans<<endl;
	return 0;
}