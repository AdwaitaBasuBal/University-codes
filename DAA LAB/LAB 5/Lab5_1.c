#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct person
struct person {
    int id;
    char *name;
    int age;
    int height;
    int weight;
};

// Function to swap two persons
void swap(struct person *a, struct person *b) {
    struct person temp = *a;
    *a = *b;
    *b = temp;
}

// Function to create a max-heap or min-heap based on age or weight
void heapify(struct person *arr, int n, int i, int isMaxHeap, int isAgeHeap) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (isAgeHeap) {
        if (isMaxHeap) {
            if (left < n && arr[left].age > arr[largest].age)
                largest = left;
            if (right < n && arr[right].age > arr[largest].age)
                largest = right;
        } else {
            if (left < n && arr[left].age < arr[largest].age)
                largest = left;
            if (right < n && arr[right].age < arr[largest].age)
                largest = right;
        }
    } else {
        if (isMaxHeap) {
            if (left < n && arr[left].weight > arr[largest].weight)
                largest = left;
            if (right < n && arr[right].weight > arr[largest].weight)
                largest = right;
        } else {
            if (left < n && arr[left].weight < arr[largest].weight)
                largest = left;
            if (right < n && arr[right].weight < arr[largest].weight)
                largest = right;
        }
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest, isMaxHeap, isAgeHeap);
    }
}

// Function to build a max-heap or min-heap based on age or weight
void buildHeap(struct person *arr, int n, int isMaxHeap, int isAgeHeap) {
	int i;
    for ( i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, isMaxHeap, isAgeHeap);
    }
}

// Function to read data from a file
int readData(struct person **arr, int *n) {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    fscanf(file, "%d", n);
    *arr = (struct person *)malloc((*n) * sizeof(struct person));
    if (*arr == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 0;
    }
    int i;
    for ( i = 0; i < *n; i++) {
        fscanf(file, "%d %s %d %d %d",
               &(*arr)[i].id, (*arr)[i].name,
               &(*arr)[i].age, &(*arr)[i].height, &(*arr)[i].weight);
    }

    fclose(file);
    return 1;
}

// Function to display the weight of the youngest person
void displayYoungestWeight(struct person *arr, int n) {
    int youngestAge = arr[0].age;
    int youngestIndex = 0;
    int i;
    for ( i = 1; i < n; i++) {
        if (arr[i].age < youngestAge) {
            youngestAge = arr[i].age;
            youngestIndex = i;
        }
    }

    float youngestWeightKg = arr[youngestIndex].weight / 2.205;
    printf("Weight of the youngest person: %.2f kg\n", youngestWeightKg);
}

// Function to insert a new person into the min-heap
void insertPerson(struct person **arr, int *n, struct person newPerson) {
    (*n)++;
    *arr = (struct person *)realloc(*arr, (*n) * sizeof(struct person));
    if (*arr == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    int i = *n - 1;
    while (i > 0 && newPerson.age < (*arr)[(i - 1) / 2].age) {
        (*arr)[i] = (*arr)[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    (*arr)[i] = newPerson;
}

// Function to delete the oldest person from the max-heap
void deleteOldestPerson(struct person *arr, int *n) {
    if (*n <= 0) {
        printf("Heap is empty.\n");
        return;
    }

    struct person oldestPerson = arr[0];
    arr[0] = arr[*n - 1];
    (*n)--;

    heapify(arr, *n, 0, 1, 1); // Rebuild the max-heap
    printf("Deleted the oldest person: %s (Age: %d)\n", oldestPerson.name, oldestPerson.age);
}

// Function to free memory and exit the program
void exitProgram(struct person *arr, int n) {
	int i;
    for ( i = 0; i < n; i++) {
        free(arr[i].name);
    }
    free(arr);
    exit(0);
}

int main() {
    int option, n = 0;
    struct person *arr = NULL;

    while (1) {
        printf("\nMAIN MENU (HEAP)\n");
        printf("1. Read Data\n");
        printf("2. Create a Min-heap based on the age\n");
        printf("3. Create a Max-heap based on the weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the oldest person\n");
        printf("7. Exit\n");
        printf("Enter option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                if (readData(&arr, &n)) {
                    printf("Data read successfully.\n");
                }
                break;
            case 2:
                if (n > 0) {
                    buildHeap(arr, n, 0, 1); // Create a min-heap based on age
                    printf("Min-heap based on age created.\n");
                } else {
                    printf("No data to create a heap.\n");
                }
                break;
            case 3:
                if (n > 0) {
                    buildHeap(arr, n, 1, 0); // Create a max-heap based on weight
                    printf("Max-heap based on weight created.\n");
                } else {
                    printf("No data to create a heap.\n");
                }
                break;
            case 4:
                if (n > 0) {
                    displayYoungestWeight(arr, n);
                } else {
                    printf("No data available.\n");
                }
                break;
            case 5:
                if (n > 0) {
                    struct person newPerson;
                    newPerson.name = (char *)malloc(50 * sizeof(char));
                    if (newPerson.name == NULL) {
                        printf("Memory allocation failed.\n");
                        break;
                    }

                    printf("Enter new person's details (Id Name Age Height Weight): ");
                    scanf("%d %s %d %d %d",
                          &newPerson.id, newPerson.name,
                          &newPerson.age, &newPerson.height, &newPerson.weight);

                    insertPerson(&arr, &n, newPerson);
                    printf("New person inserted into the Min-heap.\n");
                } else {
                    printf("No data available.\n");
                }
                break;
            case 6:
                if (n > 0) {
                    deleteOldestPerson(arr, &n);
                } else {
                    printf("No data available.\n");
                }
                break;
            case 7:
                exitProgram(arr, n);
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}
