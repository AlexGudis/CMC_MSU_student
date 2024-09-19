#include <stdio.h>
#include <string.h>

int main(void){
	int s_len, n;
	char s[80];
	scanf("%d", &n);
	scanf("%s", s);
	s_len = strlen(s);
	n = n % s_len;
	char s2[n + 1];
	for (int i = 0; i < n; i++){
		s2[i] = s[i];
	}
	s2[n] = 0;
	char s1[s_len - n + 1];
	for (int i = n; i < s_len; i++){
		s1[i - n] = s[i];
	}
	s1[s_len - n] = 0;
	for (int i = 0; i < s_len-n; i++) printf("%c", s1[i]);
	for (int i = 0; i < n; i++) printf("%c", s2[i]);
	return 0;
}
