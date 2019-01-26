#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define bug(x) cout<<#x<<"="<<x<<endl;
#define LL long long
using namespace std;
const int M=30,N=1010;
char lx[N];
int w[M],b[N];

int main(){
	scanf("%s",lx+1);
	int k;cin>>k;
	int len=strlen(lx+1);
	fr(i,1,len){
		int pos=lx[i]-'a'+1;
		b[i]=pos;
	}
	int maxn=0;
	fr(i,1,26) {
		cin>>w[i];
		maxn=max(maxn,w[i]);
	}
	LL ans=0;
	fr(i,1,len) ans+=i*w[b[i]];
	fr(i,len+1,len+k) ans+=maxn*i;
	cout<<ans<<endl;
	return 0;
}
