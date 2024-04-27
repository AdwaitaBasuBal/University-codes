#include <stdio.h>
#include <stdlib.h>

struct ITEM {
    int item_id;
    float item_profit;
    float item_weight;
    float profit_weight_ratio;
};

// Function to perform max heapify operation on the ITEM array
void maxHeapify(struct ITEM arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].profit_weight_ratio > arr[largest].profit_weight_ratio) {
        largest = left;
    }

    if (right < n && arr[right].profit_weight_ratio > arr[largest].profit_weight_ratio) {
        largest = right;
    }

    if (largest != i) {
        // Swap the items
        struct ITEM temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        maxHeapify(arr, n, largest);
    }
}

// Function to perform heap sort on the ITEM array
void heapSort(struct ITEM arr[], int n) {
    // Build max heap
    int i;
    for ( i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }

    // Extract elements from the heap one by one
    for ( i = n - 1; i >= 0; i--) {
        // Move current root to the end
        struct ITEM temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Call maxHeapify on the reduced heap
        maxHeapify(arr, i, 0);
    }
}

int main() {
    int n;
    printf("Enter the number of items: ");
    scanf("%d", &n);

    struct ITEM items[n];
    int i;
    for ( i = 0; i < n; i++) {
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%f %f", &items[i].item_profit, &items[i].item_weight);
        items[i].item_id = i + 1;
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
    }

    printf("Enter the capacity of knapsack: ");
    float capacity;
    scanf("%f", &capacity);

    heapSort(items, n);

    float maxProfit = 0;
    printf("\nItem No\tProfit\tWeight\tAmount to be taken\n");

    for ( i = n - 1; i >= 0; i--) {
        if (capacity >= items[i].item_weight) {
            printf("%d\t%.2f\t%.2f\t1.00\n", items[i].item_id, items[i].item_profit, items[i].item_weight);
            maxProfit += items[i].item_profit;
            capacity -= items[i].item_weight;
        } else {
            float fraction = capacity / items[i].item_weight;
            printf("%d\t%.2f\t%.2f\t%.2f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, fraction);
            maxProfit += items[i].item_profit * fraction;
            break;
        }
    }

    printf("\n\nMaximum profit: %.6f\n", maxProfit);

    return 0;
}

