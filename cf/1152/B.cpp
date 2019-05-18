#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<vector>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long 
using namespace std;
const int N=45;
int a[N],b[N],ans=0;
int n;

int get(int res){
	fr(i,1,res){
		if(!a[i]) return i;
	}
	return -1;
}

void out(int nm){
	printf("%d\n",ans);
	fr(i,1,nm) printf("%d ",b[i]);
	exit(0);
}

void add(){
	n++;
	int m=n,res=0;
	for(;m;m>>=1) a[++res]=m%2;
	reverse(a+1,a+1+res);
}

void c(int x){
	n^=(1<<x)-1;
	int m=n,res=0;
	for(;m;m>>=1) a[++res]=m%2;
	reverse(a+1,a+1+res);
}

int main(){
	cin>>n;
	int res=0,m=n;
	for(;m;m>>=1) a[++res]=m%2;
	reverse(a+1,a+1+res);
	//fr(i,1,res) printf("%d ",a[i]);
	int nm=0,nw=0; 
	for(;;){
		// fr(i,1,res) printf("%d ",a[i]);
		// puts("");
		int pos=get(res);
		if(pos==-1) out(nm);
		if(nw) add();
		 else b[++nm]=res-pos+1,c(res-pos+1);
		nw^=1; 
		ans++;
	}
	return 0;
}