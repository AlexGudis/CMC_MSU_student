#include <stdio.h>
#include <stdlib.h>

int summ(int m, int *a){ // Сумма всех блоков
	int sum = 0;
	for (int i = 0; i < m; i++) sum += (a[i*2] * a[i*2+1]);
	return sum;
}

int get_max(int m, int *a){
	int max = 0;
	for (int i = 0; i < m; i++) {
		if (a[i*2]*a[i*2+1] > max) max = (a[i*2]*a[i*2+1]);
	}
	return max;
}

void pr_a(int m, int *a){ // Просто функция для удобной печати массива
	for (int i = 0; i < m; i++) printf("%d %d\n", a[i*2], a[i*2+1]);
}

int pir(int m, int *a, int before, int dim_before){ 
	// dim_before -  размерность предудыщих блоков для проверки длины. before -  количество блоков предыдущего яруса
	if (!summ(m,a)) return 1; 
	//if (get_max(m, a) < dim_before * before) return 0;
	for (int i = 0; i < m; i++){
		int cnt = a[i*2+1], dim = a[i*2]; 
		// Можем ли мы вообще его взять для постройки яруса?
		//printf("before: %d\n", before);
		if (cnt > before && (before+1)*dim > before*dim_before){
			a[i*2+1] -= (before + 1);// Отправляем на рекурсию, точно взяв этот вариант построения
			before++;
			//pr_a(m,a);
			int stop = pir(m, a, before, dim);
			if (stop) return stop; // Мы дошли до конца, проверили по вариантам, все ок, можем завершить рекурсию
			else {
				before--;
				a[i*2+1] += (before + 1); // Возвращаемся обратно, вдруг дальше сможем найти варианты?
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
	ans = pir(m, a, 0, 0);
	free(a);
	if (ans) printf("Yes");
	else printf("No");
	return 0;
}

