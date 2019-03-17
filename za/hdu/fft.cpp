#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define Fr(i,x,y) for(int i=x;i<y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define Rf(i,x,y) for(int i=x;i>y;--i)
#define LL long long
using namespace std;
const int N=2e5+10;
const double PI=acos(-1);
char lx[N],ll[N];
struct cp{
    double r,i;
    cp(double _r=0.0,double _i=0.0){ r=_r,i=_i; }
    cp operator + (const cp &b){ return cp(r+b.r,i+b.i); }
    cp operator - (const cp &b){ return cp(r-b.r,i-b.i); }
    cp operator * (const cp &b){ return cp(r*b.r-i*b.i,r*b.i+i*b.r); }
}z1[N],z2[N];
int sum[N];

void change(cp y[],int len){
    int i,j,k;
    for(i=1,j=len/2;i<len-1;i++){
        if(i<j) swap(y[i],y[j]);
        k=len/2;
        while(j>=k){
            j-=k;
            k/=2;
        }
        if(j<k) j+=k;
    }
}

void fft(cp y[],int len,int on){
    change(y,len);
    for(int h=2;h<=len;h<<=1){
        cp wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(int j=0;j<len;j+=h){
            cp w(1,0);
            Fr(k,j,j+h/2){
                cp u=y[k];
                cp t=w*y[k+h/2];
                y[k]=u+t;
                y[k+h/2]=u-t;
                w=w*wn;
            }
        }
    }
    if(on==-1) Fr(i,0,len) y[i].r/=len;
}

int main(){
    while(scanf("%s%s",lx,ll)==2){
        int len1=strlen(lx),len2=strlen(ll),len=1;
        while(len<len1*2||len<len2*2) len*=2;
        rf(i,len1-1,0) z1[len1-1-i]=cp(lx[i]-'0',0);
        rf(i,len2-1,0) z2[len2-1-i]=cp(ll[i]-'0',0);
        Fr(i,len1,len) z1[i]=cp(0,0);
        Fr(i,len2,len) z2[i]=cp(0,0);
        fft(z1,len,1),fft(z2,len,1);
        Fr(i,0,len) z1[i]=z1[i]*z2[i];
        fft(z1,len,-1);
        Fr(i,0,len) sum[i]=(int)(z1[i].r+0.5);
        Fr(i,0,len){
            sum[i+1]+=sum[i]/10;
            sum[i]%=10;
        }
        len=len1+len2-1;
        while(sum[len]<=0&&len>0) len--;
        rf(i,len,0) printf("%c",sum[i]+'0');
        printf("\n");
    }
    return 0;
}
