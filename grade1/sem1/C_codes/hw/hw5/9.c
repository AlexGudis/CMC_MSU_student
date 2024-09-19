#include <stdio.h>

void pr(int m, int n, int v[n*m][2], int ind_end){
	for (int i = 0; i < ind_end; i++){
		printf("%d %d\n", v[i][0], v[i][1]);
	}
}	

int main(void){
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	int pole[n][m];
	int virus[n*m][2];
	int ind_end = 0;

	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			pole[i][j] = -1;
		}
	}

	for (int i = 0; i < k; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		x-=1;
		y-=1;
		pole[y][x] = 0;
		virus[i][0] = y;
		virus[i][1] = x;
	}
	ind_end = k; // Индекс конца нашей очереди в общем массиве всех вирусов
	for (int i = 0; i < ind_end; i++){
		int y = virus[i][0];
		int x = virus[i][1];
		if (x + 1 < m){
			if (pole[y][x+1] == -1) {
				pole[y][x+1] = pole[y][x] + 1;
				virus[ind_end][0] = y;
				virus[ind_end][1] = x+1;
				ind_end++;
			}
		}
		if (x - 1 >= 0){
			if (pole[y][x-1] == -1) {
				pole[y][x-1] = pole[y][x] + 1;
				virus[ind_end][0] = y;
				virus[ind_end][1] = x-1;
				ind_end++;
			}
		}
		if (y + 1 < n){
			if (pole[y+1][x] == -1) {
					pole[y+1][x] = pole[y][x] + 1;
					virus[ind_end][0] = y + 1;
					virus[ind_end][1] = x;
					ind_end++;
			}
		}
		if (y - 1 >= 0){
			if (pole[y-1][x] == -1) {
				pole[y-1][x] = pole[y][x] + 1;
				virus[ind_end][0] = y - 1;
				virus[ind_end][1] = x;
				ind_end++;
			}
		}
	}	

	int max = 0;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			if (pole[i][j] > max) max = pole[i][j];
		}
	}
	printf("%d", max);

	return 0;
}
