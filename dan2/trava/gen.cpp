#include <bits/stdc++.h>
#include <unistd.h>

#define PB push_back

using namespace std;



int main() {
	srand(time(NULL) * getpid());
	int n = 200000, q = 200000, val = 3;
	cout << n << " " << q << endl;
	for(int i = 1;i <= n;i++) cout << rand() % val + 1 << " ";
	cout << endl;
	int k = 1;
	for(;q--;) {
		cout << (rand() % 2 == 0 ? "?" : "+") << " " << k << endl;
		k++;
	}
	return 0;
}
