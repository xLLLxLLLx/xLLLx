#include <bits/stdc++.h>
using namespace std;

int main() {
	for(int o = 1; ; ++o) {
		system("./gen > out");
		system("./gg < out > uu");
		system("./F < out > oo");
		if(system("diff oo uu")) {
			printf("WAI!!\n");
			exit(0);
		} else {
			printf("test %d : AC!\n", o);
		}
	}
	return 0;
}