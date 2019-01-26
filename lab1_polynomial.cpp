//Nicholas Varabioff 20702729
//Ryan Gangl 20737072

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "lab1_polynomial.hpp"

using namespace std;

Polynomial::Polynomial(int A[], int size) { //class constructor with 2 input parameters
	data_size = size;
	data = new int[data_size];
	for (int i = 0; i < data_size; i++) {
		data[i] = A[i];
	}
}
Polynomial::Polynomial() {					//class constructor with random values
	data_size = rand() % 1001;
	data = new int[data_size];
	for (int i = 0; i < data_size; i++) {
		data[i] = (rand() % 2001) - 1000;
	}
	//srand(time(0))??
}
Polynomial::Polynomial(string fileName) {	//class constructor with input file ** NEEDS CHANGES **
	ifstream in_stream;
	in_stream.open(fileName.c_str());
	if (in_stream.fail()){
		cout << "File opening failed" << endl;
		exit(1);
	}
	in_stream >> data_size;
	data = new int[data_size];
	int i = 0;
	while (!in_stream.eof()){
		in_stream >> data[i];
		i++;
	}
	in_stream.close();
	
	/*for (int i = 0; i < data_size; i++) {
		cout << data[i] << endl;
	}*/
	
	//THIS FUNCTION ASSUMES THE DATA LENGTH IN THE FILE CORRESPONDS TO THE LENGTH OF THE ARRAY IN THE FILE
	//IF THE SIZE IS LONGER THAN THE GIVEN NUMBER OF ELEMENTS THEN THE UNASSIGNED VALUES WILL BE RANDOM
	//IF THE SIZE IS SHORTER THAN THE GIVEN NUMBER OF ELEMENTS THEN THERE WILL BE ERRORS
}
Polynomial::~Polynomial() {					//destructor performs cleanup if needed
		delete [] data;
}

bool Polynomial::operator==(const Polynomial& target) {			//performs *this == target
	bool success = false;
	if (target.data_size == data_size) {
		success = true;
		for (int i = 0; i < data_size; i++) {
			if (target.data[i] != data[i]) {
				success = false;
			}
		}
	}
	return success;
}
void Polynomial::print() {										//prints the polynomial (ex. 2x^3 + 1x^0)
	for (int i = 0; i < data_size; i++) {
		if (i == 0)
			cout << data[i];
		else if (i == 1)
			cout << abs(data[i]) << "x";
		else
			cout << abs(data[i]) << "x^" << i;
		if (i < data_size - 1 && data[i] >= 0)
			cout << " + ";
		else if (i < data_size - 1 && data[i] < 0)
			cout << " - ";
	}
}
Polynomial Polynomial::operator+(const Polynomial& target) {	//performs *this + target
	int result_data_size;
	int smaller;
	if (data_size >= target.data_size) {
		result_data_size = data_size;
		smaller = target.data_size;
	}
	else {
		result_data_size = target.data_size;
		smaller = data_size;
	}
	int result_data[result_data_size];
	for (int i = 0; i < smaller; i++) {
		result_data[i] = data[i] + target.data[i];
	}
	for (int i = smaller; i < result_data_size; i++) {
		if (data_size >= target.data_size)
			result_data[i] = data[i];
		else
			result_data[i] = target.data[i];
	}
	
	Polynomial result = Polynomial(result_data, result_data_size);
	
	return result;
} 
Polynomial Polynomial::operator-(const Polynomial& target) {	//performs *this - target
	int result_data_size;
	int smaller;
	if (data_size >= target.data_size) {
		result_data_size = data_size;
		smaller = target.data_size;
	}
	else {
		result_data_size = target.data_size;
		smaller = data_size;
	}
	int result_data[result_data_size];
	for (int i = 0; i < smaller; i++) {
		result_data[i] = data[i] - target.data[i];
	}
	for (int i = smaller; i < result_data_size; i++) {
		if (data_size >= target.data_size)
			result_data[i] = data[i];
		else
			result_data[i] = 0 - target.data[i];
	}
	
	Polynomial result = Polynomial(result_data, result_data_size);
	
	return result;
} 
Polynomial Polynomial::operator*(const Polynomial& target) {	//performs *this * target
	int result_data_size = data_size + target.data_size - 1;
	int result_data[result_data_size];
	for (int i = 0; i < result_data_size; i++){
		result_data[i] = 0;
	}
	for (int i = 0; i < data_size; i++) {
		for (int j = 0; j < target.data_size; j++) {
			result_data[i+j] += data[i] * target.data[j]; 
		}
	}
	Polynomial result = Polynomial(result_data, result_data_size);
	//result.print();
	//cout << endl;
	return result;
} 
Polynomial Polynomial::derivative() {							//computes the derivative d/dx of *this
	int result_data_size;
	if (data_size > 0)
		result_data_size = data_size - 1;
	else
		result_data_size = 0;
	int result_data[result_data_size];
	result_data[0] = data[1];
	for (int i = 1; i < result_data_size; i++) {
		result_data[i] = data[i+1] * (i+1);
	}
	
	Polynomial result = Polynomial(result_data, result_data_size);
	//result.print();
	//cout << endl;
	return result;
}

