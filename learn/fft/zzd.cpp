#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>
using namespace std;
const int N=1<<20;
const double PI=acos(-1.0);
struct C{
    double r,i;
    C(){}
    C(double a,double b){r=a,i=b;}
    C operator + (C x){return C(r+x.r,i+x.i);}
    C operator - (C x){return C(r-x.r,i-x.i);}
    C operator * (C x){return C(r*x.r-i*x.i,r*x.i+i*x.r);}
}a[N],b[N],w[N];
int A,B,n,L,R[N];
void FFT(C a[],int n){
    for (int i=0;i<n;i++)
        if (R[i]>i)
            swap(a[R[i]],a[i]);
    for (int t=n>>1,d=1;d<n;d<<=1,t>>=1)
        for (int i=0;i<n;i+=(d<<1))
            for (int j=0;j<d;j++){
                C tmp=w[t*j]*a[i+j+d];
                a[i+j+d]=a[i+j]-tmp;
                a[i+j]=a[i+j]+tmp;
            }
}
int main(){
    scanf("%d",&A);A++;
    scanf("%d",&B);B++;
    for (int i=0;i<A;i++)
        scanf("%lf",&a[i].r);
    for (int i=0;i<B;i++)
        scanf("%lf",&b[i].r);
    for (n=1,L=0;n<=A+B;n<<=1,L++);
    for (int i=0;i<n;i++){
        R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));/*reverse bit*/
        w[i]=C(cos(2.0*i*PI/n),sin(2.0*i*PI/n));
    }
    FFT(a,n),FFT(b,n);
    for (int i=0;i<n;i++)
        a[i]=a[i]*b[i],w[i].i=-w[i].i;
    FFT(a,n);
    A--,B--;
    for (int i=0;i<=A+B;i++)
        printf("%d ",int(a[i].r/n+0.5));
    return 0;
}