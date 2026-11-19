#include <stdio.h>

int main()
{
    int graph[20][20] = {0}, queue[20];
    int visited[20] = {0}, parent[20], path[20];
    int n, e, u, v, start, goal;
    int front = 0, rear = 0, i, node, len = 0;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    if (n < 1 || n > 20)
    {
        printf("Invalid");
        return 0;
    }

    printf("Enter number of edges: ");
    scanf("%d", &e);

    if (e < 0 || e > n * (n - 1) / 2)
    {
        printf("Invalid");
        return 0;
    }

    printf("Enter edges (u v): ");

    for (i = 0; i < e;)
    {
        scanf("%d%d", &u, &v);

        if (u < 0 || u >= n || v < 0 || v >= n)
        {
            printf("Invalid vertex! ");
            continue;
        }

        graph[u][v] = 1;
        graph[v][u] = 1;
        i++;
    }

    printf("Enter start and destination: ");
    scanf("%d%d", &start, &goal);

    if (start < 0 || start >= n || goal < 0 || goal >= n)
    {
        printf("Invalid vertex!");
        return 0;  
    }

    for (i = 0; i < n; i++)
        parent[i] = -1;

    queue[rear++] = start;
    visited[start] = 1;

    printf("BFS Traversal: ");

    while (front < rear)
    {
        node = queue[front++];
        printf("%d ", node);

        for (i = 0; i < n; i++)
        {
            if (graph[node][i] == 1 && !visited[i])
            {
                visited[i] = 1;
                parent[i] = node;
                queue[rear++] = i;
            }
        }
    }

    if (!visited[goal])
        printf("\nNo path exists");
    else
    {
        node = goal;

        while (node != -1)
        {
            path[len++] = node;
            node = parent[node];
        }

        printf("\nShortest Path: ");

        for (i = len - 1; i >= 0; i--)
            printf("%d ", path[i]);

        printf("\nDistance: %d\n", len - 1);
    }

    return 0;
}
