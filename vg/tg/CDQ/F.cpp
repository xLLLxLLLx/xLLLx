#include<bits/stdc++.h>
#define fr(i,x,y) for(int i=(x);i<=(y);++i)
#define rf(i,x,y) for(int i=(x);i>=(y);--i)
#define LL long long
#define db double
using namespace std;
const int N=1e5+10;
const db eps=1e-10;
struct data{
    int id;
    db x,y,A,B,R,k;
}q[N];
int Q[N];
db dp[N];

bool comp(data xx,data yy){
    return xx.k<yy.k;
}

bool cmp(data xx,data yy){
    return xx.x<yy.x||(xx.x==yy.x&&xx.y<yy.y);
}

bool Cmp(data xx,data yy){
    return xx.id<yy.id;
}

db Cross(db xx,db xy,db yx,db yy){
    return xx*yy-xy*yx;
}

db js(int tp,int i){
    return q[Q[tp]].x*q[i].A+q[Q[tp]].y*q[i].B;
}

void cdq(int l,int r){
    if(l==r){
       // cout<<q[l].id<<"WAI"<<endl;
        dp[q[l].id]=max(dp[q[l].id],dp[q[l].id-1]);
        q[l].x=dp[q[l].id]/(q[l].R*q[l].A+q[l].B)*q[l].R;
        q[l].y=dp[q[l].id]/(q[l].R*q[l].A+q[l].B);
        return ;
    }
    int mid=(l+r)>>1;
    cdq(l,mid);
    sort(q+l,q+mid+1,cmp);
    sort(q+mid+1,q+r+1,comp);
    int tp=0;
    /*fr(i,mid+1,r){
        db maxn=0;int kk=-1;
        fr(j,l,mid) {
            if(maxn<q[j].x*q[i].A+q[j].y*q[i].B) kk=j;
            maxn=max(maxn,q[j].x*q[i].A+q[j].y*q[i].B);
        }
        dp[q[i].id]=max(dp[q[i].id],maxn);
        printf("gg%d %lf %d\n",q[i].id,dp[q[i].id],kk);
    }*/
    fr(i,l,mid){
        while(tp>=2&&Cross(q[i].x-q[Q[tp]].x,q[i].y-q[Q[tp]].y,q[i].x-q[Q[tp-1]].x,q[i].y-q[Q[tp-1]].y)<=0) tp--;
        Q[++tp]=i;
    }
    fr(i,mid+1,r){
        db pos=js(tp,i);
        while(js(tp-1,i)>pos) tp--,pos=js(tp,i);
        dp[q[i].id]=max(dp[q[i].id],pos);
    }
    sort(q+mid+1,q+r+1,Cmp);
    cdq(mid+1,r);
}

int main(){
    int n;
    scanf("%d%lf",&n,&dp[0]);
    fr(i,1,n){
        q[i].id=i;
        scanf("%lf%lf%lf",&q[i].A,&q[i].B,&q[i].R);
        q[i].k=-q[i].A/q[i].B;
    }
    cdq(1,n);
  //  fr(i,0,n) printf("%.3f\n",dp[i]);
    printf("%.3f\n",dp[n]);
    return 0;
}

/*
10 100
5.007 5.139 1.44
5.142 5.963 1.39
5.248 5.038 1.06
5.705 5.606 1.07
5.151 5.067 1.86
5.924 5.979 1.88
5.069 5.912 1.28
5.075 5.092 1.77
5.485 5.409 1.28
5.161 5.233 1.63
148.311
*/
