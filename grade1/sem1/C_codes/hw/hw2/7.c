#include <stdio.h>

int main(void){
	int n, x;
	scanf("%d", &n);
	int a[n];
	for (int i = 0; i < n; i++) a[i] = 0;
	for (int i = 0; i < n; i++){
		scanf("%d", &x);
		if (x > 0 && x <= n){
			if (a[x - 1] != 0) {
				printf("No");
				return 0;
			}
			a[x-1]++;
		}
	}
	for (int i = 0; i < n; i++){
		if (a[i] == 0){
			printf("No");
			return 0;
		}
	}
	//for (int i = 0; i < n; i++) printf("%d\n", a[i]);
	printf("Yes");
	return 0;
}
