#include <bits/stdc++.h>
using namespace std;

int main() {
  for(int i = 1; i <= 10; ++i)
    for(int j = 1; j <= 10; ++j)
      for(int k = 1; k <= 10; ++k)
            if ((10*i+k)*j == (10*k+j)*i && i != k)
                printf("%d %d\n", 10*i+k, 10*k+j);
}