#include <stdio.h>
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

    long long len = (long long) size / sizeof(struct s1);
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
