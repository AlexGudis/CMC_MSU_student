#include <stdio.h>
#include <string.h>

int get_cnt(int n, char s[n][21], char before, int cnt, int max_cnt){ // Функция, в которой находим длину цепи
	for (int i = 0; i < n; i++){
		if (s[i][0] == before){ // Сравниваем первый символ с предыдущим по рекурсии последним символом какого-то слова
			cnt++;
			char start = s[i][0];
			char base_before = before; // Последняя буква нашего первого слова из ф-ции main
			char before = s[i][strlen(s[i])-1];
			s[i][0] = '-';
			int check = get_cnt(n,s,before,cnt, cnt);
			if (check > max_cnt) max_cnt = check;
			cnt--;
			s[i][0] = start;
			before = base_before; 
		}
	}
	// Мы составили всевозможные комбинации из имеющихся слов со стартом на слове из цикла в main
	return max_cnt;
}

int main(void){
	int n;
	int ans = 1; // Мы всегда сможем составить комбинацию из хотя бы одного слова
	scanf("%d", &n);
	char s[n][21];
	for (int i = 0; i < n; i++) {
		scanf("%s", s[i]);
	}

	for (int i = 0; i < n; i++) {
		char start = s[i][0];
		char before = s[i][strlen(s[i]) - 1];
		s[i][0] = '-';
		int check = get_cnt(n, s, before, 1, 1);
		if (check > ans) ans = check;
		s[i][0] = start;

	}


	//for (int i = 0; i < n; i++) printf("%s\n", s[i]);
	if (n == 0) printf("0");
	else printf("%d\n", ans);
	for (int i = 0; i < n; i++) {
		char start = s[i][0];
		char before = s[i][strlen(s[i]) - 1];
		s[i][0] = '-';
		int check = get_cnt(n, s, before, 1, 1);
		s[i][0] = start;
		if (check == ans) {
			printf("%s\n", s[i]);
		}

	}
	return 0;
}
