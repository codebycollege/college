#include <stdio.h>

#define MAX 5

int front = -1, rear = -1;
int queue[MAX];

void Add() {
    if ((rear + 1) % MAX == front) {
        printf("Queue is Full\n");
        return;
    }

    int job;

    printf("Enter the job number to be added: ");
    scanf("%d", &job);

    if (front == -1 && rear == -1) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % MAX;
    }

    queue[rear] = job;

    printf("Job added successfully\n");
}

void delete() {
    if (front == -1) {
        printf("Queue is Empty\n");
        return;
    }

    printf("Deleted job: %d\n", queue[front]);

    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % MAX;
    }
}

void display() {
    if (front == -1) {
        printf("Queue is Empty\n");
        return;
    }

    int i = front;

    printf("The jobs in the queue are: ");

    while (i != rear) {
        printf("%d ", queue[i]);
        i = (i + 1) % MAX;
    }

    printf("%d\n", queue[rear]);
}

int main() {
    int choice;

    do {
        printf("\n===== JOB QUEUE =====\n");
        printf("1. Add a job\n");
        printf("2. Delete a job\n");
        printf("3. Display the jobs\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                Add();
                break;

            case 2:
                delete();
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Exiting the program\n");
                break;

            default:
                printf("Invalid choice, please try again\n");
        }

    } while (choice != 4);

    return 0;
}