#include <stdio.h>
#include <string.h>

int main(void){
	char s1[1000], s2[1000];
	scanf("%s", s1);
	scanf("%s", s2);

	int n1 = strlen(s1);
	int n2 = strlen(s2);
	int ans = 0;

	if (n1 > n2){
		printf("check_1\n");
		for (int i = 0; i < n1; i++){
			int check = 1;
			for (int j = 0; j < n2; j++){
				if (s1[i+j] != s2[j]){
					check = 0;
					break;
				}
			}
			if (check == 1){
				ans = 2; // Вторая сторка является подстрокой первой строки
				break;
			}
		}
	}

	else{
		printf("check_2\n");
		for (int i = 0; i < n2; i++){
			int check = 1;
			for (int j = 0; j < n1; j++){
				if (s2[i+j] != s1[j]){
					check = 0;
					break;
				}
			}
			if (check == 1){
				ans = 1; // Первая сторка является подстрокой второй строки
				break;
			}
		}
	}

	if (ans == 1){
		printf("1 2\n");
	}
	else if (ans == 2){
		printf("2 1\n");
	}
	else{
		printf("0\n");
	}

	return 0;
}
