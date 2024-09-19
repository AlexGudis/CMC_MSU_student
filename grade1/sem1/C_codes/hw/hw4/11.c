#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

void pr(int a_ind, char a_str[2001], int b_ind, char b_str[2001], char op){
	long long a = atoi(a_str);
	long long b = atoi(b_str);
	long long ans = 0;
	if (op == '+') {
		ans = a + b;
		if (abs(ans) <= 120000) printf("%lld %c %lld = %lld\n", a, op, b, ans);
	}if (op == '-'){
		ans = a - b;
		if (abs(ans) <= 120000) printf("%lld %c %lld = %lld\n", a, op, b, ans);
	}if (op == '*') {
		ans = a * b;
		if (abs(ans) <= 120000) printf("%lld %c %lld = %lld\n", a, op, b, ans);
	}if (op == '/') {
		if (b != 0) {
			ans = a / b;
			if (abs(ans) <= 120000) printf("%lld %c %lld = %lld\n", a, op, b, ans);		
		}
	}
}

int main(void){
	char s[2001];
	scanf("%s", s);
	int s_len = strlen(s);
	char a_str[2001];
	int a_ind = 0;
	char b_str[2001];
	int b_ind = 0;
	char op = '?';
	int i = 0;
	for (int j = i; j < s_len; j++){
		if (isdigit(s[j])){
			if (op == '?'){
				a_str[a_ind] = s[j];
				a_ind++;
			}
			else {
				b_str[b_ind] = s[j];
				b_ind++;
			}
		}
		else if (s[j] == '-' || s[j] == '*' || s[j] == '/' || s[j] == '+'){
			if (a_ind != 0 && b_ind == 0 && op == '?'){
				op = s[j];
			}
			else if (a_ind != 0 && b_ind != 0){
				pr(a_ind, a_str, b_ind, b_str, op);
				for (int k = 0; k < a_ind; k++) a_str[k] = '?';
				a_ind = b_ind;
				for (int k = 0; k < a_ind; k++) a_str[k] = b_str[k];
				for (int k = 0; k < a_ind; k++) b_str[k] = '?';
				b_ind = 0;
				op = s[j];
			}
			else{
				for (int k = 0; k < a_ind; k++) a_str[k] = '?';
				for (int k = 0; k < b_ind; k++) b_str[k] = '?';
				a_ind = 0;
				b_ind = 0;
				op = '?';
			}
		}
		else{
			if (a_ind != 0 && b_ind != 0 && op != '?') pr(a_ind, a_str, b_ind, b_str, op);
			for (int k = 0; k < a_ind; k++) a_str[k] = '?';
			for (int k = 0; k < b_ind; k++) b_str[k] = '?';
			a_ind = 0;
			b_ind = 0;
			op = '?';
		}
	}
	if (a_ind != 0 && b_ind != 0 && op != '?') pr(a_ind, a_str, b_ind, b_str, op);

	return 0;
}

