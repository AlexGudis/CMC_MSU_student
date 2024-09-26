#include <dlfcn.h>
#include <stdio.h>

int main()
{
    void *handle = NULL;
    handle = dlopen("./libmyfunc.so", RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "Error while loading so\n");
        return 1;
    }

    void *func = NULL;
    func = dlsym(handle, "myfunc");
    if (!func)
    {
        fprintf(stderr, "Error while finding myfunc\n");
        return 2;
    }

    int x;
    if (scanf("%d", &x) != 1)
    {
        fprintf(stderr, "Incorrect input\n");
        return 3;
    }

    int res = ((int (*)(int)) func)(x);
    printf("Result: %d\n", res);

    dlclose(handle);
}
