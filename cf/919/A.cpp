#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;

int main(){
	int n;double m;
	cin>>n>>m;
	double maxn=100;
	fr(i,1,n){
		double x,y;
		cin>>x>>y;
		maxn=min(maxn,x/y);
	}
	printf("%.10f\n",maxn*m);
	return 0;
}