#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e6+10;
int a[N],b[N];

void fail(){
	printf("-1\n");
	exit(0);
}
/*我觉得很有必要把这份狗屎般的代码保存下来qwq...*/
int main(){
	int n;scanf("%d",&n);
	int maxn=0;
	fr(i,1,n) {
		int x;scanf("%d",&x);
		a[x]++;
		maxn=max(maxn,x);
	}
	if(!a[1]) {
		if(n==1&&a[0]) return printf("1 1\n1 1\n"),0;
			else fail();
	} 
	else if(a[1]==1) {
		fr(i,1,n) fr(j,1,1) a[i+j-2]--;
		fr(i,0,N-1) {
			if(a[i]) fail();
		}
		return printf("%d 1\n1 1\n",n),0;
	}
	else if(a[1]==2) {
		if(a[maxn]>1) fail();
		ll gg=1ll*maxn*maxn-4*n;
		if(gg<0) fail();
		ll len=sqrt(gg);
		if(len*len!=gg) fail();
		if((len+n)%2) fail();
		int x=(len+n)/2,y=(n-len)/2;
		fr(i,1,x) fr(j,1,y) a[i+j-2]--;
		fr(i,0,N-1) {
			if(a[i]) fail();
		}
		return printf("%d %d\n1 1\n",x,y),0;
	} 
	else if(a[1]==3) {
		if(a[maxn]==1) {
			int len=sqrt(n);
			fr(i,1,len){
				if(n%i) continue;
				if(check(i,n/i)) return 0;
				if(check(n/i,i)) return 0; 
			}
		} else if(a[maxn]==2) {

		} else fail();
		fail();
	} 
	else if(a[1]==4) {

	} 
	fail();
	return 0;
}