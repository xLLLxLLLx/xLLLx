#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=3e5+10;
char lx[N];
int len;

int get(int x){
	fr(i,x+2,len) {
		fr(j,x,i) fr(k,j+2,i){
			int pos=k+j;
			if(pos&1||lx[j]!=lx[k]) continue;
			if(lx[j]==lx[pos/2]) return i;
		}
	}
	return len+1;
}

int main(){
	scanf("%s",lx+1);
	len=strlen(lx+1);
	ll ans=0;
	fr(i,1,len) {
		int pos=lx[i]-'0';
		ans+=max(0,len-get(i)+1);
	}
	printf("%lld\n",ans);
	return 0;
}