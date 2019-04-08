//1056K	204MS
#include<stdio.h>
#include<string.h>
#include<algorithm>
#define M 20007
using namespace std;
int sa[M],rank[M],height[M];
int wa[M],wb[M],wv[M],ws[M];
int num[M],s[M];
int cmp(int *r,int a,int b,int l)
{
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
void get_sa(int *r,int n,int m)//求get函数
{
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0;i<m;i++)ws[i]=0;
    for(i=0;i<n;i++)ws[x[i]=r[i]]++;
    for(i=1;i<m;i++)ws[i]+=ws[i-1];
    for(i=n-1;i>=0;i--)sa[--ws[x[i]]]=i;
    for(j=1,p=1;p<n;j*=2,m=p)
    {
        for(p=0,i=n-j;i<n;i++)y[p++]=i;
        for(i=0;i<n;i++)if(sa[i]>=j)y[p++]=sa[i]-j;
        for(i=0;i<n;i++)wv[i]=x[y[i]];
        for(i=0;i<m;i++)ws[i]=0;
        for(i=0;i<n;i++)ws[wv[i]]++;
        for(i=1;i<m;i++)ws[i]+=ws[i-1];
        for(i=n-1;i>=0;i--)sa[--ws[wv[i]]]=y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
}
void get_height(int *r,int n)//求height函数
{
    int i,j,k=0;
    for(i=1;i<=n;i++)rank[sa[i]]=i;//求rank函数
    for(i=0;i<n;height[rank[i++]]=k)
        for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
}
int solve(int n)//二分求解最长长度
{
    int maxx=n/2,minn=0,mid,flag;//maxx代表重复子段最长长度，minn代表重复子段最短长度
    while(minn<=maxx)//二分求解重复子段最长长度
    {
        mid=(maxx+minn)/2;//求中间长度
        int low=sa[1],high=sa[1];//low和high记录sa的起始和结束位置
        flag=0;
        for(int i=2;i<n;i++)
            if(height[i]<mid){low=sa[i];high=sa[i];}//如果前缀比重复子段长度还要小，low和high重新赋值
            else
            {
                low=min(low,sa[i]);
                high=max(high,sa[i]);
                if(high-low>=mid){flag=1;break;}//判断结束位置和起始位置之间的距离是否大于重复子段长度
            }
        if(flag)minn=mid+1;
        else maxx=mid-1;
    }
    return maxx>=4?maxx+1:0;
}
int main()
{
    //freopen("in.txt","r",stdin);
    int n;
    while(scanf("%d",&n),n)
    {
        for(int i=0;i<n;i++)
            scanf("%d",&s[i]);
        if(n<10){printf("0\n");continue;}//如果串的长度小于10，肯定不满足题意
        for(int i=0;i<n-1;i++)
            num[i]=(s[i+1]-s[i])+90;
        int m=180;
        get_sa(num,n,m);
        get_height(num,n-1);
        printf("%d\n",solve(n-1));
    }
    return 0;
}
