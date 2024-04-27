#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int left, int mid, int right, long long int* comp) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];
    int i , j;
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for ( j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
		 
    i = 0;
	j = 0;
	int  k = left;

    while (i < n1 && j < n2) {
        (*comp)++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right, long long int *comp) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, comp);
        mergeSort(arr, mid + 1, right, comp);

        merge(arr, left, mid, right, comp);
    }
}

void displayArray(int arr[], int size) {
	int i;
    for (i = 0; i < size; ++i) 
        printf("%d ", arr[i]);
    printf("\n");
}

void processScenario(const char *inputFileName, const char* outputFileName) {
    FILE *inputFile, *outputFile;
    int option, numElements;
    struct timespec start_time, end_time;

    inputFile = fopen(inputFileName, "r");
        if (inputFile == NULL) {
            printf("Error opening input file.\n");
            exit(1);
        }

        int i, size;
        printf("Enter number of elements to be read: ");
        scanf("%d", &size);

        int arr[size];
        for (i = 0; i < size; i++) 
            fscanf(inputFile, "%d", &arr[i]);
        fclose(inputFile);

        printf("Before Sorting: ");
        displayArray(arr, size);

        clock_gettime(CLOCK_MONOTONIC, &start_time);
        long long int comp = 0;
        mergeSort(arr, 0, size - 1, &comp);
        clock_gettime(CLOCK_MONOTONIC, &end_time);

        double execution_time = (end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec);

        outputFile = fopen(outputFileName, "w");
        if (outputFile == NULL) {
            printf("Error opening output file.\n");
            exit(1);
        }
        
        for (i = 0; i < size; i++) 
            fprintf(outputFile, "%d ", arr[i]);
        fclose(outputFile);

        printf("After Sorting: ");
        displayArray(arr, size);

        printf("Number of Comparisons: %lld\n", comp);
}

int main() {
    FILE *inputFile, *outputFile;
    int option, numElements;
    
    struct timespec start_time, end_time;

    do {
        printf("MAIN MENU (MERGE SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. EXIT\n");

        printf("Enter option: ");
        scanf("%d", &option);

        switch(option) {
            case 1:
                processScenario("inAsce.dat", "outMergeAsce.dat");
                break;
            case 2:
                processScenario("inDesc.dat", "outMergeDesc.dat");
                break;
            case 3:
                processScenario("inRand.dat", "outMergeRand.dat");
                break;
            case 4:
                printf("Exiting program.\n\n");
                break;
            default:
                printf("Invalid option. Please choose again.\n");
        }
    } while(option != 4);

    return 0;
}
