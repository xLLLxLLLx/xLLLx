#include<bits/stdc++.h>
using namespace std;
char s[1309];
bool a[5201][5201];
int n,i,j,k,f,dp[2][5201][5201];

int main(){
    for(scanf("%d",&n),i=1; i<=n; ++i){
        for(scanf("%s",s),j=0;s[j]; k=s[j]-('9'<s[j]?'A'-10:'0');
        a[i][(j<<2)+1]=8&k,a[i][(j<<2)+2]=4&k,a[i][(j<<2)+3]=2&k,a[i][(j<<2)+4]=1&k,++j);
    }
    for(i=1; i<=n; ++i)
        for(j=1; j<=n; k=(bool)a[i][j],dp[k][i][j]=1+min(dp[k][i-1][j-1],min(dp[k][i][j-1],dp[k][i-1][j])),++j);
    for(k=n+1; --k; f?(exit(printf("%d\n",k)&0)):(void)0)
        for(f=!(n%(i=k)); f&&i<=n; i+=k)
            for(j=k; f&&j<=n; f&=(dp[(bool)a[i][j]][i][j]>=k),j+=k);
   	return 0;
}
