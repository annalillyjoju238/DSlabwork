#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Trie
{
    struct Trie *child[26];
    int end;
};
struct Trie *create()
{
    return calloc(1, sizeof(struct Trie));
}
void insert(struct Trie *r, char *s)
{
    while (*s)
    {
        int i = *s++ - 'a';
        if (!r->child[i])
            r->child[i] = create();
        r = r->child[i];
    }
    r->end = 1;
    printf("Word inserted\n");
}
int search(struct Trie *r, char *s)
{
    while (*s)
    {
        int i = *s++ - 'a';
        if (!r->child[i])
            return 0;
        r = r->child[i];
    }
    return r->end;
}
void display(struct Trie *r, char *s, int n)
{
    if (r->end)
    {
        s[n] = '\0';
        printf("%s\n", s);
    }
    for (int i = 0; i < 26; i++)
        if (r->child[i])
        {
            s[n] = i + 'a';
            display(r->child[i], s, n + 1);
        }
}
void autocomplete(struct Trie *r, char *s)
{
    char word[100];
    strcpy(word, s);
    int n = strlen(s);
    while (*s)
    {
        int i = *s++ - 'a';
        if (!r->child[i])
        {
            printf("No suggestions found\n");
            return;
        }
        r = r->child[i];
    }
    printf("Suggestions:\n");
    display(r, word, n);
}
int main()
{
    struct Trie *root = create();
    int ch;
    char s[100];
    while (1)
    {
        printf("\n1. Insert\n2. Search\n3. Autocomplete\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
        if (ch == 4)
            break;
        if (ch < 1 || ch > 3)
            continue;
        printf("Enter word/prefix: ");
        scanf("%99s", s);
        if (ch == 1)
            insert(root, s);
        else if (ch == 2)
            printf(search(root, s) ? "Word found\n" : "Word not found\n");
        else
            autocomplete(root, s);
    }
    return 0;
}
