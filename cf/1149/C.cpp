#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>
#include<cstring>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;

int main(){
	int n;scanf("%d",&n);
	int res=0,tmp=0;
	fr(i,1,n){
		int x;scanf("%d",&x);
		if(x==1) res++;
		else tmp++;
	}
	if(!tmp) fr(i,1,res) printf("1 ");
	else {
		printf("2 "),tmp--;
		if(res) printf("1 "),res--;
		fr(i,1,tmp) printf("2 ");
		fr(i,1,res) printf("1 ");
	}
	return 0;
}