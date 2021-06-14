#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
char nam[50];
int num = 3, alive = 1;

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

struct node{
    char name[50];
    struct node *next;
    struct node *prev;
};

struct node *head, *newnode, *tail;

void create(){
    head = 0;

    printf("Enter your name\n");
    scanf("%s", &nam);
    for (int i = 0; i < 3; i++) {
        newnode = (struct node *) malloc(sizeof (struct node));
        newnode->next = 0;
        newnode->prev = 0;

        if (head == 0) {
            tail = head = newnode;
            strcpy(newnode->name, nam);
        } else {
            if (i == 1)
                strcpy(newnode->name, "Abhash");
            else
                strcpy(newnode->name, "Riya");
            tail->next = newnode;
            newnode->prev = tail;
            tail = newnode;
        }
    }
}

void deletend(){
        struct node *temp;
    temp = tail;
        printf("%s Has been killed!!!\n\n", tail->name);
        tail = tail->prev;
        tail->next = 0;
        free(temp);
}

void delete(int pos){
    if (pos == 1){
        printf("!!!Game Over For You!!!\n");
        alive  = 0;
    } else {
        int i = 1;
        struct node *temp;
        temp = head;
        while (i < pos) {
            temp = temp->next;
            i++;
        }
        printf("%s Has been killed!!!\n\n", temp->name);
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
    }
}


void display(){
     struct node *temp;
     temp = head;
    while (temp!=0){
        printf("%s\n", temp->name);
        temp  = temp->next;
    }
}

void disparticular(int pos, int rnd){
    int i = 1;
    struct node *temp;
    temp = head;
    while (i < pos) {
        temp = temp->next;
        i++;
    }
    printf("%s is shooting...\n", temp->name);
    if (rnd != 0)
        printf("%s is SAFE!!!\n\n", temp->name);
}

void play(int n, unsigned seed){
    srand(seed);
    int i = 1, rnd;
    n = 6-n+1;
    printf("\t\tRussian Roullete\n");
    printf("!!!Game Begins!!!\n");
    printf("\n");
    printf("Players in the Game:\n");
    display();
    printf("---------------------------------------------------------------------------------------\n\n");
    while (num != 1 && alive == 1){
        delay(1);
        i = i%num;
        if (i == 0)
            i = num;
        rnd = rand()%n;
        disparticular(i, rnd);
        if (rnd == 0){
            if (i == num) {
                deletend();
                num--;
            }
            else {
                delete(i);
                num--;
            }
        }
        i++;
        if (alive == 1 && num != 1) {
            printf("Players in the Game:\n");
            display();
            printf("---------------------------------------------------------------------------------------\n\n");
        } else if (alive == 1 && num == 1){
            display();
            printf("HAS WON!!!!");
        }
    }

}


int main() {
    int n;
    unsigned seed = time(0);
    create();
    printf("Enter number of Bullets(MAX 5):\n");
    scanf("%d", &n);
    play(n, seed);
    return 0;
}