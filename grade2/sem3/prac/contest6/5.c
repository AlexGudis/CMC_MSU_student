#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int
maxx(int a, int b)
{
    if (a > b) {
        return a;
    }
    return b;
}

ssize_t
getcwd2(int fd, char *buf, size_t size)
{
    char *ans = NULL;
    int start_fd = open("./", O_RDONLY); // remember current working directory
    if (fchdir(fd) == -1) {              // Change working directory to use "." and ".." after
        fprintf(stderr, "Cannot change working directory\n");
        return -1;
    }
    struct dirent *ddir_parent = NULL;
    char *child_name = NULL;
    char *child_new = NULL;
    struct stat child_info;
    int check = 1;
    while (check != 0) {
        if (lstat(".", &child_info) == -1) {
            fprintf(stderr, "Cannot get info about child file\n");
            return -1;
        }
        if (chdir("..") == -1) {
            fprintf(stderr, "Cannot change to parent working directory\n");
            return -1;
        }
        // now we work in parent
        DIR *dir_parent = opendir("."); // open parent to find a child and get its name
        if (dir_parent == NULL) {
            fprintf(stderr, "Cannot open parent dir\n");
            return -1;
        }
        struct stat parent_info;
        while ((ddir_parent = readdir(dir_parent)) != NULL) {
            // try to find child directory in parents directory (name)
            if (lstat(ddir_parent->d_name, &parent_info) == 0) {
                // ignore some files cuz we dont have access for exp
                if (child_info.st_ino == parent_info.st_ino && child_info.st_dev == parent_info.st_dev) {
                    // we found child in parent;
                    child_new = NULL;
                    asprintf(&child_new, "%s", ddir_parent->d_name);
                    free(child_name);
                    child_name = child_new;
                }
            }
        }
        if (closedir(dir_parent) == -1) {
            fprintf(stderr, "Error while closing parent directory\n");
            return -1;
        }
        // back in child and *child_name is child's name

        check = strncmp(child_name, ".", maxx(strlen("."), strlen(child_name)));
        char *ans_new = NULL;
        if (ans != NULL && check != 0) { // we have smth
            asprintf(&ans_new, "%s/%s", child_name, ans);
            free(ans);
        } else if (check != 0) { // new one
            asprintf(&ans_new, "%s", child_name);
        } else if (ans == NULL) { // we started in root
            asprintf(&ans_new, "%s", "/");
            free(ans);
        } else if (ans != NULL && check == 0) {
            asprintf(&ans_new, "/%s", ans);
            free(ans);
        }
        ans = ans_new;
    }

    printf("%s\n", ans);
    if (fchdir(start_fd) == -1) {
        fprintf(stderr, "Cannot open cwd\n");
        return -1;
    }

    int len = strlen(ans);
    if (size != 0) {
        snprintf(buf, size, "%s", ans);
        buf[strlen(buf)] = '\0';
    }
    //printf("BUF: %s\n", buf);
    free(ans);
    free(child_new);
    return len;
}

int
main(int argc, char *argv[])
{
    char *ptr;
    size_t size;
    scanf("%ld", &size);
    ptr = malloc(size);
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Cannot open directory and get filedes\n");
        return 1;
    }
    printf("SIZE: %ld\n", getcwd2(fd, ptr, size));
    free(ptr);
    return 0;
}
