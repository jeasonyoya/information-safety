#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>

bool IsCoprime(int a, int b)
{
	int min = (a<b) ? a : b;
	int max = (a>b) ? a : b;
	int  temp = 0;
	while (true)
	{
		if (max%min == 0) break;
		else
		{
			temp = min;
			min = max % min;
			max = temp;
		}
	}
	if (min == 1) return true;
	else return false;
}
int Inverse(int a, int b)
{
	int a0 = a;
	int b0 = b;
	int t0 = 0;
	int t = 1;
	int q = a0 / b0;
	int r = a0 - q * b0;
	int temp = 0;
	while (r > 0)
	{
		temp = (t0 - q * t) % a;
		t0 = t;
		t = temp;
		a0 = b0;
		b0 = r;
		q = a0 / b0;
		r = a0 - q * b0;
	}
	if (b0 != 1) return 0;
	else return (t + a) % a;
}
void KeyProduce(int p, int q, int keys[])
{
	int n = p * q;
	int func_n = (p - 1)*(q - 1);
	int e = 0;
	int d = 0;
	do
	{
		srand(rand());
		e = rand() % func_n;
		while (e <= 1)e++;
	} while (!IsCoprime(e, func_n));
	d = Inverse(func_n, e);
	keys[0] = n;  
	keys[1] = e;
	keys[2] = p;
	keys[3] = q;
	keys[4] = d;
	printf("int the keys:n:%d,func_n:%d,e:%d,p:%d,q:%d,d:%d\n", n, func_n, e, p, q, d);

}
int FastExponentialAlgorithm(int x, int e, int m)
{
	int X, E, Y;
	X = x;
	E = e;
	Y = 1;
	while (E != 0)
	{
		if (E / 2 * 2 != E)
		{
			Y = (X*Y) % m;
			E = E - 1;
		}
		else
		{
			X = X * X%m;
			E = E / 2;
		}
	}
	return Y;
}
bool MillerRabin(int n)
{
	int m = n - 1;
	int k = 0;
	__int64 a = 0;
	int b = 0;
	while (m / 2 * 2 == m)
	{
		k++;
		m = m / 2;
	}
	srand(rand());
	a = rand() % n;
	while (a<1)a++;
	b = FastExponentialAlgorithm(a, m, n);
	if (1 == b)
		return true;
	for (int i = 0; i<k; i++)
	{
		if (b == n - 1) return true;
		else b = b * b % n;
	}
	return false;
}
int ProduceBigPrime(int max, int min)
{
	int bigprime = 0;
	do
	{
		srand(rand());
		bigprime = rand() % max;
	} while (!((bigprime > min) && (MillerRabin(bigprime))));
	return bigprime;
}
int EnCode(int x, int e, int n)
{
	return FastExponentialAlgorithm(x, e, n);
}
int DeCode(int y, int d, int p, int q)
{
	int n = p * q;
	return (FastExponentialAlgorithm(y, d, n) + n) % n;
}
void TotalEnCode(int x[], int y[], int e, int n, int total)
{
	for (int i = 0; i < total; i++)
	{
		y[i] = EnCode(x[i], e, n);
	}
}
void TotalDeCode(int y[], int x[], int d, int p, int q, int total)
{
	for (int i = 0; i < total; i++)
	{
		x[i] = DeCode(y[i], d, p, q);
	}
}
void PrintNum(int num[], int n)
{
	for (int i = 0; i < n; i++) {
		printf("%d,", num[i]);
	}
	printf("\n");
}
void PrintChar(int num[], int n)
{
	for (int i = 0; i < n; i++) {
		printf("%c", num[i]);
	}
	printf("\n");
}
void CharToNum(char ch[], int num[], int n)
{
	for (int i = 0; i < n; i++) {
		num[i] = ch[i];
	}
}
void RSA()
{
	int p, q;        
	int d, e;
	int n = 0;
	int keys[5] = { 0 };
	int MIN = 10;		
	int MAX = 100;      //方便计算取10-100的随机质素。
	int x[100] = { 0 };
	int y[100] = { 0 };
	char ch[101] = { 0 };
	int len = 0;
	char temp;
	do
	{
		p = ProduceBigPrime(MAX, MIN);
		q = ProduceBigPrime(MAX, MIN);
	} while (p == q);

	KeyProduce(p, q, keys);
	n = keys[0];
	e = keys[1];
	p = keys[2];
	q = keys[3];
	d = keys[4];
	printf("请输入明文:\n");
	gets_s(ch);
	len = strlen(ch);
	CharToNum(ch, x, len);
	TotalEnCode(x, y, e, n, len);
	TotalDeCode(y, x, d, p, q, len);

	/*printf("明文ascll码:\n");
	PrintNum(x, len);
	printf("密文ascll码:\n");
	PrintNum(y, len);*/
	printf("加密后:\n");
	PrintChar(y, len);
	printf("解密后:\n");
	PrintChar(x, len);

}
int main()
{
	RSA();
	system("pause");
	return 0;
} 
