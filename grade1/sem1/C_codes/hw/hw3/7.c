#include <stdio.h>
#include<stdlib.h>
#include <math.h>

/*
double get_len(int x1, int y1, int x2, int y2){
	return sqrtl((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

long double get_s(long double a, long double b,long double c){
	long double p = ((a+b+c)/2);
	return sqrtl(p*(p-a)*(p-b)*(p-c));
}

*/
int not_q(int x1, int y1, int x2, int y2){
	if(x1 == x2 && y1 == y2) return 0;
	return 1;
}


int main(void){
	int n;
	scanf("%d", &n);
	int a[n][2];
	long double ans = 0;
	for (int i = 0; i < n; i++) scanf("%d %d", &a[i][0], &a[i][1]);
	for (int i = 0; i < n - 2; i++){
		for (int j = i + 1; j < n - 1; j++){
			if (not_q(a[i][0],a[i][1],a[j][0],a[j][1])){
				for (int k = j + 1; k < n; k++){
					//long double check = abs( (a[i][0] - a[k][0])*(a[j][1]-a[k][1]) - (a[j][0]-a[k][0])*(a[i][1]-a[k][1])  )/2;
					long double check = fabs( (a[j][0]-a[i][0])*(a[k][1]-a[i][1]) - (a[k][0]-a[i][0])*(a[j][1]-a[i][1]) )/2;
					if (check > ans) ans = check;
				}
			}
		}
	}
	printf("%.6Lf", ans);
	return 0;
}
