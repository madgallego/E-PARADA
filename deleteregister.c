#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

typedef struct Profile {
    char plateNum[MAX];
    char profileID[MAX];
    char type;  // 'A' for cars, 'B' for motorcycles
    struct Profile *nxtPtr;
} Profile;

void clearTerminal() {
    printf("\e[1;1H\e[2J");
}
//Adds new lines
void space_up(int lines) {
    for (int i = 0; i < lines; i++)
        printf("\n");
}
//Adds n spaces
void space_left(int spaces) {
    for (int i = 0; i < spaces; i++)
        printf(" ");
}
//Delays execution of next code for n seconds
void delay(int seconds) {
    clock_t start_time = clock();
    clock_t current_time;
    double elapsed_time;

    do {
        current_time = clock();
        elapsed_time = (double)(current_time - start_time) / CLOCKS_PER_SEC;
    } while (elapsed_time < seconds);
}

Profile *create_list(FILE *inrec){
    Profile *head = NULL;
    Profile *p = NULL;
    Profile *prev = NULL;
    char tempPlate[MAX];
    char tempProfileID[MAX];
    char tempType;

    while (fscanf(inrec, "%s %s %c", tempPlate, tempProfileID, &tempType) == 3) {
      p = (Profile*)malloc(sizeof(Profile));
      strcpy(p->plateNum, tempPlate);
      strcpy(p->profileID, tempProfileID);
      p->type = tempType;
      p->nxtPtr = NULL;
      if (head == NULL) {
          head = p;
      }
      else {
          prev->nxtPtr = p;
      }
      prev = p;
    }
    return head;
}

void print(Profile*head){
    Profile * p;
    p = head;

    while(p != NULL){
        printf("%s %s %c", p->plateNum, p->profileID, p->type);
        printf("\n");
        p = p->nxtPtr;
    }
}

void freeProfile(Profile ** head){
    Profile * p;
    while(*head != NULL){
        p = *head;
        *head = (*head)->nxtPtr;
        free(p);
    }
}

int del(FILE * ifp, Profile**head, char plate[]){//function to delete profile in records
    Profile * p, * q;
    p = *head;

    if(strcmp(p->plateNum, plate) == 0){
        *head = p->nxtPtr;
        free(p);
    }
    else{
        while(p != NULL && strcmp(p->plateNum, plate) != 0){
            q = p;
            p = p->nxtPtr;
        }
        if(p == NULL){
            return 0;
        }
        else if(strcmp(p->plateNum, plate) == 0){
            q->nxtPtr = p->nxtPtr;
            free(p);
        }
    }

    p = *head;
    while(p != NULL){
        fprintf(ifp, "%s %s %c\n", p->plateNum, p->profileID, p->type);
        p = p->nxtPtr;
    }
    return 1;
}

//Gawin nalang na separate from register yung delete, bale may PMS (Park In and Park Out), Register Profile, and Delete Profile
int main(){
    Profile * head;
    FILE * ifp = fopen("file.txt", "r");
    char plate[100];
    int option, archv;

    if (ifp == NULL) {
       printf("Error opening files.\n");
       return 1;
    }

    head = create_list(ifp);
    print(head);
    fclose(ifp);

    ifp = fopen("file.txt","w");

    
    while(1){
        space_up(3);
        space_left(20);
        printf("================================================\n");
        space_left(36);
        printf("DELETE PROFILE\n");
        space_left(20);
        printf("================================================\n");
        space_up(2);
        space_left(20);
        printf("Enter Plate Number: ");
        scanf("%s", plate);
        archv = del(ifp, &head, plate);
        delay(1);
        if(archv == 0){
            space_up(1);
            space_left(20);
            printf("Plate Number not found\n");
            space_up(2);
            space_left(25);
            printf("1. End Transaction\n");
            space_left(25);
            printf("2. Try Again\n");
            space_up(2);
            space_left(25);
            printf("Choice: ");
            scanf("%d", &option);
            if(option == 1){
                break;
            }
            else if(option == 2){
                delay(1);
                clearTerminal();
                continue;
            }
        }
        else if(archv == 1){
            space_up(1);
            space_left(20);
            printf("Successfully deleted!\n");
            break;
        }
    }
    
    print(head);
    freeProfile(&head);
    fclose(ifp);
    return 0;
}