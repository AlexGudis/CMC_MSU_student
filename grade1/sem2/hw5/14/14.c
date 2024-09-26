#include <stdio.h>
#include <stdlib.h>

struct list{
	int elem;
	struct list *next;
};

typedef struct list list;

void print_list(list *head){
	list *p = head;
	while (p -> next){
		printf("%d ", p-> elem);
		p = p -> next;
	}
	printf("\n");
}


int main(void){
	FILE *fi = fopen("input.txt", "r");
	FILE *fo = fopen("output.txt", "w");
	list *head =(list *)malloc(sizeof(list *));
	list *p = head;
	int x;
	while (fscanf(fi, "%d", &x) != -1){
		p -> elem = x;
		list *l = (list *)malloc(sizeof(list *));
		p -> next = l;
		p = l;
	}
	int swapped = 1;
	while (swapped){
		swapped = 0;
		p = head;
		while (p -> next){
			if (p -> elem > p -> next -> elem){
				int check = p -> elem;
				p -> elem = p -> next -> elem;
				p -> next -> elem = check;
				swapped = 1;
			}
			p = p -> next;
		}	
	}
	p = head;
	while (p -> next){
		fprintf(fo, "%d ", p -> elem);
		p = p -> next;
	}
	return 0;
}
