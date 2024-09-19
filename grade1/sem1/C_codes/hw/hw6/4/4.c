#include<stdio.h>
#include <stdlib.h>

struct tree{
	long long key;
	long long data;
	struct tree *left;
	struct tree *right;
	struct tree *parent;
};

typedef struct tree tree;


tree *init(tree *root, long long key, long long data){ // Создание узла дерева по ключу и значению
	tree *tmp = (tree *)malloc(sizeof(tree));
	tmp->key = key;
	tmp->data = data;
	tmp->parent = NULL;
	tmp->left = tmp->right = NULL;
	root = tmp;
	return root;
}

tree *min(tree *root){
	tree *p = root;
	while (p -> left) p = p -> left;
	return p;
}

tree *search(tree *root, long long k){ // Поиск нашего узла по ключу (S)
	
	if (!root || root -> key == k) return root;
	if (k < root->key) return search(root->left, k);
	return search(root->right, k);
}

tree *insert(tree *root, long long k, long long d){ // Вставка нашего узла в нужное место или обновление его значения (A)
	tree *check = search(root, k); // Если такой элемент уже есть
	if (check) {
		check -> data = d;
		return root;
	}
	
	//printf("got it\n");
	tree *node = init(node, k, d);
	tree *a, *b;
	a = root, b = NULL;
	while (a){ // Спускаемся по дереву до тех пор, пока можем (ищем позицию)
		b = a;
		if (node -> key < a -> key){
			a = a -> left;
		} else a = a -> right;
	}
	
	// Сейчас b указывает на родителя того узла, что мы хотим вставить в дерево
	node -> parent = b;
	if (b == NULL) root = node;
	else if(node -> key < b -> key) b -> left = node;
	else b -> right = node;

	return root;
}


tree *del(tree *root, long long k){ // Удаление узла по ключу (D)
	tree *b = NULL, *c = NULL;
	b = search(root, k); // Тот узел, который хотим удалить
	if (!b) return root; // Нам нечего удалять
	// c - тот узел, к которому хотим присоединить остаток дерева, если такой имеется

	// бездетный узел
	if ((b -> right == NULL) && (b -> left == NULL)){
		if (b -> parent != NULL){
			c = b -> parent;
			if (b == c -> right) c -> right = NULL;
			else c -> left = NULL;
		}else root = NULL;
		free(b);
	}
	
	// Ребенок справа
	else if ((b -> left == NULL) && (b -> right != NULL)){
		if (b -> parent != NULL){
			c = b -> parent;
			if (b == c -> right) c -> right = b -> right;
			else c -> left = b -> right;
		}
		else root = b -> right;
		free(b);
	}

	// Ребенок слева
	else if ((b -> left != NULL) && (b -> right == NULL)){
		if (b -> parent != NULL){
			c = b -> parent;
			if (b == c -> right) c -> right = b -> left;
			else c -> left = b -> left;
		}else root = b-> left;
		free(b);
	}

	// Есть оба ребенка
	else if ((b -> left != NULL) && (b -> right != NULL)){
		c = min(b -> right);
		b -> key = c -> key; // Оставим наш узел на месте, заменив значения, а тот узел, что взяли снизу, удалим
		b -> data = c -> data;
		
		//printf("c key: %lld", c -> key);
		if (b -> key == c -> key){
			//printf("yes\n");
			b -> right = c -> right;

		}else{
			if (c -> right == NULL) c -> parent -> left = NULL;
			else c -> parent -> left = c -> right;
		}

		free(c);
	}
	
	//printf("root %lld %lld\n", root -> key, root -> data);
	return root;

}

void fr(tree *root){
	if (root){
		fr(root -> left);
		fr(root -> right);
	}
	free(root);

}


int main(void){
	char op;
	long long key, data;
	long long a[15000][2];
	long long a_ind = 0;
	tree *root = NULL;
	while (op != 'F'){
		fflush(stdin);
		scanf("%c", &op);
		if (op == 'A') {
			scanf("%lld %lld", &key, &data);
			root = insert(root, key, data);
		}
		else if(op == 'S' || op == 'D'){
			scanf("%lld", &key);
			if (op == 'S'){
				tree *ans = search(root, key); // Получаем тот самый узел
				if (ans) {
					a[a_ind][0] = ans -> key;
					a[a_ind][1] = ans -> data;
					a_ind++;
					//printf("%lld %lld\n", ans->key, ans->data); // Если будет поиск, когда еще нет дерева)
				}
			}
			if (op == 'D') root = del(root, key);
		}
		else if (op == 'F') break;
		//printf("weclwenc %c %d %d\n", op, key, data);
	}
	for (long long i = 0; i < a_ind; i++){
		printf("%lld %lld\n", a[i][0], a[i][1]);
	}
	//fr(root);
	return 0;
}
