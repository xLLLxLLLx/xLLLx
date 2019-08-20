#include<bits/stdc++.h>
using namespace std;
int n;
int a[110];
void dfs(int now){
	if(now==n)
	{
		for(int i=0;i<n;i++)
		{
			if(a[i])
			{
				cout<<i + 1<<" ";
			}
		}
		puts("");
		return ;
	}
	a[now]=0;
		dfs(now+1);
	a[now]=1;
		dfs(now+1);
}
int main()
{
	cin>>n;
	dfs(0);
}