#include <stdio.h>
#include <math.h>

int is_simple(int x){
	if (x == 1) return 0;
	if (x == 2) return 1;
	for (int i = 2; i < (int)sqrt(x) + 1; i++){
		if (x % i == 0) return 0;
	}
	return 1;
}

int hyper_simple(int x){
	while (x > 0){
		if ((x / 10 != 0) && (x % 2 == 0|| x % 10 == 5)) return 0;
		else if (!is_simple(x)) return 0;
		x /= 10;
	}
	return 1;
}

int main(void){
	int n;
	scanf("%d", &n);
	if (n == 1) printf("2 3 5 7");
	else{
		for (int i = pow(10, n - 1) + 1; i < pow(10, n); i += 2){
			if (i % 10 != 5  || i == 5){ // Сразу отбросим заведомо непростые числа 
				if (hyper_simple(i)) printf("%d ", i);	
			}
		}
	}
	return 0;
}
