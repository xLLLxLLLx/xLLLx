#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define pa pair<int,int>
#define CLR(a,x) memset(a,x,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn=4e5+10;

inline ll rd(){
    ll x=0;char c=getchar();int neg=1;
    while(c<'0'||c>'9'){if(c=='-') neg=-1;c=getchar();}
    while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
    return x*neg;
}

int N,M,Q;
char s[maxn];
int sa[maxn],rnk[maxn],hei[maxn],rank1[maxn],tmp[maxn],cnt[maxn];
int st[maxn][22];

inline void getsa(){
    int i,j=0,k;
    for(i=1;i<=N;i++) cnt[s[i]]=1;
    for(i=1;i<=M;i++) cnt[i]+=cnt[i-1];
    for(i=N;i;i--) rnk[i]=cnt[s[i]];
    
    for(k=1;j!=N;k<<=1){
        memset(cnt,0,sizeof(cnt));
        for(i=1;i<=N;i++) cnt[rnk[i+k>N?0:i+k]]++;
        for(i=1;i<=M;i++) cnt[i]+=cnt[i-1];
        for(i=N;i;i--) tmp[cnt[rnk[i+k>N?0:i+k]]--]=i;
        memset(cnt,0,sizeof(cnt));
        for(i=1;i<=N;i++) cnt[rnk[i]]++;
        for(i=1;i<=M;i++) cnt[i]+=cnt[i-1];
        for(i=N;i;i--) sa[cnt[rnk[tmp[i]]]--]=tmp[i];
        memcpy(rank1,rnk,sizeof(rank1));
        rnk[sa[1]]=j=1;
        for(i=2;i<=N;i++){
            if(rank1[sa[i]]!=rank1[sa[i-1]]||rank1[sa[i]+k>N?0:sa[i]+k]!=rank1[sa[i-1]+k>N?0:sa[i-1]+k]) j++;
            rnk[sa[i]]=j;
        }M=j;
    }
    for(i=1;i<=N;i++) sa[rnk[i]]=i;
}

inline void geth(){
    for(int i=1,j=0;i<=N;i++){
        if(rnk[i]==1) continue;
        if(j) j--;
        int x=sa[rnk[i]-1];
        while(x+j<=N&&i+j<=N&&s[x+j]==s[i+j]) j++;
        hei[rnk[i]]=j;
    }
    //fr(i,2,N) printf("%d ",hei[i]);
}

inline void getst(){
    for(int i=N;i;i--){
        st[i][0]=hei[i];
        for(int j=1;st[i+(1<<(j-1))][j-1];j++){
            st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
        }
    }
}

inline int rmq(int l,int r){
    if(l>r) return N-sa[r]+1;
    int x=log2(r-l+1);
    return min(st[l][x],st[r-(1<<x)+1][x]);
}

ll sum[maxn<<2],siz[maxn<<2];
bool laz[maxn<<2];

inline void update(int p){sum[p]=sum[p<<1]+sum[p<<1|1],siz[p]=siz[p<<1]+siz[p<<1|1];}

inline void pushdown(int p){
    if(!laz[p]) return;
    int a=p<<1,b=p<<1|1;
    sum[a]=siz[a]=0,laz[a]=1;
    sum[b]=siz[b]=0,laz[b]=1;
    laz[p]=0;
}

int erase(int p,int l,int r,int x,int y){
    if(x<=l&&r<=y){
        int re=siz[p];
        siz[p]=sum[p]=0;laz[p]=1;
        pushdown(p);
        return re;
    }else{
        pushdown(p);
        int m=l+r>>1,re=0;
        if(x<=m) re=erase(p<<1,l,m,x,y);
        if(y>=m+1) re+=erase(p<<1|1,m+1,r,x,y);
        update(p);
        return re;
    }
}

void add(int p,int l,int r,int x,int y){
    if(l==r){
        siz[p]+=y,sum[p]+=1ll*y*l;
    }else{
        pushdown(p);
        int m=l+r>>1;
        if(x<=m) add(p<<1,l,m,x,y);
        else add(p<<1|1,m+1,r,x,y);
        update(p);
    }
}

inline bool cmp(int a,int b){return rnk[a]<rnk[b];}

int A[maxn],B[maxn];

ll solve(int k,int l){
    sort(A+1,A+k+1,cmp);sort(B+1,B+l+1,cmp);
    ll re=0;
    for(int i=k,j=l;i;i--){
        if(i!=k){
            int x=rmq(rnk[A[i]]+1,rnk[A[i+1]]),t=erase(1,0,N,x+1,N);
            add(1,0,N,x,t);
        }
        for(;rnk[B[j]]>=rnk[A[i]]&&j;j--)
            add(1,0,N,rmq(rnk[A[i]]+1,rnk[B[j]]),1);
        re+=sum[1];
    }
    erase(1,0,N,0,N);
    for(int i=k,j=l;j;j--){
        if(j!=l){
            int x=rmq(rnk[B[j]]+1,rnk[B[j+1]]),t=erase(1,0,N,x+1,N);
            add(1,0,N,x,t);
        }
        for(;rnk[A[i]]>rnk[B[j]]&&i;i--)
            add(1,0,N,rmq(rnk[B[j]]+1,rnk[A[i]]),1);
        re+=sum[1];
    }
    erase(1,0,N,0,N);
    return re;
}

int main(){
    int i,j,k;
    N=rd(),Q=rd();
    scanf("%s",s+1);
    M=128;
    getsa();geth();getst();
    for(i=1;i<=Q;i++){
        int a=rd(),b=rd();
        for(j=1;j<=a;j++)
            A[j]=rd();
        for(j=1;j<=b;j++)
            B[j]=rd();
        printf("%lld\n",solve(a,b));
    }
    return 0;
}