#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e5+10;
int a[N];

int main(){
	int n;cin>>n;
	fr(i,1,n) scanf("%d",&a[i]);
	int lt=0,rt=0,maxn=0;
	fr(i,1,n){
		if(a[i]==a[i-1]){
			if(a[i]==1) lt++; 
			else rt++;
		} else {
			if(a[i]==1) lt=1;
			else rt=1;
		}
		maxn=max(maxn,min(lt,rt));
	}
	cout<<maxn*2<<endl;
	return 0;
}
