#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=110,M=110;
LL a[N],q[N][M],tmp;
 
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
 
void insert(int rk,LL x){
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
 
bool check(int rk,int bit,LL y,LL x){
    int k=((y>>bit)&1),d=((x>>bit)&1);
    if(!bit) {
        if(d) {
            if(k) {
                if(!q[rk][bit]) return false;
                else {
                    y^=q[rk][bit];
                    tmp=y;
                    return true;
                }
            } else {
                tmp=y;
                return true;
            }
        }
        else return false;
    }
    if(d) {
        if(k) {
            if(check(rk,bit-1,y,x)) return true;
            else if(!q[rk][bit]) return false;
            else {
                y^=q[rk][bit];
                rf(i,bit-1,0)
                    if(!((y>>i)&1)) y^=q[rk][i];
                tmp=y;
                return true;
            }
        }
        else {
            if(!q[rk][bit]){
                rf(i,bit-1,0)
                    if(!((y>>i)&1)) y^=q[rk][i];
                tmp=y;
                return true;
            } else {
                if(check(rk,bit-1,y^q[rk][bit],x)) return true;
                else {
                    rf(i,bit-1,0)
                        if(!((y>>i)&1)) y^=q[rk][i];
                    tmp=y;
                    return true;
                }
            }
        }
    }
    else {
        if(k) {
            if(q[rk][bit]) y^=q[rk][bit];
            else return false;
        }
        if(check(rk,bit-1,y,x)) return true;
        else return false;
    }
}
 
int main(){
    int n;read(n);
    fr(i,1,n) read(a[i]);
    fr(i,1,n) insert(i+1,a[i]);
    int ans=1;
    fr(i,1,n){
        LL pos=a[i];
        rf(j,60,0) if(!((pos>>j)&1)) pos^=q[i][j];
        if(i==11) printf("%lld\n",pos);
        rf(j,i-1,1){
            if(check(j,60,a[j],pos)) pos=tmp;
            else break;
            if(i==11) printf("%lld\n",pos);
            ans=max(ans,i-j+1);
        }
    }
    printf("%d\n",ans);
}
