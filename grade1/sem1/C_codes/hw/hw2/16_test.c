#include <stdio.h>

int main(void){
	int n, x1, x2, x3;
	scanf("%d", &n);
	int a[n];
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	int result = 0;
	for (int i = 0; i < n; i++){
		result ^= a[i];
	}
	printf("%d", result);
	for (int i = 0; i < 32; i++){
		if ((result >> i) & 1){
			int check = 0;
			for (int j = 0; j < n; j++){
				if ((a[j]) >> i) & 1){
					check ^= a[i];
				}
			}
			if (check == result){
				x1 = x1 | (1 << i);
				x2 = x2 | (1 << i);
				x3 = x3 | (1 << i);
			}
			else {
				x1 = x1 | (1 << i);
				x2 = x2 & (0 << i);
				x3 = x3 & (0 << i);
			}
		}else{
			int check = 0;
			for (int k = 0; k < n; k++){
				if (!((a[k] >> i) & 1)){
					check = ^= a[k];
				}
			}
			if (check != result){
				x1 = x1 & (0 << i);
				x2 = x2 | (1 << i);
				x3 = x3 | (1 << i);
			}
			else{
				x1 = x1 & (0 << i);
				x2 = x2 & (0 << i);
				x3 = x3 & (0 << i);
			}
		}
	}
	int result2 = result ^ x1;

	return 0;
}
