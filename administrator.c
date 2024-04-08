#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <time.h>
#define MAX 100

typedef struct { //struct of Admin
	char user[MAX];
	char passkey[MAX];

} Admin;

struct node { //struct of Profile
	char plateNum [MAX];
	char profileID [MAX];
	char type;
    struct node * nxtPtr;
};// for records linked list
typedef struct node Profile;

/*void traverseProfile(void){}
void dscrpncyCheck(void){}
void registerProfile(void)*/
Profile *create_list(FILE*inrec);//read profile records from file
void display(Profile*head);//to display data from records file on screen(temp function)
void Administrator(Profile **head);

/*void Administrator(Profile **head){
    Admin admin;
    Profile * p, *new;
    int option;
    char plate[MAX];
    p = head;

    printf("Admin: ");
    scanf("%s", admin.user);
    printf("Password: ");
    scanf("%s", admin.passkey);

    printf("\n1. PMS\n2. Search Profile\n");
    scanf("%d", &option);

    if(option == 1){ //PMS instructions
        printf("\nChoose Action:\n1. Park In\n2. Park Out\n");
        scanf("%d", &option);
        if(option == 1){ //if Park In
            traverseProfile();
        }
        else if(option == 2){ //if Park Out
            dscrpncyCheck();
        }
    }
    else if(option == 2){ //Search Profile Instructions
        printf("Enter Plate Number: ");
        scanf("%s", plate);
        while(1){ //Traverse the linked list
            if (p->nxtPtr == NULL){ //If plate number not found
                printf("\nPlate number not found\n");
                printf("\n1. End Transaction\n2. Register Profile\n");
                scanf("%d", &option);
                if(option == 1){
                    break;
                }
                else if(option == 2){ //Profile register
                    registerProfile();
                    break;
                }
            }
            else if(plate == (*p).plateNum){ //If plate number found
                printf("%s %s", (*p).plateNum, (*p).profileID);
                break;
            }
            else{ //Continue to look for the plate number
                p = p->nxtPtr;
            }
        }
    }
}*/

int main(){

    Profile *profile;
    
    FILE *inrec = fopen("records.txt", "r");
    /*FILE *inlog = fopen("logbook.txt", "r");
    FILE *indcy = fopen("discrepancy.txt", "r");*/

    if (inrec == NULL /*|| inlog == NULL || indcy == NULL*/) {
       printf("Error opening files.\n");
       return 1; // Exit with error
    }
   
    profile = create_list(inrec); 
    display(profile);
    //Administrator(&profile);
    //CODE GOES HERE - xar;)



    fclose(inrec);
    /*fclose(inlog);
    fclose(indcy);*/
}

Profile *create_list(FILE *inrec) {
    Profile *head = NULL;
    Profile *p = NULL;
    Profile *prev = NULL;
    char tempPlate[MAX];
    char tempProfileID[MAX];
    char tempType;

    while (fscanf(inrec, "%s %s %c", tempPlate, tempProfileID, &tempType) == 3) {
        p = (Profile*)malloc(sizeof(Profile));
        if (p == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        strcpy(p->plateNum, tempPlate);
        strcpy(p->profileID, tempProfileID);
        p->type = tempType;
        p->nxtPtr = NULL;

        if (head == NULL) {
            head = p;
        } else {
            prev->nxtPtr = p;
        }

        prev = p;
    }

    return head;
}//creating profile linked list function

void display(Profile*head){
  Profile *p;
  p=head;
  printf("Data in Records File:");
  while(p!=NULL){
    printf("\n%s %s %c", p->plateNum, p->profileID, p->type);
    p=p->nxtPtr;
  }
  printf("\n");
}//temporary funcion for checking