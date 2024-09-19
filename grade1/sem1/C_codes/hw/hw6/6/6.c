#include <stdio.h>
#include <stdlib.h>

struct list{
	int elem;
	struct list *next;
};

typedef struct list list; 


int in(list *l, int x){
	while (l->next){
		if (l->elem == x) return 1; // Значит элемент входит в последовательность
		l = l->next;
	}
	return 0;
}

int main(void){
	FILE *f = fopen("input.txt", "r");
	FILE *out = fopen("output.txt", "w+");
	int x = 0;
	list *l1 = (list *)malloc(sizeof(list)); // Указатель на начало нашего первого однонаправленного списка	
	list *l2 = (list *)malloc(sizeof(list));
	list *head1 = l1; // Запомним положение головы) 
	list *head2 = l2;

	while (fscanf(f, "%d", &x) != EOF){
		if (x == -1) break;
		l1->elem = x;
		list *l = (list *)malloc(sizeof(list));
		l1->next = l;
		l1 = l; // Переместимся по нашему листу
	}
	l1 = head1; // Вернемся на место головы)

	//while (l1->next){
	//	printf("%d ", l1->elem);
	//	l1 = l1->next;
	//}
	//printf("\n");

	while (fscanf(f, "%d", &x) != EOF){
		if (x == -1) break;
		l2->elem = x;
		list *l = (list *)malloc(sizeof(list));
		l2 -> next = l;
		l2 = l;
	}
	l2 = head2;

	//while (l2 -> next){
	//	printf("%d ", l2 -> elem);
	//	l2 = l2 -> next;
	//}
	//printf("\n");

	while (l1 -> next){
		if (!in(l2, l1->elem)) fprintf(out, "%d ", l1 -> elem);
		l1 = l1 -> next;
	}

	fclose(f);
	fclose(out);

	return 0;
}
