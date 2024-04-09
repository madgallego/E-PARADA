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
void clearTerminal();
void space_up(int lines);
void space_left(int spaces);
void delay(int seconds);
void SignIn();
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

    SignIn();
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

void clearTerminal() {
    system("clear || cls");
}

void space_up(int lines) {
    for (int i = 0; i < lines; i++)
        printf("\n");
}

void space_left(int spaces) {
    for (int i = 0; i < spaces; i++)
        printf(" ");
}

void delay(int seconds) {
    clock_t start_time = clock();
    clock_t current_time;
    double elapsed_time;

    do {
        current_time = clock();
        elapsed_time = (double)(current_time - start_time) / CLOCKS_PER_SEC;
    } while (elapsed_time < seconds);
}

void SignIn() {
    Admin admin[5] = {{"lex", "bbmharc"}, {"lester", "bblester"}, {"yno", "bbyno"}, {"joy", "bbxar"}, {"cs1b", "satuits"}};
    Admin enter;
    while (1) {
        clearTerminal();
        space_up(5);
        space_left(20);
        printf("-------------------------------\n");
        space_left(20);
        printf("        ADMIN LOGIN\n");
        space_left(20);
        printf("-------------------------------\n");
        space_up(2);
        space_left(25);
        printf("User: ");
        scanf("%s", enter.user);
        space_left(25);
        printf("Password: ");
        scanf("%s", enter.passkey);
        space_up(2);
        space_left(20);
        printf("-------------------------------\n");
        // Check if the input_passkey matches any of the predefined passkeys
        int i;
        int flag = 0;
        for (i = 0; i < 5; i++) {
            if ((strcmp(admin[i].user, enter.user) == 0) && (strcmp(admin[i].passkey, enter.passkey) == 0)) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            space_up(2);
            space_left(20);
            printf("Log in successful\n"); //successful
            delay(2);
            clearTerminal();
            break;
        } else {
            space_up(2);
            space_left(20);
            printf("Invalid passkey. Try again.\n"); //err
            delay(2);
        }
    }
}