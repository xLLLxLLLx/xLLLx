/*

假设N=1024, F=10

则这N个数可以看成N个F位的数字从0到1023

0101010101010101

0011001100110011

0000111100001111

.....

每一列就是一个数字

每一行可以作为你输出的字符串



每一次交互会确定一位的值,所以10次交互就可以确定所有位的值

一共有 N-B个值

最后看少了哪些值,就代表哪些位缺失了



然后由于B<=15

所以可以只交互四次,相当于所有数字都对16取模



原先是

0 1 2 3 ...1023

现在是



0 1 2...15 0 1 2 ...15...



我们称每16个数字为一个数字块

因为最多消失15个位置,所以一旦出现当前数字小于等于上一个数字,

就表示切换到了下一个数字块

而每一个数字块对应的位置都是唯一确定的,因此可以找出所有缺失的位置



*/



```C++
#include <bits/stdc++.h>

using namespace std;





void send(bool in[], bool out[], int N, int B)

{

​	for(int i = 0; i < N; i++)

​		std::cout << in[i];

​	std::cout << std::endl;

​	char c;

​	for(int i = 0; i < N-B; i++)

​	{

​		std::cin >> c;

​		out[i] = (c=='1');

​	}

}



int main()

{

​	int T;

​	std::cin >> T;

​	

​	while(T--)

​	{

​		int N, B, F;

​		std::cin >> N >> B >> F;

​		

​		int set[N-B];

​		for(int i = 0; i < N-B; i++)

​			set[i] = 0;

​		

​		bool in[N];

​		bool out[N-B];

​		

​		for(int k = 0; k < 4; k++)

​		{

​			for(int i = 0; i < N; i++)

​				in[i] = i&(1 << k);

​			send(in, out, N, B);

​			for(int i = 0; i < N-B; i++)

​				set[i] += out[i]*(1 << k);

​		}

​		

​		bool status[N];

​		for(int i = 0; i < N; i++)

​			status[i] = false;

​		

​		int pre = 0;

​		int last = -1;

​		for(int i = 0; i < N-B; i++)

​		{

​			if(set[i] <= last)

​				pre += 16;

​			status[pre + set[i]] = true;

​			last = set[i];

​		}

​		

​		for(int i = 0; i < N; i++)

​			if(!status[i])

​				std::cout << i << " ";

​		

​		std::cout << std::endl;

​		std::cin >> pre;

​	}

​	

​	return 0;

}
```

