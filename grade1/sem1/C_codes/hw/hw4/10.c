#include <stdio.h>
#include <string.h>

int min(int a, int b){
	if (a < b) return a;
	return b;
}

int get_func(int len_s, char s[len_s]){
	int k = 0;
	int p[len_s];
	p[0] = 0;
	for (int i = 0; i < len_s; i++) p[i] = 0;
	for (int i = 1; i < len_s; i++){
		k = p[i-1];
		while (k > 0 && s[i] != s[k]){
			k = p[k - 1];
		}
		if (s[i] == s[k]){
			k++;
		}
		p[i] = k;
	}

	//for (int i = 0; i < len_s; i++){
	//	printf("%d ", p[i]);
	//}
	//printf("\n");

	return p[len_s-1];
}


int main(void){
	char s1[1000001], s2[1000001], s3[2000002], s4[2000002];
	scanf("%s", s1);
	scanf("%s", s2);
	int len_s1 = strlen(s1);
	int len_s2 = strlen(s2);

	for (int i = 0; i < len_s1; i++){
		s3[i] = s1[i];
	}
	s3[len_s1] = ' ';
	for (int i = len_s1 + 1; i < len_s1 + len_s2 + 1; i++){
		s3[i] = s2[i - len_s1 - 1];
	}
	s3[len_s1 + len_s2 + 1] = '\0';
	int len_s3 = strlen(s3);
	//printf("%d\n", len_s3);
	//for (int i = 0; i < len_s3; i++) printf("%c", s3[i]);
	printf("%d ", get_func(len_s3, s3));



	for (int i = 0; i < len_s2; i++){
		s4[i] = s2[i];
	}
	s4[len_s2] = ' ';
	for (int i = len_s2 + 1; i < len_s2 + len_s1 + 1; i++){
		s4[i] = s1[i - len_s2 - 1];
	}
	s4[len_s1 + len_s2 + 1] = '\0';
	int len_s4 = strlen(s4);
	printf("%d", get_func(len_s4, s4));

	

	return 0;
}
