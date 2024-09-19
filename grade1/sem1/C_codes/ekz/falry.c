#include <stdio.h>
#include <stdlib.h>

struct list{
	int key;
	struct list *next;
	struct list *sublist_head;
};

typedef struct list list;

int get_min_len(list *garland, int len_now, int min_len){
	if (garland -> next){
		len_now++;
		min_len = get_min_len(garland->next, len_now, min_len);
		len_now--;
	}
	if (garland -> sublist_head){
		int check = len_now;
		len_now = 1;
		min_len = get_min_len(garland -> sublist_head, len_now, min_len);
		len_now = check;
	}
	if (min_len == 0) return len_now;
	if (len_now < min_len && garland->next == NULL && garland->sublist_head == NULL) return len_now;
	return min_len;
}

int go(list *garland, int len_now, int min_len, int lamp_now, int lowest_lamp){
	if (garland->key < lamp_now) lamp_now = garland -> key;
	if (garland -> next){
		len_now++;
		lowest_lamp = go(garland->next, len_now, min_len, lamp_now, lowest_lamp);
		len_now--;
	}
	if (garland -> sublist_head){
		int check_len = len_now;
		len_now = 1;
		int check_lamp = lamp_now;
		lamp_now = 1001;
		lowest_lamp = go(garland -> sublist_head, len_now, min_len, lamp_now, lowest_lamp);
		len_now = check_len;
		lamp_now = check_lamp;
	}
	if(len_now == min_len && garland -> next == NULL && garland -> sublist_head == NULL){
		//printf("check\n");
		if (lamp_now < lowest_lamp) return lamp_now;
		return lowest_lamp;
	}
	return lowest_lamp;
}


int examine(struct list *garland){
	if (!garland) return -1;
	int len = get_min_len(garland,1,0);
	//printf("len: %d\n", len);
	return go(garland, 1, len, 1001, 1001);
}


int main(void){
	list *garland = malloc(sizeof(list));
	garland -> key = 3;
	list *l1 = malloc(sizeof(list));
	garland -> next = l1;
	l1 -> key = 1;
	list *l2 = malloc(sizeof(list));
	l1 -> next = l2;
	l2 -> key = 5;
	list *l3 = malloc(sizeof(list));
	l2 -> sublist_head = l3;
	l3 -> key = 4;
	l3 -> next = NULL;
	l2 -> next = NULL;
	list *l4 = malloc(sizeof(list));
	garland -> sublist_head = l4;
	l4 -> key = 2;
	/*list *l5 = malloc(sizeof(list));
	l4 -> next = l5;
	l5 -> key = 2;
	l5 -> next = NULL;
	list *l6 = malloc(sizeof(list));
	l4 -> sublist_head = l6;
	l6 -> key = 3;
	l6 -> next = NULL;
	list *l7 = malloc(sizeof(list));
	l6 -> next = l7;
	l7 -> key = 3;
	*/printf("%d\n", examine(garland));

	return 0;
}
