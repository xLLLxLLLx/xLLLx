#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=2e6+10,M=6e5+10,mod=19260817;
int ch[N][4],sh[N][4],f[N],cnt=0,size=0,res=0,tr;
LL b[M];
char lx[M];

LL mul(LL x,LL y){
	return (x*y)%mod;
}

LL add(LL x,LL y){
	return (x+y)%mod;
}

void Add(LL &x,LL y){
	x=(x+y)%mod;
}

void Mul(LL &x,LL y){
	x=(x*y)%mod;
}

void insert(){
	int len=strlen(lx+1),fa=0;
	fr(i,1,len) {
		int pos=lx[i]-'a'+1;
		if(!ch[fa][pos]) ch[fa][pos]=++cnt;
		fa=ch[fa][pos];
	}
	fa=0;
	rf(i,len,1) {
		int pos=lx[i]-'a'+1;
		if(!sh[fa][pos]) sh[fa][pos]=++size,f[sh[fa][pos]]=fa;
		fa=sh[fa][pos];
	}
}

int find(int len){
	int fa=0;
	rf(i,len,2) {
		if(fa>tr) res++;
		int pos=lx[i]-'a'+1;
		if(!sh[fa][pos]) sh[fa][pos]=++size,f[sh[fa][pos]]=fa;
		fa=sh[fa][pos];
	}
	return fa;
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,n) {
		scanf("%s",lx+1);
		insert();
	}
	tr=size;
	fr(i,1,m){
		scanf("%s",lx+1);
		int len=strlen(lx+1),flg=0;
		res=0;
		int tmp=find(len);
		if(!res) {printf("YES\n");continue;}
		int nw=0;
		fr(j,2,len){
			int pos=lx[j-1]-'a'+1;
			if(!ch[nw][pos]) break;
			nw=ch[nw][pos];
			if(tmp>tr) res--;
			tmp=f[tmp];
			if(!res) {printf("%d\n",j),printf("YES\n");flg=1;break;}
		}
		if(!flg) printf("NO\n");
	}
	return 0;
}
