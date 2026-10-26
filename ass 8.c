#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

typedef struct node Node;

Node *createNode(int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Node *insert(Node *root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    else
        printf("Duplicate values are not allowed.\n");

    return root;
}

void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int height(Node *root) {
    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}

int findMin(Node *root) {
    if (root == NULL)
        return -1;

    while (root->left != NULL)
        root = root->left;

    return root->data;
}

void mirror(Node *root) {
    if (root == NULL)
        return;

    Node *temp = root->left;
    root->left = root->right;
    root->right = temp;

    mirror(root->left);
    mirror(root->right);
}

int search(Node *root, int value) {
    if (root == NULL)
        return 0;

    if (root->data == value)
        return 1;

    if (value < root->data)
        return search(root->left, value);

    return search(root->right, value);
}

int main() {
    Node *root = NULL;
    int choice, value, n, i;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter values to construct BST:\n");

    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    do {
        printf("\n\n--- BINARY SEARCH TREE ---\n");
        printf("1. Insert new node\n");
        printf("2. Longest path from root\n");
        printf("3. Minimum data value\n");
        printf("4. Mirror the tree\n");
        printf("5. Search a value\n");
        printf("6. Display inorder traversal\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                printf("Node inserted successfully.\n");
                break;

            case 2:
                printf("Number of nodes in longest path: %d\n", height(root));
                break;

            case 3:
                if (root == NULL)
                    printf("Tree is empty.\n");
                else
                    printf("Minimum data value: %d\n", findMin(root));
                break;

            case 4:
                mirror(root);
                printf("Left and right pointers swapped.\n");
                printf("Inorder traversal of mirrored tree: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                printf("Enter value to search: ");
                scanf("%d", &value);

                if (search(root, value))
                    printf("Value found in the tree.\n");
                else
                    printf("Value not found in the tree.\n");
                break;

            case 6:
                printf("Inorder traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 7:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 7);

    return 0;
}