//#include<bits/stdc++.h>
#include<iostream>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e5+10;
struct data{
	int tp,x,y;
}b[N];
int a[N],c[N],mk[N];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%d",&a[i]),c[a[i]]++,mk[a[i]]=i;
	int gg=0,maxn=0,res=0;
	fr(i,0,2e5) if(c[i]>maxn) maxn=c[i],gg=i;
	rf(i,mk[gg]-1,1){
		if(a[i]>gg) b[++res].tp=2,b[res].x=i,b[res].y=i+1;
		if(a[i]<gg) b[++res].tp=1,b[res].x=i,b[res].y=i+1;
	}
	fr(i,mk[gg]+1,n){
		if(a[i]>gg) b[++res].tp=2,b[res].x=i,b[res].y=i-1;
		if(a[i]<gg) b[++res].tp=1,b[res].x=i,b[res].y=i-1;
	}
	printf("%d\n",res);
	fr(i,1,res) printf("%d %d %d\n",b[i].tp,b[i].x,b[i].y);
	return 0;
}