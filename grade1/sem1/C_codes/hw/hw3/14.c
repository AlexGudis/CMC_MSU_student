#include <stdio.h>
#include <stdlib.h>
int get_coords(char c){
	return c - 'A';

}

int main(void){
	int base_i = 0, base_j = 0, cnt = 0;
	char ans = 'N';
	while (1){
		// cnt % 2 == 0 - выставление ферзя по координатам коня
		// cnt % 2 == 1 - выставление коня по координатам ферзя
		char c;
		int new_i, new_j;
		if (cnt != 0){ // Считываем символ переноса строки
			scanf("%c", &c);
		}
		scanf("%c", &c);
		if (c == 'X') {
			if (ans == 'N' && base_j == 7 && base_i == 7){
				cnt--;
				if (cnt % 2 == 0) ans = 'G';
				else ans = 'T';
			}
			if (ans == 'N' && (base_j != 7 || base_i != 7)) ans = 'C';
			break;
		}
		scanf("%d", &new_i);
		new_i--;
		new_j = get_coords(c);
		
		if (base_i == 7 && base_j == 7) { // Они дошли до H8, но зачем-то продолжили играть дальше
			ans = 'C';
		}
		//printf("ans now: %c\n", ans);
		//printf("base: %d %d\n", base_i, base_j);
		//printf("new: %d %d\n", new_i, new_j);
		//printf("\n");
	
	
		if (cnt % 2 == 0){
			int flag = 0;
			if (abs(new_i - base_i) == 1){
				if (abs(new_j - base_j) == 2){
					flag = 1;
				}
			}
			if (abs(new_i - base_i) == 2){
				if (abs(new_j - base_j) == 1){
					flag = 1;
				}
			}
			if (!flag) ans = 'C';
		}
		else{
			int flag = 0;
			for (int check = 1; check < 8; check++){
				if (abs(new_i - base_i) == check && abs(new_j - base_j)==0){
					flag = 1;
					break;
				}			
				if (abs(new_j - base_j) == check && abs(new_i - base_i)==0){
					flag = 1;
					break;
				}
				if (abs(new_i - base_i) == check && abs(new_j - base_j)==check){
					flag = 1;
					break;
				}
			} 
			if (!flag) ans = 'C';
		}
		base_i = new_i;
		base_j = new_j;
		cnt++;
	}
	if (ans == 'C') printf("Cheaters");
	if (ans == 'G') printf("Garik");
	if (ans == 'T') printf("Tolik");
	return 0;
}
