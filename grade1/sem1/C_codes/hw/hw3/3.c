#include <stdio.h>

void reverse(void){
	int n;
	scanf("%d", &n);
	if (n != 0){
		reverse();
		printf("%d", n);
		printf(" ");
	}
}

int main(void){
	reverse();
	return 0;
}

