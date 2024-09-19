#include <stdio.h>
#include <math.h>

int main(void){
	int n;
	scanf("%d", &n);
	double s[n], a[n], v = 0, ans = 0;
	for (int i = 0; i < n; i++) scanf("%lf", &s[i]);
	for (int i = 0; i < n; i++) scanf("%lf", &a[i]);

	for (int i = 0; i < n; i++){
		if (a[i] > 0.00000001 || a[i] < -0.00000001){
			ans += (-2*v + sqrt(4*v*v + 8*a[i]*s[i]))/(2*a[i]);
			//printf("s[i] = %lf ::: a[i] = %lf ::: v = %lf\n", s[i], a[i], v);
			double check_vo = v;
			v = sqrt(2*a[i]*s[i] + check_vo*check_vo);
		}else{
			ans += (s[i]/v);
		}
	}
	printf("%.4lf", ans);
	return 0;
}
