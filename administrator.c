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

/*FUNCTION PROTOTYPES*/

/*void traverseProfile(void);
void dscrpncyCheck(void){}*/
Profile *create_list(FILE*inrec);//read profile records from file
void display(Profile*head);//to display data from records file on screen(temp function)
void Administrator(Profile *head);

void Administrator(Profile *head) {
    Admin admin;
    Profile *p = head, *new;
    int option;
    char plate[MAX];

    printf("Admin: ");
    scanf("%s", admin.user);
    printf("Password: ");
    scanf("%s", admin.passkey);

    printf("\n1. PMS\n2. Search Profile\n");
    scanf("%d", &option);

    if (option == 1) { // PMS instructions
        printf("\nChoose Action:\n1. Park In\n2. Park Out\n");
        scanf("%d", &option);
        if (option == 1) { // if Park In
            // Call function for Park In
        } else if (option == 2) { // if Park Out
            // Call function for Park Out
        }
    } else if (option == 2) { // Search Profile Instructions
        printf("Enter Plate Number: ");
        scanf("%s", plate);
        while (p != NULL) { // Traverse the linked list
            if (strcmp(p->plateNum, plate) == 0) { // If plate number found
                printf("%s %s\n", p->plateNum, p->profileID);
                break;
            }
            p = p->nxtPtr;
        }
        if (p == NULL) { // If plate number not found
            printf("Plate number not found\n");
            printf("\n1. End Transaction\n2. Register Profile\n");
            scanf("%d", &option);
            if (option == 2) { // Profile register
                new = (Profile *) malloc(sizeof(Profile));
                printf("REGISTER\n");
                printf("Profile ID: ");
                scanf("%s", new->profileID);
                printf("Vehicle Type: ");
                scanf(" %c", &new->type);
                strcpy(new->plateNum, plate);

                // Traverse to the end of the list to add new profile
                p = head;
                while (p->nxtPtr != NULL) {
                    p = p->nxtPtr;
                }
                p->nxtPtr = new;
                new->nxtPtr = NULL;
            }
        }
    }
}


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
    //CODE GOES HERE - xar;)
    //Administrator(&profile);
    



    fclose(inrec);
    /*fclose(inlog);
    fclose(indcy);*/
}

Profile *create_list(FILE*inrec){
  int k,n;
  Profile *p, *head;
  fscanf(inrec, "%d", &n);//num of profiles in the records
  for(k=0; k<n; k++){
    if(k==0){
      head=(Profile*)malloc(sizeof(Profile));
      p=head;
    }
    else{
      p->nxtPtr=(Profile*)malloc(sizeof(Profile));
      p=p->nxtPtr;
    }
    fscanf(inrec,"%s %s %c", p->plateNum, p->profileID, &p->type);
  }
  p->nxtPtr=NULL;
  return head;
}//creating profile linked list function

void display(Profile*head){
  int count = 1;
  Profile *p;
  p=head;
  printf("Data in Records File:");
  while(p!=NULL){
    printf("\n%s %s %c", p->plateNum, p->profileID, p->type);
    count++;
    p=p->nxtPtr;
  }
  printf("\n");
}//temporary funcion for checking