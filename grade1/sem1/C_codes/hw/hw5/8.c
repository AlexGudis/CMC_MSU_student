#include <stdio.h>
#define DEST -17841

void pr(int n, int pole[n][n]){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			printf("%d  ", pole[i][j]);
		}
		printf("\n");
	}
	printf("###############\n");
}


int main(void){
	int n, sxn, syn, xk, yk;
	scanf("%d %d %d %d %d", &n, &sxn, &syn, &xk, &yk);
	int ans = n*n; // Наш ответ
	int pole[n][n];
	sxn--; syn--; xk--; yk--;
	int steps[n*n][2]; // Наша очередь ходов
	steps[0][0] = sxn;
	steps[0][1] = syn;
	int ind_end = 1;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			pole[i][j] = -1;
		}
	}
	pole[sxn][syn] = 0;
	pole[xk][yk] = DEST;
	
	for (int i = 0; i < ind_end; i++){
		//pr(n, pole);
		int xn = steps[i][0];
		int yn = steps[i][1];
		if (xn + 2 < n && yn + 1 < n){ // 1
			if (pole[xn+2][yn+1] <= -1){
				if (pole[xn+2][yn+1] == DEST){
					ans = pole[xn][yn] + 1;
					break;
				}
				pole[xn+2][yn+1] = pole[xn][yn] + 1;
				steps[ind_end][0] = xn+2;
				steps[ind_end][1] = yn+1;
				ind_end++;
			}
		}

		if (xn + 1 < n && yn + 2 < n){ // 2
			if (pole[xn+1][yn+2] <= -1){
				if (pole[xn+1][yn+2] == DEST){
					ans = pole[xn][yn] + 1;
					break;
				}
				pole[xn+1][yn+2] = pole[xn][yn] + 1;
				steps[ind_end][0] = xn+1;
				steps[ind_end][1] = yn+2;
				ind_end++;
			}
		}

		if (xn - 1 >= 0 && yn + 2 < n){ // 3
			if (pole[xn-1][yn+2] <= -1){
				if (pole[xn-1][yn+2] == DEST){
					ans = pole[xn][yn] + 1;
					break;
				}
				pole[xn-1][yn+2] = pole[xn][yn] + 1;
				steps[ind_end][0] = xn-1;
				steps[ind_end][1] = yn+2;
				ind_end++;
			}
		}

		if (xn - 2 >= 0 && yn + 1 < n){ // 4
			if (pole[xn-2][yn+1] <= -1){
				if (pole[xn-2][yn+1] == DEST){
					ans = pole[xn][yn] + 1;
					break;
				}
				pole[xn-2][yn+1] = pole[xn][yn] + 1;
				steps[ind_end][0] = xn-2;
				steps[ind_end][1] = yn+1;
				ind_end++;
			}
		}

		if (xn - 2 >= 0 && yn - 1 >= 0){ // 5
			if (pole[xn-2][yn-1] <= -1){
				if (pole[xn-2][yn-1] == DEST){
					ans = pole[xn][yn] + 1;
					break;
				}
				pole[xn-2][yn-1] = pole[xn][yn] + 1;
				steps[ind_end][0] = xn-2;
				steps[ind_end][1] = yn-1;
				ind_end++;
			}
		}
		if (xn - 1 >= 0 && yn - 2 >= 0){ // 6
			if (pole[xn-1][yn-2] <= -1){
				if (pole[xn-1][yn-2] == DEST){
					ans = pole[xn][yn] + 1;
					break;
				}
				pole[xn-1][yn-2] = pole[xn][yn] + 1;
				steps[ind_end][0] = xn-1;
				steps[ind_end][1] = yn-2;
				ind_end++;
			}
		}
		
		if (xn + 1 < n && yn - 2 >= 0){ // 7
			if (pole[xn+1][yn-2] <= -1){
				if (pole[xn+1][yn-2] == DEST){
					ans = pole[xn][yn] + 1;
					break;
				}
				pole[xn+1][yn-2] = pole[xn][yn] + 1;
				steps[ind_end][0] = xn+1;
				steps[ind_end][1] = yn-2;
				ind_end++;
			}
		}

		if (xn + 2 < n && yn - 1 >= 0){ // 8
			if (pole[xn+2][yn-1] <= -1){
				if (pole[xn+2][yn-1] == DEST){
					ans = pole[xn][yn] + 1;
					break;
				}
				pole[xn+2][yn-1] = pole[xn][yn] + 1;
				steps[ind_end][0] = xn+2;
				steps[ind_end][1] = yn-1;
				ind_end++;
			}
		}
		
	}

	if (sxn == xk && syn == yk) printf("0");
	else if (ans != n*n) printf("%d", ans);
	else printf("-1");

	return 0;
}
