#include <stdio.h>
#include <stdlib.h>

int get_med(int a, int b, int c){
	if (a > b){
		int tmp = b;
		b = a;
		a = tmp;
	}
	if (b > c){
		int tmp = c;
		c = b;
		b = tmp;
	}
	if (a > b){
		int tmp = b;
		b = a;
		a = tmp;
	}
	return b;

}


void solve(int a[], int  n){
	if (n == 1){
		printf("%d", a[0]);
	}
	else{
		int b[n - 2];
		for (int i = 0; i < n - 2; i++){
			b[i] = get_med(a[i], a[i+1], a[i+2]);
		}
		solve(b, n-2);
	}
}

int main(void){
	int n;
	scanf("%d", &n);
	int a[n];
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	solve(a, n);

}
