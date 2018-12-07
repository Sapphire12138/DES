#include <iostream>
#include <cmath>
using namespace std;

int IP_Table[64] = {
	58,50,42,34,26,18,10,2,
	60,52,44,36,28,20,12,4,
	62,54,46,38,30,22,14,6,
	64,56,48,40,32,24,16,8,
	57,49,41,33,25,17, 9,1,
	59,51,43,35,27,19,11,3,
	61,53,45,37,29,21,13,5,
	63,55,47,39,31,23,15,7};

int IP_Inverse[64] = {
	40,8,48,16,56,24,64,32,
	39,7,47,15,55,23,63,31,
	38,6,46,14,54,22,62,30,
	37,5,45,13,53,21,61,29,
	36,4,44,12,52,20,60,28,
	35,3,43,11,51,19,59,27,
	34,2,42,10,50,18,58,26,
	33,1,41, 9,49,17,57,25};

int PC1_Table[56] = {
	57,49,41,33,25,17,9,
	1,58,50,42,34,26,18,
	10,2,59,51,43,35,27,
	19,11,3,60,52,44,36,
	63,55,47,39,31,23,15,
	7,62,54,46,38,30,22,
	14,6,61,53,45,37,29,
	21,13,5,28,20,12,4};

int PC2_Table[48] = {
	14,17,11,24,1,5,
	3,28,15,6,21,10,
	23,19,12,4,26,8,
	16,7,27,20,13,2,
	41,52,31,37,47,55,
	30,40,51,45,33,48,
	44,49,39,56,34,53,
	46,42,50,36,29,32};

int E_Table[48] = {
	32,1,2,3,4,5,
	4,5,6,7,8,9,
	8,9,10,11,12,13,
	12,13,14,15,16,17,
	16,17,18,19,20,21,
	20,21,22,23,24,25,
	24,25,26,27,28,29,
	28,29,30,31,32,1};

int P_Table[32] = {
	16,7,20,21,29,12,28,17,
	1,15,23,26,5,18,31,10,
	2,8,24,14,32,27,3,9,
	19,13,30,6,22,11,4,25};

