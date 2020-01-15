#include <iostream>
#include <string>

using namespace std;

void swap(string x, string y) {
	string temp = x;
	x = y;
	y = temp;
}

void permutations(string A, int first, int last) {
	if (first >= last) {
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
	//TEST CASES:
	//Test 1: Length of A is zero
	cout << "Test 1: Length of A is zero\n";
	permutations("", 0, 0);
	//Test 2: First is greater than last
	cout << "Test 2: First is greater than last\n";
	permutations("acb", 3, 0);
	//Test 3: Length of A is 1
	cout << "Test 3: Length of A is 1\n";
	permutations("a", 0, 0);
	//Test 4: Length of A is 2, all different
	cout << "Test 4: Length of A is 2, all different\n";
	permutations("ab", 0, 1);
	//Test 5: Length of A is 2, all same
	cout << "Test 5: Length of A is 2, all same\n";
	permutations("aa", 0, 1);
	//Test 6: Length of A is 3, all different
	cout << "Test 6: Length of A is 3, all different\n";
	permutations("abc", 0, 2);
	//Test 7: Length of A is 3, all same
	cout << "Test 7: Length of A is 3, all same\n";
	permutations("aaa", 0, 2);
	//Test 8: Length of A is 3, two same
	cout << "Test 8: Length of A is 3, two same\n";
	permutations("aba", 0, 2);
	//Test 9: Length of A is 4, all different
	cout << "Test 9: Length of A is 4, all different\n";
	permutations("abcd", 0, 3);
	//Test 10: Length of A is 5, some special characters
	cout << "Test 10: Length of A is 5, some special characters\n";
	permutations("a1b$4", 0, 3);
	//Test 11: Length of A is 5, all different
	cout << "Test 11: Length of A is 5, all different\n";
	permutations("abcde", 0, 4);
	//Test 12: Length of A is 5, some repeated
	cout << "Test 12: Length of A is 5, some repeated\n";
	permutations("aabcc", 0, 4);
}
