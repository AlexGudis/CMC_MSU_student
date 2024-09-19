#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(void){
	char s[10000];
	int s_len;
	scanf("%s", s);
	//for (int i = 0; s[i] != 0; i++) printf("%c\n", s[i]);
	s_len = strlen(s);
	//printf("%d\n", s_len);
	for (int t = 1; t <= s_len; t++){
		int flag = 1;
		for (int i = 0; i < s_len; i++){
			if (t <= i){
				if (s[i] != s[i - t]){
					flag = 0;
					break;
				}
			}
		}
		if (flag) printf("%d ", t);
	}
	return 0;
}
