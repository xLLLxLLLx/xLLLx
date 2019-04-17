#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e7+1;
int id[N],a[2];
LL ans=1e18;

void cal(LL gg,int x,int y){
	if(ans>gg) ans=gg,a[0]=x,a[1]=y;
}

LL yz[3];

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n){
		int x;scanf("%d",&x);
		if(id[x]) cal(x,id[x],i);
		id[x]=i; 
	}
	fr(i,1,N-1){
		int res=0;
		for(int j=i;j<=N;j+=i){
			if(id[j]) yz[++res]=j;
			if(res==2){
				cal(yz[1]*1LL*yz[2]/i,id[yz[1]],id[yz[2]]);
				break;
			}
		}
	} 
	if(a[0]>a[1]) swap(a[0],a[1]);
	printf("%d %d\n",a[0],a[1]);
	return 0;
}