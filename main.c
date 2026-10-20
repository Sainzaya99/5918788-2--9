
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define V 10
#define E 20
#define INF 1000000

int graph[V][V];
int dist[V][V];
int next[V][V];

void createGraph() {
    int i, j;
    int count = 0;

    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = INF;
        }
    }

    for (i = 1; i < V; i++) {
        int j = rand() % i;
        int w = rand() % 100 + 1;

        graph[i][j] = w;
        graph[j][i] = w;
        count++;
    }

    while (count < E) {
        int u = rand() % V;
        int v = rand() % V;

        if (u != v && graph[u][v] == INF) {
            int w = rand() % 100 + 1;

            graph[u][v] = w;
            graph[v][u] = w;
            count++;
        }
    }
}

void printGraph() {
    int i, j;

    printf("Graph\n");
    printf("Vertices : %d\n", V);
    printf("Edges    : %d\n", E);
    printf("\nEdge       Weight\n");

    for (i = 0; i < V; i++) {
        for (j = i + 1; j < V; j++) {
            if (graph[i][j] != INF) {
                printf("(%d, %d)       %d\n",
                    i, j, graph[i][j]);
            }
        }
    }
}

void floydWarshall() {
    int i, j, k;

    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];

            if (i != j && graph[i][j] != INF)
                next[i][j] = j;
            else
                next[i][j] = -1;
        }
    }

    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {

                if (dist[i][k] != INF &&
                    dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {

                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

void printPath(int u, int v) {
    if (next[u][v] == -1) {
        printf("No path");
        return;
    }

    printf("%d", u);

    while (u != v) {
        u = next[u][v];
        printf(" -> %d", u);
    }
}

void printShortestPaths() {
    int i, j;
    int count = 0;

    printf("\nShortest Paths\n\n");

    for (i = 0; i < V; i++) {
        for (j = i + 1; j < V; j++) {

            printf("%d -> %d\n", i, j);

            printf("Path     : ");
            printPath(i, j);

            printf("\nDistance : %d\n\n", dist[i][j]);

            count++;
        }
    }

    printf("Total vertex pairs : %d\n", count);
}

int main() {
    srand(time(NULL));

    createGraph();
    printGraph();

    floydWarshall();
    printShortestPaths();

    return 0;
}
