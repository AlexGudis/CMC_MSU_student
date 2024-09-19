#include <stdio.h>
#include <stdlib.h>


int main(void){
	int *p;
	p = malloc(sizeof(int) * 3);
	int cnt = 0;
	int ans = 0;
	int last = -1;
	while (1){
		scanf("%d", &p[cnt]);
		if (p[cnt] == 0){
			break;
		}else{
			last = p[cnt];
			cnt++;
			p = realloc(p, sizeof(int) * cnt * 3);
		}
	}
	
	//printf("%d\n", last);
	for (int i = 0; i < cnt - 1; i++){
		if (p[i] < last) ans++;
	}

	free(p);
	printf("%d", ans);


	return 0;	
}
