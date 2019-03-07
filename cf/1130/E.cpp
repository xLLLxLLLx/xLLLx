#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2010;
int a[N];

int main(){
	int k;scanf("%d",&k);
	LL sum=k+2000;
	cout<<"2000"<<endl;
	cout<<"-1 ";
	fr(i,2,2000){
		if(!sum) cout<<"0 ";
		else if(sum>=1e6) {
			cout<<"1000000 ";
			sum-=1e6;
		} else {
			cout<<sum<<" ";
			sum=0;
		}
	}
	return 0;
}
