#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
int IP[64] = {
	58, 50, 42, 34, 26, 18, 10, 2, 
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6, 
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17,  9, 1, 
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5, 
	63, 55, 47, 39, 31, 23, 15, 7 };
int E[48] = {
	32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
	8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1 };
int P[32] = {
	16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23, 26, 5,  18, 31, 10,
	2,  8, 24, 14, 32, 27, 3,  9,  19, 13, 30, 6,  22, 11, 4,  25 };
int _IP[64] = {
	40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41,  9, 49, 17, 57, 25 };
int PC1[56] = {
	57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
	10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
	14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4 };
int PC2[48] = {
	14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
	23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32 };
int SBOX[8][4][16] = {
	// S1
	14, 4,  13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
	0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
	4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
	15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13 ,
	// S2
	15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
	3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
	0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
	13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9 ,
	// S3
	10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
	13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
	13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
	1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12 ,
	// S4
	7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
	13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
	10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
	3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14 ,
	// S5 
	2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
	14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
	4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
	11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3 ,
	// S6
	12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
	10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
	9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
	4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13 ,
	// S7
	4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
	13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
	1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
	6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12 ,
	// S8
	13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
	1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
	7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
	2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11 };
int Left[16] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };
int keyC[16][28] = { 0 }, keyD[16][28] = { 0 };
void EChange(int R[], int newR[]);
int SubKeys[16][48] = { 0 };
void F_func(int R[], int K[], int i);
void Xor(int *Array1, int *Array2, int len);
 void CharToBit(char input[], int output[])
{
	int i, j, k;
	for (j = 0; j<8; j++)
	{
		for (i = 0; i<8; i++)
		{
			output[7 * (j + 1) - i + j] = (input[j] >> i) & 1;

		}
	}
}
char BitToChar(int intput[], char output[])
{
	int i, j, k;
	for (j = 0; j<8; j++)
	{
		for (i = 0; i<8; i++)
		{
			k = pow(2, 7 - i);
			output[j] = output[j] + k * intput[i + 8 * j];

		}
	}
	
	return *output;
}
/*明文*/
int IPChange(int output[],char ms[]) {
	CharToBit(ms, output);
	int i, j, k;
	int a[64] = { 0 };
	for (k = 0; k < 64; k++) {
		a[k] = output[k];
	}
	for (i = 0; i < 64; i++) {
		j = IP[i] - 1;
		output[i] = a[j];
	}
	return *output;
}
void _IPChange(int input[], int output[]) {
	int i, j;
	for (i = 0; i < 64; i++) {
		j = _IP[i] - 1; 
		output[i] = input[j];
	}
}
int IPLR(int output[], char output3[]) {
	int i, j, k;
	int newR[48] = { 0 }, output1[64] = { 0 }, output2[64] = { 0 };
	int R[17][32] = { 0 }, L[17][32] = { 0 };
	for (i = 0; i < 64; i++)
	{
		if (i < 32) {
			L[0][i] = output[i];
		}
		else
		{
			R[0][i - 32] = output[i];
		}
	}
	for (j = 1; j<16; j++)
	{
		for (k = 0; k<32; k++)
		{
			L[j][k] = R[j - 1][k];
		}
		F_func(R[j - 1], R[j], j - 1);
		Xor(R[j], L[j - 1], 32);
		
	}
	for (i = 0; i<32; i++)
	{
		L[16][i] = R[15][i];
	}
	F_func(R[15], R[16], 15);
	Xor(R[16], L[15], 32);
	for (i = 0; i<32; i++)
	{
		output1[i] = R[16][i];
		output1[32 + i] = L[16][i];
	}
	_IPChange(output1, output2);
	output3[8] = BitToChar(output2, output3);
	return *output3;
}
int _IPLR(int output[], char output3[]) {
	int i, j, k;
	int newR[48] = { 0 }, output1[64] = { 0 }, output2[64] = { 0 };
	int R[17][32] = { 0 }, L[17][32] = { 0 };
	for (i = 0; i < 64; i++)
	{
		if (i < 32) {
			L[0][i] = output[i];
		}
		else
		{
			R[0][i - 32] = output[i];
		}
	}
	for (j = 1; j<16; j++)
	{
		for (k = 0; k<32; k++)
		{
			L[j][k] = R[j - 1][k];
		}
		F_func(R[j - 1], R[j], 16 - j);
		Xor(R[j], L[j - 1], 32);
	}
	for (i = 0; i<32; i++)
	{
		L[16][i] = R[15][i];
	}
	F_func(R[15], R[16], 0);
	Xor(R[16], L[15], 32);
	for (i = 0; i<32; i++)
	{
		output1[i] = R[16][i];
		output1[32 + i] = L[16][i];
	}
	_IPChange(output1, output2);
	output3[8] = BitToChar(output2, output3);
	return *output3;
}
void EChange(int R[], int newR[]) {
	int i, j;
	for (i = 0; i < 48; i++) {
		j = E[i] - 1;
		newR[i] = R[j];
	}
	
}
void Xor(int *Array1, int *Array2, int len) {
	int i;
	for (i = 0; i<len; i++)
	{
		*(Array1 + i) = *(Array1 + i) ^ *(Array2 + i);
	}
}
void SChange(int input[], int output[]) {
	int i = 0;
	int j = 0;
	int INT[8] = { 0 };
	for (; i<48; i = i + 6)
	{

		INT[j] = SBOX[j][(input[i] << 1) + (input[i + 5])][(input[i + 1] << 3) + (input[i + 2] << 2) + (input[i + 3] << 1) + (input[i + 4])];
		j++;
	}
	for (j = 0; j<8; j++)
	{
		for (i = 0; i<4; i++)
		{
			output[3 * (j + 1) - i + j] = (INT[j] >> i) & 1;
		}
	}
}
void PChange(int input[], int output[]) {
	int i, j;
	for (i = 0; i < 32; i++) {
		j = P[i] - 1;
		output[i] = input[j];
	}
}
void F_func(int input[32], int output[32], int i)
{
	int j;  
	int a[48] = { 0 };
	int b[32] = { 0 };
	EChange(input, a);
	Xor(a, SubKeys[i], 48);
	SChange(a, b);
	PChange(b, output);
	
}
/* 密文*/
void SetKey(char key[], int newkey[]) {
	int i, j;
	int keybit[64] = { 0 };
	CharToBit(key, keybit);
	for (i = 0; i < 56; i++) {
		j = PC1[i] - 1;
		newkey[i] = keybit[j];
	}

}