int leftMove_Table[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

int S_Box[8][4][16] = {
	//SBox1
	14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
	0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
	4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
	15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13,
	//SBox2
	15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
	3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
	0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
	13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9,
	//SBox3
	10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
	13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
	13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
	1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12,
	//SBox4
	7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
	13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
	10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
	3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14,
	//SBox5
	2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
	14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
	4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
	11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3,
	//SBox6
	12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
	10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
	9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
	4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13,
	//SBox7
	4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
	13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
	1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
	6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12,
	//SBox8
	13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
	1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
	7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
	2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11};



template<typename T>
void outputArray(const T array[], int len, int breakPoint = 8) {
	cout << "\n\t";
	for(int i = 0; i < len; ++i) {
		if(i % breakPoint == 0)	cout << "\n\t";
		cout << array[i] << " ";
	}
	cout << "\n\n";
}

template<typename T>
bool isEqual(const T array1[], const T array2[], int len) {
	for(int i = 0; i < len; ++i)
		if(array1[i] != array2[i])
			return false;
	return true;
}

//Set the array target to the same as the mod
void setArray(const int mod[], int target[], int len) {
	for(int i = 0; i < len; ++i)
		target[i] = mod[i];
}

//Convert the C string into the binary array
//The third parameter is the length of the first parameter input[]
void charToBit(const char input[], int output[], int len = 8) {
	for(int i = 0; i < len; ++i)
		for(int j = 0; j < 8; ++j)
			output[8*i + 7 - j] = (input[i] >> j) & 1;
}

//Convert the binary array into the C string
//The third parameter is the length of the first parameter input[]
void bitToChar(const int input[], char output[], int len = 64) {
	int num = len / 8;
	for(int i = 0; i < num; ++i) {
		int tempNum = 0;
		for(int j = 0; j < 8; ++j)
			tempNum += input[8*i + 7 - j] * pow(2, j);
		output[i] = tempNum;
	}
}

//The third parameter is the length of the ouput array
void replaceData(int input[], int output[], int transArray[], int len) {
	for(int i = 0; i < len; ++i)
		output[i] = input[transArray[i] - 1];
}

void leftMove(int data[], int size, int moveNum) {
	moveNum = moveNum % size;
	int temp[size];
	for(int i = 0; i < size; ++i)
		temp[i] = data[i];
	for(int i = 0; i < size - moveNum; ++i)
		data[i] = temp[i + moveNum];
	for(int i = 0; i < moveNum; ++i)
		data[size - moveNum + i] = temp[i];
}

void XOROperate(int data1[], int data2[], int result[], int len) {
	for(int i = 0; i < len; ++i)
		result[i] = (data1[i] == data2[i]) ? 0 : 1;
}

//The third parameter is the length of the first parameter input[]
void halfDivide(const int input[], int left[], int right[], int size) {
	for(int i = 0; i < size / 2; ++i)
		left[i] = input[i];
	for(int i = 0; i < size / 2; ++i)
		right[i] = input[size / 2 + i];
}

//Merge two arrays into one
//The parameter size is the length of the input array
void mergeArray(const int left[], const int right[], int output[], int size) {
	for(int i = 0; i < size; ++i)
		output[i] = left[i];
	for(int i = 0; i < size; ++i)
		output[i + size] = right[i];
}

// SBox Operation
// The length of the input array is 48 and the length of the output array is 32
void SBoxOpe(const int input[], int output[]) {
	int begin = 0, row = 0, column = 0, SBoxData = 0;
	for(int i = 0; i < 8; ++i) {
		begin = 6 * i;
		row = 2*input[begin] + input[begin + 5];
		column = 8*input[begin + 1] + 4*input[begin + 2] + 2*input[begin + 3] + input[begin + 4];
		SBoxData = S_Box[i][row][column];
		for(int j = 0; j < 4; ++j) {
			output[4*i + 3 - j] = (SBoxData >> j) & 1;
		}
	}
}

void DES_Encode(int input[], int output[], int key[], int len) {
	if(len != 64)	return;
	int preOutputArray[64];
	int initialIPResult[64], LArray[32], RArray[32], E_RArray[48], PC2result[48], SBoxResult[32], PResult[32];
	int PC1result[56], CArray[28], DArray[28], leftMoveResult[56];
	int xorS[48], xorF[32];

	//The initial IP
	replaceData(input, initialIPResult, IP_Table, 64);
	//Get L and R
	halfDivide(initialIPResult, LArray, RArray, 64);
	//PC1
	replaceData(key, PC1result, PC1_Table, 56);
	//Get C and D
	halfDivide(PC1result, CArray, DArray, 56);

	for(int i = 0; i < 16; ++i) {
		//Left move
		leftMove(CArray, 28, leftMove_Table[i]);
		leftMove(DArray, 28, leftMove_Table[i]);
		//Merge C array and D array
		mergeArray(CArray, DArray, PC1result, 28);
		//PC2, and the result of the PC2 is the subkey
		replaceData(PC1result, PC2result, PC2_Table, 48);
		//Operate E transform
		replaceData(RArray, E_RArray, E_Table, 48);
		//XOR
		XOROperate(E_RArray, PC2result, xorS, 48);
		//SBox Operation
		SBoxOpe(xorS, SBoxResult);
		//P transform, and the result of this operation is the result of the f function
		replaceData(SBoxResult, PResult, P_Table, 32);
		//Get the new R array
		XOROperate(LArray, PResult, xorF, 32);

		setArray(RArray, LArray, 32);
		setArray(xorF, RArray, 32);
	}
	mergeArray(RArray, LArray, preOutputArray, 32);
	replaceData(preOutputArray, output, IP_Inverse, 64);
}

void DES_Decode(int input[], int output[], int key[], int len) {
	if(len != 64)	return;
	int preOutputArray[64];
	int initialIPResult[64], LArray[32], RArray[32], E_RArray[48], PC2result[48], SBoxResult[32], PResult[32];
	int PC1result[56], CArray[28], DArray[28], leftMoveResult[56];
	int xorS[48], xorF[32];
	int subkey[16][48];

	//The initial IP
	replaceData(input, initialIPResult, IP_Table, 64);
	//Get L and R
	halfDivide(initialIPResult, LArray, RArray, 64);
	//PC1
	replaceData(key, PC1result, PC1_Table, 56);
	//Get C and D
	halfDivide(PC1result, CArray, DArray, 56);

	//Create all subkeys
	for(int i = 0; i < 16; ++i) {
		leftMove(CArray, 28, leftMove_Table[i]);
		leftMove(DArray, 28, leftMove_Table[i]);
		mergeArray(CArray, DArray, PC1result, 28);
		//PC2, and the result of the PC2 is the subkey
		replaceData(PC1result, PC2result, PC2_Table, 48);
		//Store the ith subkey
		setArray(PC2result, subkey[i], 48);	
	}

	for(int i = 0; i < 16; ++i) {
		//Operate E transform
		replaceData(RArray, E_RArray, E_Table, 48);
		//XOR
		XOROperate(E_RArray, subkey[15 - i], xorS, 48);
		//SBox Operation
		SBoxOpe(xorS, SBoxResult);
		//P transform, and the result of this operation is the result of the f function
		replaceData(SBoxResult, PResult, P_Table, 32);
		//Get the new R array
		XOROperate(LArray, PResult, xorF, 32);

		setArray(RArray, LArray, 32);
		setArray(xorF, RArray, 32);	
	}
	mergeArray(RArray, LArray, preOutputArray, 32);
	replaceData(preOutputArray, output, IP_Inverse, 64);
}


int main(void) {
	try {
		char inputChar[9] = "abcdefgh", outputChar[9], keyChar[9] = "12345678";
		int inputInt[64], outputInt[64], keyInt[64];
		int decodeOutput[64];
		charToBit(inputChar, inputInt, 8);
		charToBit(keyChar, keyInt, 8);


		DES_Encode(inputInt, outputInt, keyInt, 64);

		outputArray(outputInt, 64, 8);



		// int testInt[8] = {0,0,0,0,1,1,0,0};
		// bitToChar(outputInt, outputChar, 64);
		// outputArray(outputChar, 8, 8);
		
		DES_Decode(outputInt, decodeOutput, keyInt, 64);
		bitToChar(decodeOutput, outputChar, 64);
		cout << "\n\tThe deciphered data is as follows:\n";
		outputArray(outputChar, 8);
		bool equalJudge = isEqual(inputInt, decodeOutput, 64);
	}
	catch(...) {
		cerr << "\n\tUnknown exception is captured.\n";
		return 0;
	}
}
