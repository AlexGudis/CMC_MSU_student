#include <stdio.h>

int in(int a[8], int check){
	for (int j = 0; j < 8; j++){
		if (a[j] == check){
			return j;
		}
	}
	return -1;
}

int max(int a[8]){
	int now_max = -1;
	for (int j = 0; j < 8; j++){
		if (a[j] > now_max) now_max = a[j];
	}
	return now_max;
}

int sum(int a[8], int b[8]){
	int summ = 0;
	for (int i = 0; i < 8; i++) {
		summ += a[i];
		summ += b[i];
	}
	return summ;
}


int main(void){
	int a[8], b[8];
	for (int i = 0; i < 8; i++) scanf("%d", &a[i]);
	for (int i = 0; i < 8; i++) scanf("%d", &b[i]);
	//for (int i = 0; i < 8; i++) printf("%d ", first[i]);
	//printf("\n");
	//for (int i = 0; i < 8; i++) printf("%d ", second[i]);
	if (max(a) != max(b)){
		printf("-1");
		return 0;
	}
	int summ = sum(a, b);
	for (int i = 0; i < 8; i++){
		int ind = in(b, a[i]);
		if (ind != -1){
			summ -= a[i];
			a[i] = 0;
			b[ind] = 0;
		}
	}
	printf("%d", summ);
	return 0;
}
