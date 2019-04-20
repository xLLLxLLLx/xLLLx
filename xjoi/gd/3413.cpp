#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define ll long long
using namespace std;
const int N=1e5+10;
vector<int>g[N];
double f[N],dp[N],nm[N];

void read(int &x){
	char ch=getchar();x=0;
	for(;ch<'0'||ch>'9';ch=getchar()) ;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}
 
int main(){
    int n;read(n);
    fr(i,1,n){
    	if(i!=1) dp[i]=double(f[i]+nm[i]+1)/nm[i];
      for(int j=1;j*i<=n;++j)
        f[j*i]+=dp[i],nm[j*i]+=1;
    }
    printf("%.5f\n",dp[n]);
    return 0;
}