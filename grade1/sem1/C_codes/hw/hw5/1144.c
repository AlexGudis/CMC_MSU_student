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

void hyper(int n, int digits_now, int x){
	int check = is_simple(x);
	if (digits_now == n && check) printf("%d ", x);
	else if ((digits_now < n && check) || x == 0 ){
		int base = x;

		x = x * 10 + 1;
		hyper(n, digits_now+1, x);
		x = base;

		x = x * 10 + 2;
		hyper(n, digits_now+1, x);
		x = base;
	
		x = x * 10 + 3;
		hyper(n, digits_now+1, x);
		x = base;

		x = x * 10 + 5;
		hyper(n, digits_now+1, x);
		x = base;

		x = x * 10 + 7;
		hyper(n, digits_now+1, x);
		x = base;

		x = x * 10 + 9;
		hyper(n, digits_now+1, x);
		x = base;

	}
}

int main(void){
	int n;
	scanf("%d", &n);
	hyper(n, 0, 0);

	return 0;
}
