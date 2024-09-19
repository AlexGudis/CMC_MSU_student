#include <stdio.h>


int in(int a[], int x, int n){
	for (int i = 0; i < n; i++){
		if (a[i] == x) return i;
	}
	return 0;
}

int nu(int a[], int n){
	for (int i = 0; i < n; i++){
		if (!a[i]) return i;
	}
}

int main(void){
	int n = 0;
	scanf("%d", &n);
	int a[n];
	for (int i = 0; i < n; i++) a[i] = 0;
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		int check = in(a, x,n);
		if (check) a[check] = 0;
		else{
			int zero = nu(a, n);
			a[zero] = x;
		}
	}
	for (int i = 0; i < n; i++){
		if (a[i]) printf("%d ", a[i]);
	}
	return 0;
}
