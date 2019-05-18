#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>
#include<cstring>

#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e5+10,M=310,C=30;
char lx[N],ch[2];
int dp[M][M][M];
int nm[4],mk[M][4];
vector<int>g[C];

bool check(){
	return dp[nm[1]][nm[2]][nm[3]]!=-1;
}

int get(int st,int pos){
	st++;
	int l=0,r=g[pos].size()-1,ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(g[pos][mid]>=st) ans=g[pos][mid],r=mid-1;
		else l=mid+1;
	}
	return ans;
}

void Min(int &x,int y){
	if(y==-1) return ;
	if(x==-1) x=y;
	else x=min(x,y);
}

int main(){
	int n,q;scanf("%d%d",&n,&q);
	scanf("%s",lx+1);
	fr(i,1,n){
		int pos=lx[i]-'a'+1;
		g[pos].push_back(i);
	}
	memset(dp,-1,sizeof dp);
	fr(o,1,q){
		scanf("%s",ch+1);
		dp[0][0][0]=0;
		if(ch[1]=='+') {
			int x;scanf("%d%s",&x,ch+1);
			int pos=ch[1]-'a'+1;
			if(x==1){
				fr(i,0,nm[2]) fr(j,0,nm[3]) {
					if(dp[nm[x]][i][j]==-1) continue;
					dp[nm[x]+1][i][j]=get(dp[nm[x]][i][j],pos);
				}
				mk[++nm[x]][1]=pos;
				fr(i,0,nm[2]) fr(j,0,nm[3]) {
					int st=dp[nm[x]][i][j];
					if(st==-1) continue;
					if(i+1<=nm[2]) Min(dp[nm[x]][i+1][j],get(st,mk[i+1][2]));
					if(j+1<=nm[3]) Min(dp[nm[x]][i][j+1],get(st,mk[j+1][3]));
				}
			} else if(x==2){
				fr(i,0,nm[1]) fr(j,0,nm[3]) {
					if(dp[i][nm[x]][j]==-1) continue;
					dp[i][nm[x]+1][j]=get(dp[i][nm[x]][j],pos);
				}
				mk[++nm[x]][2]=pos;
				fr(i,0,nm[1]) fr(j,0,nm[3]) {
					int st=dp[i][nm[x]][j];
					if(st==-1) continue;
					if(i+1<=nm[1]) Min(dp[i+1][nm[x]][j],get(st,mk[i+1][1]));
					if(j+1<=nm[3]) Min(dp[i][nm[x]][j+1],get(st,mk[j+1][3]));
				}
			} else {
				fr(i,0,nm[1]) fr(j,0,nm[2]) {
					if(dp[i][j][nm[x]]==-1) continue;
					dp[i][j][nm[x]+1]=get(dp[i][j][nm[x]],pos);
				}
				mk[++nm[x]][3]=pos;
				fr(i,0,nm[1]) fr(j,0,nm[2]) {
					int st=dp[i][j][nm[x]];
					if(st==-1) continue;
					if(i+1<=nm[1]) Min(dp[i+1][j][nm[x]],get(st,mk[i+1][1]));
					if(j+1<=nm[2]) Min(dp[i][j+1][nm[x]],get(st,mk[j+1][2]));
				}
			}
			if(check()) printf("YES\n");
			else printf("NO\n");
		} else {
			int x;scanf("%d",&x);
			if(x==1) fr(i,0,nm[2]) fr(j,0,nm[3]) dp[nm[x]][i][j]=-1;
			else if(x==2) fr(i,0,nm[1]) fr(j,0,nm[3]) dp[i][nm[x]][j]=-1;
			else fr(i,0,nm[1]) fr(j,0,nm[2]) dp[i][j][nm[x]]=-1;
			nm[x]--;
			if(check()) printf("YES\n");
			else printf("NO\n");
		}
		// printf("nw=s%d\n",o);
		// fr(i,1,3){
		// 	fr(j,1,nm[i]) printf("%d ",mk[j][i]);
		// 	puts("");
		// }
		// fr(i,0,nm[1]) fr(j,0,nm[2]) fr(k,0,nm[3]) printf("dp[%d][%d][%d]=%d\n",i,j,k,dp[i][j][k]);
	}
	return 0;
}