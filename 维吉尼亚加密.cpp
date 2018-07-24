#include<stdlib.h>
#include<stdio.h>
char LEFT(char input[]) {
	int i;
	int j;
	int k;
	char temp;
	temp=input[0];
	for ( i = 0; i < 26; i++)
	{	
		input[i]=input[i+1];
		input[26]=temp;
		//printf("%c ",input[i]);
	}
	return *input;
}
void A(char input[],char output[])
{
	int i;
	int j;
	for(i=0;i<26;i++){
		output[i]=input[i];
	}
} 
void Change(char input[],char output[]){
	int i;
	for(i=0;i<_mbstrlen(input);i++){
		if(input[i]<='Z'&&input[i]>='A'){
			output[i]=input[i]+32;
		}
		else if(input[i]<='z'&&input[i]>='a'){
			output[i]=input[i];
		}
	}
/*	for(i=0;i<_mbstrlen(input);i++){
		printf("%c ",output[i]);
	}*/
	
}
void Encrypt(char input[],char key[],char b[26][26],char output[]){
	int m1[100],k1[100],c1[100];
	int i,j,k;
	for(i=0;i<_mbstrlen(key);i++){
		k1[i]=key[i]-'a';
	}
	for(i=0;i<_mbstrlen(input);i++){
		m1[i]=input[i]-'a';
		output[i]=b[k1[i%_mbstrlen(key)]][m1[i]];
	}
	for(i=0;i<_mbstrlen(input);i++){
		printf("%c ",output[i]);
	}
}
void Decrypt(char input[],char key[],char b[26][26],char output[]){
	int m1[100],k1[100],c1[100];
	int i,j,k;
	for(i=0;i<_mbstrlen(key);i++){
		k1[i]=key[i]-'a';
	}
	for(i=0;i<_mbstrlen(input);i++){
		//m1[i]=input[i]-'a';
		for(j=0;j<26;j++){
			if(input[i]==b[k1[i%_mbstrlen(key)]][j]){
			output[i]=j+'a';
			}
		}
	}
	for(i=0;i<_mbstrlen(input);i++){
		printf("%c ",output[i]);
	}
}
int main() {
	char a[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	char ms[100] = { 0 };
	char ms_1[100]={ 0 };
	char key[100] = { 0 };
	char key_1[100] = { 0 };
	char b[26][26]={ 0 };
	char miwen[100]={ 0 }; 
	int i;
	int j;
	printf("请输入明文：\n");
	gets(ms);
	printf("请输入密钥：\n");
	gets(key);
	Change(ms,ms_1);
	Change(key,key_1);
	A(a,b[0]);
	for(i=1;i<26;i++){
		a[26]=LEFT(a);
		A(a,b[i]);
	}
	printf("加密后：\n");
	Encrypt(ms_1,key_1,b,miwen);
	printf("\n解密后：\n");
	Decrypt(miwen,key_1,b,miwen);
	system("pause");
	return 0;
}
