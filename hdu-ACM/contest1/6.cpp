#include <bits/stdc++.h>
using namespace std;

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
}

