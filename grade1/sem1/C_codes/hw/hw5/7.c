#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOCK_SIZE 50

int q_c(char c1, char c2){ // Сравнение символов
	if (('a' <= c1 && c1 <= 'z') && ('A' <= c2 && c2 <= 'Z')) return -1;
	else if ( ('a' <= c1 && c1 <= 'z') && ('a' <= c2 && c2 <= 'z') && c1 < c2) return -1;
	else if ( ('A' <= c1 && c1 <= 'Z') && ('A' <= c2 && c2 <= 'Z') && c1 < c2) return -1;
	else if (c1 == c2) return 0;
	else return 1;
}

int q(const char *s1, const char *s2){ // Сравниваем две строки
	int len_s1 = strlen(s1);
	int len_s2 = strlen(s2);
	if (len_s1 < len_s2) {
		for (int k = 0; k < len_s1; k++){
			if (q_c(s1[k],s2[k]) < 0) return -1;
			else if (q_c(s1[k],s2[k]) > 0) return 1;
		}
		return -1; // Строки совпали посимвольно, но длина второй больше
	}
	else if(len_s1 > len_s2){
		for (int k = 0; k < len_s2; k++){
			if (q_c(s1[k], s2[k]) < 0) return -1;
			else if(q_c(s1[k], s2[k]) > 0) return 1;
		}
		return 1; 
	}
	else{
		for (int k = 0; k < len_s1; k++){
			if (q_c(s1[k], s2[k]) < 0) return -1;
			else if(q_c(s1[k], s2[k]) > 0) return 1;
		}
		return 0;
	}

	
}

void pr(const char *s){
	int len = strlen(s);
	for (int k = 0; k < len; k++){
		printf("%c", s[k]);
	}
	printf("\n");
}


int cmpstr(const void* a, const void* b)
{
    const char* aa = *(const char**)a;
    const char* bb = *(const char**)b;
    return q(aa,bb);
}

int main(void){
	int n;
	scanf("%d", &n);
	char* p[n]; // Массив указателей на начало строк
	char drop_it;
	scanf("%c", &drop_it); // Перевод строки после ввода количества строк
	for (int i = 0; i < n; i++){
		int len = BLOCK_SIZE;
		char* s = malloc(sizeof(char) * len);
		int ind = 0;
		while (1){
			scanf("%c", &s[ind]);
			if (s[ind] == '\n') {
				s[ind] = '\0';
				break;
			}
			else{
				ind++;
				if (ind >= len) {
					len *= 5;
					s = realloc(s, sizeof(char) * len);
				}
			}
		}
		p[i] = s;
	}

	qsort(p, n, sizeof(char *), cmpstr);

	for (int i = 0; i < n; i++){
		pr(p[i]);
	}

	//printf("%d\n", q("evr", "evrrwe")); 

	return 0;
}
