#include <stdio.h>

// Function to reverse bits of num
int reverseBits(int num)
{
    int NO_OF_BITS = sizeof(num) * 8;
    int reverse_num = 0;
    int i;
    for (i = 0; i < NO_OF_BITS; i++) {
        if ((num & (1 << i)))
            reverse_num |= 1 << ((NO_OF_BITS - 1) - i);
    }
    return reverse_num;
}

// Driver code
int main()
{
    unsigned int x = 2;
    printf("%u", reverseBits(x));
    getchar();
}
