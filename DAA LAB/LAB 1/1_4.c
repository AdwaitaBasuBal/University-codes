#include <stdio.h>

void EXCHANGE(int* p, int* q) {
    
    int temp = *p;
    *p = *q;
    *q = temp;
}

void ROTATE_RIGHT(int* p1, int p2) {
    
    if (p2 <= 1) {
        return;
    }

    
    int temp = p1[p2 - 1];

    
    for (int i = p2 - 1; i > 0; i--) {
        p1[i] = p1[i - 1];
    }

    
    p1[0] = temp;
}

int main() {
	 int i=0, arr[10];
	 printf("Enter 10 elements: ");
	 while(i<10){
	 scanf("%d", &arr[i]);
	 i++;
	 }
	 
	 printf("Enter the number of elements to rotate: ");
	 int p2 = 0; 
	 scanf("%d", &p2);
    ROTATE_RIGHT(arr, p2);

    // Output the rotated array
    for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
