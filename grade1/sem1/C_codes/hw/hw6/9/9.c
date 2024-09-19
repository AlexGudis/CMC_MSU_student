#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAX_SIZE 1100000


int go(uint32_t *a, uint32_t a_len, int type_now, int cur_i){
	//printf("cur_i: %d \n", cur_i);
	//printf("type_now: %d\n", type_now);
	//printf("########\n");
	//printf("\n");
	if (cur_i == 0 || type_now == -2){ // Корень дерева, от него будем отталкиваться или тип все еще не определен
				
		// По фатку именно на этом этапе идет определение типа дерева
		if (2*cur_i+1 < a_len && a[2*cur_i+1] > a[cur_i]){
			if (type_now == -2) type_now = 1;
			else if(type_now != 1) return 0;
			int check = go(a, a_len, type_now, 2*cur_i+1);
			if (check != type_now) return 0; // Значит где-то по дереву ниже наша сортировка нарушилась
		}else if (2*cur_i+1 < a_len && a[2*cur_i+1] < a[cur_i]){
			if (type_now == -2) type_now = -1;
			else if(type_now != -1) return 0;
			int check = go(a, a_len, type_now, 2*cur_i+1);
			if (check != type_now) {
				//printf("ans_i: %d\n", cur_i);
				//printf("ans_check: %d\n", check);
				//printf("ans_type: %d\n", type_now);
				return 0;
			}
		}else if (2*cur_i+1 < a_len && a[2*cur_i+1] == a[cur_i]){
			type_now = go(a, a_len, type_now, 2*cur_i+1); // Не изменяем наш тип, а присваиваем его сюда
			if (!type_now) return 0; // Значит где-то ниже по дереву установился и нарушился порядок
		}

		if (2*cur_i+2 < a_len && a[2*cur_i+2] > a[cur_i]){
			if (type_now == -2) type_now = 1;
			else if (type_now != 1) return 0;
			int check = go(a, a_len, type_now, 2*cur_i+2);
			if (check != type_now) return 0;
		}else if(2*cur_i+2 < a_len && a[2*cur_i+2] < a[cur_i]){
			if (type_now == -2) type_now = -1;
			else if (type_now != -1) return 0;
			int check = go(a, a_len, type_now, 2*cur_i+2);
			if (check != type_now) return 0;
		}else if (2*cur_i+2 < a_len && a[2*cur_i+2] == a[cur_i]){
			type_now = go(a, a_len, type_now, 2*cur_i+2);
			if (!type_now) return 0;
		}

	}
	else{ // Мы не в корне дерева, тип точно определен
		if (2*cur_i+1 < a_len && a[2*cur_i+1] > a[cur_i]){
			if (type_now != 1) return 0;
			int check = go(a, a_len, type_now, 2*cur_i+1);
			if (check != type_now) return 0;
		}else if (2*cur_i+1 < a_len && a[2*cur_i+1] < a[cur_i]){
			if (type_now != -1) return 0;
			int check = go(a, a_len, type_now, 2*cur_i+1);
			if (check != type_now) {
				//printf("yeees\n");
				return 0;
			}
		}else if (2*cur_i+1 < a_len && a[2*cur_i+1] == a[cur_i]){
			type_now = go(a, a_len, type_now, 2*cur_i+1);
			if (!type_now) return 0;
		}

		if (2*cur_i+2 < a_len && a[2*cur_i+2] > a[cur_i]){
			//printf("yeees cur2_i: %d\n", cur_i);
			//printf("type in 2: %d\n", type_now);
			//printf("hight\n");
			if (type_now != 1) return 0;
			int check = go(a, a_len, type_now, 2*cur_i+2);
			if (check != type_now) return 0;
		}else if(2*cur_i+2 < a_len && a[2*cur_i+2] < a[cur_i]){
			//printf("yeeees cur2_i: %d\n", cur_i);
			//printf("type in 2: %d\n", type_now);
			//printf("middle\n");
			if (type_now != -1) return 0;
			int check = go(a, a_len, type_now, 2*cur_i+2);
			if (check != type_now) return 0;
		}else if (2*cur_i+2 < a_len && a[2*cur_i+2] == a[cur_i]){
			//printf("yeeees cur2_i: %d\n", cur_i);
			//printf("type in 2: %d\n", type_now); 
			type_now = go(a, a_len, type_now, 2*cur_i+2);
			if (!type_now) return 0;
		}

	}

	//printf("cur_ii: %d\n", cur_i);
	//printf("type: %d\n", type_now);
	//printf("\n");
	return type_now;

}

int main(void){
	FILE *fb = fopen("input.bin", "rb");
	FILE *fo = fopen("output.bin", "wb");
	//uint32_t a[] = {16, 16, 13, 16, 4, 2, 5, 19};
	//uint32_t a_len = 8;
	
	uint32_t *a = (uint32_t *)malloc(sizeof(uint32_t) * MAX_SIZE);
	uint32_t a_len = fread(a,sizeof(uint32_t), MAX_SIZE, fb);
	//for (int i = 0; i < a_len; i++) printf("%d ", a[i]);
	//printf("\n");

	//printf("%d\n", go(a, a_len, -2, 0));
	uint32_t ans =  go(a, a_len, -2, 0);
	if (ans == -2) { // Значит, что все числа равны, тогда пусть это будет 1
		ans = 1;
		fwrite(&ans, sizeof(uint32_t), 1, fo); 
	}
	else fwrite(&ans, sizeof(uint32_t), 1, fo);
	
	//printf("%d\n", ans);
	return 0;
}
