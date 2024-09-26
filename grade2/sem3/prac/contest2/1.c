#include <stdio.h>
#include <stdlib.h>

int main(void){
    char s1[128], s2[128], s3[128];


    if (scanf("%128s", s1) == EOF){
        exit(1);
    }
    if (scanf("%128s", s2) == EOF){
        exit(1);
    }
    if (scanf("%128s", s3) == EOF){
        exit(1);
    }

    printf("[Host:%s,Login:%s,Password:%s]\n", s1, s2, s3);
    return 0;
}
