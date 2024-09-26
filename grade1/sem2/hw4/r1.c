#include <stdio.h>

unsigned int f(unsigned int n){
	if (n == 0){
		return 1;
	}
	else{
		n -= 1;
		return (f(n) + 2 * f(n));
	}
	
}

int main(void){
	unsigned int n;
	scanf("%u", &n);
	printf("%u\n", f(n));
}
