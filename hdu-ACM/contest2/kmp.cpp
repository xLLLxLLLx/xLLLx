#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
char lx[N];
int nx[N];

void kmp(char *t, int *a, int m) {
  a[1] = 0;
  int p = 0;
  for(int i = 2; i <= m; ++i) {
    if(t[i] == t[p + 1]) { 
    	a[i] = ++p;
    	continue; 
   	}
    while(p && t[i] != t[p+1]){
      p = a[p];
      if(t[i] == t[p+1]) {
      	break;
      }
    }
    if (t[i] == t[p + 1]) {
    	a[i] = ++p;
    } else {
    	a[i] = 0;
    }
  }
  for(int i = 1; i <= m; ++i) {
  	printf("%d %d\n", i, nx[i]);
  }
}

int main() {
	scanf("%s", lx + 1);
	kmp(lx, nx, strlen(lx + 1));
	return 0;
}