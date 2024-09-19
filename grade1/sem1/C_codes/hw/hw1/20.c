#include <stdio.h>
#include <math.h>

int main(void) {
	double a, b, c, d;
	scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
	if (a < b){
		double tmp = b;
		b = a;
		a = tmp;
	}
	if (c < d){
		double tmp = d;
		d = c;
		c = tmp;
	}
	if (a >= c && b >= d){
		printf("YES\n");
	}
	else if (d > b){
		printf("NO\n");
	}else{
		double z = sqrtl(c*c + d*d), sina = d/z, sinb = b/z, cosa = c/z, cosb = sqrtl(z*z - b*b)/z;
		double x = z * (cosb * cosa * cosa - cosb * sina * sina + 2 * sinb * sina * cosa);
		if (x <= a) printf("YES\n");
		else printf("NO\n");
	}
}
