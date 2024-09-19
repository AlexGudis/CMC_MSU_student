#include <stdio.h>
#include <stdlib.h>

struct list{
	int value;
	struct list *next;
	struct list *prev;

};

typedef struct list list;

void pr(list *head, list *tail){
	list *p = head;
	while (p != tail){
		printf("%d ", p -> value);
		p = p -> next;
	}
}

int main(void){
	FILE *fr = fopen("input.txt", "r+");
	FILE *fo = fopen("output.txt", "w+");
	int n, m;
	fscanf(fr, "%d %d", &n, &m);
	list *name = (list *)malloc(sizeof(list)); // Заглавный указатель
	list *head = (list *)malloc(sizeof(list)); // Начало нашего списка
	list *tail;
	
	name -> next = head;
	head -> prev = name;
	list *p = head;
	for (int i = 0; i < n; i++){
		list *l = (list *) malloc(sizeof(list));
		p -> value = i+1;
		p -> next = l;
		l -> prev = p;
		p = p -> next;
	}

	tail = p; // Т.к. в p сейчас неинициализированный кусок списка, пусть он и будет хвостом
	
	p = head;
	list **ps =	(list **)malloc(sizeof(list) * n);
	for (int i = 0; i < n; i++){
		ps[i] = p;
		p = p->next;
	}

	//for (int i = 0; i < n; i++){
	//	printf("%d ", ps[i] -> value);
	//}

	p = head;
	for (int i = 0; i < m; i++){
		int start, stop;
		fscanf(fr, "%d %d", &start, &stop);
		list *start_p = ps[start - 1];
		list *stop_p = ps[stop - 1];

		if (start_p == head) continue;	
		else{
			start_p -> prev -> next = stop_p -> next;
			stop_p -> next -> prev = start_p -> prev;
			head -> prev = stop_p;
			stop_p -> next = head;
			name -> next = start_p;
			start_p -> prev = name;
			head = start_p;
		}

	}

	//printf("%d\n", head -> value);
	//pr(head, tail);
	p = head;
	while (p != tail){
		fprintf(fo, "%d ", p -> value);
		p = p -> next;
	}
	return 0;
}
