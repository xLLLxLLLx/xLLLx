#include<bits/stdc++.h>
using namespace std;
const int mod = 1000000007;
int n;char mp[4][10003];
int dp[10003][8][2],fb[10003];
bool check(int x,int s)
{
	for(int i=1;i<=3;i++)
	if(s>>(i-1)&1 && (mp[i][x-1]=='O'||mp[i][x+2]=='O'))
		return true;
	return false;
}
void update(int &x,int y){x=(x+y)%mod;}
int main()
{
	scanf("%d%s%s%s",&n,mp[1]+1,mp[2]+1,mp[3]+1);
	for(int i=1;i<=n;i++)fb[i]=(mp[1][i]!='.')+((mp[2][i]!='.')<<1)+((mp[3][i]!='.')<<2);
	dp[1][0][0]=1;
	for(int x=1;x<=n;x++)
		for(int s=0;s<8;s++)
			for(int t=0;t<=1;t++)
			if(dp[x][s][t]&&(s&fb[x])==0)
			{
				int v=dp[x][s][t],next,tt;
				s|=fb[x];
				next=s^7;tt=check(x,next);
				update(dp[x+1][next][tt|t],v);
				if((s&3)==0)
				{
					next=s^4;tt=check(x,next)|(mp[3][x]=='O');
					update(dp[x+1][next][tt|t],v);
				}
				if(s==0||s==1)
				{
					next=s^1;tt=check(x,next)|(mp[1][x]=='O');
					update(dp[x+1][next][tt|t],v);
				}
				s^=fb[x];
			}
	cout<<dp[n+1][0][1]<<endl;
}

