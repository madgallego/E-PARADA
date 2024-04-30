/* PROGRAMMING PROJECT FOR CS103
 ______     ____     ___     ____     ___     ____     ___
|  ____|   |  _ \   / _ \   |  _ \   / _ \   |  _ \   / _ \ 
| |___     | [_] | / /_\ \  | [_] | / /_\ \  | | | | / /_\ \
|  ___| [] |  __/  | ___  | |   _/  | ___  | | | | | | ___  | 
| |____    | |     | |  | | | |\ \  | |  | | | |_/ / | |  | |
|______|   |_|     |_|  |_| |_| \_\ |_|  |_| |___ /  |_|  |_|

Electronic Parking and Documentation Algorithm

 programmed by: GABARDA, GALLEGO, JOLOC, TABAYAG

 ACADEMIC YEAR 2023-2024
 CS103 MS ARLENE SATUITO

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100
#define MAX_ADMINS 5 // Limiting to 5 admins
#define SECURITY_KEY "12345678" // Example 8-digit security key for resetting password

/*-------------------------------ALL STRUCTURE DEFINITION HERE!!!!--------------------------------------*/
typedef struct { //struct of Admin
	char user[MAX];
	char passkey[MAX];
} Admin;
struct node { //struct of Profile
	char plateNum [MAX];
	char profileID [MAX];
	char type;//(A:CAR,B:MOTOR)
    struct node * nxtPtr;
};// for records linked list
typedef struct node Profile;
typedef struct logbook{
    char plateNum[MAX];
    char profileID[MAX];
    //unsure!!
    //char type;

    //0 for logged out, 1-X for parking designation
    int status;
    
    struct tm timeIn;
    struct tm timeOut;
    struct logbook * next;
}log;

/*-------------------------------ALL FUNCTION PROTOTYPES HERE!!!!--------------------------------------*/

//Handles parking animation depending on return of useLog. Please subtract 1 from designation for array operations
void peterParker(int designation, int car[20], int motor[20]);

//Presents lower parking spot for car and occupied spots
void carParkerlower(int car[20]);

//presents upper parking spot for car and occupied spots
void carParkerupper(int car[20]);

//presents lower parking spot for motor and occupied spots
void motorParkerlower(int motor[20]);

//presents upper parking spot for motor and occupied spots
void motorParkerupper(int motor[20]);

//prints upward arrow
void arrow(int artype, int designation, int vtype);

//prints downward arrow
void arrowD(int artype, int designation, int vtype);

//prints logbook. Option 0 for print to screen(search logs for today), 1 for print to logbook.txt(end of execution)
void printLog(log * head, int option);

//prints current logged in users. Happens after every termination of useLog function(to update logbook displayed)
void currLog(log * head);

//read records.txt to Profile lined list
Profile *create_list(FILE*inrec);

//displays data from records.txt(temp function)
void display(Profile*head);

/*screen layout functions for SignIn()*/
int SignIn(); //return 0 for successful login, 1 if not
void clearTerminal();//cears terminal
void space_up(int lines);//adds lines
void space_left(int spaces);//adds n spaces 
void delay(int seconds);//delays execution of next line for n seconds

//free the allocated space in linked list
void freeProfile(Profile ** head);

//void Administrator(Profile **head);
int traverseProfile(Profile * head, char plate[]);

//return int 0 for no prob; 1 for no Plate Num
void dscrpncyCheck(Profile * profile, char plate[], char id[]);
/*RETURNS PARKING DESIGNATION 
  FOR USING: KEEP TRACK OF LOG HEAD AND PROFILE HEAD
  CAR ARRAY IN MAIN (SIZE 20) PASS AS IS, SAME WITH MOTOR (SIZE 20)
  OPTION FOR LOG IN OR LOG OUT */
int useLog(log *head, Profile * pHead, int * car, int * motor, int option);

//creates new struct for new profile and store to a.txt file
//void registerProfile(void);

//Main function admin log in and for managing the program
void Administrator(Profile **head);

