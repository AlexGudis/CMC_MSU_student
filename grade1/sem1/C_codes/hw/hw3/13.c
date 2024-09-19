#include <stdio.h>


void f(int n, int start, int cnt, int base_k, int ans[base_k]){
	cnt++;
	if (cnt == base_k) {
		for (int i = 0; i < base_k; i++) printf("%d ", ans[i]);
		printf("\n");
	}
	else{
		while (n - start + cnt >= base_k && start < n - 1){
			start++;
			ans[cnt] = start;
			f(n, start, cnt, base_k, ans);
		}
	}
}


int main(void){
	int n, k, st = 0, cnt = 0;
	scanf("%d %d", &n, &k);
	int ans[k];
	while (n - st >= k  && st < n){
		//printf("YEEES start: %d\n", st);
		ans[cnt] = st;
		f(n, st, cnt, k, ans);
		st++;
	}
}
