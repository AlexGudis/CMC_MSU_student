#include <stdio.h>


int main(void){
	long long n, m;
	scanf("%lld", &n);
	long long a[n];
	for (long long i = 0; i < n; i++) scanf("%lld", &a[i]);
	scanf("%lld", &m);
	long long x[m];
	for (long long i = 0; i < m; i++) scanf("%lld", &x[i]);

	for (long long i = m - 1; i > -1; i--){
		long long res = 0;
		long long tmp = x[i];
		for (long long j = 0; j < n; j++){
			if (j == 0){
				res += a[j];
			}else{
				res += a[j] * x[i];
				x[i] *= tmp;
			}
		}
		if (i != 0) printf("%lld ", res);
		else printf("%lld", res);
	}
}
