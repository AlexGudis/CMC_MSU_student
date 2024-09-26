static int result = 0;

extern int (*ex_function)(int, int);

int calculate(int count, int *numbers){
	for (int i = 0; i < count; ++i){
		result = ex_function(result, numbers[i]);
	}
	return result; 
}
