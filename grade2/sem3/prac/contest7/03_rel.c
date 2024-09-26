#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Elem
{
    char *name;
    ino_t file_id;
    dev_t dev_id;
} Elem;

Elem *
create_elem(char *name, ino_t ino, dev_t dev)
{
    Elem *ans = (Elem *) calloc(1, sizeof(Elem));
    ans->name = calloc(1, strlen(name) + 1);
    strcpy(ans->name, name);
    ans->file_id = ino;
    ans->dev_id = dev;
    return ans;
}

void
delete_elem(Elem *elem)
{
    free(elem->name);
    free(elem);
    return;
}

int
main(int argc, char *argv[])
{
    struct stat st;
    Elem **arr;
    arr = calloc(1, sizeof(Elem *));
    int arr_size = 1;
    int arr_len = 0;
    DIR *dp = opendir(argv[2]);
    struct dirent *d;
    chdir(argv[2]);
  
    printf("Check\n");
    while ((d = readdir(dp)) != NULL) {
        stat(d->d_name, &st);
        printf("Check2\n");
        if (!S_ISDIR(st.st_mode)) {
            if (arr_len == arr_size) {
                arr_size *= 2;
                arr = realloc(arr, sizeof(Elem *) * arr_size);
            }
            arr[arr_len] = create_elem(d->d_name, st.st_ino, st.st_dev);
            arr_len += 1;
        }
    }
    closedir(dp);

    printf("End loop1\n");
    size_t ans = 0;
    chdir(argv[1]);
    printf("CHdr\n");
    dp = opendir(argv[1]);
    printf("\n");
    if (dp == NULL) {
        printf("ERROR\n");
    }
    while ((d = readdir(dp)) != NULL) {
        printf("Check2.5\n");
        lstat(d->d_name, &st);
        printf("Check3\n");
        if (S_ISREG(st.st_mode) && access(d->d_name, W_OK) == 0) {
            for (int i = 0; i < arr_len; ++i) {
                printf("I: %d\n", i);
                if (strcmp(d->d_name, arr[i]->name) == 0 && st.st_ino == arr[i]->file_id &&
                    st.st_dev == arr[i]->dev_id) {
                    ans += st.st_size;
                }
            }
        }
    }
    closedir(dp);

    printf("%lu\n", ans);

    for (int i = 0; i < arr_len; ++i) {
        delete_elem(arr[i]);
    }
    free(arr);
    return 0;
}
