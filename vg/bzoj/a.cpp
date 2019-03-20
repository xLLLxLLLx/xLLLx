#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e9+100;
class node{
    public:
    node* l=NULL,*r=NULL,*fa=NULL;
    int siz=1,val,rnd,sum=1;
    node(int _val=0,int _rnd=0):val(_val),rnd(_rnd){}
    void asksiz(){
        siz=sum;
        if(l!=NULL) siz+=l->siz;
        if(r!=NULL) siz+=r->siz;
    }
    void print(){
        if(fa!=NULL) printf("fa=%d ",fa->val);
        else printf("fa! ");
        if(l!=NULL) printf("l=%d ",l->val);
        else printf("l! ");
        if(r!=NULL) printf("r=%d ",r->val);
        else printf("r! ");
        printf("val=%d siz=%d rnd=%d sum=%d\n",val,siz,rnd,sum);
        printf("\n");
    }
};
class Treap{
    public:
    node *root=new node(-MAXN,0);
    node *pos=NULL,*pre=NULL,*swapp;
    int swp(node *son){
        node *fa=son->fa;
        //printf("%d %d\n",fa->val,son->val);
        //fflush(stdout);
        if(son->val < fa->val){
        fa->l=son->r;
        if(son->r!=NULL) son->r->fa=fa;
        son->r=fa;
        }
        else{
        fa->r=son->l;
        if(son->l!=NULL) son->l->fa=fa;
        son->l=fa;
        }
        son->fa=fa->fa;fa->fa=son;
        //fa=son->fa;
        if(son->val < son->fa->val) son->fa->l=son; else son->fa->r=son;
        //printf("$%d %d\n",son->fa->val,son->val);
        //fflush(stdout);
        fa->asksiz();son->asksiz();
        return 0;
    }
    void add(int x){
        pos=root;
        while(pos!=NULL){
        if(pos->val==x){
            pos->sum++; 
            while(pos->val!=-MAXN) pos->asksiz(),pos=pos->fa;
            return; 
            }
        pre=pos;
        if(pos->val > x) pos=pos->l; else pos=pos->r;
        }
        if(pre->val>x){pre->l=new node(x,rand());pre->l->fa=pre; pos=pre->l;}
        else{pre->r=new node(x,rand()); pre->r->fa=pre;pos=pre->r;}
        while(pos->rnd<pos->fa->rnd){
        swp(pos);
        if(pos->fa->val==-MAXN) break;
        }
        while(pre->val!=-MAXN) pre->asksiz(),pre=pre->fa;
    }
    void del(int x){
        pos=root;
        while(pos->val!=x){
        if(pos->val > x) pos=pos->l;
        else pos=pos->r;
        }
        if(pos->sum>1){
        pos->sum--;
        while(pos->val!=-MAXN) pos->asksiz(),pos=pos->fa;
        return;
        }
        while((pos->l!=NULL)&&(pos->r!=NULL)){
        //pos->print();
        if(pos->l->rnd < pos->r->rnd) swp(pos->l);
        else swp(pos->r);
        //pos->print();
        }
        pre=NULL;
        if(pos->l!=NULL) pre=pos->l;
        if(pos->r!=NULL) pre=pos->r;
        if(pre!=NULL){
        pre->fa=pos->fa;
        if(pre->fa->val < pre->val) pre->fa->r=pre;
        else pre->fa->l=pre;
        }else{
        if(pos->fa->r==pos) pos->fa->r=NULL;
        else pos->fa->l=NULL;
        }
        pre=pos->fa;
        while(pre->val!=-MAXN){
        pre->asksiz();
        pre=pre->fa;
        }
        delete pos;
    }
    void rating(int x){
        pos=root; int ans=0;
        while(pos->val!=x){
        if(pos->val>x){
            pos=pos->l;
            continue;
        }
        if(pos->l!=NULL) ans+=pos->l->siz;
        ans+=pos->sum;
        pos=pos->r;
        }
        if(pos->l!=NULL) ans+=pos->l->siz;
        printf("%d\n",ans);
    }
    void ask(int x){
        pos=root->r;
        while(x){
        if((pos->l!=NULL)&&(x<= pos->l->siz)){
            pos=pos->l; continue;
        }
        if(pos->l!=NULL) x-=pos->l->siz;
        if(x<=pos->sum){
            printf("%d\n",pos->val);
            return;
        }
        x-=pos->sum; pos=pos->r;
        }
    }
    void askl(int x){
        pos=root->r;int ans=-MAXN;
        while(pos!=NULL){
        if(pos->val>=x) pos=pos->l;
        else{
            ans=max(pos->val,ans);
            pos=pos->r;
        }
        }
        printf("%d\n",ans);
    }
    void askr(int x){
        pos=root->r;int ans=MAXN;
        while(pos!=NULL){
        if(pos->val<=x) pos=pos->r;
        else{
            ans=min(ans,pos->val);
            pos=pos->l;
        }
        }
        printf("%d\n",ans);
    }
    void print(node *x){
        printf("x=%d siz=%d ",x->val,x->siz);
        if(x->l!=NULL) printf("l=%d ",x->l->val);
        if(x->r!=NULL) printf("r=%d ",x->r->val);
        printf("\n");
        if(x->l!=NULL) print(x->l);
        if(x->r!=NULL) print(x->r);
    }

}T;

int main(){
    srand(time(NULL));
    int t,xx,yy,cse=0;
    scanf("%d",&t);
    for(int o=1;o<=t;++o) {
    scanf("%d%d",&xx,&yy);
    //if(xx>=3) printf("%d %d %d\n",++cse,xx,yy);
    switch(xx){
        case 1:T.add(yy);break;
        case 2:T.del(yy);break;
        case 3:T.rating(yy);break;
        case 4:T.ask(yy);break;
        case 5:T.askl(yy);break;
        case 6:T.askr(yy);break;
    }
    //printf("\nt=%d\n",t);
    //T.print(T.root);
    }
}
