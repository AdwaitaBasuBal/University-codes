/*Aim of the program: Write a program to implement Binary Search to give the position of
leftmost appearance of the element in the array being searched. Display the number of
comparisons made while searching.*/

#include<stdio.h>
int count = 0;

int searchBinary(int arr[], int l, int m, int h, int k){
	if(l>h)
	return m;
	else if(arr[m] == k)
	{count++;return m;}
	else if(arr[m]>k)
	{count++;return searchBinary(arr, l, (l+(m-l)/2), m, k);}
	else if(arr[m]<k)
	{count++;return searchBinary(arr, m, (m+(h-m)/2), h, k);}
	else
	return -1;
}

int main(){
	int i, n, k, mid, high, low;
	printf("Enter the size of array: ");
	scanf("%d", &n);
	int arr[n];
	printf("Enter elements in asc order: ");
	for(i=0;i<n;i++){
		scanf("%d", &arr[i]);
	}
	printf("Enter key to be searched: ");
	scanf("%d", &k);
	low=0; high=n;
	mid=low + (high-low)/2;
	int index = searchBinary(arr,low,mid,high,k);
	printf("index::%d\ncount::%d\n", index, count);
	return 0;
	
}
