#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=3e5+10;
struct data{
	int id,w;
}gg[N];
char lx[N];
int qz[N];

void fail(){
	printf(":(\n");
	exit(0);
}

int main(){
	int n;scanf("%d",&n);
	if(n&1) fail();
	scanf("%s",lx+1);
	int res=0,tmp=0,pos=0;
	fr(i,1,n){
		if(lx[i]=='(') res++;
		if(lx[i]==')') tmp++;
	}
	res=n/2-res,tmp=n/2-tmp;
	if(res<0||tmp<0) fail();
	fr(i,1,n){
		if(lx[i]=='?'){
			if (res){
				lx[i]='(';
				res--;
			} else lx[i]=')';
		}
	}
	int nw=0;
	fr(i,1,n){
		if(lx[i]=='(') nw++;
		if(lx[i]==')') nw--;
		if(i!=n) if(nw<=0) fail();
	}
	fr(i,1,n) printf("%c",lx[i]);
	return 0;
}