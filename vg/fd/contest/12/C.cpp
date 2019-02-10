#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<map>
#include<stack>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e6+10,M=6e5+10,mod=1e9+7;
int ch[N][4],sh[N][4],A[M],b[M],f[N];
int hc=0,hs=0;
LL ds=M;
char lx[M];
map<LL,int>mp;

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

void Mul(LL &x,LL y){
	x=(x*y)%mod;
}

LL add(LL x,LL y){
	return (x+y)%mod;
}

LL mul(LL x,LL y){
	return (x*y)%mod;
}

void push(){
	LL zz=a[0],pos=ds;
	fr(i,1,2) {
		Add(zz,mul(a[i],pos));
		Mul(pos,pos);
	}
	mp[zz]=1;
}

void insert(){
	int fa=0,len=strlen(lx+1);
	fr(i,1,len) {
		int pos=lx[i]-'a'+1;
		if(!ch[fa][pos]) ch[fa][pos]=++hc;
		A[i]=fa=ch[fa][pos];
	}
	rf(i,len,1) {
		int pos=lx[i]-'a'+1;
		if(!sh[fa][pos]) sh[fa][pos]=++hs;
		f[ch[fa][pos]]=fa;
		B[i]=fa=sh[fa][pos];
	}
	A[0]=0;B[len+1]=0;
	fr(i,0,len-1) push(A[i],B[i+2]);
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,n) scanf("%s",lx+1),insert();
	fr(i,1,m) {
		scanf("%s",lx+1);
		int x=0,y=Get();
		
	}
	return 0;
}