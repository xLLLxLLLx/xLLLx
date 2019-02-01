#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
#define fi first
#define se second
using namespace std;
const int N=310;
map<int,int>mp;
map<int,int> :: iterator sit;
int v[N],w[N];

int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}

int Get(int x,int y){
	int a=max(x,y),b=min(x,y);
	return gcd(a,b);
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%d",&v[i]);
	fr(i,1,n) scanf("%d",&w[i]);
	int maxn=1e8,pos=v[1];
	fr(i,2,n) pos=Get(pos,v[i]);
	if(pos!=1) return printf("-1\n"),0;
	mp[0]=0;
	fr(i,1,n){
		for(sit=mp.begin();sit!=mp.end();++sit){
			int pos=(*sit).fi,tmp=(*sit).se;
			int zz=Get(pos,v[i]);
			if(mp.count(zz)) mp[zz]=min(mp[zz],tmp+w[i]);
			else mp[zz]=tmp+w[i];
		}
	}
	printf("%d\n",mp[1]);
	return 0;
}
