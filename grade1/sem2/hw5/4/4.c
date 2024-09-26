#include <stdio.h>

int main(void){
	FILE *f = fopen("data.in", "r");
	int n = 0;
	int x;
	while (fscanf(f, "%d", &x) != -1){
		n++;
	} 
	printf("%d", n);


	return 0;
}
