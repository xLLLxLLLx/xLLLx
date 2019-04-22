#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=25;
int a[N][N],b[N];

bool check(int x){
	int res=0;
	for(;x;x/=10) res+=x%10;
	return res==10;
}

int main(){
	int res=0,nw=0;
	int n;cin>>n;
	while(nw<n){
		res++;
		int pos=res*9;
		pos++;
		if(check(pos)) nw++;
	}
	cout<<res*9+1<<endl;
	return 0;
}