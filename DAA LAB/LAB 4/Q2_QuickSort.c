#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high, long long int* comparisons) {
    int pivot = arr[high];
    int i = low;

    for (int j = low; j <= high - 1; j++) {
        (*comparisons)++;
        if (arr[j] < pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[high]);
    return i;
}

void quickSort(int arr[], int low, int high, long long int* comparisons) {
    if (low < high) {
        int pi = partition(arr, low, high, comparisons);

        quickSort(arr, low, pi - 1, comparisons);
        quickSort(arr, pi + 1, high, comparisons);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) 
        printf("%d ", arr[i]);
    printf("\n");
}

void processScenario(const char* inputFileName, const char *outputFileName) {
    FILE *inputFile, *outputFile;
    int numElements;
    printf("Enter number of elements to be read: ");
    scanf("%d", &numElements);

    inputFile = fopen(inputFileName, "r");
        if (inputFile == NULL) {
            printf("Error opening input file.\n");
            exit(1);
        }

        int arr[numElements];
        for (int i = 0; i < numElements; i++) {
            fscanf(inputFile, "%d", &arr[i]);
        }
        fclose(inputFile);

        printf("Before Sorting: ");
        printArray(arr, numElements);

        long long int comparisons = 0;
        quickSort(arr, 0, numElements - 1, &comparisons);

        outputFile = fopen(outputFileName, "w");
        if (outputFile == NULL) {
            printf("Error opening output file.\n");
            exit(1);
        }

        for (int i = 0; i < numElements; i++) 
            fprintf(outputFile, "%d ", arr[i]);
        fclose(outputFile);

        printf("After Sorting: ");
        printArray(arr, numElements);
        printf("Number of Comparisons: %lld\n", comparisons);

        // Determine if it's a best-case or worst-case scenario
        if (comparisons == (numElements * (numElements - 1)) / 2) 
            printf("Scenario: Best-case\n\n");
        else if (comparisons == (numElements * (numElements - 1))) 
            printf("Scenario: Worst-case\n\n");
        else 
            printf("Scenario: Average-case\n\n");
}

int main() {
    int option, numElements;

    do {
        printf("MAIN MENU (QUICK SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. EXIT\n");

        printf("Enter option: ");
        scanf("%d", &option);

        switch(option) {
            case 1:
                processScenario("inAsce.dat", "outQuickAsce.dat");
                break;
            case 2:
                processScenario("inDesc.dat", "outQuickDesc.dat");
                break;
            case 3:
                processScenario("inRand.dat", "outQuickRand.dat");
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
