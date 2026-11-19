
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 26

typedef struct TrieNode
{
    struct TrieNode *children[SIZE];
    int isEndOfWord;
} TrieNode;

// Create Node
TrieNode *createNode()
{
    TrieNode *newNode = malloc(sizeof(TrieNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->isEndOfWord = 0;

    for (int i = 0; i < SIZE; i++)
        newNode->children[i] = NULL;

    return newNode;
}

// Insert
void insert(TrieNode *root, char word[])
{
    TrieNode *temp = root;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';

        if (temp->children[index] == NULL)
            temp->children[index] = createNode();

        temp = temp->children[index];
    }

    temp->isEndOfWord = 1;
    printf("Word inserted successfully.\n");
}

// Search
int search(TrieNode *root, char word[])
{
    TrieNode *temp = root;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';

        if (temp->children[index] == NULL)
            return 0;

        temp = temp->children[index];
    }

    return temp->isEndOfWord;
}

// Display
void displayWords(TrieNode *root, char word[], int depth)
{
    if (root->isEndOfWord)
    {
        word[depth] = '\0';
        printf("%s\n", word);
    }

    for (int i = 0; i < SIZE; i++)
    {
        if (root->children[i] != NULL)
        {
            word[depth] = 'a' + i;
            displayWords(root->children[i], word, depth + 1);
        }
    }
}

// Autocomplete
void autocomplete(TrieNode *root, char prefix[])
{
    TrieNode *temp = root;

    for (int i = 0; prefix[i] != '\0'; i++)
    {
        int index = prefix[i] - 'a';

        if (temp->children[index] == NULL)
        {
            printf("No words found!\n");
            return;
        }

        temp = temp->children[index];
    }

    char word[100];
    strcpy(word, prefix);

    printf("Words starting with %s:\n", prefix);
    displayWords(temp, word, strlen(prefix));
}

// Main
int main()
{
    TrieNode *root = createNode();
    int choice;
    char word[100];

    while (1)
    {
        printf("\n--- TRIE ---\n");
        printf("1. Insert\n2. Search\n3. Autocomplete\n");
        printf("4. Display All\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter word: ");
            scanf("%99s", word);
            for (int i = 0; word[i]; i++)
                word[i] = tolower((unsigned char)word[i]);
            insert(root, word);
            break;

        case 2:
            printf("Enter word: ");
            scanf("%99s", word);
            for (int i = 0; word[i]; i++)
                word[i] = tolower((unsigned char)word[i]);
            printf(search(root, word) ? "Word found.\n" : "Word not found.\n");
            break;

        case 3:
            printf("Enter prefix: ");
            scanf("%99s", word);
            for (int i = 0; word[i]; i++)
                word[i] = tolower((unsigned char)word[i]);
            autocomplete(root, word);
            break;

        case 4:
        {
            char result[100];
            printf("All words:\n");
            displayWords(root, result, 0);
            break;
        }

        case 5:
            printf("Program terminated.\n");
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }
}
