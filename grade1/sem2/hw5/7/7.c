#include <stdio.h>
#include <string.h>

int main(void){
	int n;
	scanf("%d", &n);
	char s_unic[500][11]; // Список различных строк
	int arr_len = 0; // Количество уникальных строк
	while (n > 0){
		char s[11];
		scanf("%s", s);
		int check = 1; // Покажет нам, есть ли данная строка в списке уникальных строк
		for (int i = 0; i < arr_len; i++){
			if (strcmp(s_unic[i], s) == 0){ // 0 - строки эквивалентны
				check = 0;
				break;
			}
		}

		if (check){ // Значит, сравнив эту строку со всеми остальными мы не нашли совпадений
			strncpy(s_unic[arr_len], (const char *) s, 10);
			arr_len++;
		}
		n--;
	}
	printf("%d\n", arr_len);

	return 0;
}