/*--------------------------------FUNCTIONS DEFINITIONS START HERE!!!!--------------------------------------*/
int main(){
    FILE *inrec = fopen("records.txt", "r");
    FILE *inlog = fopen("logbook.txt", "r");
    FILE *indisc = fopen("discrepancy.txt", "r");
    if (inrec == NULL || inlog == NULL || indisc == NULL) {
       printf("Error opening files.\n");
       return 1; // Exit with error
    }

    int signInResult;

    do{
        signInResult = SignIn();
        
        if(signInResult==0){
            break;
        }else if(signInResult==1){
            return 1;//signin not successful
        }
    }while(signInResult==2);

    Profile *profile; 
    profile = create_list(inrec); //creating the list
    display(profile);

    //Administrator(&profile);
    //CODE CONTINUES DOWN HERE - xar;)

    

    //ARRAYS TO BE USED FOR CHECKING MAX CAP AND FOR PRINTING
    /*int car[20] = {0}; //CHANGE SIZE IF NEEDED
    int motor[20] = {0}; //CHANGE SIZE IF NEEDED
    //declare logbook
    log * head = (log *) (malloc(sizeof(log)));
    head->next = NULL; */ 




    fclose(inrec);
    fclose(inlog);
    fclose(indisc);
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
    printf("\e[1;1H\e[2J");
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

void resetPasskey(const char *filename, Admin admin[], int admin_count, const char *username) {
    int found = 0;
    char new_passkey[MAX];

    // Find the specified admin
    for (int i = 0; i < admin_count; i++) {
        if (strcmp(admin[i].user, username) == 0) {
            found = 1;

            // Prompt for a new passkey
            printf("Enter a new passkey for user '%s': ", username);
            scanf("%s", new_passkey);

            // Update the passkey in the admin array
            strcpy(admin[i].passkey, new_passkey);
            break;
        }
    }

    if (found==0) {
        printf("Error: User '%s' not found.\n", username);
        return;
    }

    // Write the updated admin data back to the file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to write to %s.\n", filename);
        return;
    }

    for (int i = 0; i < admin_count; i++) {
        fprintf(file, "%s %s\n", admin[i].user, admin[i].passkey);
    }

    fclose(file);

    printf("Passkey for user '%s' has been reset successfully.\n", username);
}

