#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;
const int N=1<<18;
const double PI=acos(-1.0);
struct C{
    double r,i;
    C(){r=i=0;}
    C(double a,double b){r=a,i=b;}
    C operator + (C a){return C(r+a.r,i+a.i);}
    C operator - (C a){return C(r-a.r,i-a.i);}
    C operator * (C a){return C(r*a.r-i*a.i,r*a.i+i*a.r);}
}a[N],b[N],a1[N],b1[N],a2[N],b2[N],a3[N],b3[N],w[N];
int A,B,n,L,res[N],R[N];
double tot[N];
vector <int> ans;
char s[N],t[N];
void FFT (C a[N],int n){
    for (int i=0;i<n;i++)
        if (i<R[i])
            swap(a[i],a[R[i]]);
    for (int d=1,t=n>>1;d<n;d<<=1,t>>=1)
        for (int i=0;i<n;i+=(d<<1))
            for (int j=0;j<d;j++){
                C tmp=w[t*j]*a[i+j+d];
                a[i+j+d]=a[i+j]-tmp;
                a[i+j]=a[i+j]+tmp;
            }
}
int main(){
    scanf("%s%s",s,t);
    A=strlen(s),B=strlen(t);
    // (s-t)(s-t)st
    //=ssst-2sstt+sttt
    for (int i=0;i<n;i++)
        a[i]=b[i]=C(0,0);
    for (int i=0;i<A;i++)
        a[i].r=s[i]-'a'+1;
    for (int i=0;i<B;i++)
        b[B - i - 1].r=t[i]=='?'?0:(t[i]-'a'+1);
    for (n=1,L=0;n<=A+B;n<<=1,L++);
    for (int i=0;i<n;i++){
        R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
        w[i]=C(cos(2*i*PI/n),sin(2*i*PI/n));
        a1[i]=a[i]*a[i]*a[i];
        b1[i]=b[i];
        a2[i]=a[i]*a[i];
        b2[i]=b[i]*b[i];
        a3[i]=a[i];
        b3[i]=b[i]*b[i]*b[i];
        if(i <= 5) {
            cout<<"a3="<<a1[i].r <<"a2=" <<a2[i].r <<"a1=" << a3[i].r<<endl;
        }
    }
    FFT(a1,n),FFT(b1,n),FFT(a2,n),FFT(b2,n),FFT(a3,n),FFT(b3,n);
    for (int i=0;i<n;i++){
        a1[i]=a1[i]*b1[i];
        a2[i]=a2[i]*b2[i];
        a3[i]=a3[i]*b3[i];
        w[i].i*=-1.0;
    }
    FFT(a1,n),FFT(a2,n),FFT(a3,n);
    for (int i=0;i<n;i++)
        tot[i]=a1[i].r-2.0*a2[i].r+a3[i].r;
    printf("%d\n", n);
    for (int i=0;i<n;i++) {
        res[i]=int(tot[i]+0.5);
        printf("%d ", res[i]);
    }
    puts("");
    ans.clear();
    for (int i=B-1;i<A;i++)
        if (!res[i])
            ans.push_back(i-B+1);
    printf("%d\n",ans.size());
    for (vector <int>::iterator i=ans.begin();i!=ans.end();i++)
        printf("%d\n",*i);
    return 0;
}