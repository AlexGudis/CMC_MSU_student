#include <stdio.h>
#include <stdlib.h>

struct list{
	int value;
	struct list* next;

};
typedef struct list list;


void pr(list *l){
	while (l) {
		printf("%d ", l->value);
		l = l -> next;
	}
	printf("\n");
}


list *merge(list *l1, list *l2){
	list *ans = (list *)malloc(sizeof(list *)); // Указатель на начало суммы списоков
	list *p = ans;
	//printf("l1: ");
	//pr(l1);
	//printf("l2: ");
	//pr(l2);

	while (l1 && l2){ // То есть мы полностью еще не прошли по обоим спискам

		if (l1->value > l2->value){ // Значит нужно поменять значения и добавить в список
			p-> value= l2->value;
			l2 = l2 -> next;
		}
		else{
			p -> value = l1 -> value;
			l1 = l1 -> next;
		}
	
		if (l1 != NULL || l2 != NULL){
			list *l = (list *)malloc(sizeof(list *));
			p -> next = l;
			p = p -> next;
		}
	}
	
	//pr(ans);
	while (l1){ // Значит первой закончилась вторая половина, а здесь все значения больше
		p->value = l1->value;
		if (l1 -> next != NULL){
			list *l = (list *)malloc(sizeof(list *));
			p -> next = l;
			p = p -> next;
			l1 = l1->next;
		}
		else break;
	}

	while (l2){ // Значит первой закончилась первая половина, а здесь все значения больше
		p->value = l2->value;
		if (l2 -> next != NULL){
			list *l = (list *)malloc(sizeof(list *));
			p -> next = l;
			p = p -> next;
			l2 = l2->next;
		}
		else break;
	}
	

	//pr(ans);
	//printf("\n");
	
	return ans;
}

list *get_m(list *l){
	list *m = l;
	list *fin = l -> next;

	while (fin != NULL && fin -> next != NULL){ // fin придет к концу в два раза быстрее. Значит, в m получим середину
		m = m -> next;
		fin = fin -> next -> next;
	}
	
	return m;
}


list *merge_sort(list *ll){
	if (ll == NULL || ll->next == NULL) return ll;
	list *l1 = ll;
	list *m = get_m(ll);
	list *l2 = m -> next;
	m -> next = NULL; // Разорвем связь, чтобы у нас было два несвязанных списка

	//printf("in merge l1: ");
	//pr(l1);
	//printf("in merge l2: ");
	//pr(l2);

	l1 = merge_sort(l1);
	l2 = merge_sort(l2);

	return merge(l1, l2);
}


int main(void){
	FILE *fi = fopen("input.txt", "r+");
	FILE *fo = fopen("output.txt", "w+");
	list *head = (list *)malloc(sizeof(list *));
	int x;
	int check_first = 1;
	list *p;
	while (fscanf(fi, "%d", &x) != EOF){
		if (check_first){
			p = head;
			check_first = 0;
		}
		else{
			list *new = (list *)malloc(sizeof(list *));
			p -> next = new;
			p = p -> next;

		}
		p->value = x;
	}
	p = head;
	//pr(p);
	
	list *ans = merge_sort(head);
	
	//pr(ans);
	while (ans){
		fprintf(fo, "%d ", ans->value);
		ans = ans -> next;
	}

	free(head);
	free(ans);
	fclose(fi);
	fclose(fo);
	return 0;
}
