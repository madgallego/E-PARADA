#include <stdio.h>
#include<stdlib.h>
#include<time.c>
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

void traverseProfile(void){}
void dscrpncyCheck(void){}

int Administrator(Profile * head){
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
                    new = (Profile *) malloc(sizeof(Profile));
                    printf("REGISTER");
                    Printf("Profile ID: ");
                    scanf("%s", new->profileID);
                    Printf("Vehicle Type: ");
                    scanf(" %c", new->type);
                    strcpy(new->plateNum, plate);
                    p->nxtPtr=new;
                    new->nxtPtr=NULL;
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
}

int main(){
    Profile profile;

    Administrator(&profile);
}
