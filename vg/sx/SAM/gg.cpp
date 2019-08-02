#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<queue>
using namespace std;
#define MAX 2222
inline int read()
{
    int x=0,t=1;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}
int ans[MAX][MAX];
int last,tot;
char ch[MAX];
struct Node
{
    int son[26];
    int ff,len;
}t[MAX<<1];
void init()
{
    last=tot=1;
    memset(t,0,sizeof(t));
}
void extend(int c)
{
    int p=last,np=++tot;last=np;
    t[np].len=t[p].len+1;
    while(p&&!t[p].son[c])t[p].son[c]=np,p=t[p].ff;
    if(!p)t[np].ff=1;
    else
    {
        int q=t[p].son[c];
        if(t[q].len==t[p].len+1)t[np].ff=q;
        else
        {
            int nq=++tot;
            t[nq]=t[q];
            t[nq].len=t[p].len+1;
            t[np].ff=t[q].ff=nq;
            while(p&&t[p].son[c]==q)t[p].son[c]=nq,p=t[p].ff;
        }
    }
}
int main()
{
    int T=read();
    while(T--)
    {
        scanf("%s",ch+1);
        for(int i=1,l=strlen(ch+1);i<=l;++i)
        {
            init();
            for(int j=i;j<=l;++j)
            {
                extend(ch[j]-97);
                ans[i][j]=ans[i][j-1]+t[last].len-t[t[last].ff].len;
                printf("d[%d][%d]=%d\n", i, j, ans[i][j]);
            }
        }
        int Q=read();
        while(Q--)
        {
            int l=read(),r=read();
            printf("%d\n",ans[l][r]);
        }
    }
    return 0;
}