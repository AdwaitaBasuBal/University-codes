#include <stdio.h>

void insertion_sort(int arr[], int n, int *comparisons)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
            (*comparisons)++;
        }
        arr[j + 1] = key;
    }
}

void read_input_file(const char *filename, int arr[], int *n)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return;
    }
    int num;
    *n = 0;
    while (fscanf(file, "%d", &num) != EOF)
    {
        arr[(*n)++] = num;
    }
    fclose(file);
}

void write_output_file(const char *filename, int arr[], int n)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error creating file: %s\n", filename);
        return;
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%d ", arr[i]);
    }
    fclose(file);
}
int main()
{
    int option;
    while (1)
    {
        printf("MAIN MENU (INSERTION SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. EXIT\n");
        const char *input_filename, *output_filename;
        printf("Enter option: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            input_filename = "inAsce.dat";
            output_filename = "outInsAsce.dat";
            break;
        case 2:
            input_filename = "inDesc.dat";
            output_filename = "outInsDesc.dat";
            break;
        case 3:
            input_filename = "inRand.dat";
            output_filename = "outInsRand.dat";
            break;
        case 4:
            printf("You have chosen to exit");
            exit(0);
        default:
            printf("Invalid option. Please enter a valid option.\n");
            break;
        }
        int arr[300];
        int n;
        read_input_file(input_filename, arr, &n);
        printf("Before Sorting: ");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
        int comparisons = 0;
        insertion_sort(arr, n, &comparisons);
        write_output_file(output_filename, arr, n);
        printf("\nAfter Sorting: ");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
        printf("Number of Comparisons: %d\n", comparisons);
        if (comparisons == 0)
        {
            printf("Scenario: Best-case\n");
        }
        else
        {
            printf("Scenario: Worst-case\n");
        }
    }
    return 0;
}
