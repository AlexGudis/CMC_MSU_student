#include<stdio.h>
static int func(int acc, int x){
	return acc + x;
}
int (*ex_function)(int, int) = func;

int calculate(int num, int *numbers);

int seq[5] = {4, 8, 16, 23, 42};
int main(void){
	int result = calculate(6, seq);
	printf("%d\n", result);
	return 0;
}
