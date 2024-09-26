#include<stdio.h>

unsigned int f(unsigned int n){  // Функция будет считать кол-во единиц
	if (!n) return 0;
	return (1 & n) + f(n>>1);


}


int main(void){
	unsigned int n;
	scanf("%u", &n);
	printf("%u\n", 32 - f(n));
	return 0;
}
