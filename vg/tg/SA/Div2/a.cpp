#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define N 200005
using namespace std;
inline int read()
{
    char c=getchar(); int num=0,f=1;
    while (c<'0'||c>'9') { if (c=='-') f=-1; c=getchar(); }
    while (c<='9'&&c>='0') { num=num*10+c-'0'; c=getchar(); }
    return num*f;
}
int n,m=N-1,Q,k,ret,SA[N],rnk[N],height[N],tp[N],tax[N];
int s[N],rmq[N][25],tot[N],ans[N],fr[N],mn[N<<2];
char str[N];
void Rsort()
{
    for (int i=0;i<=m;i++) tax[i]=0;
    for (int i=1;i<=n;i++) tax[rnk[tp[i]]]++;
    for (int i=1;i<=m;i++) tax[i]+=tax[i-1];
    for (int i=n;i>=1;i--) SA[tax[rnk[tp[i]]]--]=tp[i];
}
bool cmp(int *f,int x,int y,int w)
{
    return f[x]==f[y]&&f[x+w]==f[y+w];
}
void suffix_array()
{
    for (int i=1;i<=n;i++) rnk[i]=s[i],tp[i]=i;
    Rsort();
    for (int w=1,p=1;p<n;w+=w,m=p)
    {
        p=0;
        for (int i=n-w+1;i<=n;i++) tp[++p]=i;
        for (int i=1;i<=n;i++) if (SA[i]>w) tp[++p]=SA[i]-w;
        Rsort(); swap(rnk,tp); rnk[SA[1]]=p=1;
        for (int i=2;i<=n;i++)
         rnk[SA[i]]=cmp(tp,SA[i],SA[i-1],w)?p:++p;
    }
    for (int i=1,k=0;i<=n;i++)
    {
        if (k) k--;
        int j=SA[rnk[i]-1];
        while (s[i+k]==s[j+k]) k++;
        height[rnk[i]]=k;
    }
}
int find(int l,int r)
{
    int j=log(r-l+1)/log(2);
    return min(rmq[l][j],rmq[r-(1<<j)+1][j]);
}
void RMQ()
{
    for (int i=1;i<=n;i++) rmq[i][0]=height[i];
    for (int j=1;j<20;j++)
     for (int i=1;i<=n;i++)
     {
        if (i+(1<<(j-1))>n) rmq[i][j]=rmq[i][j-1];
         else rmq[i][j]=min(rmq[i][j-1],rmq[i+(1<<(j-1))][j-1]);
     }
}
void change(int now,int l,int r,int begin,int end,int val)
{
    if(now==1) printf("%d %d %d %d %d %d\n",now,l,r,begin,end,val);
    if (begin<=l&&r<=end)
    {
        mn[now]=max(mn[now],val); return;
    }
    int mid=l+r>>1;
    if (begin<=mid) change(now<<1,l,mid,begin,end,val);
    if (end>mid) change(now<<1|1,mid+1,r,begin,end,val);
}
void query(int now,int l,int r,int pos)
{
    ret=max(ret,mn[now]);
    if (l==r) return;
    int mid=l+r>>1; 
    if (pos<=mid) query(now<<1,l,mid,pos);
     else query(now<<1|1,mid+1,r,pos);
}
int main()
{
    Q=read(); k=read();
    int last=255;
    for (int i=1;i<=Q;i++)
    {
        scanf("%s",str+1);
        int l=strlen(str+1);
        if (k==1) ans[i]=l*(l+1)/2;
        if (last=='a'-1) last='z';
        if (n) s[++n]=++last;
        for (int j=1;j<=l;j++) s[++n]=str[j],fr[n]=i;
    }
    if (k==1)
    {
        for (int i=1;i<=Q;i++) printf("%d ",ans[i]);
        return 0;
    }
    m=max(m,last);
    suffix_array(); 
    RMQ();
    int l=1;
    for (int r=1;r<=n;r++)
    {
        if (fr[SA[r]]) tot[fr[SA[r]]]++;
        if (fr[SA[r]]&&tot[fr[SA[r]]]==1) tot[0]++;
        if (tot[0]<k) continue;
        while (l<r&&tot[0]>k)
        {
            if(fr[SA[l]]) tot[fr[SA[l]]]--;
            if (fr[SA[l]]&&!tot[fr[SA[l]]]) tot[0]--;
            l++;
        }
        while (l<r&&tot[0]==k)
        {
            if (tot[0]==k) change(1,1,n,l,r,find(l+1,r));
            if(fr[SA[l]]) tot[fr[SA[l]]]--;
            if (fr[SA[l]]&&!tot[fr[SA[l]]]) { tot[fr[SA[l]]]++; break; }
            l++;
        }
        if (tot[0]==k) change(1,1,n,l,r,find(l+1,r));
    }
    for (int i=1;i<=n;i++)
    {
        ret=0;
        query(1,1,n,i);
        ans[fr[SA[i]]]+=ret;
    }
   // for (int i=1;i<=Q;i++) printf("%d ",ans[i]);
    return 0;
}