bool PolynomialTest::test_constructors()  {	//Tests the constructors
	bool success = true;
	//FIRST CONSTRUCTOR:
	int size1 = 9;
	int A[size1] = {1,2,3,4,5,6,7,8,9};
	Polynomial PC1 = Polynomial(A, size1);
	//A[2] = 12; //Uncomment for failure
	for (int i = 0; i < size1; i++) {
		if (PC1.data[i] != A[i]) 
			success = false;
	}
	//SECOND CONSTRUCTOR: hard to test for expected values since values are random
	Polynomial PC2 = Polynomial();
	//THIRD CONSTRUCTOR
	Polynomial PC3 = Polynomial("text.txt");
	ifstream in_stream_test;
	in_stream_test.open("text.txt");
	if (in_stream_test.fail()){
		cout << "File opening failed" << endl;
		exit(1);
	}
	int size3;
	in_stream_test >> size3;
	int C[size3];
	int i = 0;
	while (!in_stream_test.eof()){
		in_stream_test >> C[i];
		i++;
	}
	in_stream_test.close();
	//C[3] = 14; //Uncomment for failure
	for (int i = 0; i < size3; i++) {
		if (PC3.data[i] != C[i])
			success = false;
	}
	//END OF CONSTRUCTOR TESTS
	return success;
}
bool PolynomialTest::test_isEqual() {		 //Tests '==' operator
	bool success = true;
	//TESTING: Comparing multiple Polynomials with their predicted results
	//TEST CASES
	//1. Exact same
	//2. Same length, same coefficients but negative
	//3. Same length, different coefficients
	//4. Different lengths, mostly same coefficients
	//5. Different lengths, different coefficients
	//6. Compare all to length 0
	//7. Compare all to length > 0 and coefficients 0
	
	int sA = 8;
	int sB = 8;
	int sC = 8;
	int sD = 8;
	int sE = 12;
	int sF = 0;
	int sG = 14;
	
	int A[sA] = {-86,-72,-18,86,53,79,-63,-80};
	int B[sB] = {-86,-72,-18,86,53,79,-63,-80};
	int C[sC] = {86,72,18,-86,-53,-79,63,80};
	int D[sD] = {36,-57,-3,81,94,-16,91,98};
	int E[sE] = {36,-57,-3,81,94,-16,91,98,0,14,27,16};
	int F[sF];
	int G[sG] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	Polynomial pA = Polynomial(A, sA);
	Polynomial pB = Polynomial(B, sB);
	Polynomial pC = Polynomial(C, sC);
	Polynomial pD = Polynomial(D, sD);
	Polynomial pE = Polynomial(E, sE);
	Polynomial pF = Polynomial(F, sF);
	Polynomial pG = Polynomial(G, sG);
	
	//CASE 1: Exact same
	if (!(pA == pB)) success = false;
	//CASE 2: Same length, negative coefficients
	if (pA == pC) success = false;
	if (pB == pC) success = false;
	//CASE 3: Same length, different coefficients
	if (pA == pD) success = false;
	if (pB == pD) success = false;
	if (pC == pD) success = false;
	//CASE 4: Different length, some same coefficients
	if (pD == pE) success = false;
	//CASE 5: Different length, different coefficients
	if (pA == pE) success = false;
	if (pB == pE) success = false;
	if (pC == pE) success = false;
	//CASE 6: length 0
	if (pA == pF) success = false;
	if (pB == pF) success = false;
	if (pC == pF) success = false;
	if (pD == pF) success = false;
	if (pE == pF) success = false;
	//CASE 7: all coefficients 0
	if (pA == pG) success = false;
	if (pB == pG) success = false;
	if (pC == pG) success = false;
	if (pD == pG) success = false;
	if (pE == pG) success = false;
	if (pF == pG) success = false;
	
	return success;	
}
bool PolynomialTest::test_addition() {		 //Tests '+' operator
	bool success = true;
	//TESTING: Comparing multiple Polynomials with their predicted results
	//TEST CASES
	//1. Same number of coefficients
	//2. Different number of coefficients
	//3. Adding with 0/empty
	
	int sA = 8;
	int sB = 8;
	int sC = 8;
	int sD = 8;
	int sE = 12;
	int sF = 0;
	int sG = 14;
	
	int A[sA] = {-86,-72,-18,86,53,79,-63,-80};
	int B[sB] = {-86,-72,-18,86,53,79,-63,-80};
	int C[sC] = {86,72,18,-86,-53,-79,63,80};
	int D[sD] = {36,-57,-3,81,94,-16,91,98};
	int E[sE] = {36,-57,-3,81,94,-16,91,98,0,14,27,16};
	int F[sF];
	int G[sG] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	Polynomial pA = Polynomial(A, sA);
	Polynomial pB = Polynomial(B, sB);
	Polynomial pC = Polynomial(C, sC);
	Polynomial pD = Polynomial(D, sD);
	Polynomial pE = Polynomial(E, sE);
	Polynomial pF = Polynomial(F, sF);
	Polynomial pG = Polynomial(G, sG);
	
	//CASE 1: Same number of coefficients
	int AB[8] = {-172,-144,-36,172,106,158,-126,-160};
	int AC[8] = {0,0,0,0,0,0,0,0};
	int AD[8] = {-50,-129,-21,167,147,63,28,18};
	int BC[8] = {0,0,0,0,0,0,0,0};
	int BD[8] = {-50,-129,-21,167,147,63,28,18};
	int CD[8] = {122,15,15,-5,41,-95,154,178};
	Polynomial pAB = Polynomial(AB, 8);
	Polynomial pAC = Polynomial(AC, 8);
	Polynomial pAD = Polynomial(AD, 8);
	Polynomial pBC = Polynomial(BC, 8);
	Polynomial pBD = Polynomial(BD, 8);
	Polynomial pCD = Polynomial(CD, 8);
	if (!(pA + pB == pAB)) success = false;
	if (!(pA + pC == pAC)) success = false;
	if (!(pA + pD == pAD)) success = false;
	if (!(pB + pC == pBC)) success = false;
	if (!(pB + pD == pBD)) success = false;
	if (!(pC + pD == pCD)) success = false;
	//CASE 2: Different number of coefficients
	int AE[sE] = {-50,-129,-21,167,147,63,28,18,0,14,27,16};
	int BE[sE] = {-50,-129,-21,167,147,63,28,18,0,14,27,16};
	int CE[sE] = {122,15,15,-5,41,-95,154,178,0,14,27,16};
	int DE[sE] = {72,-114,-6,162,188,-32,182,196,0,14,27,16};
	Polynomial pAE = Polynomial(AE, sE);
	Polynomial pBE = Polynomial(BE, sE);
	Polynomial pCE = Polynomial(CE, sE);
	Polynomial pDE = Polynomial(DE, sE);
	if (!(pA + pE == pAE)) success = false;
	if (!(pB + pE == pBE)) success = false;
	if (!(pC + pE == pCE)) success = false;
	if (!(pD + pE == pDE)) success = false;
	//CASE 3: Adding 0
	if (!(pA + pF == pA)) success = false;
	if (!(pB + pF == pB)) success = false;
	if (!(pC + pF == pC)) success = false;
	if (!(pD + pF == pD)) success = false;
	if (!(pE + pF == pE)) success = false;	
	
	return success;
}
bool PolynomialTest::test_subtraction() {	 //Tests '-' operator
	bool success = true;
	//TESTING: Comparing multiple Polynomials with their predicted results
	//TEST CASES
	//1. Same number of coefficients - both ways
	//2. Different number of coefficients - both ways
	//3. Subtracting by 0/empty
	//4. Subtracting from 0/empty
	
	int sA = 8;
	int sB = 8;
	int sC = 8;
	int sD = 8;
	int sE = 12;
	int sF = 0;
	int sG = 14;
	
	int A[sA] = {-86,-72,-18,86,53,79,-63,-80};
	int B[sB] = {-86,-72,-18,86,53,79,-63,-80};
	int C[sC] = {86,72,18,-86,-53,-79,63,80};
	int D[sD] = {36,-57,-3,81,94,-16,91,98};
	int E[sE] = {36,-57,-3,81,94,-16,91,98,0,14,27,16};
	int F[sF];
	int G[sG] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	Polynomial pA = Polynomial(A, sA);
	Polynomial pB = Polynomial(B, sB);
	Polynomial pC = Polynomial(C, sC);
	Polynomial pD = Polynomial(D, sD);
	Polynomial pE = Polynomial(E, sE);
	Polynomial pF = Polynomial(F, sF);
	Polynomial pG = Polynomial(G, sG);
	
	//CASE 1: Same number of coefficients
	int A_B[8] = {0,0,0,0,0,0,0,0};
	int B_A[8] = {0,0,0,0,0,0,0,0};
	int A_C[8] = {-172,-144,-36,172,106,158,-126,-160};
	int C_A[8] = {172,144,36,-172,-106,-158,126,160};
	int A_D[8] = {-122,-15,-15,5,-41,95,-154,-178};
	int D_A[8] = {122,15,15,-5,41,-95,154,178};
	int B_C[8] = {-172,-144,-36,172,106,158,-126,-160};
	int C_B[8] = {172,144,36,-172,-106,-158,126,160};
	int B_D[8] = {-122,-15,-15,5,-41,95,-154,-178};
	int D_B[8] = {122,15,15,-5,41,-95,154,178};
	int C_D[8] = {50,129,21,-167,-147,-63,-28,-18};
	int D_C[8] = {-50,-129,-21,167,147,63,28,18};
	Polynomial pA_B = Polynomial(A_B, 8);
	Polynomial pB_A = Polynomial(B_A, 8);
	Polynomial pA_C = Polynomial(A_C, 8);
	Polynomial pC_A = Polynomial(C_A, 8);
	Polynomial pA_D = Polynomial(A_D, 8);
	Polynomial pD_A = Polynomial(D_A, 8);
	Polynomial pB_C = Polynomial(B_C, 8);
	Polynomial pC_B = Polynomial(C_B, 8);
	Polynomial pB_D = Polynomial(B_D, 8);
	Polynomial pD_B = Polynomial(D_B, 8);
	Polynomial pC_D = Polynomial(C_D, 8);
	Polynomial pD_C = Polynomial(D_C, 8);
	if (!(pA - pB == pA_B)) success = false;
	if (!(pB - pA == pB_A)) success = false;
	if (!(pA - pC == pA_C)) success = false;
	if (!(pC - pA == pC_A)) success = false;
	if (!(pA - pD == pA_D)) success = false;
	if (!(pD - pA == pD_A)) success = false;
	if (!(pB - pC == pB_C)) success = false;
	if (!(pC - pB == pC_B)) success = false;
	if (!(pB - pD == pB_D)) success = false;
	if (!(pD - pB == pD_B)) success = false;
	if (!(pC - pD == pC_D)) success = false;
	if (!(pD - pC == pD_C)) success = false;
	//CASE 2: Different number of coefficients
	int A_E[sE] = {-122,-15,-15,5,-41,95,-154,-178,0,-14,-27,-16};
	int E_A[sE] = {122,15,15,-5,41,-95,154,178,0,14,27,16};
	int B_E[sE] = {-122,-15,-15,5,-41,95,-154,-178,0,-14,-27,-16};
	int E_B[sE] = {122,15,15,-5,41,-95,154,178,0,14,27,16};
	int C_E[sE] = {50,129,21,-167,-147,-63,-28,-18,0,-14,-27,-16};
	int E_C[sE] = {-50,-129,-21,167,147,63,28,18,0,14,27,16};
	int D_E[sE] = {0,0,0,0,0,0,0,0,0,-14,-27,-16};
	int E_D[sE] = {0,0,0,0,0,0,0,0,0,14,27,16};
	Polynomial pA_E = Polynomial(A_E, sE);
	Polynomial pE_A = Polynomial(E_A, sE);
	Polynomial pB_E = Polynomial(B_E, sE);
	Polynomial pE_B = Polynomial(E_B, sE);
	Polynomial pC_E = Polynomial(C_E, sE);
	Polynomial pE_C = Polynomial(E_C, sE);
	Polynomial pD_E = Polynomial(D_E, sE);
	Polynomial pE_D = Polynomial(E_D, sE);
	if (!(pA - pE == pA_E)) success = false;
	if (!(pE - pA == pE_A)) success = false;
	if (!(pB - pE == pB_E)) success = false;
	if (!(pE - pB == pE_B)) success = false;
	if (!(pC - pE == pC_E)) success = false;
	if (!(pE - pC == pE_C)) success = false;
	if (!(pD - pE == pD_E)) success = false;
	if (!(pE - pD == pE_D)) success = false;
	//CASE 3: Subtracting by 0
	if (!(pA - pF == pA)) success = false;
	if (!(pB - pF == pB)) success = false;
	if (!(pC - pF == pC)) success = false;
	if (!(pD - pF == pD)) success = false;
	if (!(pE - pF == pE)) success = false;
	//CASE 4: Subdracting from 0
	int An[sA] = {86,72,18,-86,-53,-79,63,80};
	int Bn[sB] = {86,72,18,-86,-53,-79,63,80};
	int Cn[sC] = {-86,-72,-18,86,53,79,-63,-80};
	int Dn[sD] = {-36,57,3,-81,-94,16,-91,-98};
	int En[sE] = {-36,57,3,-81,-94,16,-91,-98,0,-14,-27,-16};
	Polynomial pAn = Polynomial(An, sA);
	Polynomial pBn = Polynomial(Bn, sB);
	Polynomial pCn = Polynomial(Cn, sC);
	Polynomial pDn = Polynomial(Dn, sD);
	Polynomial pEn = Polynomial(En, sE);
	if (!(pF - pA == pAn)) success = false;
	if (!(pF - pB == pBn)) success = false;
	if (!(pF - pC == pCn)) success = false;
	if (!(pF - pD == pDn)) success = false;
	if (!(pF - pE == pEn)) success = false;
	
	return success;
}
bool PolynomialTest::test_multiplication() { //Tests '*' operator
	bool success = true;
	//TESTING: Comparing multiple Polynomials with their predicted results
	//TEST CASES
	//1. Same number of coefficients
	//2. Different number of coefficients
	//3. Multiplying by 0
	//4. Multiplying by empty
	
	//Rule for polynomial multiplication: Degree(PQ) = Degree(P) + Degree(Q)
	//So we can use size(PQ) = size(P) + size(Q) - 1
	
	int sA = 4;
	int sB = 4;
	int sC = 4;
	int sD = 4;
	int sE = 6;
	int sF = 0;
	int sG = 7;
	
	int A[sA] = {71,70,13,-34};
	int B[sB] = {71,70,13,-34};
	int C[sC] = {-71,-70,-13,34};
	int D[sD] = {13,-35,-70,28};
	int E[sE] = {-87,58,60,12,-83,15};
	int F[sF];
	int G[sG] = {0,0,0,0,0,0,0};
	
	Polynomial pA = Polynomial(A, sA);
	Polynomial pB = Polynomial(B, sB);
	Polynomial pC = Polynomial(C, sC);
	Polynomial pD = Polynomial(D, sD);
	Polynomial pE = Polynomial(E, sE);
	Polynomial pF = Polynomial(F, sF);
	Polynomial pG = Polynomial(G, sG);
	
	//CASE 1: Same number of coefficients
	int AxB[7] = {5041, 9940, 6746, -3008, -4591, -884, 1156};
	int AxC[7] = {-5041, -9940, -6746, 3008, 4591, 884, -1156};
	int AxD[7] = {923, -1575, -7251, -3809, 2240, 2744, -952};
	int BxC[7] = {-5041, -9940, -6746, 3008, 4591, 884, -1156};
	int BxD[7] = {923, -1575, -7251, -3809, 2240, 2744, -952};
	int CxD[7] = {-923, 1575, 7251, 3809, -2240, -2744, 952};
	Polynomial pAxB = Polynomial(AxB, 7);
	Polynomial pAxC = Polynomial(AxC, 7);
	Polynomial pAxD = Polynomial(AxD, 7);
	Polynomial pBxC = Polynomial(BxC, 7);
	Polynomial pBxD = Polynomial(BxD, 7);
	Polynomial pCxD = Polynomial(CxD, 7);
	if (!(pA * pB == pAxB)) success = false;
	if (!(pA * pC == pAxC)) success = false;
	if (!(pA * pD == pAxD)) success = false;
	if (!(pB * pC == pBxC)) success = false;
	if (!(pB * pD == pBxD)) success = false;
	if (!(pC * pD == pCxD)) success = false;
	//CASE 2: Different number of coefficients
	int AxE[9] = {-6177, -1972, 7189, 8764, -6245, -6629, -437, 3017, -510};
	int BxE[9] = {-6177, -1972, 7189, 8764, -6245, -6629, -437, 3017, -510};
	int CxE[9] = {6177, 1972, -7189, -8764, 6245, 6629, 437, -3017, 510};
	int DxE[9] = {-1131, 3799, 4840, -8440, -4075, 3940, 5621, -3374, 420};
	Polynomial pAxE = Polynomial(AxE, 9);
	Polynomial pBxE = Polynomial(BxE, 9);
	Polynomial pCxE = Polynomial(CxE, 9);
	Polynomial pDxE = Polynomial(DxE, 9);
	if (!(pA * pE == pAxE)) success = false;
	if (!(pB * pE == pBxE)) success = false;
	if (!(pC * pE == pCxE)) success = false;
	if (!(pD * pE == pDxE)) success = false;
	//CASE 3: Multiplying by 0
	int AxG[10] = {0,0,0,0,0,0,0,0,0,0};
	int BxG[10] = {0,0,0,0,0,0,0,0,0,0};
	int CxG[10] = {0,0,0,0,0,0,0,0,0,0};
	int DxG[10] = {0,0,0,0,0,0,0,0,0,0};
	int ExG[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	Polynomial pAxG = Polynomial(AxG, 10);
	Polynomial pBxG = Polynomial(BxG, 10);
	Polynomial pCxG = Polynomial(CxG, 10);
	Polynomial pDxG = Polynomial(DxG, 10);
	Polynomial pExG = Polynomial(ExG, 12);
	if (!(pA * pG == pAxG)) success = false;
	if (!(pB * pG == pBxG)) success = false;
	if (!(pC * pG == pCxG)) success = false;
	if (!(pD * pG == pDxG)) success = false;
	if (!(pE * pG == pExG)) success = false;
	//CASE 4: Multiplying by empty
	int AxF[3] = {0,0,0};
	int BxF[3] = {0,0,0};
	int CxF[3] = {0,0,0};
	int DxF[3] = {0,0,0};
	int ExF[5] = {0,0,0,0,0};
	Polynomial pAxF = Polynomial(AxF, 3);
	Polynomial pBxF = Polynomial(BxF, 3);
	Polynomial pCxF = Polynomial(CxF, 3);
	Polynomial pDxF = Polynomial(DxF, 3);
	Polynomial pExF = Polynomial(ExF, 5);
	if (!(pA * pF == pAxF)) success = false;
	if (!(pB * pF == pBxF)) success = false;
	if (!(pC * pF == pCxF)) success = false;
	if (!(pD * pF == pDxF)) success = false;
	if (!(pE * pF == pExF)) success = false;
	
	return success;
}
bool PolynomialTest::test_derivative() {	 //Tests derivative function
	bool success = true;
	//TESTING: Comparing multiple Polynomials with their predicted results
	//TEST CASES:
	//1. Polynomial with integer coefficients
	//2. Polynomial with 0 coefficients
	//3. Empty Polynomial
	
	int sA = 8;
	int sB = 12;
	int sC = 14;
	int sD = 0;

	int A[sA] = {-86,-72,-18,86,53,79,-63,-80};
	int B[sB] = {36,-57,-3,81,94,-16,91,98,0,14,27,16};
	int C[sC] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int D[sD];
	
	Polynomial pA = Polynomial(A, sA);
	Polynomial pB = Polynomial(B, sB);
	Polynomial pC = Polynomial(C, sC);
	Polynomial pD = Polynomial(D, sD);
	
	int Ad[sA-1] = {-72,-36,258,212,395,-378,-560};
	int Bd[sB-1] = {-57,-6,243,376,-80,546,686,0,126,270,176};
	int Cd[sC-1] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
	int Dd[0];
	
	Polynomial pAd = Polynomial(Ad, sA-1);
	Polynomial pBd = Polynomial(Bd, sB-1);
	Polynomial pCd = Polynomial(Cd, sC-1);
	Polynomial pDd = Polynomial(Dd, 0);

	//CASE 1: Polynomial with integer coefficients
	if (!(pA.derivative() == pAd)) success = false;
	if (!(pB.derivative() == pBd)) success = false;
	//CASE 2: Polynomial with 0 coefficients
	if (!(pC.derivative() == pCd)) success = false;
	//CASE 3: Empty Polynomial
	if (!(pD.derivative() == pDd)) success = false;
	
	return success;
}
void PolynomialTest::test_print() {			 //Tests print function
	cout << endl << "For Printing test, these should all look the same: " << endl;
	int A[8] = {-86,-72,-18,86,53,79,-63,-80};
	int B[5] = {0,0,0,0,0};
	int C[0];
	Polynomial pA = Polynomial(A,8);
	Polynomial pB = Polynomial(B,5);
	Polynomial pC = Polynomial(C,0);
	cout << "-86 - 72x - 18x^2 + 86x^3 + 53x^4 + 79x^5 - 63x^6 - 80x^7\n\t***AND***\n";
	pA.print();
	cout << endl << endl;
	cout << "0 + 0x + 0x^2 + 0x^3 + 0x^4\n\t***AND***\n";
	pB.print();
	cout << endl;
	pC.print();
}

void PolynomialTest::run() {					//Runs all tests
	bool pass = true;
	//Test constructors check
	if (test_constructors())
		cout << "Test-Constructors: Passed" << endl;
	else {
		cout << "Test-Constructors1: Failed" << endl;
		pass = false;
	}
	//Test '==' operator check
	if (test_isEqual())
		cout << "Test-IsEqual: Passed" << endl;
	else {
		cout << "Test-IsEqual: Failed" << endl;
		pass = false;
	}
	//Test '+' operator check
	if (test_addition())
		cout << "Test-Addition: Passed" << endl;
	else {
		cout << "Test-Addition: Failed" << endl;
		pass = false;
	}
	//Test '-' operator check
	if (test_subtraction())
		cout << "Test-Subtraction: Passed" << endl;
	else {
		cout << "Test-Subtraction: Failed" << endl;
		pass = false;
	}
	//Test '*' operator check
	if (test_multiplication())
		cout << "Test-Multiplication: Passed" << endl;
	else {
		cout << "Test-Multiplication: Failed" << endl;
		pass = false;
	}
	//Test derivative check
	if (test_derivative())
		cout << "Test-Derivative: Passed" << endl;
	else {
		cout << "Test-Derivative: Failed" << endl;
		pass = false;
	}
	//Test print check
	string yn;
	test_print();
	cout << endl << "Are these the same? Y/N" << endl;
	cin >> yn;
	if (yn != "Y")
		pass = false;
	//Summary
	if (pass)
		cout << endl << "ALL TESTS SUCCESSFUL";
	else
		cout << endl << "TESTS UNSUCCESSFUL"; 
}
	
int main() {	
	PolynomialTest my_test;
	my_test.run();
	
	return 0;
}
