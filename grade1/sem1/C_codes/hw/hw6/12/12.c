#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALG_SIZE 26

struct node{
	struct node *next[ALG_SIZE];
	int count;
};

struct list{
	char elem;
	struct list *next;
};

typedef struct node node;
typedef struct list list;

void insert(node *root, list *st, list *stop){
	node *p = root;
	while (st != stop){
		if (p->next[st->elem - 'a'] == NULL){
			p->next[st->elem - 'a'] = (node *)malloc(sizeof(node *));
		}
		p = p->next[st->elem - 'a'];
		st = st->next;
	}
	p->count++;
}

int search(node *root, list *st, list *stop){
	node *p = root;
	while (st != stop){
		p = p -> next[st->elem - 'a'];
		st = st -> next;
		if (p == NULL) return 0;
	}
	if (p->count > 0) return 1;
	return 0;
}

void pr(list *p, list *stop){
	while (p != stop){
		printf("%c", p->elem);
		p = p -> next;
	}
	printf("\n");
}


int main(void){
	list *start = (list *)malloc(sizeof(list));
	char s[2001];
	int s_len;
	scanf("%2000s", s);
	s_len = strlen(s);
	list *p = start;
	for (int i = 0; i < s_len; i++){
		p -> elem = s[i];
		list *l = (list *)malloc(sizeof(list));
		p -> next = l;
		p = p -> next;
	}
	p = NULL;
	p = start;
	/*while (p){
		printf("%c", p -> elem);
		p = p -> next;
	}*/
	list **ps = (list **)malloc(sizeof(list) * s_len);
	printf("check poin 1\n");
	for (int i = 0; i < s_len; i++){
		ps[i] = p;
		p = p->next;
	}

	node *root = (node *)malloc(sizeof(node));
	int ans = 0;
	
	printf("check point 2\n");
	for (int i = 0; i < s_len; i++){
		for (int ll = 1 ; ll <= s_len; ll++){
			if (i + ll <= s_len){
				//printf("%d %d\n", i, ll);
				list *st = ps[i];
				list *fi = ps[i + ll];
				pr(st, fi);
				if (!search(root, st, fi)){
					ans++;
					insert(root, st, fi);
				}
			}else break;
		}	
	}
	

	printf("%d\n", ans+1);
	return 0;
}
