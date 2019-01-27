#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110,M=30;
char lx[N][N];
int cnt=0,p[M],a[M][M],b[M],c[M],vis[M],n;

int zh(char ch){
	return int(ch-'a'+1);
}

bool check(int x,int y){
	int lenx=strlen(lx[x]+1),leny=strlen(lx[y]+1);
	fr(i,1,min(lenx,leny)){
		if(lx[x][i]!=lx[y][i]) {
			if(a[zh(lx[y][i])][zh(lx[x][i])]) return false;
			a[zh(lx[x][i])][zh(lx[y][i])]=1;
			return true;
		}
	}
	if(lenx>leny) return false;
	return true;
}

void dfs(int x){
	vis[x]=1;
	p[++cnt]=x;
	for(int i=1;i<=26;++i){
		if(a[x][i]) {
			b[i]--;
			if(!b[i]) dfs(i);
		}
	}
}

int main(){
	scanf("%d",&n);
	fr(i,1,n) scanf("%s",lx[i]+1);
	fr(i,1,n) fr(j,i+1,n)
		if(!check(i,j)) return printf("Impossible\n"),0;
	fr(k,1,26)
	 fr(i,1,26)
	  fr(j,1,26) a[i][j]=(a[i][j]|(a[i][k]&a[k][j]));
	fr(i,1,26) if(a[i][i]) return printf("Impossible\n"),0;
	fr(i,1,26)
	 fr(j,1,26){
	 	if(a[i][j]) b[j]++;
	 }
	fr(i,1,26){
		if(!b[i]&&!vis[i]) dfs(i);
	}
	fr(i,1,26) cout<<char(p[i]+'a'-1);
	return 0;
}
