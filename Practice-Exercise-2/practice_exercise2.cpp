
#include <iostream>

using namespace std;

struct TwinPair {
	int val1, val2;
	TwinPair() : val1(0), val2(0) {}
};

bool is_prime(int num) {
    bool flag=true;
    for(int i = 2; i <= num / 2; i++) {
       if(num % i == 0) {
          flag = false;
          break;
       }
    }
    return flag;
}

TwinPair find_twin_primes (unsigned int chosen_index) {
	unsigned int count = 0;
	TwinPair tp = TwinPair();
	unsigned int i = 3;
	while (count != chosen_index) {
		if (is_prime(i) && is_prime(i + 2)) {
			tp.val1 = i;
			tp.val2 = i + 2;
			count++;
		}
		i += 2;
	}
	return tp;
}

int main() {
	for (int i = 0; i < 10; i++) {
		TwinPair A = find_twin_primes(i);
		cout << A.val1 << ", " << A.val2 << endl;
	}
}
