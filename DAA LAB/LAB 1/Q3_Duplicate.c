#include<stdio.h>

void dublicate_calculate(int arr[], int max_element, int n,FILE *fptr2){
    int a[max_element+1], duplicate=0,l=0,largest;

    for(int i=0;i<=max_element;i++) a[i]=0;

    for(int i=0;i<n;i++){
        a[arr[i]]++;
    }
    
    for(int i=0;i<=max_element;i++){
        if(a[i]>1) duplicate++;
        if(a[i]>l){
            l=duplicate;
            largest=i;
        }
    }
    fprintf(fptr2,"Total number of duplicate values= %d & The most repeating element in the array = %d",duplicate,largest);

}
int main(){
//receiving elements from user
int n,max_element=0;
FILE *fptr,*fptr2;
fptr=fopen("input.txt","r");
fptr2=fopen("output.txt","w");
printf("Enter no. of elements: ");
scanf("%d",&n);
int arr[n];

// to calculate sum and minimum maximum value simultaneously
for(int i=0;i<n;i++){
     fscanf(fptr,"%d",&arr[i]);
     if(arr[i]>=max_element) max_element=arr[i];
}
 dublicate_calculate(arr,max_element,n,fptr2);
}
