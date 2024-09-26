#include <stdio.h>
#include <stdlib.h>

int comp(const void* a, const void* b)
{

    int x1 = *(const int*)a;
    int x2 = *(const int*)b;
    return (x1 > x2) - (x1 < x2);
}

void sort_even_odd(size_t count, int* data)
{
    int len_data = count; // len of data array
    int data1[len_data]; // even up
    int data2[len_data]; // odd down
    int ind_even = 0, ind_odd = 0;

    for (int i = 0; i < len_data; i++) {
        if (data[i] % 2 == 0) {
            data1[ind_even] = data[i];
            ind_even++;
        } else {
            data2[ind_odd] = data[i];
            ind_odd++;
        }
    }

    qsort(data1, ind_even, sizeof(data1[0]), comp);
    qsort(data2, ind_odd, sizeof(data2[0]), comp);

    for (int i = 0; i < ind_even; i++)
        printf("%d ", data1[i]);
    printf("\n");
    for (int j = 0; j < ind_odd; j++)
        printf("%d ", data2[j]);

    int i = 0;
    int j = ind_odd - 1;
    int data_index = 0;
    while (i != ind_even) {
        data[data_index] = data1[i];
        data_index++;
        i++;
    }

    while (j != -1) {
        data[data_index] = data2[j];
        j--;
        data_index++;
    }

    printf("\n");
    for (int i = 0; i < len_data; i++)
        printf("%d ", data[i]);
}

int main(void)
{
    int i = 0;
    int data[6];
    while (i != 6) {
        scanf("%d", &data[i]);
        i++;
    }
    sort_even_odd(6, data);
}
