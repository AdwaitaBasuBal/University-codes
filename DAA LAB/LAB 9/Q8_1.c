#include <stdio.h>
#include <stdlib.h>

// Node structure for adjacency list
struct Node {
    int data;
    struct Node* next;
};

// Graph structure with an array of adjacency lists
struct Graph {
    int V; // Number of vertices
    struct Node** adjList; // Array of adjacency lists
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
struct Graph* createGraph(int V) {
	int i = 0;
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->adjList = (struct Node*)malloc(V * sizeof(struct Node));
    for (i = 0; i < V; ++i) {
        graph->adjList[i] = NULL;
    }

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Add an edge from dest to src (since the graph is undirected)
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// Function to print the degree and adjacent vertices of each node
void printGraph(struct Graph* graph) {
	int i = 0;
    for (i = 0; i < graph->V; ++i) {
        printf("Node %d - Degree: ", i + 1);

        // Count degree
        int degree = 0;
        struct Node* current = graph->adjList[i];
        while (current) {
            ++degree;
            current = current->next;
        }

        printf("%d, Adjacent Vertices: ", degree);

        // Print adjacent vertices
        current = graph->adjList[i];
        while (current) {
            printf("%d ", current->data + 1); // +1 for 1-based indexing
            current = current->next;
        }

        printf("\n");
    }
}

int main() {
    int n, m, i; // n: number of vertices, m: number of edges
    printf("Enter the number of vertices and edges: ");
    scanf("%d %d", &n, &m);

    struct Graph* graph = createGraph(n);

    printf("Enter the edges (u v): \n");
    for (i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u - 1, v - 1); // -1 for 0-based indexing
    }

    printf("\nGraph Representation:\n");
    printGraph(graph);

    return 0;
}
