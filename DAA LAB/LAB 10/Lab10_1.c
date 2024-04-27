#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 5

void printPath(int parent[], int j) {
    // Base Case: If j is the source
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j]);

    printf("->%d", j);
}

void printSolution(int dist[], int n, int parent[]) {
    printf("Source Destination Cost Path\n");
    int i;
    for (i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) {
            printf("%d %d INF -\n", n, i + 1);
        } else {
            printf("%d %d %d %d", n, i + 1, dist[i], n);
            printPath(parent, i);
            printf("\n");
        }
    }
}

int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index, v;

    for (v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

void dijkstra(int graph[V][V], int src) {
    int dist[V];
    int sptSet[V];
    int parent[V];
    int i;
    int count;
    int v;

    for (i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);

        sptSet[u] = 1;

        for (v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printSolution(dist, src + 1, parent);
}

int main() {
    int graph[V][V];
    int i, j;

    printf("Enter the Number of Vertices: ");
    int vertices;
    scanf("%d", &vertices);

    printf("Enter the Graph (Adjacency Matrix):\n");
    for (i = 0; i < vertices; i++) {
        for (j = 0; j < vertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    int start_vertex;
    printf("Enter the Source Vertex: ");
    scanf("%d", &start_vertex);

    dijkstra(graph, start_vertex - 1);

    return 0;
}

