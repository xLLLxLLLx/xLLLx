//by xay5421 2449670833@qq.com
#include<set>
#include<cstdio>
//#define int long long
//#define debug(...) fprintf(stderr,__VA_ARGS__)
#define debug(...) ((void)0)
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
typedef long long ll;typedef unsigned long long ull;
template<typename T>inline void rd(T&x){int f=0,c;while(c=getchar(),c<48||57<c)f^=!(c^45);x=(c&15);while(c=getchar(),47<c&&c<58)x=x*10+(c&15);if(f)x=-x;}
template<typename T>inline void pt(T x){if(x<0)x=-x,putchar('-');if(x>9)pt(x/10);putchar(x%10+48);}
template<typename T>inline void pt(T x,int c){pt(x),putchar(c);}
template<typename T>inline T max(const T&x,const T&y){return x<y?y:x;}
template<typename T>inline T min(const T&x,const T&y){return x<y?x:y;}
const int N=200005;
int T,n,m,ans,w[N],lst=-1;std::multiset<int>S;
signed main(){
    rd(T);
    while(T--){
        rd(n),rd(m);
        rep(i,1,n)rd(w[i]);
        long long sum=0;int ans=0;S.clear();
        lst=-1;
        rep(i,1,n){
            sum+=w[i];
            if(lst!=-1)S.insert(lst),--ans,sum+=lst;
            while(sum>m){
                lst=*S.rbegin();
                sum-=*S.rbegin();
                S.erase(--S.end());
                ++ans;
            }
            S.insert(w[i]);
            pt(ans,i==n?'\n':' ');
        }
    }
    return 0;
}