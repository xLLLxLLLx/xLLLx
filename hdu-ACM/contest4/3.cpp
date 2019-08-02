#include <cstdio>
const int N=1e5+10;
int n,m;
int que[N],qn;
inline bool solve(int n,long long m)
{
		printf("%d %d\n", n, m);
    if (!n) return true;
    if (m<n) return false;
    if (m<=n*2)
    {
        if (m&1)
        {
            if (!solve(m-n-1,m)) return false;
            for (int i=m-n;i+i<m;i++) que[++qn]=i,que[++qn]=m-i;
            return true;
        }
        else
        {
            if (!solve(m-n-1,m/2)) return false;
            que[++qn]=m/2;
            for (int i=m-n;i+i<m;i++) que[++qn]=i,que[++qn]=m-i;
            return true;
        }
    }
    for (int j=n+1;j<=m;j++)
        if (m%j==0 && solve(n,j))
            return true;
    return false;
}
int main()
{
    int kase;
    scanf("%d",&kase);
    while (kase--)
    {
        int k;
        scanf("%d%d",&n,&k);
        long long sum=(long long )n*(1+n)/2;
        if (sum%k!=0)
            printf("no\n");
        else
        {
            qn=0;sum/=k;
            printf("yes\n");
            solve(n,sum);
            for (int i=1;i<=n;)
            {
                int cnt=0;
                long long s=0;
                while (s<sum)
                    s+=que[i+cnt],cnt++;
                for (int j=1;j<cnt;j++) printf("%d ",que[i+j-1]);
                printf("%d\n",que[i+cnt-1]);
                i+=cnt;
            }
        }
    }
}