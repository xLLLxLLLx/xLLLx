#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=3e5+10;
int a[N],b[N];

void fail(){
	printf("No\n");
	exit(0);
}

bool check(int l,int r){
	int L=0,R=0;
	fr(i,l,r){
		if(b[i]<l||b[i]>r) return false;
		if(b[i]<i)
			if(L>b[i]) return false;
			 else L=b[i];
		else if(b[i]>i)
			if(R>b[i]) return false;
			 else R=b[i];
	}
	return true;
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%d",&b[i]),a[i]=(b[i]==i);
	fr(i,2,n-1) if(!a[i-1]&&!a[i]&&!a[i+1]) fail();
	fr(i,1,n){
		if(!a[i]){
			int l=i,r=i,nw=0;
			while((a[r+1]^nw)&&r+1<=n) r++,nw^=1;
			//printf("%d %d\n",l,r);
			if(!check(l,r)) fail();
			i=r;
		}
	}
	printf("Yes\n");
	return 0;
}