#include <stdio.h>

long
get_len(char *buf)
{
    long ans = 0;
    while (buf[ans]) {
        ans++;
    }
    return ans;
}

void
normalize_path(char *buf)
{
    long len = get_len(buf);
    for (int i = 1; i < len; ++i) {
        //   /a/b/../c -->  /a/c
        if (buf[i] == '.' && buf[i + 1] == '.' && buf[i - 1] == '/' && (buf[i + 2] == '/' || i + 2 == len)) {
            buf[i] = 0;
            buf[i + 1] = 0;
            int j = i - 2;
            while (j > 0 && (buf[j] == 0 || buf[j] == '/')) {
                j--;
            }
            while (j > 0 && buf[j] != '/') {
                buf[j] = 0;
                j--;
            }
        }

        //    /a/b/./c --> /a/b/c
        else if (buf[i] == '.' && buf[i - 1] == '/' && (buf[i + 1] == '/' || i + 1 == len)) {
            buf[i] = 0;
        }

        //    /a/b/c/ --> /a/b/c
        else if (buf[i] == '/' && i == len - 1) {
            buf[i] = 0;
        }
    }
    int check = 0;
    for (int i = 1; i < len; ++i) {
        if (buf[i] == '/' && check) {
            buf[i] = 0;
            check = 0;
        } else if (buf[i] == 0) {
            check = 1;
        }
    }
    int index = 0;
    for (int i = 1; i < len; ++i) {
        if (buf[i] == '/' && buf[i + 1] == 0) {
            index = i;
        } else if (buf[i] != 0) {
            index = 0;
        }
    }
    if (index) {
        buf[index] = 0;
    }

    int real_index = 0;
    for (int i = 0; i < len; ++i) {
        if (buf[i]) {
            buf[real_index] = buf[i];
            if (i != real_index) {
                buf[i] = 0;
            }
            real_index++;
        }
    }
}
