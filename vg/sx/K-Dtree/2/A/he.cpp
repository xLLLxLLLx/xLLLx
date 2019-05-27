#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <set>
#include <map>
#define mp make_pair
#define pb push_back
#define pii pair<int,int>
#define link(x) for(edge *j=h[x];j;j=j->next)
#define inc(i,l,r) for(int i=l;i<=r;i++)
#define dec(i,r,l) for(int i=r;i>=l;i--)
const int MAXN=5e4+10;
const double eps=1e-8;
#define ll long long
const ll inf=1e15+10;
const ll INF=1e5;
using namespace std;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return x*f;
}
int rt,pos,k,n;
typedef struct node{
    int p[6],c[2];ll maxx[6],minn[6];
    friend bool operator <(node aa,node bb){
        if(aa.p[pos]!=bb.p[pos])return aa.p[pos]<bb.p[pos];
        for(int i=pos+1;i<=k;i++){
            if(aa.p[i]!=bb.p[i])return aa.p[i]<bb.p[i];
        }
        for(int i=1;i<pos;i++){
            if(aa.p[i]!=bb.p[i])return aa.p[i]<bb.p[i];
        }
    }
}node;
node a[MAXN<<2];
int built(int l,int r,int now){
    if(l>r)return 0;
    int mid=(l+r)>>1;
    pos=now,nth_element(a+l,a+mid,a+r+1);
    for(int i=1;i<=k;i++)a[mid].maxx[i]=a[mid].minn[i]=a[mid].p[i];
    a[mid].c[0]=a[mid].c[1]=0;
    if(l<mid)a[mid].c[0]=built(l,mid-1,now%k+1),up(mid,a[mid].c[0]);
    if(r>mid)a[mid].c[1]=built(mid+1,r,now%k+1),up(mid,a[mid].c[1]);
    return mid;
}
typedef struct Tmp{
    int p[6];ll dis;
    friend bool operator<(Tmp aa,Tmp bb){return aa.dis<bb.dis;}
}Tmp;
ll dist(node aa,node bb){
    ll ans=0;
    for(int i=1;i<=k;i++)ans+=1LL*(aa.p[i]-bb.p[i])*(aa.p[i]-bb.p[i]);
    return ans;
}
priority_queue<Tmp>que;
node t;
stack<Tmp>s;
void querty(int x,int now){
        if(!x)return ;
        ll res=dist(a[x],t);
        if(res<(que.top()).dis){
            que.pop();
            Tmp tt;tt.dis=res;
            for(int i=1;i<=k;i++)tt.p[i]=a[x].p[i];
            que.push(tt);
        }
         ll tt=t.p[now]-a[x].p[now];
         if(tt<=0){
            querty(a[x].c[0],now%k+1);
             if(que.top().dis>tt*tt)
                 querty(a[x].c[1],now%k+1);
         }
         else{
            querty(a[x].c[1],now%k+1);
             if(que.top().dis>tt*tt)
                 querty(a[x].c[0],now%k+1);        
         }
}
int main(){
    while(scanf("%d%d",&n,&k)!=EOF){
        inc(i,1,n){
            inc(j,1,k)a[i].p[j]=read();
        }
        rt=built(1,n,1);
        int q=read();
        while(q--){
            inc(i,1,k)t.p[i]=read();
            int K=read();
            Tmp t1;t1.dis=inf;
            inc(i,1,K)que.push(t1);
            querty(rt,1);
            while(!que.empty())s.push(que.top()),que.pop();
            printf("the closest %d points are:\n",K);
            while(!s.empty()){
                Tmp tt=s.top();
                for(int i=1;i<=k;i++){
                    if(i!=k)printf("%d ",tt.p[i]);
                    else printf("%d\n",tt.p[i]);
                }
                s.pop();
            }
        }
    }
    return 0;
}