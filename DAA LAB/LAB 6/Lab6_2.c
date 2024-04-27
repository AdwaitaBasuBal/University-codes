#include <stdio.h>
#include <stdlib.h>

struct SYMBOL {
    char alphabet;
    int frequency;
    struct SYMBOL *left;
    struct SYMBOL *right;
};

struct MinPriorityQueue {
    int size;
    struct SYMBOL **heap;
};

// Function to swap two SYMBOL pointers
void swap(struct SYMBOL **x, struct SYMBOL **y) {
    struct SYMBOL *temp = *x;
    *x = *y;
    *y = temp;
}

// Function to perform min-heapify operation
void minHeapify(struct MinPriorityQueue *queue, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < queue->size && queue->heap[left]->frequency < queue->heap[smallest]->frequency) {
        smallest = left;
    }

    if (right < queue->size && queue->heap[right]->frequency < queue->heap[smallest]->frequency) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&queue->heap[i], &queue->heap[smallest]);
        minHeapify(queue, smallest);
    }
}

// Function to build a min-heap
void buildMinHeap(struct MinPriorityQueue *queue) {
	int i;
    for ( i = (queue->size - 1) / 2; i >= 0; i--) {
        minHeapify(queue, i);
    }
}

// Function to extract the minimum from the min-heap
struct SYMBOL *extractMin(struct MinPriorityQueue *queue) {
    if (queue->size == 0) {
        return NULL;
    }

    struct SYMBOL *minSymbol = queue->heap[0];
    queue->heap[0] = queue->heap[queue->size - 1];
    queue->size--;
    minHeapify(queue, 0);
    return minSymbol;
}

// Function to insert a SYMBOL into the min-heap
void insert(struct MinPriorityQueue *queue, struct SYMBOL *symbol) {
    queue->size++;
    int i = queue->size - 1;

    while (i > 0 && symbol->frequency < queue->heap[(i - 1) / 2]->frequency) {
        queue->heap[i] = queue->heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    queue->heap[i] = symbol;
}

// Function to construct the Huffman tree
struct SYMBOL *buildHuffmanTree(char alphabet[], int frequency[], int n) {
    struct MinPriorityQueue queue;
    queue.size = n;
    queue.heap = (struct SYMBOL **)malloc(n * sizeof(struct SYMBOL *));
    int i;
    for ( i = 0; i < n; i++) {
        struct SYMBOL *symbol = (struct SYMBOL *)malloc(sizeof(struct SYMBOL));
        symbol->alphabet = alphabet[i];
        symbol->frequency = frequency[i];
        symbol->left = NULL;
        symbol->right = NULL;
        queue.heap[i] = symbol;
    }

    buildMinHeap(&queue);

    while (queue.size > 1) {
        struct SYMBOL *left = extractMin(&queue);
        struct SYMBOL *right = extractMin(&queue);

        struct SYMBOL *mergedSymbol = (struct SYMBOL *)malloc(sizeof(struct SYMBOL));
        mergedSymbol->alphabet = '->'; // Placeholder for internal nodes
        mergedSymbol->frequency = left->frequency + right->frequency;
        mergedSymbol->left = left;
        mergedSymbol->right = right;

        insert(&queue, mergedSymbol);
    }

    struct SYMBOL *huffmanRoot = extractMin(&queue);

    free(queue.heap);
    return huffmanRoot;
}

// Function for in-order traversal of the Huffman tree
void inorderTraversal(struct SYMBOL *root) {
    if (root) {
        inorderTraversal(root->left);
        printf("%c ", root->alphabet);
        inorderTraversal(root->right);
    }
}

int main() {
    int n;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    char alphabet[n];
    int frequency[n];
    int i;
    printf("Enter the alphabets: ");
    for ( i = 0; i < n; i++) {
        scanf(" %c", &alphabet[i]); // Use a space before %c to consume newline character
    }

    printf("Enter its frequencies: ");
    for ( i = 0; i < n; i++) {
        scanf("%d", &frequency[i]);
    }

    struct SYMBOL *huffmanRoot = buildHuffmanTree(alphabet, frequency, n);

    printf("In-order traversal of the tree (Huffman): ");
    inorderTraversal(huffmanRoot);
    printf("\n");

    return 0;
}

