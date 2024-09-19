#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1100000

int main(void){
	FILE *fb = fopen("input.bin", "rb");
	FILE *fo = fopen("output.bin", "wb");
	//int a[] = {16 ,11 ,9 ,10 ,57,6 ,8 ,1 ,2 ,4};
	//int a_len = 10;
	int type = -2;

	int *a = (int *)malloc(sizeof(int) * MAX_SIZE);
	int a_len = fread(a, sizeof(int), MAX_SIZE, fb);
	
	for (int i = 0; i < a_len; i++){
		if (i*2 + 1 < a_len){
			if (type == -2){
				if (a[i] < a[i*2+1]) type = 1;
				if (a[i] > a[i*2+1]) type = -1;
			}
			else{
				if ((a[i] < a[i*2+1]) && type != 1){
					type = 0;
					break;
				}
				if ((a[i] > a[i*2+1]) && type != -1){
					type = 0;
					break;
				}
			}
		}

		if (i*2+2 < a_len){
			if (type == -2){
				if (a[i] < a[i*2+2]) type = 1;
				if (a[i] > a[i*2+2]) type = -1;
			}
			else{
				if ((a[i] < a[i*2+2]) && type != 1){
					type = 0;
					break;
				}
				if ((a[i] > a[i*2+2]) && type != -1){
					type = 0;
					break;
				}
			}
		}
	}
	if (type == -2) {
		type = 1;
		//printf("%d\n",type);
		fwrite(&type, sizeof(int), 1, fo);
	}else {
		//printf("%d\n", type);
		fwrite(&type, sizeof(int), 1, fo);
	}
	fclose(fo);
	fclose(fb);
	return 0;
}
