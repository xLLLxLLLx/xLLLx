#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=6e5+10;
map<int,int>mp[4][N];
char lx[N];
int sh[N][4],gg[N],GG[N],g[N],ch[N][4],hc=0,hs=0;

void insert(){
	int len=strlen(lx+1),fa=0;
	fr(i,1,len) {
		int pos=lx[i]-'a'+1;
		if(!ch[fa][pos]) ch[fa][pos]=++hc;
		fa=ch[fa][pos],gg[i]=fa;
	}
	fa=0;
	rf(i,len,1) {
		int pos=lx[i]-'a'+1;
		if(!sh[fa][pos]) sh[fa][pos]=++hs,g[hs]=fa;
		fa=sh[fa][pos],GG[i]=fa;
	}
	gg[0]=0,GG[len+1]=0;
	fr(i,1,len) {
		int pos=lx[i]-'a'+1;
		mp[pos][gg[i-1]][GG[i+1]]=1;
	}
}

int res=0;

int bl(int len){
	int fa=0;
	rf(i,len,1) {
		int pos=lx[i]-'a'+1;
		if(!sh[fa][pos]) sh[fa][pos]=++hs,g[hs]=fa;
		fa=sh[fa][pos];
	}
	return fa;
}

int main(){
	int n,m;scanf("%d%d",&n,&m);
	fr(i,1,n) scanf("%s",lx+1),insert();
	fr(i,1,m) {
		res=0;
		scanf("%s",lx+1);
		int len=strlen(lx+1);
		int tmp=bl(len),fa=0;
		int flg=0;
		fr(i,1,len) {
			int pos=lx[i]-'a'+1;
			tmp=g[tmp];
			fr(j,1,3){
				if(j==pos) continue;
				if(mp[j][fa].count(tmp)) {flg=1;printf("YES\n");break;}
			}
			if(flg) break;
			if(!ch[fa][pos]) break;
			fa=ch[fa][pos];
		}
		if(!flg) printf("NO\n");
	}
	return 0;
}
