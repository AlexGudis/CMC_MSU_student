#include <stdio.h>
#include <string.h>

int
parse_rwx_permissions(const char *str)
{
    if (!str) {
        return -1;
    }
    char sample[] = {"rwxrwxrwx"};
    int len = strlen(str);
    if (len != sizeof(sample) - 1) { // becauce \0 in the end
        return -1;
    }

    int ans = 0;
    int start = 1;
    char check;
    for (int i = len - 1; i > -1; --i) {
        check = sample[i] ^ str[i];
        if (check == 0) {
            ans += start;
        }
        else if (check != (sample[i] ^ '-')) {
            return -1;
        }

        start *= 2;
    }
    return ans;
}

int
main(void)
{
    char s[100];
    scanf("%100s", s);
    s[strlen(s)] = 0;
    //printf("%s\n", s);
    printf("%d\n", parse_rwx_permissions(s));
    return 0;
}
