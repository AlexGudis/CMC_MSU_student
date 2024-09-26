#include <stdio.h>

int main(void){
	unsigned int mask[] = {0xffff, 0xff00ff, 0xf0f0f0f, 0x33333333, 0x55555555};
	unsigned int n;
	scanf("%u", &n);
	unsigned int *ptr = mask; // ebx
	ptr += 4;
	unsigned int counter = 1; // ecx
	unsigned int eax = n;
	unsigned int edx = 0;

	do{
		edx = eax;
		eax &= (*ptr);
		edx &= (~(*ptr));
		eax = eax << counter;
		edx = edx >> counter;
		eax = edx | eax;
		counter *= 2;
		ptr -= 1;
	}while(ptr >= mask);
	
	printf("%u", eax);


	return 0;
}
