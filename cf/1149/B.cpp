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
const int N=55;
int a[N][N];

void fail(){
	printf("NO\n");
	exit(0);
}

int main(){
	int n;cin>>n;
	fr(i,1,n) fr(j,1,n){
		char ch;cin>>ch;
		if(ch=='#') a[i][j]=1;
	}
	fr(i,1,n){
		fr(j,1,n){
			if(!a[i][j]){
				a[i][j]=1;
				fr(o,1,2){
					if(o+i>n) fail();
					if(a[o+i][j]) fail();
					a[o+i][j]=1;
				}
				fr(o,-1,1){
					if(!o) continue;
					if(o+j<=0||o+j>n) fail();
					if(a[i+1][o+j]) fail();
					a[i+1][o+j]=1;
				}
			}
		}
	}
	printf("YES\n");
	return 0;
}