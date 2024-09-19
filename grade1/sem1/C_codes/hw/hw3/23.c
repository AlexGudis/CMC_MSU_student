#include <stdio.h>
#include <stdlib.h>

int summ(int m, int *a){ // Сумма всех блоков
	int sum = 0;
	for (int i = 0; i < m; i++) sum += (a[i*2] * a[i*2+1]);
	return sum;
}


int ch_one(int m, int *a){ // Проверка, что у нас остался один вариантов блоков. Только для последнего яруса!
	int sum = summ(m, a);
	for (int i = 0; i < m; i++){
		//printf("summ: %d\n", sum);
		if ((a[i*2] * a[i*2+1]) == sum) return 1;
	}
	return 0;
}

int check_cnt(int cnt, int dim, int before){ // Функция проверит, можем ли мы из данных блоков собрать новый ярус?
	for (int i = 1; i <= cnt; i++){
		if ((i * dim) - before == 1){
			return i;
		} 
	}
	return -1; // Значит, собрать новый ярус никак нельзя
}

void pr_a(int m, int *a){
	for (int i = 0; i < m; i++) printf("%d %d\n", a[i*2], a[i*2+1]);
}

int pir(int m, int *a, int before){
	for (int i = 0; i < m; i++){
		int cnt = a[i*2+1], dim = a[i*2];
		if (ch_one(m, a)){ // Осталось проверить только один ярус для постройки фундамента
			//printf("Only one\n");
			if (cnt * dim > before) return 1;
		}
		else{ // Вдруг возможны другие варианты разложения?
			int ch_cnt = check_cnt(cnt, dim, before); // Сколько блоков из этого яруса нам нужно? 
			// Можем ли мы вообще его взять для постройки яруса?
			//printf("before: %d\n", before);  
			if (ch_cnt != -1){
				//printf("work\n");
				a[i*2+1] -= ch_cnt;// Отправляем на рекурсию, точно взяв этот вариант построения
				before++;
				//pr_a(m,a);
				int stop = pir(m, a, before);
				if (stop) return stop; // Мы дошли до конца, проверили по вариантам, все ок, можем завершить рекурсию
				else {
					before--;
					a[i*2+1] += ch_cnt; // Возвращаемся обратно, вдруг дальше сможем найти варианты?
				}
			}
		}		
	} 
	return 0; // Если никакой из вариантов разложения нам не подошел, значит, его и нет)))

}


int main(void){
	int m, ans;
	scanf("%d", &m);
	//printf("%d\n", m);
	int *a = malloc(2 * m * sizeof(int));
	for (int i = 0; i < m; i++){
		int si, ci;
		scanf("%d", &si);
		scanf("%d", &ci);
		a[i*2] = si;
		a[i*2+1] = ci;
	} 
	//for (int i = 0; i < m; i++){
	//	printf("%d %d\n", a[i*2], a[i*2+1]);
	//}
	ans = pir(m, a, 0);
	if (ans) printf("Yes");
	else printf("No");
	return 0;
}
