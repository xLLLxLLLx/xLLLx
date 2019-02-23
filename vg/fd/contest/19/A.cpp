#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=10;
int a[N];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n){
		int x;scanf("%d",&x);
		a[x]++;
	}
	int ans1=0,ans2=0,ans3=0;
	if(a[2]){
		int pos=a[1];
		pos=min(pos,a[2]);
		pos=min(pos,a[4]);
		ans1=pos;
		a[1]-=pos,a[2]-=pos,a[4]-=pos;
	}
	if(a[2]){
		int pos=a[1];
		pos=min(pos,a[2]);
		pos=min(pos,a[6]);
		ans2=pos;
		a[1]-=pos,a[2]-=pos,a[6]-=pos;
	}
	if(a[3]){
		int pos=a[1];
		pos=min(pos,a[3]);
		pos=min(pos,a[6]);
		a[1]-=pos,a[3]-=pos,a[6]-=pos;
		ans3=pos;
	}
	if(ans1+ans2+ans3!=n/3) return printf("-1\n"),0;
	fr(i,1,ans1) printf("1 2 4\n");
	fr(i,1,ans2) printf("1 2 6\n");
	fr(i,1,ans3) printf("1 3 6\n");
}
