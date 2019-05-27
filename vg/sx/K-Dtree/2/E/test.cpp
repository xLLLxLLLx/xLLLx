#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
int a[1100];

int main(){
	int n;
	cin>>n;
	fr(i,1,n) cin>>a[i];
	int l=1,r=5;
	int mid=(l+r)>>1;
	nth_element(a+l+1,a+mid+1,a+r+1);
	printf("%d\n",a[mid]);
	return 0;
}