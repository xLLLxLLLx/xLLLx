#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=1e4+10;
string lx;
int c[N];

int main(){
	int n;
	scanf("%d",&n);getchar();
	getline(cin,lx);
	int len=lx.length();
	int lt=-1;
	fr(i,0,len-1){
		if(lx[i]=='?'||lx[i]=='!'||lx[i]=='.'){
			c[++c[0]]=i-lt;
			lt=i;
		}
	}
	int ans=0,pos=0,nw=0;
	fr(i,1,c[0]) if(c[i]-(i!=1)>n) return printf("Impossible\n"),0;
	fr(i,1,c[0]){
		pos+=c[i];
		if(pos>n){
			ans++;
			nw=i-1;
			pos=c[i]-1;
		}
	}
	cout<<ans+1<<endl;
	return 0;
}
