#include <stdio.h>

int main(void){
	int n, m;
	scanf("%d", &n);
	int a[n];
	for (int i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}
	scanf("%d", &m);
	int b[m];
	int ans[n+m];
	for (int i = 0; i < m; i++){
		scanf("%d", &b[i]);
	}
	int i = 0, j_a = 0, j_b = 0;
	while (i < n + m){
		if (j_a < n){
			ans[i] = a[j_a];
			i++;
			j_a++;
		}
		if (j_b < m){
			ans[i] = b[j_b];
			i++;
			j_b++;
		}
	}
	for (int i = 0; i < n+m; i++){
		if (i != n+m -1) printf("%d ", ans[i]);
		else printf("%d", ans[i]);
	}
	return 0;
}
