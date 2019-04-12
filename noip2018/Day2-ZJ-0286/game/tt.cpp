#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
const int N=100;
int n,m,mask;
vector<int>qx[10000];
int a[N][N],b[N],res=0;

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) 2333;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void js(int val){
	int x=(val+1)/m,y=(val+1)%m;
	if(y) x++;
	else y=m;
	a[x][y]=1;
}

void dfs(int lena,int lenb){
	if(lena==n&&lenb==m){
		int nx=1,ny=1;
		qx[++res].push_back(a[1][1]);
		fr(i,1,n+m-2){
			if(b[i]) ny++;
			else nx++;
			qx[res].push_back(a[nx][ny]);
		}
	}
	if(lena<n) b[lena+lenb+1]=0,dfs(lena+1,lenb);
	if(lenb<m) b[lena+lenb+1]=1,dfs(lena,lenb+1);
}
//shut up!
bool pd(int x,int y){
	int lenx=qx[x].size(),leny=qx[y].size();
	fr(i,0,lenx-1){
		if(qx[x][i]>qx[y][i]) return true;
		if(qx[y][i]>qx[x][i]) return false;
	}
	return true;
}

bool check(int mask){
	int tmp=res;
	dfs(0,0);
	printf("%d\n",res);
	fr(i,tmp,res) 
	 fr(j,i+1,res){
	 	if(!pd(i,j)) return false;
	 }
	return true;
}

int main(){
	read(n),read(m);
	int mask=(1<<(n+m))-1;
	int ans=0;
	fr(i,0,mask){
		memset(a,0,sizeof a);
		fr(j,0,n+m-1){
			if((i>>j)&1) js(j);
		}
		if(check(i)) printf("%d\n",i),ans++;
	}
	printf("%d\n",ans);
	return 0;
}
