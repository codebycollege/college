#include <stdio.h>

// Selection Sort
void selection_sort(float arr[], int n) {
    float temp;

    for (int i = 0; i < n - 1; i++) {
        int min = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[min] > arr[j]) {
                min = j;
            }
        }

        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

// Bubble Sort
void bubble_sort(float arr[], int n) {
    float temp;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {

            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Display Array
void display(float arr[], int n) {
    printf("\nPercentages are:\n");

    for (int i = 0; i < n; i++) {
        printf("%.2f\n", arr[i]);
    }

    printf("\n");
}

// Display Top Five Percentages
void topfive(float arr[], int n) {
    int count;

    printf("\nTop Five Percentages:\n");

    count = (n < 5) ? n : 5;

    for (int i = n - 1; i >= n - count; i--) {
        printf("%.2f\n", arr[i]);
    }
}

// Main Function
int main() {

    float per[100];
    int n, i, choice;

    printf("Enter the number of students: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100) {
        printf("Invalid number of students!\n");
        return 0;
    }

    printf("Enter the First Year percentages:\n");

    for (i = 0; i < n; i++) {
        scanf("%f", &per[i]);
    }

    do {

        printf("\n========== MENU ==========\n");
        printf("1. Selection Sort\n");
        printf("2. Bubble Sort\n");
        printf("3. Display Percentages\n");
        printf("4. Display Top Five Percentages\n");
        printf("5. Exit\n");

        printf("==========================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                selection_sort(per, n);
                printf("\nArray sorted using Selection Sort.\n");
                display(per, n);
                break;

            case 2:
                bubble_sort(per, n);
                printf("\nArray sorted using Bubble Sort.\n");
                display(per, n);
                break;

            case 3:
                display(per, n);
                break;

            case 4:
                // Sort in ascending order before displaying top five
                bubble_sort(per, n);
                topfive(per, n);
                break;

            case 5:
                printf("\nExiting the program...\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 5);

    return 0;
}