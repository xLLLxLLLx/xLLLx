#include<bits/stdc++.h>
using namespace std;
const int N=2010;
int k,n,m;
int a[N<<2],cnt;
char s[N],t[N];
inline void Work(int x){
	if(!x)return;
	a[++cnt]=x;
	reverse(s,s+n);reverse(s+x,s+n);
}
int main(){
	scanf("%d%s%s",&n,s,t);
	for(int i=0;i<n;i++){
		int j=i;
		for(;j<n;j++)
			if(s[j]==t[n-i-1])break;
		if(j==n){
			puts("-1");
			return 0;
		}
		Work(n);Work(j);Work(1);
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)printf("%d ",a[i]);
	return 0;
}