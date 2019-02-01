#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110,M=30;
int a[M][M],p[M],d[M],vis[M],res=0;
char lx[N][N];

bool check(int x,int y){
	int lenx=strlen(lx[x]+1),leny=strlen(lx[y]+1);
	fr(i,1,min(lenx,leny)){
		if(lx[x][i]!=lx[y][i]) {
			int pos=lx[x][i]-'a'+1,tmp=lx[y][i]-'a'+1;
			if(a[tmp][pos]) return false;
			a[pos][tmp]=1;return true;
		}
	}
	if(lenx>leny) return false;
	return true;
}

void dfs(int x){
	p[++res]=x;vis[x]=1;
	fr(i,1,26){
		if(a[x][i]){
			d[i]--;
			if(!d[i]) dfs(i);
		}
	}
}

int main(){
	int n;scanf("%d",&n);
	fr(i,1,n) scanf("%s",lx[i]+1);
	fr(i,1,n) 
	 fr(j,i+1,n) if(!check(i,j)) return printf("Impossible\n"),0;
	fr(k,1,26) fr(i,1,26) fr(j,1,26) a[i][j]=(a[i][j]|(a[i][k]&a[k][j]));
	fr(i,1,26) if(a[i][i]) return printf("Impossible\n"),0;
	fr(i,1,26) fr(j,1,26) if(a[i][j]) d[j]++;
	fr(i,1,26){
		if(!vis[i]&&!d[i]) dfs(i); 
	}
	fr(i,1,26) printf("%c",char(p[i]+'a'-1));
	return 0;
}
