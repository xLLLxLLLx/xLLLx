#include <iostream>
#include <cstdio>
#define LL long long
using namespace std;
const int maxn=15;
 
int n,T;
LL M[maxn],b[maxn],m[maxn],mul;
 
void ext_gcd(LL a,LL b,LL &x,LL &y)
{
    if(b==0)
    {
        x=1;
        y=0;
    }
    else
    {
        ext_gcd(b,a%b,y,x);
        y-=x*(a/b);
    }
}
 
void input()
{
    mul=1;
    scanf("%d",&n);
    for(int i=0; i<n; i++)
    {
        scanf("%lld %lld",&m[i],&b[i]);
        mul*=m[i];
    }
}
 
void slove(int co)
{
    LL x,y,ans=0;
    for(int i=0; i<n; i++)  M[i]=mul/m[i];
    for(int i=0; i<n; i++)
    {
          ext_gcd(M[i],m[i],x,y);
          ans=(ans+M[i]*x*b[i])%mul;
    }
    if(ans<0)  ans=(ans+mul)%mul;
    printf("Case %d: %lld\n",co,ans);
}
 
int main()
{
    scanf("%d",&T);
    for(int co=1; co<=T; co++)
    {
        input();
        slove(co);
    }
    return 0;
}