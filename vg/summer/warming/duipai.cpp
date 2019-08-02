#include <bits/stdc++.h>
using namespace std;

int main() {
	for(int o = 1; ; ++o) {
		system("./gen > out");
		system("./ff < out > oo");
		system("./std < out > uu");
		if(system("diff oo uu")) {
			printf("WAI!!!\n");
			return 0;
		} else {
			printf("test %d : AC!!!\n", o);
		}
	}
	return 0;
}