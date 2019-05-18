#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e6+10;
struct data{
	int x,y;
}a[N];
int res=0;
int n;

int main(){
	cin>>n;
	if(n==1||n==2) printf("No\n");
	else {
		printf("Yes\n");
		fr(i,1,n/2) a[++res]=(data){i,n-i+1};
		int pos=res/2*2,tmp=res*2-pos;
		if(n&1) {
			pos++;
			printf("%d %d ",pos,n/2+1);
			fr(i,1,res) {
				if(i%2==0){
					printf("%d %d ",a[i].x,a[i].y);
				}
			}
		} else {
			printf("%d ",pos);
			fr(i,1,res) {
				if(i%2==0){
					printf("%d %d ",a[i].x,a[i].y);
				}
			}
		}
		puts("");
		printf("%d ",tmp);
		fr(i,1,res){
			if(i&1){
				printf("%d %d ",a[i].x,a[i].y);
			}
		}
		puts("");
	}
	return 0;
}