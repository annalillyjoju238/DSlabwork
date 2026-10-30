
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

// Separate Chaining
typedef struct Node
{
    int key, value;
    struct Node *next;
} Node;

Node *chainTable[SIZE] = {NULL};

// Open Addressing
typedef struct
{
    int key, value, status;
} Entry;

Entry openTable[SIZE];

// Hash Function
int hashFunction(int key)
{
    return key % SIZE;
}

// Initialize
void initialize()
{
    int i;
    for (i = 0; i < SIZE; i++)
        openTable[i].status = 0;
}

// Insert
void insert()
{
    int key, value, index, choice;

    printf("Enter key and value: ");
    scanf("%d%d", &key, &value);

    index = hashFunction(key);
    printf("Hash index = %d\n", index);

    if (openTable[index].status == 0 &&
        chainTable[index] == NULL)
    {
        openTable[index].key = key;
        openTable[index].value = value;
        openTable[index].status = 1;
        printf("Inserted at index %d\n", index);
    }
    else
    {
        printf("Collision occurred!\n");
        printf("1. Separate Chaining\n");
        printf("2. Open Addressing\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            Node *newNode = malloc(sizeof(Node));

            if (newNode == NULL)
            {
                printf("Memory allocation failed!\n");
                return;
            }

            newNode->key = key;
            newNode->value = value;
            newNode->next = chainTable[index];
            chainTable[index] = newNode;

            printf("Inserted using Chaining\n");
        }
        else if (choice == 2)
        {
            int i, pos, found = 0;

            for (i = 0; i < SIZE; i++)
            {
                pos = (index + i) % SIZE;

                if (openTable[pos].status != 1)
                {
                    openTable[pos].key = key;
                    openTable[pos].value = value;
                    openTable[pos].status = 1;
                    printf("Inserted at index %d\n", pos);
                    found = 1;
                    break;
                }
            }

            if (!found)
                printf("Hash table is full!\n");
        }
        else
            printf("Invalid choice!\n");
    }
}

// Search
void search()
{
    int key, index, i, pos;
    Node *temp;

    printf("Enter key to search: ");
    scanf("%d", &key);

    index = hashFunction(key);

    // Search Open Addressing
    for (i = 0; i < SIZE; i++)
    {
        pos = (index + i) % SIZE;

        if (openTable[pos].status == 0)
            break;

        if (openTable[pos].status == 1 &&
            openTable[pos].key == key)
        {
            printf("Found! Value = %d\n",
                   openTable[pos].value);
            return;
        }
    }

    // Search Chaining
    temp = chainTable[index];

    while (temp != NULL)
    {
        if (temp->key == key)
        {
            printf("Found! Value = %d\n", temp->value);
            return;
        }
        temp = temp->next;
    }

    printf("Key not found!\n");
}

// Delete
void deleteKey()
{
    int key, index, i, pos;
    Node *temp, *prev = NULL;

    printf("Enter key to delete: ");
    scanf("%d", &key);

    index = hashFunction(key);

    // Delete Open Addressing
    for (i = 0; i < SIZE; i++)
    {
        pos = (index + i) % SIZE;

        if (openTable[pos].status == 0)
            break;

        if (openTable[pos].status == 1 &&
            openTable[pos].key == key)
        {
            openTable[pos].status = 2;
            printf("Key deleted!\n");
            return;
        }
    }

    // Delete Chaining
    temp = chainTable[index];

    while (temp != NULL)
    {
        if (temp->key == key)
        {
            if (prev == NULL)
                chainTable[index] = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            printf("Key deleted!\n");
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("Key not found!\n");
}

// Main Function
int main()
{
    int choice;

    initialize();

    while (1)
    {
        printf("\n--- HASH TABLE ---\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            insert();
            break;
        case 2:
            search();
            break;
        case 3:
            deleteKey();
            break;
        case 4:
            return 0;
        default:
            printf("Invalid choice!\n");
        }
    }
}
