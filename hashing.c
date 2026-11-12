#include <stdio.h>

#define SIZE 50

int table[SIZE];
int collisions = 0;

void initialize() {
    for (int i = 0; i < SIZE; i++)
        table[i] = -1;
}

void insert(int id) {
    int index = id % SIZE;
    int start = index;

    while (table[index] != -1) {
        if (table[index] == id) {
            printf("ID already exists!\n");
            return;
        }

        collisions++;
        index = (index + 1) % SIZE;

        if (index == start) {
            printf("Hash table is full!\n");
            return;
        }
    }

    table[index] = id;
    printf("Record inserted successfully!\n");
}

int search(int id) {
    int index = id % SIZE;
    int count = 0;

    while (table[index] != -1 && count < SIZE) {
        if (table[index] == id)
            return count + 1;

        index = (index + 1) % SIZE;
        count++;
    }

    return 0;
}

void display() {
    printf("\nHash Table:\n");

    for (int i = 0; i < SIZE; i++) {
        if (table[i] != -1)
            printf("%d : %d\n", i, table[i]);
    }
}

int main() {
    int ids[] = {
        105,110,115,120,125,130,135,140,
        145,150,155,160,165,170,175,180,
        185,190,195,200,205,210,215,220,
        225,230,235,240,245,250
    };

    int choice, id, comparisons;

    initialize();

    for (int i = 0; i < 30; i++)
        insert(ids[i]);

    while (1) {
        printf("\n1. Insert\n2. Search");
        printf("\n3. Display\n4. Collisions");
        printf("\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Student ID: ");
                scanf("%d", &id);
                insert(id);
                break;

            case 2:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                comparisons = search(id);

                if (comparisons)
                    printf("Record found!");
                else
                    printf("Record not found!");

                printf("\nComparisons: %d", comparisons);
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Total collisions: %d", collisions);
                break;

            case 5:
                return 0;

            default:
                printf("Invalid choice!");
        }
    }
}
