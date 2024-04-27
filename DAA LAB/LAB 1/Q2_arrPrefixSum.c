#include<stdio.h>

int main(){
	
	int i=0, n;
	printf("Enter size: ");
	scanf("%d", &n);
	int arr[n], arr2[n];
	printf("Enter elements\n");
	for(;i<n;i++){
		scanf("%d", &arr[i]);
	}
	int sum=0;
	arr2[0]=arr[0];
	
	for(i=1;i<n;i++)
	{
		sum+=arr[i];
		arr2[i]= sum;
	}
	i=0;
	for(;i<n;i++){
		printf("%d ", arr2[i]);
	}
	return 0;
}
