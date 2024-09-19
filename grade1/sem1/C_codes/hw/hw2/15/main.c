#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    scanf("%d", &n);
    int a[n], result = 0, flag = 1, check_1[n], check_0[n], cnt_1 = 0, cnt_0 = 0, ans_1 = 0, ans_0 = 0;
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < n; i++) result ^= a[i];
    int result_base = result;
    //printf("result = %d\n", result);
    //if ((result >> 1) & 1) printf("yep");
    for (int k = 0; k < 32; k++){
        if (((result >> k) & 1) && flag) {
            flag = 0;
            for (int i = 0; i < n; i++){
                if ((a[i] >> k) & 1){
                    check_1[cnt_1] = a[i];
                    cnt_1++;
                }
                else{
                    check_0[cnt_0] = a[i];
                    cnt_0++;
                }
            }
        }
        if (!flag) break;
        result = result_base;
    }
    /*
    printf("%d %d", cnt_0, cnt_1);
    printf("________\n");
    for (int i = 0; i < cnt_0; i++) printf("%d  ", check_0[i]);
    printf("\n");
    for (int j = 0; j < cnt_1; j++) printf("%d   ", check_1[j]);
    printf("_________\n");
    */
    for (int i = 0; i < cnt_1; i++){
        ans_1 ^= check_1[i];
    }
    for (int i = 0; i < cnt_0; i++){
        ans_0 ^= check_0[i];
    }
    if (ans_0 > ans_1) {
        int tmp = ans_0;
        ans_0 = ans_1;
        ans_1 = tmp;
    }
    printf("%d %d", ans_0, ans_1);

    return 0;
}
