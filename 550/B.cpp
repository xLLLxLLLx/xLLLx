//#include<bits/stdc++.h>
#include<iostream>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2010;
int a[N],b[N];

int main(){
	int n;cin>>n;
	fr(i,1,n){
		int x;cin>>x;
		if(x&1) a[++a[0]]=x;
		else b[++b[0]]=x;
	}
	sort(a+1,a+1+a[0]),sort(b+1,b+1+b[0]);
	if(a[0]==b[0]) printf("0\n");
	else if(a[0]>b[0]){
		int ans=0;
		fr(i,1,a[0]-b[0]-1) ans+=a[i];
		printf("%d\n",ans);
	} else {
		int ans=0;
		fr(i,1,b[0]-a[0]-1) ans+=b[i];
		printf("%d\n",ans);
	}
	return 0;
}