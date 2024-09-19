#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    scanf("%d", &n);
    int a[n], result = 0, flag = 1, check_1[n], check_2[n], cnt_1 = 0, cnt_2 = 0, ans_0 = 0, ans_1 = 0, ans_2 = 0;
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < n; i++) result ^= a[i];
    for (int i = 0; i < 32; i++){
        int dg = 0;
        if ((result >> i) & 1){ // i-ый бит-единица
            for (int j = 0; j < n; j++){
                if ((a[j] >> i) & 1){
                    dg ^= a[j];
                }
            }
            if (dg != result){
                ans_0 = dg;
                flag = 0;
            }
        }
        else{ // i-ый бит нулевой
            for (int j = 0; j < n; j++){
                if (!((a[j] >> i) & 1)){
                    dg ^= a[j];
                }
            }
            if (dg != result){
                ans_0 = dg;
                flag = 0;
            }
        }
        if (!flag){
            break;
        }
    }

    int k = 0;
    int b[n-1];
    for (int i = 0; i < n;i++){
        if (a[i] != ans_0){
            b[k] = a[i];
            k++;
        }
    }

    flag = 1;
    result = 0;
    for (int i = 0; i < n-1;i++) result ^= b[i];
    for (int k = 0; k < 32; k++){
        if (((result >> k) & 1) && flag) {
            flag = 0;
            for (int i = 0; i < n - 1; i++){
                if ((b[i] >> k) & 1){
                    check_1[cnt_1] = b[i];
                    cnt_1++;
                }
                else{
                    check_2[cnt_2] = b[i];
                    cnt_2++;
                }
            }
        }
        if (!flag) break;
    }

    for (int i = 0; i < cnt_1; i++){
        ans_1 ^= check_1[i];
    }
    for (int i = 0; i < cnt_2; i++){
        ans_2 ^= check_2[i];
    }

    if (ans_0 > ans_1){
        int tmp = ans_1;
        ans_1 = ans_0;
        ans_0 = tmp;
    }
    if (ans_1 > ans_2){
        int tmp = ans_2;
        ans_2 = ans_1;
        ans_1 = tmp;
    }
        if (ans_0 > ans_1){
        int tmp = ans_1;
        ans_1 = ans_0;
        ans_0 = tmp;
    }
    printf("%d %d %d", ans_0, ans_1, ans_2);
    return 0;
}
