#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
const int N=1e4+10;
char lx[5]={'a', 'e', 'i', 'o' ,'u'};
int c[N][5],r[N][5];

int main(){
	int t;cin>>t;
	fr(i,5,t/5){
		if(t%i==0){
			string ll="";
			int n=i,m=t/i;
			fr(i,1,n){
				fr(j,1,m){
						int pos=(i-1+j-1)%5;
						ll+=lx[pos];
				}
			}
			cout<<ll<<endl;
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}