#include<bits/stdc++.h>
using namespace std;
int main(){
    int i;
  for (i=1;;i++){
        printf("The result of No. %d Case is:  ",i);
        system("./tt > out");
        system("./std < out > oo");
        system("./my < out > uu");
        if (system("diff oo uu")){
            printf("Wrong Answer\n");
            return 0;
        }
        else printf("Accepted\n");
    }
    return 0;
}
