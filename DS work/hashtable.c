#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
typedef struct Node
{
    int key, value;
    struct Node *next;
} Node;
typedef struct
{
    int key, value, status;
} Entry;
Node *chain[SIZE] = {NULL};
Entry table[SIZE];
int hash(int key)
{
    return (key % SIZE + SIZE) % SIZE;
}
// Separate Chaining
void insertChain(int k, int v)
{
    int i = hash(k);
    Node *n = malloc(sizeof(Node));
    if (!n)
        return;
    n->key = k;
    n->value = v;
    n->next = chain[i];
    chain[i] = n;
    printf("Inserted using Chaining\n");
}
// Linear Probing
void insertOpen(int k, int v)
{
    int i = hash(k);
    for (int j = 0; j < SIZE; j++)
    {
        int p = (i + j) % SIZE;
        if (table[p].status != 1)
        {
            table[p] = (Entry){k, v, 1};
            printf("Inserted at index %d\n", p);
            return;
        }
    }
    printf("Table Full\n");
}
// Search
int search(int k)
{
    int i = hash(k);
    for (int j = 0; j < SIZE; j++)
    {
        int p = (i + j) % SIZE;
        if (table[p].status == 0)
            break;
        if (table[p].status == 1 && table[p].key == k)
        {
            printf("Found! Value = %d\n", table[p].value);
            return 1;
        }
    }
    for (Node *n = chain[i]; n; n = n->next)
    {
        if (n->key == k)
        {
            printf("Found! Value = %d\n", n->value);
            return 1;
        }
    }
    printf("Key Not Found\n");
    return 0;
}
// Delete
void deleteKey(int k)
{
    int i = hash(k);
    for (int j = 0; j < SIZE; j++)
    {
        int p = (i + j) % SIZE;
        if (table[p].status == 0)
            break;
        if (table[p].status == 1 && table[p].key == k)
        {
            table[p].status = 2;
            printf("Key Deleted\n");
            return;
        }
    }
    Node *n = chain[i], *prev = NULL;
    while (n)
    {
        if (n->key == k)
        {
            if (prev)
                prev->next = n->next;
            else
                chain[i] = n->next;
            free(n);
            printf("Key Deleted\n");
            return;
        }
        prev = n;
        n = n->next;
    }
    printf("Key Not Found\n");
}
int main()
{
    int choice, k, v, method;
    while (1)
    {
        printf("\n1.Insert  2.Search  3.Delete  4.Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter key and value: ");
            scanf("%d%d", &k, &v);
            int i = hash(k);
            if (table[i].status == 0 && chain[i] == NULL)
            {
                table[i] = (Entry){k, v, 1};
                printf("Inserted at index %d\n", i);
            }
            else
            {
                printf("Collision! 1.Seperate Chaining  2.Open Addressing: ");
                scanf("%d", &method);

                if (method == 1)
                    insertChain(k, v);
                else if (method == 2)
                    insertOpen(k, v);
                else
                    printf("Invalid Method\n");
            }
            break;
        case 2:
            printf("Enter key: ");
            scanf("%d", &k);
            search(k);
            break;
        case 3:
            printf("Enter key: ");
            scanf("%d", &k);
            deleteKey(k);
            break;
        case 4:
            return 0;
        default:
            printf("Invalid Choice\n");
        }
    }
}
