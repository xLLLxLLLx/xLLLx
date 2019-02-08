#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<map>
#include<stack>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
int a[10000];

int main(){
	int n;cin>>n;
	fr(i,1,n) cin>>a[i];
	sort(a+1,a+1+n);
	fr(i,1,100){
		int x;cin>>x;
		cout<<lower_bound(a+1,a+1+n,x)-a<<" "<<upper_bound(a+1,a+1+n,x)-a<<endl;
	}
	return 0;
}