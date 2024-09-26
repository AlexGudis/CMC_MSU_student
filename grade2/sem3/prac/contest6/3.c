#include <stdio.h>
#include <stdlib.h>

struct s1
{
    char f1;
    long long f2;
    char f3;
};

struct s2
{
    char f1;
    char f3;
    long long f2;
};

size_t
compactify(void *ptr, size_t size)
{
    if ((long long) size <= 0) {
        return 0;
    }

    long long len = (long long)size / sizeof(struct s1);
    long long new_size = len * sizeof(struct s2);
    struct s1 s_old;
    struct s2 s_tmp;
    struct s1 *ptr_s1 = ptr;
    struct s2 *ptr_s2 = ptr;
    for (long long i = 0; i < len; ++i) {
        s_old = ptr_s1[i];
        s_tmp.f1 = s_old.f1;
        s_tmp.f2 = s_old.f2;
        s_tmp.f3 = s_old.f3;
        ptr_s2[i] = s_tmp;
    }
    return new_size;
}

int
main(void)
{
    int n;
    scanf("%d", &n);
    void *ptr = calloc(n, sizeof(struct s1));
    char f1, f3;
    long long f2;
    struct s1 s;
    struct s1 *ptr_s1 = ptr;
    struct s2 *ptr_s2 = ptr;
    for (int i = 0; i < n; i++) {
        scanf("%hhd", &f1);
        scanf("%lld", &f2);
        scanf("%hhd", &f3);
        s.f1 = f1;
        s.f2 = f2;
        s.f3 = f3;
        ptr_s1[i] = s;
    }
    for (int i = 0; i < n; i++) {
        printf("%d, %lld, %d\n", ptr_s1[i].f1, ptr_s1[i].f2, ptr_s1[i].f3);
    }
    printf("ANS: %lu\n\n", compactify((void *) ptr, n * sizeof(struct s1)));
    for (int i = 0; i < n; i++) {
        printf("%d, %lld, %d\n", ptr_s2[i].f1, ptr_s2[i].f2, ptr_s2[i].f3);
    }
    return 0;
}
