#include <stdio.h>
#include <stdlib.h>
FILE *fptr1, *fptr2;

void findGCD(int n, int m){
    int i =1, gcd=0;
    for(;i<=n && i<=m;i++)
    {
        if((n%i==0)&&(m%i==0))
        gcd = i;
    }
    fprintf(fptr2, "The GCD of %d and %d is %d\n", n,m,gcd);
}
int main(){

    int n, m;
    
    fptr1 = fopen("inGCD.dat", "r");
    if (fptr1 == NULL)
    {
        printf("Input File not found");
        exit(1);
    }

    fptr2 = fopen("outGCD.dat", "w");
    if (fptr2 == NULL)
    {
        printf("Output File not found");
        exit(1);
    }
    //fprintf(fptr2, "Hello World");

    while (1)
    {
        fscanf(fptr1, "%d", &n);
        fscanf(fptr1, "%d", &m);
        findGCD(n,m);
        if(feof(fptr1))
        break;
    }
    // fprintf(fptr1, "%d", num);
    fclose(fptr1);
    fclose(fptr2);
    return 0;
}