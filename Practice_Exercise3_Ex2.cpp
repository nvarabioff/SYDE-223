#include <iostream>
#include <string>

using namespace std;

void swap(string x, string y) {
	string temp = x;
	x = y;
	y = temp;
}

void permutations(string A, int first, int last) {
	if (first == last) {
		cout << A << endl;
	} else {
		for (int i = first; i <= last; i++) {
			swap((A[first]), (A[i]));
			permutations(A, first+1, last);
			swap((A[first]), (A[i]));
		}
	}
}

int main() {
	/* DRIVER
	string te = "ABC";
	int n = te.length();
	permutations(te, 0, n-1);
	return 0;
	*/
	//Test 1: Length of A is zero
	cout << "Test 1: \n";
	permutations("", 0, 0);
	//Test 2: Length of A is 1
	cout << "Test 2: \n";
	permutations("a", 0, 0);
	//Test 3: Length of A is 2, different
	cout << "Test 3: \n";
	permutations("ab", 0, 1);
	//Test 4: Length of A is 2, same
	cout << "Test 4: \n";
	permutations("aa", 0, 1);
	//Test 5: Length of A is 3, different
	cout << "Test 5: \n";
	permutations("abc", 0, 2);
	//Test 6: Length of A is 3, same
	cout << "Test 6: \n";
	permutations("aaa", 0, 2);
	//Test 7: Length of A is 4, different
	cout << "Test 7: \n";
	permutations("abcd", 0, 3);
	//Test 8: Length of A is 5, different
	cout << "Test 8: \n";
	permutations("abcde", 0, 4);
}
