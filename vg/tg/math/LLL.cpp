#include<bits/stdc++.h> 
#define LL long long 
#define fr(i,x,y) for(int i=x;i<=y;++i) 
#define rf(i,x,y) for(int i=x;i>=y;--i) 
using namespace std; 
const int N=30; 
int dp[30][N][4]; 
int cnt=0,qx[N]; 
 
int search(int len,int v,int now,int lmt){ 
    if(len<=0) { 
        if(!v) return 1; 
        else return 0; 
    } 
    if(dp[len][v][now]!=-1&&!lmt) return dp[len][v][now]; 
    LL sum=0; 
    int up=min(9,v); 
    if(lmt) up=min(qx[len],up); 
    fr(i,0,up){ 
        if(i&&!now) break; 
        if(i) sum+=search(len-1,v-i,now-1,lmt&&i==qx[len]); 
        else sum+=search(len-1,v,now,lmt&&i==qx[len]); 
    } 
    return lmt==0?dp[len][v][now]=sum:sum; 
} 
 
int work(LL x,LL st){ 
    cnt=0; 
    if(!x) return !st; 
    if(x<0) return 0; 
    for(;x;x/=10) qx[++cnt]=x%10; 
    return search(cnt,st,3,1); 
} 
 
void read(LL &x){ 
    x=0;char ch=getchar(); 
    for(;ch<'0'||ch>'9';ch=getchar()) 233333; 
    for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48); 
} 
 
int main(){ 
    int T;scanf("%d",&T); 
    fr(o,1,T){ 
        memset(dp,-1,sizeof dp); 
        LL L,R,st;read(L),read(R),read(st); 
        if(st>=28) printf("0\n"); 
        else printf("%d\n",work(R,st)-work(L-1,st)); 
    } 
    return 0; 
}