int SignIn() {
    FILE *file = fopen("passkey.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open passkey.txt.\n");
        return -1;
    }

    Admin admin[MAX_ADMINS]; // Only five admins
    int admin_count = 0;

    while (admin_count < MAX_ADMINS && fscanf(file, "%s %s", admin[admin_count].user, admin[admin_count].passkey) == 2) {
        admin_count++;
    }

    fclose(file);

    Admin enter;
    int attempts = 0;

    while (attempts < 3) {
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

        int i;
        int flag = 0;
        for (i = 0; i < admin_count; i++) {
            if ((strcmp(admin[i].user, enter.user) == 0) && (strcmp(admin[i].passkey, enter.passkey) == 0)) {
                flag = 1;
                break;
            }
        }

        if (flag == 1) {
            space_up(1);
            space_left(20);
            printf("Log in successful\n");
            delay(2);
            clearTerminal();
            return 0;
        } else {
            space_up(1);
            space_left(20);
            printf("Invalid user or passkey.\n");
            attempts++;
            delay(2);
        }
    }

    clearTerminal();
    space_up(2);
    space_left(20);
    printf("Too many failed attempts. Would you like to:\n");
    printf("1. Exit Program\n");
    printf("2. Reset Password using Security Key\n");

    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        return 1; // Sign-in not successful, exit
    } else if (choice == 2) {
        printf("Enter 8-digit Security Key: ");
        char security_key[9];
        scanf("%s", security_key);

        if (strcmp(security_key, SECURITY_KEY) == 0) {
            printf("Security key verified. You can reset your password.\n");
            // Reset passkey for the specified user
            resetPasskey("passkey.txt", admin, admin_count, enter.user);
            return 2;
        } else {
            printf("Incorrect security key. Exiting program.\n");
            return 1;
        }
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

/*void Administrator(Profile **head){
    Admin admin;
    Profile * p;
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
                dscrpncyCheck(p, plate, id);
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
    }
}*/

int traverseProfile(Profile * head, char plate[]){
    Profile *p;

    p = head;
    while(p->nxtPtr != NULL){
        if((strcmp(plate, p->plateNum) != 0)){ //if plate number found
            if(p->type == 'A') // if car
                return 2;
            else if(p->type == 'B') //if motorcycle
                return 3;
            else
                printf("ERROR: No vehicle type identified");
        }
        else{
            p = p->nxtPtr;
        }
    }
    
    if(p->nxtPtr == NULL)
        return 1;
}

void dscrpncyCheck(Profile * head, char plate[], char id[]){
    FILE * ifp = fopen("discrepancy.txt","a");
    Profile * p;
    int option;

    p = head;
    while(p->nxtPtr != NULL){
        if((strcmp(plate, p->plateNum) == 0) && (strcmp(id, p->profileID) == 0)){
            printf("Parking Details Complete!\nSuccessfully Recorded");
            break;
        }
        else if((strcmp(plate, p->plateNum) == 0) && (strcmp(id, p->profileID) != 0)){
            printf("Driver Profile does not match in Database\n");
            printf("\n1. End Transaction\n2. Archive Transaction to Discrepancy File\n");
            scanf("%d", &option);
            if(option == 1){
                break;
            }
            else if(option == 2){
                fprintf(ifp, "Plate Number: %s | Profile ID: %s -> Discrepancy: %s\n", p->plateNum, p->profileID, id);
                break;
            }
        }
        else{
            p = p->nxtPtr;
        }
    }
    fclose(ifp);
}

//option if log in (1) or log out (2)
/*int useLog(log *head, Profile * pHead, int * car, int * motor, int option)
{
    log *p, *new;
    char tempNo[MAX];
    char tempID[MAX];
    int choice;
    int temphr, tempmin;
    int outNotFound = 0;
    time_t t;

    p = head;

    if(option == 1){
        printf("Log IN\nPlate No: ");
        scanf("%s", tempNo);
        printf("Driver ID: ");
        scanf("%s", tempID);
        //ends once profile is registered or transaction is ended
        if(traverseProfile(pHead, tempNo) == 1){
            printf("Plate Number is not in our data base.\n\t1. End Transaction\n\t2. Register Profile\n");
            scanf("%d", &choice);
            if(option == 1){
                return 0;
            }
            else if(option == 2){
                registerProfile(-parameters here-);
            }
        }
        dscrpncyCheck(pHead, tempNo, tempID);
        //making new pointer
        new = (log *) malloc(sizeof(log));
        strcpy(new->plateNum, tempNo);
        strcpy(new->profileID, tempID);
        t = time(NULL);
        new->timeIn = *localtime(&t);
        new->next = NULL;

        int profileType = traverseProfile(pHead, tempNo);

        if (profileType == 2) {
            for (int i = 0; i < 20; i++) {
                if (car[i] == 0) {
                    new->status = i + 1; // setup parking spot for return
                    car[i] = 1;
                    break;
                }
            }
        } else if (profileType == 3) {
            for (int i = 0; i < 20; i++) {
                if (motor[i] == 0) {
                    new->status = i + 21; // setup parking spot for return
                    motor[i] = 1;
                    break;
                }
            }
        }
        //adding log details
        while(p->next!= NULL){
            p = p->next;
        }
        
        p->next = new;

        // Return parking spot number, 0 for logout
        return new->status;
    }
     else if (option == 2) {
        do {
            printf("Log OUT\nPlate No: ");
            scanf("%s", tempNo);
            printf("Driver ID: ");
            scanf("%s", tempID);

            // Reset pointer to the start of the list
            p = head;

            while (p != NULL) {
                if (strcmp(p->plateNum, tempNo) == 0) {
                    if (p->status == 0) {
                        printf("User already logged out. Exiting Log Out.\n");
                        return 0;
                    } else {
                        dscrpncyCheck(pHead, tempNo, tempID);

                        t = time(NULL);
                        p->timeOut = *localtime(&t);
                        p->status = 0;

                        float balance = (((p->timeOut.tm_hour * 60 + p->timeOut.tm_min) - (p->timeIn.tm_hour * 60 + p->timeIn.tm_min)) * 0.5);
                        printf("Total balance is: Php %.2f\n", balance);

                        return p->status;
                    }
                }

                p = p->next;
            }

            printf("Driver not logged in.\n\t1. End Transaction\n\t2. Log Out another driver\n");
            scanf("%d", &choice);
        } while (choice == 2);

        return 0;
    }

    return -1; // Invalid option
}*/