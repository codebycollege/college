#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

typedef struct Node {
    int index;
    char cityName[30];
    int cost;
    struct Node *next;
} Node;

char cities[MAX][30];
Node *adjList[MAX];
int visited[MAX];
int numberOfCities;

int findCity(const char *name) {
    for (int i = 0; i < numberOfCities; i++) {
        if (strcmp(cities[i], name) == 0)
            return i;
    }
    return -1;
}

void addEdge(int src, int dest, int cost) {
    Node *n1 = (Node *)malloc(sizeof(Node));
    n1->index = dest;
    strcpy(n1->cityName, cities[dest]);
    n1->cost = cost;
    n1->next = adjList[src];
    adjList[src] = n1;

    Node *n2 = (Node *)malloc(sizeof(Node));
    n2->index = src;
    strcpy(n2->cityName, cities[src]);
    n2->cost = cost;
    n2->next = adjList[dest];
    adjList[dest] = n2;
}

void displayGraph() {
    printf("\n--- Graph (Adjacency List) ---\n");

    for (int i = 0; i < numberOfCities; i++) {
        printf("%s", cities[i]);

        for (Node *p = adjList[i]; p != NULL; p = p->next) {
            printf(" -> %s (%d)", p->cityName, p->cost);
        }

        printf("\n");
    }
}

void DFS(int cityIndex) {
    visited[cityIndex] = 1;

    for (Node *p = adjList[cityIndex]; p != NULL; p = p->next) {
        if (!visited[p->index]) {
            DFS(p->index);
        }
    }
}

int isGraphConnected() {
    for (int i = 0; i < numberOfCities; i++) {
        visited[i] = 0;
    }

    if (numberOfCities == 0)
        return 0;

    DFS(0);

    for (int i = 0; i < numberOfCities; i++) {
        if (!visited[i])
            return 0;
    }

    return 1;
}

int main() {
    int flights;
    char src[30], dest[30];
    int cost;

    printf("Enter number of cities: ");
    scanf("%d", &numberOfCities);

    if (numberOfCities < 1 || numberOfCities > MAX) {
        printf("Invalid number of cities!\n");
        return 1;
    }

    for (int i = 0; i < numberOfCities; i++) {
        printf("Enter name of city %d: ", i + 1);
        scanf("%29s", cities[i]);
        adjList[i] = NULL;
    }

    printf("Enter number of flights: ");
    scanf("%d", &flights);

    for (int i = 0; i < flights; i++) {
        printf("Flight %d - enter source destination cost: ", i + 1);
        scanf("%29s %29s %d", src, dest, &cost);

        int s = findCity(src);
        int d = findCity(dest);

        if (s == -1 || d == -1) {
            printf("Invalid city name! Flight skipped.\n");
            continue;
        }

        addEdge(s, d, cost);
    }

    displayGraph();

    if (isGraphConnected())
        printf("\nGraph is connected\n");
    else
        printf("\nGraph is NOT connected\n");

    for (int i = 0; i < numberOfCities; i++) {
        Node *p = adjList[i];

        while (p != NULL) {
            Node *t = p;
            p = p->next;
            free(t);
        }
    }

    return 0;
}