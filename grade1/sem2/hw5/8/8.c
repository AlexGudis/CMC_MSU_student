#include <stdlib.h>
#include <stdio.h>

int comp(const void *i, const void *j)
{
  return *(int *)i - *(int *)j;
}



int main(void){
	FILE *fi = fopen("input.txt", "r");
	FILE *fo = fopen("output.txt", "w");
	int a[1000];
	int arr_len = 0;
	while (fscanf(fi, "%d" , &a[arr_len]) != -1){
		arr_len++;
	}
	qsort(a, arr_len, sizeof(int),  comp);

	for (int i = 0; i < arr_len; i++) fprintf(fo, "%d ", a[i]);
	
	return 0;
}
