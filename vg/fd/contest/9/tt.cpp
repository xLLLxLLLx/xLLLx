#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=510;
multiset<int>q[N][N];

int main(){
	int n;cin>>n;
	fr(i,1,n){
		int x;cin>>x;
		q[1][1].insert(x);
	}
	cout<<*(q[1][1].rbegin())<<endl;
}
