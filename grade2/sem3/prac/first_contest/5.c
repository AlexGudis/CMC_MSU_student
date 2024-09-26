#include <stdio.h>
#include <stdlib.h>

enum
{
    MAX_VALUE = 10,
    MIN_VALUE = 0,
};

void
print_arr(int n, int *arr)
{
    for (int i = 0; i < n; ++i) {
        printf("%d", arr[i]);
    }
    printf("\n");
}

int
max_index(int n, int *arr)
{
    for (int i = n - 2; i != -1; i--) {
        if (arr[i] < arr[i + 1]) {
            return i;
        }
    }
    return -1;
}

int
index_bigger_element(int n, int *arr, int elem)
{
    for (int i = n - 1; i != -1; i--) {
        if (arr[i] > elem) {
            return i;
        }
    }
    return -1;
}

void
swap(int *arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
    return;
}

void
reverse_create(int n, int *arr, int index) // swap the tail of an array
{
    for (int i = index + 1; i < index + ((n - index) / 2 + 1); ++i) {
        swap(arr, i, n - (i - index));
    }
}

int
main(void)
{
    int n, index, elem, swap_index;
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "5.c, line 55, cannot read n value\n");
        return 1;
    }
    if (n >= MAX_VALUE || n <= MIN_VALUE) {
        fprintf(stderr, "5.c, line 58, incorrect n\n");
        return 1;
    }
    int arr[MAX_VALUE - 1];
    for (int i = 1; i != n + 1; ++i) {
        arr[i - 1] = i;
    }

    index = max_index(n, arr);
    print_arr(n, arr);
    while (index != -1) {
        elem = arr[index];
        swap_index = index_bigger_element(n, arr, elem);
        swap(arr, index, swap_index);
        reverse_create(n, arr, index);
        print_arr(n, arr);
        index = max_index(n, arr);
    }

    return 0;
}
