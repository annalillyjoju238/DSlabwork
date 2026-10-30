
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key, height;
    struct Node *left, *right;
} Node;

// Helper functions
int height(Node *n)
{
    return n == NULL ? 0 : n->height;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

Node *createNode(int key)
{
    Node *n = malloc(sizeof(Node));
    if (n == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    n->key = key;
    n->height = 1;
    n->left = n->right = NULL;
    return n;
}

int getBalance(Node *n)
{
    return n == NULL ? 0 : height(n->left) - height(n->right);
}

// Rotations
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *t = x->right;

    x->right = y;
    y->left = t;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *t = y->left;

    y->left = x;
    x->right = t;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

// Insert
Node *insert(Node *root, int key)
{
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
    {
        printf("Duplicate key!\n");
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int b = getBalance(root);

    if (b > 1 && key < root->left->key)
        return rightRotate(root); // LL

    if (b < -1 && key > root->right->key)
        return leftRotate(root); // RR

    if (b > 1 && key > root->left->key)
    { // LR
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (b < -1 && key < root->right->key)
    { // RL
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Find minimum node
Node *minValueNode(Node *n)
{
    while (n->left != NULL)
        n = n->left;
    return n;
}

// Delete
Node *deleteNode(Node *root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        if (root->left == NULL || root->right == NULL)
        {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                free(root);
                return NULL;
            }

            *root = *temp;
            free(temp);
        }
        else
        {
            Node *temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int b = getBalance(root);

    if (b > 1 && getBalance(root->left) >= 0)
        return rightRotate(root); // LL

    if (b > 1 && getBalance(root->left) < 0)
    { // LR
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (b < -1 && getBalance(root->right) <= 0)
        return leftRotate(root); // RR

    if (b < -1 && getBalance(root->right) > 0)
    { // RL
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Search
Node *search(Node *root, int key)
{
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

// Traversals
void inorder(Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void preorder(Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

// Main
int main()
{
    Node *root = NULL;
    int choice, key;

    while (1)
    {
        printf("\n1.Insert\n2.Delete\n3.Search\n");
        printf("4.Inorder\n5.Preorder\n6.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter key: ");
            scanf("%d", &key);
            root = insert(root, key);
            break;

        case 2:
            printf("Enter key: ");
            scanf("%d", &key);

            if (search(root, key) == NULL)
                printf("Key not found!\n");
            else
            {
                root = deleteNode(root, key);
                printf("Key deleted!\n");
            }
            break;

        case 3:
            printf("Enter key: ");
            scanf("%d", &key);
            printf(search(root, key) ? "Key found!\n" : "Key not found!\n");
            break;

        case 4:
            printf("Inorder: ");
            inorder(root);
            printf("\n");
            break;

        case 5:
            printf("Preorder: ");
            preorder(root);
            printf("\n");
            break;

        case 6:
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }
}
