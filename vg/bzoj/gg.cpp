#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=1<<18;
double PI=acos(-1.0);
int n,m,c,x[N],y[N],t=0;
int s,L,R[N];
LL ans=0,xymax=0;
struct C{
    double r,i;
    C(){}
    C(double a,double b){r=a,i=b;}
    C operator + (C x){return C(r+x.r,i+x.i);}
    C operator - (C x){return C(r-x.r,i-x.i);}
    C operator * (C x){return C(r*x.r-i*x.i,r*x.i+i*x.r);}
}w[N],A[N],B[N];
LL calc(LL c){
    return c*c*n+c*t*2;
}
LL getc_val(int t,int n){
    LL c1=-t/n,c2=c1+1,c3=c1-1;
    return min(min(calc(c1),calc(c2)),calc(c3));
}
void FFT(C a[],int n){
    for (int i=0;i<n;i++)
        if (i<R[i])
            swap(a[i],a[R[i]]);
    for (int t=n>>1,d=1;d<n;d<<=1,t>>=1)
        for (int i=0;i<n;i+=(d<<1))
            for (int j=0;j<d;j++){
                C tmp=w[t*j]*a[i+j+d];
                a[i+j+d]=a[i+j]-tmp;
                a[i+j]=a[i+j]+tmp;
            }
}
int main(){
    scanf("%d%d",&n,&m);
    for (int i=0;i<n;i++)
        scanf("%d",&x[i]);
    for (int i=0;i<n;i++)
        scanf("%d",&y[i]),t+=x[i]-y[i],ans+=x[i]*x[i]+y[i]*y[i];
    ans+=getc_val(t,n);
    for (s=1,L=0;s<n*3;s<<=1,L++);
    for (int i=0;i<s;i++){
        R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
        w[i]=C(cos(2*i*PI/s),sin(2*i*PI/s));
        A[i]=B[i]=C(0,0);
    }
    for (int i=0;i<n;i++)
        A[i]=C(x[n-i-1],0),B[i]=B[i+n]=C(y[i],0);
    for(int i = 0; i < n; ++i) {
        cout<<A[i].r<<" "<<B[i].r<<endl;
    }
    FFT(A,s),FFT(B,s);
    for (int i=0;i<s;i++)
        A[i]=A[i]*B[i],w[i].i*=-1.0;
    FFT(A,s);
    for (int i=n-1;i<2*n;i++)
        xymax=max(xymax,(LL)(A[i].r/s+0.5));
    ans-=xymax*2;
    printf("%lld",ans);
    return 0;
}