#include <bits/stdc++.h>
using namespace std;

int main() {
	for(int i = 1; ;++i) {
		system("./gen > out");
		system("./B < out > oo");
		system("./tt < out > uu");
		if(system("diff oo uu")) {
			printf("WRONG!!\n");
			return 0;
		} else {
			printf("test%d: AC!\n", i);
		}
	}
	return 0;
}