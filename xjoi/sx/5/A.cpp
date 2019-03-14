#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=x;i<=y;++i)
#define rf(i,x,y) for(int i=x;i>=y;--i)
#define LL long long
using namespace std;
const int N=5010,M=5;
int nm[M];
char A[N],B[N];

int zh(char ch){
    if(ch=='Z') return 1;
    if(ch=='P') return 2;
    if(ch=='S') return 3;
    if(ch=='B') return 4;
    return 0;
}

int main(){
    int k;scanf("%d",&k);
    scanf("%s%s",A+1,B+1);
    int lena=strlen(A+1),lenb=strlen(B+1);
    int kk=zh(A[1]),ff=1;
    fr(i,2,lena){ if(zh(A[i])!=kk) ff=0;}
    if(ff){
        fr(i,1,lenb){
            if(zh(B[i])!=kk) ff=0;
        }
        if(ff) return printf("%d\n",lena-lenb+1),0;
    }
    int ans=0;
    fr(p,0,lena-lenb){
        int l=0,r=0,flg=1;
        fr(i,1,lenb){
            int L=max(1,p+i-k),R=min(lena,p+i+k);
            if(L>R) {flg=0;break;}
            while(l<L) nm[zh(A[l])]--,l++;
            while(r<R) r++,nm[zh(A[r])]++;
            if(nm[zh(B[i])]<=0) {flg=0;break;}
        }
        memset(nm,0,sizeof nm);
        ans+=flg;
    }
    printf("%d\n",ans);
    return 0;
}
