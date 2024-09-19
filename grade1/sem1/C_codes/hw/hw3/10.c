#include <stdio.h>

int f(int check){
	int x;
	char op;
	//printf("Here we go again\n");
	if (scanf("%d", &x)){
		return x;
	}
	else{
		//printf("We got it, bro\n");
		scanf("%c", &op);
		if (op == '*') return f(1) * f(1);
		else return f(1)/f(1);
	}
	return -1;

}

int main(void){
	printf("%d", f(1));
	return 0;
}
