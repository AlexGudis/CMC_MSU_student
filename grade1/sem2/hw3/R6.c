#include <stdio.h>
#include <limits.h>

int main(void){

	unsigned int minn = 0xFFFFFFFF;
	unsigned int min_now = 0;

	scanf("%u", &min_now);
	while (min_now){
		if (min_now <= minn){
			minn = min_now;
		}
		scanf("%u", &min_now);
	}
	printf("%u\n", minn); 
	return 0;
}
