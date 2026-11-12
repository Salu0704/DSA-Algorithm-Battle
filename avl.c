#include <stdio.h>
#include <stdlib.h>

struct Node {
    int id, height;
    struct Node *left, *right;
};

int comparisons = 0;

int max(int a, int b) {
    return a > b ? a : b;
}

int height(struct Node *n) {
    return n == NULL ? 0 : n->height;
}

struct Node* createNode(int id) {
    struct Node *n = malloc(sizeof(struct Node));
    n->id = id;
    n->left = n->right = NULL;
    n->height = 1;
    return n;
}

int balance(struct Node *n) {
    return n == NULL ? 0 : height(n->left) - height(n->right);
}

struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *t = x->right;

    x->right = y;
    y->left = t;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *t = y->left;

    y->left = x;
    x->right = t;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

struct Node* insert(struct Node *root, int id) {
    if (root == NULL)
        return createNode(id);

    if (id < root->id)
        root->left = insert(root->left, id);
    else if (id > root->id)
        root->right = insert(root->right, id);
    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int b = balance(root);

    if (b > 1 && id < root->left->id)
        return rightRotate(root);

    if (b < -1 && id > root->right->id)
        return leftRotate(root);

    if (b > 1 && id > root->left->id) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (b < -1 && id < root->right->id) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

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

int main() {
    struct Node *root = NULL;

    int ids[] = {
        105,110,115,120,125,130,135,140,
        145,150,155,160,165,170,175,180,
        185,190,195,200,205,210,215,220,
        225,230,235,240,245,250
    };

    int n = 30, choice, id;

    for (int i = 0; i < n; i++)
        root = insert(root, ids[i]);

    while (1) {
        printf("\n\n1. Insert\n2. Search");
        printf("\n3. Inorder Traversal\n4. Tree Height");
        printf("\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Student ID: ");
                scanf("%d", &id);

                if (search(root, id))
                    printf("ID already exists!");
                else {
                    root = insert(root, id);
                    printf("Record inserted successfully!");
                }
                break;

            case 2:
                printf("Enter ID to search: ");
                scanf("%d", &id);

                comparisons = 0;

                if (search(root, id))
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
