#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1010;
int a[N];

int main(){
	int n;cin>>n;
	fr(i,1,n) cin>>a[i];
	int ans=1e5,res=-1;
	fr(i,1,200){
	 int pos=0;
	 fr(j,1,n){
	 	if(a[j]==i) continue;
		else if(a[j]>i) pos+=(a[j]-i-1);
		else pos+=(i-1-a[j]);
	 }
	 if(pos<ans) ans=pos,res=i;
	}
	cout<<res<<" "<<ans<<endl;
	return 0;
}
