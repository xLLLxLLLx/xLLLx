#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=2e5+10;
int mk[N];
char lx[N];

int main(){
	int n;scanf("%d",&n);
	scanf("%s",lx+1);
	int pos=0;
	fr(i,1,n){
		if(lx[i]=='('){
			pos++;
			printf("%d",pos&1);
			
		} else {
			pos--;
			printf("%d",(pos&1)^1);
		}
	}
	puts("");
	return 0;
}