#include <stdio.h>

int main(void){
	int n;
	scanf("%d", &n);
	long long a[n][2*n];
	long long  a_t[n][2*n];
	for (int i = 0; i < n; i++){
		for (int j = 0; j < 2*n; j++){
			long long x;
			scanf("%lld", &x);
			a[i][j] = x;
		}
	}

	for (int i = 0; i < n; i++){
		for (int j = 0; j < 2*n; j+=2){
			a_t[i][j] = a[j/2][2*i];
			a_t[i][j+1] = a[j/2][2*i+1]*(-1);
		}
	}

	for (int i = 0; i < n; i++){
		for (int j = 0; j < 2*n; j++){
			printf("%lld ", a_t[i][j]);
		}
		printf("\n");
	}

	return 0;
}
