#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_VERTICES 10
#define NUM_EDGES 20
#define INF 999999

typedef struct {
    int u;
    int v;
    int weight;
} Edge;

int adj[MAX_VERTICES][MAX_VERTICES];
Edge edges[NUM_EDGES];

void dfs(int v, bool visited[]) {
    visited[v] = true;
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (adj[v][i] != INF && !visited[i]) {
            dfs(i, visited);
        }
    }
}

bool is_connected() {
    bool visited[MAX_VERTICES] = { false };
    dfs(0, visited);
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (!visited[i]) return false;
    }
    return true;
}

void generate_graph() {
    while (1) {
        for (int i = 0; i < MAX_VERTICES; i++) {
            for (int j = 0; j < MAX_VERTICES; j++) {
                if (i == j) adj[i][j] = 0;
                else adj[i][j] = INF;
            }
        }

        int count = 0;
        while (count < NUM_EDGES) {
            int u = rand() % MAX_VERTICES;
            int v = rand() % MAX_VERTICES;

            if (u == v || adj[u][v] != INF) continue;

            int weight = (rand() % 100) + 1;

            adj[u][v] = weight;
            adj[v][u] = weight;

            edges[count].u = (u < v) ? u : v;
            edges[count].v = (u < v) ? v : u;
            edges[count].weight = weight;

            count++;
        }

        if (is_connected()) break;
    }
}

int get_min_vertex(int dist[], bool visited[]) {
    int min_val = INF;
    int min_index = -1;

    for (int i = 0; i < MAX_VERTICES; i++) {
        if (!visited[i] && dist[i] < min_val) {
            min_val = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void print_path(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%d", j);
        return;
    }
    print_path(parent, parent[j]);
    printf(" -> %d", j);
}

void dijkstra(int start) {
    int dist[MAX_VERTICES];
    bool visited[MAX_VERTICES];
    int parent[MAX_VERTICES];

    for (int i = 0; i < MAX_VERTICES; i++) {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[start] = 0;

    for (int count = 0; count < MAX_VERTICES - 1; count++) {
        int u = get_min_vertex(dist, visited);
        if (u == -1) break;

        visited[u] = true;

        for (int v = 0; v < MAX_VERTICES; v++) {
            if (!visited[v] && adj[u][v] != INF) {
                if (dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    for (int target = start + 1; target < MAX_VERTICES; target++) {
        printf("%d -> %d\n", start, target);
        printf("Path     : ");
        print_path(parent, target);
        printf("\nDistance : %d\n\n", dist[target]);
    }
}

int main() {
    srand((unsigned int)time(NULL));

    generate_graph();

    printf("Graph\n");
    printf("Vertices : 10\n");
    printf("Edges    : 20\n\n");

    printf("Edges\n");
    for (int i = 0; i < NUM_EDGES; i++) {
        printf("(%d, %d) Weight: %d\n", edges[i].u, edges[i].v, edges[i].weight);
    }
    printf("\n");

    printf("Shortest Paths\n\n");
    for (int start = 0; start < MAX_VERTICES; start++) {
        dijkstra(start);
    }

    printf("Total vertex pairs : 45\n");

    return 0;
}