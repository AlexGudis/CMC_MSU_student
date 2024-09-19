#include <stdio.h>
#include <math.h>

int main(void){
	int n;
	scanf("%d", &n);
	double a[n][4];
	for (int i = 0; i < n; i++){
		scanf("%lf %lf %lf %lf", &a[i][0], &a[i][1], &a[i][2], &a[i][3]);
	}
	for (int i = 0; i < n - 1; i++){
		for (int j = i + 1; j < n; j++){
			double len = sqrt( (a[j][0]-a[i][0])*(a[j][0]-a[i][0]) + (a[j][1]-a[i][1])*(a[j][1]-a[i][1]) + (a[j][2]-a[i][2])*(a[j][2]-a[i][2]));
			if (len <= (a[i][3] + a[j][3])) {
				printf("YES");
				return 0;
			}
		}
	}
	printf("NO");
	return 0;
}
