#include<stdio.h>

int main(){
	int n;
	printf("Enter number of elements:");
	scanf("%d", &n);
	int arr[n];
	printf("Enter the elements: ");
	int i=0, sum=0;
	for(;i<n;i++){
		scanf("%d", &arr[i]);
		sum+=arr[i];
	}
	float avg = sum/n;
	int min = arr[0], max = arr[n-1];
	printf("Enter element to search: ");
	int key;
	scanf("%d",&key);
	for(i=0;i<n;i++){
		if(arr[i]<min)
			min = arr[i];
		else if(arr[i]>max)
			max = arr[i];
		if(key==arr[i])
			printf("Key found at posn %d\n", i+1);
	}
	for(i=0;i<n;i++){
		printf("%d\t", arr[i]);
	}
	printf("\nMax:%d\tMin:%d\tSum:%d\tAvg:%0.2f",max,min,sum,avg);
	
	//reverse array
	int temp=0;
	
	for(i=0;i<n/2;i++)
	{
		temp = arr[i];
		arr[i] = arr[n-1-i];
		arr[n-1-i] = temp;
	}
	printf("\n");
	for(i=0;i<n;i++){
		printf("%d\t", arr[i]);
	}
	
	return 0;
}
