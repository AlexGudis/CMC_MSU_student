#include <stdio.h>
#include <stdlib.h>

struct tree{
	int x;
	struct tree *left;
	struct tree *right;
};

typedef struct tree tree;

int get_hight(int n_now, int n_max, tree *t){
	if (!t) return 0;
	if (t -> left){
		n_now++;
		n_max = get_hight(n_now, n_max, t -> left);
		n_now--;
	}
	if (t -> right){
		n_now++;
		n_max = get_hight(n_now, n_max, t -> right);
		n_now--;
	}
	if (t -> right == NULL && t -> left == NULL){
		if (n_max == -1) return n_now;
		else if (n_now > n_max) return n_now;
	}
	return n_max;
}


tree *find(int key, tree *t){
	if (t -> left) find(key, t-> left);
	if (key == t -> x) return t;
	if (t -> right) find(key, t -> right);
}

int go(tree *t1, tree *t2){
	if (t1 -> x != t2 -> x) return 0;
	if (t1 -> right && t2 -> right) {
		int ans = go(t1 -> right, t2 -> right);
		if (!ans) return 0;
	}	
	else if(t1 -> right != NULL && t2 -> right == NULL) return 0;
	if (t1 -> left && t2 -> left) {
		int ans = go (t1 -> left, t2 -> left);
		if (!ans) return 0;
	}
	else if (t1 -> left != NULL && t2 -> left == NULL) return 0;
	return 1;
}

int is_subset(int size, struct tree *t1, struct tree *t2){
	if (get_hight(1,-1,t1) > get_hight(1, -1, t2)) return 0;
	tree *start_t2 = NULL;
	start_t2 = find(t1 -> x, t2);
	if (start_t2){ // Значит мы нашли такой же ключ во втором дереве
		int ans = go(t1, start_t2);
		if (!ans) return 0;
		return 1;
	}
	else return 0;

}

void print_tree(struct tree *t){
	if (t -> left) print_tree(t -> left);
	printf("%d ", t -> x);
	if (t -> right) print_tree(t -> right);

}

int main(void){
	tree *t1_3 = malloc(sizeof(tree));
	tree *t1_2 = malloc(sizeof(tree));
	tree *t1 = malloc(sizeof(tree));
	tree *t2_5 = malloc(sizeof(tree));
	tree *t2_4 = malloc(sizeof(tree));
	tree *t2_3 = malloc(sizeof(tree));
	tree *t2_2 = malloc(sizeof(tree));
	tree *t2 = malloc(sizeof(tree));
	//tree *t1_4 = malloc(sizeof(tree));
	//tree *t1_5 = malloc(sizeof(tree));
	

	t1 -> x = 1;
	t1 -> right = t1_2;
	t1_2 -> x = 2;
	t1_2 -> right = t1_3;
	t1_3 -> x = 3;
	//t1 -> left = t1_4;
	//t1_4 -> x = -2;
	//t1_2 -> left = t1_5;
	//t1_5 -> x = 7;

	t2 -> x = 1;
	t2 -> right = t2_2;
	t2_2 -> x = 2;
	t2_2 -> right = t2_3;
	t2_3 -> x = 3;
	t2_3 -> right = t2_4;
	t2_4 -> x = 4;
	t2_4 -> right = t2_5;
	t2_5 -> x = 5;

	//print_tree(t2);
	//printf("%d\n", get_hight(1, -1, t1));
	//tree *ans_t = NULL;
	//ans_t = find(3, t1);
	//if (ans_t) printf("YES\n");
	//else printf("NO\n");
	
	printf("%d\n", is_subset(get_hight(1, -1, t1), t1, t2));

	return 0;
}
