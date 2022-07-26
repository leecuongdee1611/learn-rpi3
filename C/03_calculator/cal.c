#include <stdio.h>

int add(int *n1, int *n2);
int sub(int *n1, int *n2);
int mul(int *n1, int *n2);
int div(int *n1, int *n2);


int main()
{
	char op;
	int n1, n2;
	
	
while(1)
{	
	printf("Nhap vao so thu nhat: ");
	scanf("%d", &n1);
	printf("Nhap vao so thu hai: ");
	scanf("%d", &n2);
	printf("Nhap vao phep toan: ");
	scanf(" %c", &op);
	switch(op)
	{
		case '+':
			printf("Ket qua: %d + %d = %d\n",n1, n2, add(&n1, &n2));
		break;
		case '-':
			printf("Ket qua: %d - %d = %d\n",n1, n2, sub(&n1, &n2));
		break;
		case '*':
			printf("Ket qua: %d * %d = %d\n",n1, n2, mul(&n1, &n2));
		break;
		case '/':
			printf("Ket qua: %d / %d = %d\n",n1, n2, div(&n1, &n2));
		break;
		default:
			printf("Phep toan nhap vao khong dung\n");
	}
}
	return 0;
}


int add(int *n1, int *n2)
{
	int re = *n1 + *n2;
	return re;
}

int sub(int *n1, int *n2)
{
	int re = *n1 - *n2;
	return re;
}

int mul(int *n1, int *n2)
{
	int re = *n1 * *n2;
	return re;
}

int div(int *n1, int *n2)
{
	int re = *n1 / *n2;
	return re;
}

