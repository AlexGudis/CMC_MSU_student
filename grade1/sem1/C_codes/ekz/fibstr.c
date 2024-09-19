#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *fibocci(char *s){
	int len_s = strlen(s);
	int f1 = 1, f2 = 2, ind_now = 0;
	char *ans_s = malloc(sizeof(char) * 2000); // Точно хватит на хранение результирующей строки
	for (int i = 0; i < len_s; i++){
		if (i == f2 || i == 0 || i == 1){
			ans_s[ind_now] = s[i];
			ind_now++;
			ans_s[ind_now] = ' ';
			ind_now++;
			if (i == f2){
				int tmp = f2;
				f2 = f1 + f2;
				f1 = tmp;
			}
		}
		else{
			ans_s[ind_now] = s[i];
			ind_now++;
		}
		//printf("%d %d\n", f1, f2);
	}
	int ans_len = strlen(ans_s);
	ans_s[ans_len] = 0;
	ans_s = realloc(ans_s, sizeof(char) * (ans_len + 1));
	free(s);
	for (int i = 0; i < ans_len; i++) printf("%c", ans_s[i]);
	return ans_s;

}

int main(void){
	char *s = malloc(sizeof(char) * 2000);
	scanf("%1000s", s);
	int len_s = strlen(s);
	//for (int i = 0; i < len_s; i++) printf("%c", s[i]);
	s[len_s] = 0;
	s = realloc(s, sizeof(char) * (len_s + 1));
	//printf("\n");
	fibocci(s);

	return 0;
}
