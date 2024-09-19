#include <stdio.h>
#define MAX 1000000
//3^25 = 847_288_609_443 >> 1_000_000_000



int main(void) {
	long long arr[25], i = 0, ans = 0, q = 1, left = 0, right = 0, a, len_a;
	scanf("%lld", &a);
	while (a > 0){
		arr[i] = a % 3;
		a /= 3;
		i++;
	}
	len_a = i;
	/*i = 0;
	while (arr[i] != 4){
		printf("%lld", arr[i]);
		i++;
	}
	printf("\n");*/

	i = 0;
	while (i < len_a){
		if (arr[i] == 2){
			if (i != len_a - 1){
				arr[i+1]++;
				arr[i] = -1;
			}
			else{
				arr[i+1] = 1;
				arr[i] = -1;
				len_a++;
			}
		}
		else if (arr[i] == 3){
			if (i != len_a - 1){
				arr[i+1]++;
				arr[i] = 0;
			}
			else{
				arr[i+1] = 1;
				arr[i] = 0;
				len_a++;
			}
		}
		//printf("%lld", arr[i]);
		i++;
	}
	//printf("\n");

	i = 0;
	while (i < len_a){
		if (arr[i] == -1){
			left += q;
			ans++;
		}
		else if (arr[i] == 1){
			right += q;
			ans++;
		}
		i++;
		q*=3;
	}
	//printf("%lld\n", right - left);

	if (right > MAX || left > MAX) printf("%d", -1);
	else printf("%lld", ans);
}
