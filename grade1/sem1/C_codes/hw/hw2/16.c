#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
	int n, cnt = 0;
	scanf("%d", &n);
	int a[50000];
	for (int i = 0; i < 50000; i++) a[i] = 0;
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		int ind = x / 32, ind_plus = x % 32, base = a[ind];
		//printf("a[ind] before: %d ::: x == %d\n", a[ind], x);
		if ((a[ind] >> ind_plus) & 1){
			a[ind] = base;
			a[ind] -= pow(2, ind_plus);
		}
		else{
			a[ind] = base;
			a[ind] = a[ind] | (1 << ind_plus);
		}
		//printf("a[ind] after: %d \n", a[ind]);
	}
	//printf("\n");
	for (int i = 0; i < 50000; i++){
		int base = a[i];
		//printf("a[i] = %d\n", a[i]);
		for (int j = 0; j < 32; j++){
			if ((a[i] >> j) & (1)){
				printf("%d    ", 32 * i + j);
				cnt++;
			}
			a[i] = base;
		}
		if (cnt == 3) break;
	}
	return 0;
}
