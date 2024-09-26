#include <stdio.h>
#include <dlfcn.h>

int myfunc2(int x)
{
    return x * x;
}

int main()
{
    void* mainhandle = dlopen(NULL, RTLD_LAZY);
    void* myfunc2handle = dlsym(mainhandle, "myfunc2");
    int x;
    scanf("%d", &x);
    int res = ((int(*)(int))myfunc2handle)(x);
    printf("Result: %d\n", res);
    dlclose(mainhandle);
}
