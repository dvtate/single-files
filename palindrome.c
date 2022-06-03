#include <stdio.h>

static int
is_palindrome(long x)
{
    int n = 0;
    char buf[32];
    do
        buf[n++] = x % 10;
    while ((x /= 10));
    for (int i = 0; i < n / 2; i++)
        if (buf[i] != buf[n - i - 1])
            return 0;
    return 1;
}

int
main(void)
{
    int n;
    printf("enter n: ");
    while (scanf("%d", &n) == 1) {
        long start = 1;
        for (int i = 0; i < n - 1; i++)
            start *= 10;
        long end = start * 10;
        long best = 0;
        printf("solving....\n");
        for (long a = end - 1; a >= start; a--)
            for (long b = a; a * b > best && b >= start; b--)
                if (is_palindrome(a * b))
                    best = a * b;
        printf("%ld\n", best);
    }
}


/* python
n = int(input('Input: '))
end = int('1'+'0'*(n-1))
start = half = end*10
highest = 0

while highest == 0:
    half -= 1
    full = int(str(half) + str(half)[::-1])
    for i in range(start - 1, end, -1):
        if full//i >= start:
            break
        if full/i == full//i:
            highest = full
            break
print(highest)
*/