void LeftKey(int CDkey[], int keyCD[], int left) {
	int i;
	for (i = 0; i<28; i++)
	{
		keyCD[i] = CDkey[(i + left) % 28];
	}

}
void KeyPC2(int newkey[], int SubKeys[]) {
	int i, j;
	for (i = 0; i < 48; i++) {
		j = PC2[i] - 1;
		SubKeys[i] = newkey[j];
	}

}
void SetKeyCD(int newkey[],int key[]) {
	int i, j;
	int C[28], D[28];
	int PC_2[16][56] = { 0 };
	SetKey(key, newkey);
	for (i = 0; i < 56; i++)
	{
		if (i < 28) {
			C[i] = newkey[i];
		}
		else
		{
			D[i - 28] = newkey[i];
		}
	}
	for (j = 0; j < 16; j++) {
		if (j ==0) {
			LeftKey(C, keyC[j], Left[j]);
	
			LeftKey(D, keyD[j], Left[j]);
	
		}
		else
		{
			LeftKey(keyC[j-1], keyC[j], Left[j]);
	
			LeftKey(keyD[j-1], keyD[j], Left[j]);
		
		}
	}
	for (i = 0; i<16; i++)
	{
		for (j = 0; j<28; j++)
		{
			PC_2[i][j] = keyC[i][j];
			PC_2[i][j + 28] = keyD[i][j];	}
	}
	for (i = 0; i < 16; i++)
	{
		KeyPC2(PC_2[i], SubKeys[i]);
	}
}
int main() {
	int i,j, k;
	char ms[9] = { 0 }, key[9] = { 0}, key2[9] = {0}, output2[8] = { 0 };
	char  output4[8] = { 0 }, output5[8] = { 0 };
	int output[64] = { 0 };
	int newkey[56] = { 0 }, output3[64] = { 0 },newkey2[56] = { 0 };
	int keyC[16][28] = { 0 }, keyD[16][28] = { 0 };
	printf("***DES***\n");
	printf("please input the message:\n");
	gets(ms);
	printf("please input the key:\n");
	gets(key);
	output[64] = IPChange(output,ms);
	printf("\n");
	SetKeyCD(newkey,key);
	printf("加密后：\n");
	printf("\n");
	output2[8] = IPLR(output, output2);
	for (i = 0; i < 8; i++) {
		printf("%c ", output2[i]);
	}
	printf("\n");
	printf("\n");
	printf("解密后：\n");
	printf("\n");
	strcpy(key2, key);
	output3[64] = IPChange(output3,output2);
	SetKeyCD(newkey2, key2);
	output4[8] = _IPLR(output3, output4);
	for (i = 0; i < 8; i++) {
		printf("%c ", output4[i]);
	}
	printf("\n");
	printf("\n");
	system("pause");
	return 0;
}
