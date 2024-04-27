#include <stdio.h>
#include <stdlib.h>
FILE *fptr1, *fptr2;
void decimalToBinary(int n)
{

    if (n == 1)
    {
        fprintf(fptr2, "%d", 1);
        return;
    }
    else if (n == 0)
    {
        fprintf(fptr2, "%d", 0);
        return;
    }

    decimalToBinary(n / 2);
    fprintf(fptr2, "%d", n % 2);
    return;
}

int main()
{
    int n, i = 0, temp=0;
    
    fptr1 = fopen("inDec.dat", "r");
    if (fptr1 == NULL)
    {
        printf("Input File not found");
        exit(1);
    }

    fptr2 = fopen("outBin.dat", "w");
    if (fptr2 == NULL)
    {
        printf("File not found");
        exit(1);
    }

    printf("Enter a value for n: ");
    scanf("%d", &n);

    while (i < n)
    {
        fscanf(fptr1, "%d", &temp);
        printf("%d", temp);
        fprintf(fptr2, "The Binary equivalent of %d is ", temp);
        decimalToBinary(temp);
        i++;
        fprintf(fptr2, "\n");
    }
    // fprintf(fptr1, "%d", num);
    fclose(fptr1);
    fclose(fptr2);
    return 0;
}
