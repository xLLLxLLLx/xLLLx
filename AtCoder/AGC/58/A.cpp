#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long 
using namespace std;
const int N=12;
int mk[N],g[N];

int main(){
	int n,k;scanf("%d%d",&n,&k);
	fr(i,1,k) {
		int x;scanf("%d",&x);
		mk[x]=1;
	}
	int res=0;
	for(;n;n/=10) g[++res]=n%10;
	reverse(g+1,g+1+res);
	int F=1;
	fr(i,1,res){
		int flg=0;
		fr(j,0,9){
			if(!mk[j]&&j>=g[i]){
				flg=1;
				if(j>g[i]) {
					g[i]=j;int tmp=0;
					rf(t,9,0) if(!mk[t]) tmp=t;
					fr(t,i+1,res) g[t]=tmp;
					fr(t,1,res) printf("%d",g[t]);
					return 0;
				}
				g[i]=j;
				break;
			}
		}
		if(!flg) F=0;
	}
	if(!F){
		int tmp=0;
		rf(i,9,1) if(!mk[i]) tmp=i;
		printf("%d",tmp);
		rf(i,9,0) if(!mk[i]) tmp=i;
		fr(i,1,res) printf("%d",tmp);
	}
	else fr(i,1,res) printf("%d",g[i]);
	return 0;
}