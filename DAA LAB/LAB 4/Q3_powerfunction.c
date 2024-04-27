#include <stdio.h>

int power(int n, int m) 
{
    int ans = 1;
    if (n == 1 || m == 1)
        return n;
    else if (m == 0)
        return 1;
    else {
        while (m > 1) {
            if (m % 2 == 0)
                ans *= n*n;
            else 
                ans *= n*n*n;
            m /= 2;
        }
        return ans;
    }
}

int main() {
    int num, pow;
    printf("Enter an integer: ");
    scanf("%d", &num);
    printf("Enter the power: ");
    scanf("%d", &pow);

    printf("%d^%d = %d\n\n", num, pow, power(num, pow));
    return 0;
}
