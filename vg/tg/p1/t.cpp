#include<iostream>
#include<cstdio>
#include<cstring>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110,M=60;
LL a[N],q[N][M+1],dp[N][N],tmp;

void read(int &x){
    char ch=getchar();x=0;
    for(;ch<'0'||ch>'9';ch=getchar()) ;
    for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}
 
void read(LL &x){
    char ch=getchar();x=0;
    for(;ch<'0'||ch>'9';ch=getchar()) ;
    for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}

void insert(int rk,LL x) {
    fr(i,0,60) q[rk][i]=q[rk-1][i];
    rf(i,60,0){
        if((x>>i)&1){
            if(!q[rk][i]){
                q[rk][i]=x;
                break;
            }
            else x^=q[rk][i];
        }
    }
}

bool check(int rk,int bit,LL y,LL x) {
    int d=(y>>bit)&1,k=(x>>bit)&1;
    if(!bit) {
        if(k) return false;
        else {
            if(d){
                tmp=y;
                return true;
            } else {
                if(!q[rk][bit]) return false;
                else {
                    y^=q[rk][bit];
                    tmp=y;
                    return true;
                }
            }
        }
    }
    if(k) {
        if(d) return check(rk,bit-1,y,x);
        else {
            if(!q[rk][bit]) return false;
            else return check(rk,bit-1,y^q[rk][bit],x);
        }
    } else {
        if(d) {
            if(q[rk][bit]) {
                if(check(rk,bit-1,y^q[rk][bit],x)) return true;
                else {
                  rf(i,bit-1,0) if((y>>i)&1) y^=q[rk][i];
                  tmp=y;
                  return true;
                }
            } else {
                rf(i,bit-1,0) if((y>>i)&1) y^=q[rk][i];
                tmp=y;
                return true;
            }
        } else {
            if(check(rk,bit-1,y,x)) return true;
            else if(!q[rk][bit]) return false;
            else {
                y^=q[rk][bit];
                rf(i,bit-1,0) if((y>>i)&1) y^=q[rk][i];
                tmp=y;
                return true;
            }
        }
    }
}

void Min(LL &x,LL y) {
    if(x!=-1) {
        if(y!=-1) x=min(x,y);
    } else x=y;
}

int main() {
    int n;
    while(scanf("%d",&n)==1){
      fr(i,1,n) read(a[i]),insert(i+1,a[i]);
      memset(dp,-1,sizeof dp);
      fr(i,1,n) {
          fr(j,1,n) dp[i][j]=dp[i-1][j];
          LL pos=a[i];
          rf(j,M,0) if((pos>>j)&1) pos^=q[i][j];
          Min(dp[i][1],pos);
          fr(j,1,n) {
              if(dp[i-1][j]==-1) continue;
              if(check(i,M,a[i],dp[i-1][j])) Min(dp[i][j+1],tmp);
          }
      }
      int ans=0;
      fr(i,1,n) if(dp[n][i]!=-1) ans=i;
      printf("%d\n",ans);
    }
    return 0;
}
