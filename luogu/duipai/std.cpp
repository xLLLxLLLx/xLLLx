#include <cstdio>
#include <cmath>
#include <unordered_map>
std::unordered_map <int,int> Hash;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
#define mul(a,b,p) (1ll*(a)*(b)%p)
int exbsgs(int A,int B,int p)
{
    if(B==1) return 0;
    int ct=0,d,k=1;
    while((d=gcd(A,p))^1)
    {
        if(B%d) return -1;
        B/=d,p/=d,++ct;
        k=mul(k,A/d,p);
        if(k==B) return ct;
    }
    int t=sqrt(p)+1,kt=1;
    Hash.clear();
    for(int i=0;i<t;i++)
    {
        Hash[mul(kt,B,p)]=i;
        kt=mul(kt,A,p);
    }
    k=mul(k,kt,p);
    for(int i=1;i<=t;i++)
    {
        if(Hash.find(k)!=Hash.end()) return i*t-Hash[k]+ct;
        k=mul(k,kt,p);
    }
    return -1;
}
int main()
{
    int a,p,b;
    scanf("%d%d%d",&a,&p,&b);
    while(a&&p&&b)
    {
        int ans=exbsgs(a,b,p);
        if(~ans) printf("%d\n",ans);
        else puts("No Solution");
        scanf("%d%d%d",&a,&p,&b);
    }
    return 0;
}
