#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

/*------------------FUNCTION REQUIREMENTS--------------
//please define with return int (0 for no prob,1 for no Plate Num)
int traverseProfile(Profile * head, char plate[], char id[]);
//please define with void return and void parameters
void registerProfile(void);
//please define with return int and parameter of profile ID. RETURN 0 IF NO ERROR, 1 IF NO ID
int dscrpncyCheck(char plate[], char id[]);
//-----------------------------------------------------*/
int traverseProfile(Profile * head, char plate[], char id[]);

//screen layout functions
void clearTerminal();
void space_up(int lines);
void space_left(int spaces);
void delay(int seconds);

int SignIn(); //return 0 for successful login, 1 for not
Profile *create_list(FILE*inrec);//read records.txt to Profile lined list
void display(Profile*head);//displays data from records.txt(temp function)
void Administrator(Profile **head);

void Administrator(Profile **head){
    Admin admin;
    Profile * p, *new;
    int option, parkIn, dscrpncy;
    char plate[MAX];
    char id[MAX];
    p = *head;

    printf("\n1. PMS\n2. Search Profile\n");
    scanf("%d", &option);

    if(option == 1){ //PMS instructions
        printf("\nChoose Action:\n1. Park In\n2. Park Out\n");
        scanf("%d", &option);
        if(option == 1){ //if Park In
            printf("Plate No.: ");
            scanf("%s", plate);
            printf("Driver ID: ");
            scanf("%s", id);
            parkIn = traverseProfile(p, plate, id);
            if(parkIn == 0){
                dscrpncy = dscrpncyCheck(plate, id);
            }
            else if(parkIn == 1){
                printf("\nPlate number not found\n");
                printf("\n1. End Transaction\n2. Register Profile\n");
                scanf("%d", &option);
                    if(option == 1){
                        printf("\nTransaction Ended");
                    }
                    else if(option == 2){
                        registerProfile();
                    }
                }
            }
        }
        /*else if(option == 2){ //if Park Out
            dscrpncyCheck();
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
    }*/
}

int main(){
    FILE *inrec = fopen("records.txt", "r");
    FILE *inlog = fopen("logbook.txt", "r");
    FILE *indcy = fopen("discrepancy.txt", "r");
    if (inrec == NULL || inlog == NULL || indcy == NULL) {
       printf("Error opening files.\n");
       return 1; // Exit with error
    }
    
    if(SignIn() == 1){
        return 1;//signin not successful
    }

    Profile *profile;
    
    
   
    profile = create_list(inrec); 
    display(profile);
    Administrator(&profile);
    //CODE GOES HERE - xar;)



    fclose(inrec);
    /*fclose(inlog);
    fclose(indcy);*/
}//main function

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

int SignIn() {
    Admin admin[5] = {{"lex", "bbmharc"}, {"lester", "bblester"}, {"yno", "bbyno"}, {"joy", "bbxar"}, {"cs1b", "satuits"}}; //where to store this po?
    Admin enter;
    int count=0;//sign in attempts
    while (count <3) {
        clearTerminal();
        space_up(3);
        space_left(20);
        printf("==============================\n");
        space_left(32);
        printf("LOGIN\n");
        space_left(20);
        printf("==============================\n");
        space_up(2);
        space_left(25);
        printf("Admin: ");
        scanf("%s", enter.user);
        space_left(25);
        printf("Password: ");
        scanf("%s", enter.passkey);
        space_up(2);
        space_left(20);
        printf("===============================\n");
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
            space_up(1);
            space_left(20);
            printf("Log in successful\n"); //successful
            delay(2);
            clearTerminal();
            return 0;
        } else {
            space_up(1);
            space_left(20);
            printf("Invalid user or passkey. Try again.\n"); //err
            count++; 
            delay(3);
        }
    }
    printf("Wrong Password");
    return 1;
}