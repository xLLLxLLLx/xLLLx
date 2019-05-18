#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int MASK=6e5+10;
struct data{ int x,y; };
vector<int> g[15];
int nm[15],pw[15]={1},ans=0;
int f[MASK][5],sum[15][3],a[15],bit[15],num[MASK][15];

int js(int x,int y){
	if(x==1) return y-1;
	if(x==2) return 3+y-1;
	if(x==3) return 5+y-1;
	else return 9;
}

data zh(int x){
	if(x<=3) return (data){1,x+1};
	if(x<=6) return (data){2,x-2};
	if(x<=8) return (data){3,x-4};
	else return (data){4,4}; 
}

void init(){
  bit[0]=1;
  for(int i=1;i<=10;++i) {
  	bit[i]=(bit[i-1]<<1)+bit[i-1];
  }
  for(int i=0;i<bit[10];++i) {
		int k=i;
		for(int j=0;j<10;++j) {
	    num[i][j]=k%3;
	    k/=3;
		}
	}
}

int main(){
	init();
	int n;scanf("%d",&n);
	fr(i,1,n) {
		int x,v,y;
		scanf("%d%d%d",&x,&v,&y);
		if (x>y) swap(x,y);
		int pos=js(x,y);
		g[pos].push_back(v),nm[pos]++;
	}
	fr(i,0,9) {
		if(!nm[i]) continue;
		data gg=zh(i);
		f[2*bit[i]][gg.x]=1;
		f[2*bit[i]][gg.y]=1;
		sort(g[i].begin(),g[i].end());
	}
	fr(i,0,9) {
		int len=g[i].size();
		rf(j,len-1,1) sum[i][1]+=g[i][j],sum[i][2]+=g[i][j];
		if(len) sum[i][2]+=g[i][0];
	}
	fr(i,0,bit[10]-1) {
		fr(j,1,4) {
			if(!f[i][j]) continue;
			fr(k,0,9) {
				if(!nm[k]) continue;
				data gg=zh(k);
				// printf("now%d %d %d\n",j,gg.x,gg.y);
				if(!num[i][k]) {
					if(nm[k]>1){
						if(j==gg.x) {
							if(nm[k]&1) {
								f[i+bit[k]][gg.x]=1;
							}
							else {
								f[i+bit[k]][gg.y]=1;
							}
						} else if(j==gg.y) {
							if(nm[k]&1) {
								f[i+bit[k]][gg.y]=1;
							}
							else {
								f[i+bit[k]][gg.x]=1;
							}
						}
					} else {
						if(j==gg.x) f[i+2*bit[k]][gg.y]=1;
						if(j==gg.y) f[i+2*bit[k]][gg.x]=1;
					}
				} else if(num[i][k]==1) {
					if(j==gg.x) f[i+bit[k]][gg.y]=1;
					if(j==gg.y) f[i+bit[k]][gg.x]=1;
				} else continue;
			}
		}
	}
	fr(i,0,bit[10]-1){
		fr(j,1,4) {
			if(!f[i][j]) continue;
			int now=0;
			fr(k,0,9){
				int pos=num[i][k];
				now+=sum[k][pos];
			}
			ans=max(ans,now);
		}
	}
	printf("%d\n",ans);
	return 0;
}