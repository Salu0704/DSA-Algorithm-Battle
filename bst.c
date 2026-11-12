#include <stdio.h>
#include <stdlib.h>

struct Node {
    int id;
    struct Node *left, *right;
};

int comparisons = 0;

struct Node* createNode(int id) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->id = id;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node *root, int id) {
    if (root == NULL)
        return createNode(id);

    if (id < root->id)
        root->left = insert(root->left, id);
    else if (id > root->id)
        root->right = insert(root->right, id);

    return root;
}

struct Node* search(struct Node *root, int id) {
    if (root == NULL)
        return NULL;

    comparisons++;

    if (root->id == id)
        return root;

    if (id < root->id)
        return search(root->left, id);

    return search(root->right, id);
}

void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->id);
        inorder(root->right);
    }
}

int height(struct Node *root) {
    if (root == NULL)
        return 0;

    int l = height(root->left);
    int r = height(root->right);

    return 1 + (l > r ? l : r);
}

int main() {
    struct Node *root = NULL;
    int ids[] = {
        105, 110, 115, 120, 125, 130, 135, 140,
        145, 150, 155, 160, 165, 170, 175, 180,
        185, 190, 195, 200, 205, 210, 215, 220,
        225, 230, 235, 240, 245, 250
    };

    int n = 30, choice, id;

    for (int i = 0; i < n; i++)
        root = insert(root, ids[i]);

    while (1) {
        printf("\n\n1. Insert\n2. Search\n3. Inorder Traversal");
        printf("\n4. Tree Height\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Student ID: ");
                scanf("%d", &id);
                if (search(root, id) != NULL) {
                    printf("ID already exists!");
                } else {
                    root = insert(root, id);
                    printf("Record inserted successfully!");
                }
                break;

            case 2:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                comparisons = 0;

                if (search(root, id) != NULL)
                    printf("Record found!");
                else
                    printf("Record not found!");

                printf("\nComparisons: %d", comparisons);
                break;

            case 3:
                printf("Student IDs: ");
                inorder(root);
                break;

            case 4:
                printf("Tree Height: %d", height(root));
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice!");
        }
    }

    return 0;
}
