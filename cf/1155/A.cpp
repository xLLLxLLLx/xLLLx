#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
#define db double
using namespace std;
const int N=3e5+10;
char lx[N];

int main(){
	int n;cin>>n;
	scanf("%s",lx+1);
	int maxn=0,res=-1;
	fr(i,1,n){
		int pos=lx[i]-'a'+1;
		if(pos<maxn){
			printf("YES\n");
			printf("%d %d\n",res,i);
			return 0;
		}
		if(pos>maxn) maxn=pos,res=i;
	}
	printf("NO\n");
	return 0;
}