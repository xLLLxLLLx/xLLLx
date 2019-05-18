#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;

int main(){
	int n;scanf("%d",&n);
	char ch;
	int maxn=0,pos=0;
	fr(o,1,n){
		cin>>ch;
		if(ch=='-') pos--;
		else pos++;
		pos=max(pos,0);
		maxn=max(maxn,pos);
	}
	printf("%d\n",maxn);
	return 0;
}