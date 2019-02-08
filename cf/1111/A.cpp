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
const int N=1010;
char lx[N],ll[N];
char bj[10]={'a','u','e','i','o'};

int main(){
	scanf("%s%s",lx+1,ll+1);
	int len=strlen(lx+1),len2=strlen(ll+1);
	if(len!=len2) return printf("No\n"),0;
	fr(i,1,len){
		int flg1=0,flg2=0;
		fr(j,0,4) {
			if(lx[i]==bj[j]) flg1=1;
			if(ll[i]==bj[j]) flg2=1;
		}
		if(flg1!=flg2) return printf("No\n"),0;
	}
	printf("Yes\n");
	return 0;
}