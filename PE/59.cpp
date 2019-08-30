#include <iostream>  
#include <vector>
using namespace std;

int main()
{
  vector<int>p;
  p.push_back(1);
  int n = 1;
  while (1)
  {
    int i = 0;
    int k = 1;
    p.push_back(0);

    while (k <= n)
    {
      int mark;
      if (i % 4 == 0 || i % 4 == 1)
        mark = 1;
      else
        mark = -1;
      p[n] += mark*p[n - k];
      p[n] %= 1000000;
      i++;

      int j = i / 2 + 1;
      if (i % 2 != 0)
        k = (3 * j*j + j) / 2;
      else
        k = (3 * j*j - j) / 2;
    }
    if (p[n] == 0)
      break;
    n++;
  }
  cout << n << endl;
  // system("pause");
  return 0;
}
