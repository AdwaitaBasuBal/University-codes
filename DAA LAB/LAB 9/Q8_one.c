#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define V 100 // Maximum number of vertices
#define INF INT_MAX

// Function to find the vertex with the minimum key value
int minKey(int key[], bool mstSet[], int n) {
    int min = INF, min_index, v;
    for ( v = 0; v < n; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the cost adjacency matrix of the minimum spanning tree
void printMST(int parent[], int graph[V][V], int n) {
	int i, j;
    printf("Cost Adjacency Matrix of the Minimum Spanning Tree:\n");
    for ( i = 0; i < n; i++) {
        for ( j = 0; j < n; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

// Function to perform Prim's algorithm
void primMST(int graph[V][V], int n, int startVertex) {
    int parent[V], i, count, v; 
    int key[V];    
    bool mstSet[V]; 

    // Initialize key values and mstSet
    for ( i = 0; i < n; i++) {
        key[i] = INF;
        mstSet[i] = false;
    }

    // Always include the starting vertex as the first vertex
    key[startVertex] = 0;
    parent[startVertex] = -1; // No parent for the starting vertex

    // Construct the MST with (n-1) edges
    for ( count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet, n); // Pick the minimum key vertex not yet included in MST
        mstSet[u] = true; // Include the picked vertex in MST

        // Update key value and parent index of adjacent vertices of the picked vertex
        for ( v = 0; v < n; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the cost adjacency matrix of the minimum spanning tree
    printMST(parent, graph, n);

    // Calculate and print the total weight of the minimum spanning tree
    int totalWeight = 0;
    for ( i = 0; i < n; i++) {
        if (parent[i] != -1) {
            totalWeight += graph[i][parent[i]];
        }
    }
    printf("Total Weight of the Spanning Tree: %d\n", totalWeight);
}

int main() {
    int n, startVertex;
    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);
    printf("Enter the Starting Vertex: ");
    scanf("%d", &startVertex);

    int graph[V][V], i, j; // Input graph represented as an adjacency matrix

    // Read the adjacency matrix from the input file "inUnAdjMat.dat"
    FILE *inputFile = fopen("inUnAdjMat.dat", "r");
    if (inputFile == NULL) {
        printf("Failed to open the input file.\n");
        return 1;
    }

    for ( i = 0; i < n; i++) {
        for ( j = 0; j < n; j++) {
            fscanf(inputFile, "%d", &graph[i][j]);
        }
    }

    fclose(inputFile);

    // Call the Prim's algorithm to find the minimum spanning tree
    primMST(graph, n, startVertex - 1); // Adjust for 0-based indexing
	return 0;
}
