//by xay5421 2449670833@qq.com
#include<set>
#include<cstdio>
#define int long long
//#define debug(...) fprintf(stderr,__VA_ARGS__)
#define debug(...) ((void)0)
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
typedef long long ll;typedef unsigned long long ull;
template<typename T>inline void rd(T&x){int f=0,c;while(c=getchar(),c<48||57<c)f^=!(c^45);x=(c&15);while(c=getchar(),47<c&&c<58)x=x*10+(c&15);if(f)x=-x;}
template<typename T>inline void pt(T x){if(x<0)x=-x,putchar('-');if(x>9)pt(x/10);putchar(x%10+48);}
template<typename T>inline void pt(T x,int c){pt(x),putchar(c);}
template<typename T>inline T max(const T&x,const T&y){return x<y?y:x;}
template<typename T>inline T min(const T&x,const T&y){return x<y?x:y;}
const int N=10000005;
int T,P,Q,p[664585];bool vis[N];
int fpow(int a,int b){int res=1;for(;b;b>>=1,a=(__int128)a*a%P)if(b&1)res=(__int128)res*a%P;return res;}
void pre(){
    vis[0]=vis[1]=1;
    for(int i=2;i<N;++i){
        if(!vis[i])p[++*p]=i;
        for(int j=1;j<=*p&&i*p[j]<N;++j){
            vis[i*p[j]]=1;
            if(i%p[j]==0)break;
        }
    }
}
bool chk(int x){
    if(x<N)return vis[x]==0;
    for(int i=1;i<=*p&&1ll*p[i]*p[i]<=x;++i){
        if(x%p[i]==0)return 0;
    }
    return 1;
}
int find(int P){
    while(!chk(P))--P;
    return P;
}
signed main(){
    pre();
    rd(T);
    rep(i,1,T){
        rd(P); 
        int Q=find(P-1);
        printf("%lld\n", Q);
        ll res=P-1;
        for(int i=P-1;i>Q;--i){
            res=(__int128)res*fpow(i,P-2)%P;
        }
        pt(res,'\n');
    }
    return 0;
}