#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long LL;
const int N=1e7+5;
const int NN=1e6;
unsigned int prime[NN],cnt;           //prime[N]会MLE
bool vis[N];

void is_prime()
{
    cnt=0;
    memset(vis,0,sizeof(vis));
    for(int i=2;i<N;i++)
    {
        if(!vis[i])
        {
            prime[cnt++]=i;
            for(int j=i+i;j<N;j+=i)
            {
                vis[j]=1;
            }
        }
    }
}

int main()
{
    is_prime();
    int t;
    cin>>t;
    for(int kase=1;kase<=t;kase++)
    {
        LL n;
        cin>>n;
        int ans=1;
        for(int i=0;i<cnt&&prime[i]*prime[i]<=n;i++)
        {
            if(n%prime[i]==0)
            {
                int e=0;
                while(n%prime[i]==0)
                {
                    n/=prime[i];
                    e++;
                }
                ans*=(2*e+1);
            }
        }
        if(n>1)
            ans*=(2*1+1);
        printf("Case %d: %d\n",kase,(ans+1)/2);
    }
}