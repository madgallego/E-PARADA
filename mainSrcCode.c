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
#include <ctype.h>

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

/*//Handles parking animation depending on return of useLog. Please subtract 1 from designation for array operations
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
void currLog(log * head);*/

//read records.txt to Profile lined list
Profile *create_list(FILE*inrec);

//displays data from records.txt(temp function)
void display(Profile*head);

/*screen layout functions for SignIn()*/
int SignIn(); //return 0 for successful login, 1 if not
int resetPasskey(const char *filename, Admin admin[], int admin_count, const char *username);
void clearTerminal();//cears terminal
void space_up(int lines);//adds lines
void space_left(int spaces);//adds n spaces 
void delay(int seconds);//delays execution of next line for n seconds

//free the allocated space in linked list
void freeProfile(Profile ** head);

//void Administrator(Profile **head);
int traverseProfile(Profile * head, const char *plate[]);

//return int 0 for no prob; 1 for no Plate Num
void dscrpncyCheck(Profile * profile, const char *plate[],const char *id[]);
/*RETURNS PARKING DESIGNATION 
  FOR USING: KEEP TRACK OF LOG HEAD AND PROFILE HEAD
  CAR ARRAY IN MAIN (SIZE 20) PASS AS IS, SAME WITH MOTOR (SIZE 20)
  OPTION FOR LOG IN OR LOG OUT */
int useLog(log **head, Profile * pHead, int * car, int * motor, int option);

//creates new struct for new profile and store to a.txt file
int rgstr(Profile ** head, const char *plate[], const char *id[]);

//Main function admin log in and for managing the program
int Administrator(Profile **head);

/*--------------------------------FUNCTIONS DEFINITIONS START HERE!!!!--------------------------------------*/
int main(){
    FILE *inrec = fopen("records.txt", "r");
    FILE *inlog = fopen("logbook.txt", "r");
    FILE *indisc = fopen("discrepancy.txt", "r");
    if (inrec == NULL || inlog == NULL || indisc == NULL) {
       printf("Error opening files.\n");
       return 1; // Exit with error
    }

    int sign_in_result, option;

    do {
        sign_in_result = SignIn();
        
        if (sign_in_result == 0) {// Successful login            
            break;
        } else if (sign_in_result == 1) {// Exit program due to unsuccessful login or incorrect security key            
            return 1;
        }// Reset the password using security key
        space_up(1);
        space_left(20);
        printf("Password has been reset successfully.\n");
        delay(2);
        
    } while (sign_in_result == 2);  // Continue if password reset was successful and retry login

    Profile *profile; 
    profile = create_list(inrec); //creating the list
    
    option = Administrator(&profile);

    if (option == 1) {// End the transaction
        delay(2);
        clearTerminal();
        return 0;
    } else if (option == 2) {//register new profile
        clearTerminal();
        space_up(3);
        space_left(20);
        printf("================================================\n");
        space_left(36);
        printf("REGISTER PROFILE\n");
        space_left(20);
        printf("================================================\n");
        space_up(2);
        space_left(20);
        printf("Enter ID: ");
        scanf("%s", id);

        if(rgstr(&p, plate, id)==0){
            space_up(1);
            space_left(20);
            printf("Registered Successfully!\n");
        }// Register a new profile
    }

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
    return 0:
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

int SignIn() {
    FILE *file = fopen("passkey.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open 'passkey.txt'.\n");
        return 1;  // Error opening file
    }

    Admin admin[MAX_ADMINS];
    int admin_count = 0;

    // Read the admin data from the file
    while (admin_count < MAX_ADMINS && fscanf(file, "%s %s", admin[admin_count].user, admin[admin_count].passkey) == 2) {
        admin_count++;
    }

    fclose(file);

    Admin entered_user;
    int attempts = 0;

    while (attempts < 3) {
        clearTerminal();
        space_up(3);
        space_left(20);
        printf("================================================\n");
        space_left(41);
        printf("LOGIN\n");
        space_left(20);
        printf("================================================\n");
        space_up(2);
        space_left(25);
        printf("Admin: ");
        scanf("%s", entered_user.user);
        space_left(25);
        printf("Password: ");
        scanf("%s", entered_user.passkey);
        space_up(2);
        space_left(20);
        printf("================================================\n");

        int authenticated = 0;
        for (int i = 0; i < admin_count; i++) {
            if (strcmp(admin[i].user, entered_user.user) == 0 && strcmp(admin[i].passkey, entered_user.passkey) == 0) {
                authenticated = 1;
                break;
            }
        }

        if (authenticated==1) {
            space_up(1);
            space_left(20);
            printf("Login successful.\n");
            delay(2);
            clearTerminal();
            return 0;  // Successful login
        } else {
            attempts++;
            space_up(1);
            space_left(20);
            printf("Invalid username or password. Attempts left: %d\n", 3 - attempts);
            delay(2);
        }
    }
    int choice;
    // Handle failed login attempts
    clearTerminal();
    space_up(3);
    space_left(20);
    printf("================================================\n");
    space_left(39);
    printf("LOGIN FAILED\n");
    space_left(20);
    printf("================================================\n");
    space_left(20);
    printf("Too many failed attempts. Would you like to:\n");
    space_up(2);
    space_left(25);
    printf("1. Exit Program\n");
    space_left(25);
    printf("2. Reset Password using Security Key\n");
    space_up(2);
    space_left(25);
    printf("Choice: ");
    scanf("%d", &choice);   

    if (choice == 1) {
        return 1;  // Exit program
    } else if (choice == 2) {
        clearTerminal();
        space_up(3);
        space_left(20);
        printf("================================================\n");
        space_left(37);
        printf("RESET PASSWORD\n");
        space_left(20);
        printf("================================================\n");
        space_up(2);
        space_left(20);
        printf("Enter the 8-digit security key: ");
        char security_key[9];
        scanf("%s", security_key);

        if (strcmp(security_key, SECURITY_KEY) == 0) {//security passkey matches
            clearTerminal();
            space_up(3);
            space_left(20);
            printf("================================================\n");
            space_left(37);
            printf("RESET PASSWORD\n");
            space_left(20);
            printf("================================================\n");
            
            int reset_result = resetPasskey("passkey.txt", admin, admin_count, entered_user.user);
            if (reset_result == 0) {
                return 2;
            } else {
                space_up(1);
                space_left(20);
                printf("Error resetting password.\n\n");
                return 1;
            }
        } else {
            space_up(2);
            space_left(20);
            printf("Incorrect security key. Exiting program.\n");
            return 1;  // Exit program due to incorrect security key
        }
    }

    return 1;  // Default return for unexpected behavior
}

int resetPasskey(const char *filename, Admin admin[], int admin_count, const char *username) {
    // Check if the username exists in the admin array
    int user_found = 0;
    for (int i = 0; i < admin_count; i++) {
        if (strcmp(admin[i].user, username) == 0) {
            user_found = 1;
            // Prompt for a new passkey
            char new_passkey[MAX];
            space_up(2);
            space_left(20);
            printf("Enter a new passkey for user '%s': ", username);
            scanf("%s", new_passkey);
            strcpy(admin[i].passkey, new_passkey);  // Update the passkey
            break;
        }
    }

    if (user_found==0) {
        space_up(2);
        space_left(20);
        printf("Error: User '%s' not found.\n", username);
        return 1;  // Indicate error
    }

    // Rewrite the admin data to the file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Unable to open '%s' for writing.\n", filename);
        delay(1);
        return 1;  // Indicate error
    }

    for (int i = 0; i < admin_count; i++) {
        fprintf(file, "%s %s\n", admin[i].user, admin[i].passkey);
    }

    fclose(file);
    return 0;  // Indicate success
}

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

void freeProfile(Profile ** head){
    Profile * p;
    while(*head != NULL){
        p = *head;
        *head = (*head)->nxtPtr;
        free(p);
    }
}

int rgstr(Profile ** head, const char *plate[], const char *id[]){
    Profile * new, * p;
    char type;

    p = *head;
    new = (Profile*)malloc(sizeof(Profile));
    while(p != NULL){
        p = p->nxtPtr;
    }
    clearTerminal();
    space_up(3);
    space_left(20);
    printf("================================================\n");
    space_left(36);
    printf("REGISTER PROFILE\n");
    space_left(20);
    printf("================================================\n");
    space_up(2);
    space_left(20);
    printf("Please indicate vehicle type (A=car, B=motorcycle)\n");
    space_left(20);
    printf("Vehicle Type: ");
    scanf(" %c", &type);

    type = toupper(type);
    
    if(p == NULL){
        strcpy(new->plateNum, plate);
        strcpy(new->profileID, id);
        new->type = type;
        new->nxtPtr = NULL;
        p = new;
    }

    /*FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Unable to open '%s' for writing.\n", filename);
        delay(1);
        return 1;  // Indicate error
    }

    for (int i = 0; i < admin_count; i++) {
        fprintf(file, "%s %s\n", admin[i].user, admin[i].passkey);
    }

    fclose(file);*/
    return 0;
}

int Administrator(Profile **head){
    Profile *p = *head;
    int option, parkIn;
    char plate[MAX];
    char id[MAX];
    char type[MAX];
    
    space_up(3);
    space_left(20);
    printf("================================================\n");
    space_left(40);
    printf("E-PARADA\n");
    space_left(20);
    printf("================================================\n");
    space_up(2);
    space_left(25);
    printf("1. PMS\n");
    space_left(25);
    printf("2. Search Profile\n");
    space_up(2);
    space_left(25);
    printf("Choice: ");
    scanf("%d", &option);

    if(option == 1){ //PMS instructions
        clearTerminal();
        space_up(3);
        space_left(20);
        printf("================================================\n");
        space_left(36);
        printf("PARKING (PMS)\n");
        space_left(20);
        printf("================================================\n");
        space_up(2);
        space_left(25);
        printf("1. Park In\n");
        space_left(25);
        printf("2. Park Out\n");
        space_up(2);
        space_left(25);
        printf("Choice: ");
        scanf("%d", &option);

        if(option == 1){
            return 2;
        }
        else if(option == 2){
            return 3;
        }

                       
    }          
    else if(option == 2){ //Search Profile Instructions
        clearTerminal();
        space_up(3);
        space_left(20);
        printf("================================================\n");
        space_left(36);
        printf("SEARCH PROFILE\n");
        space_left(20);
        printf("================================================");
        space_up(3);
        space_left(25);
        printf("Enter Plate Number: ");
        scanf("%s", plate);

        while (p != NULL) { // Traverse the linked list
            if (strcmp(plate, p->plateNum) == 0) { // If plate number is found
                space_up(1);
                space_left(25);
                printf("Search Result\n\n");
                space_left(25);
                printf("Plate Number: %s\n", p->plateNum);
                space_left(25);
                printf("ID: %s\n", p->profileID);
                space_left(25);
                printf("Vehicle Type: %c\n\n", p->type);
                space_left(20);
                printf("================================================\n\n");
                break;
            } else {
                p = p->nxtPtr; // Continue to the next node
            }
            if (p == NULL) { // Plate number not found
                space_up(1);
                space_left(25);
                printf("Plate number not found.\n\n");
                space_left(25);
                printf("1. End Transaction\n");
                space_left(25);
                printf("2. Register Profile\n\n\n");
                space_left(25);
                printf("Choice: ");
                scanf("%d", &option);
        
                
                }
            }
        }              
    }
}

int traverseProfile(Profile * head, const char *plate[]){
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

void dscrpncyCheck(Profile * head, const char *plate[], const char *id[]){
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
/*int useLog(log **head, Profile * pHead, int * car, int * motor, int option)
{
    log * p, *q, *new;
    char tempNo[MAX];
    char tempID[MAX];
    int choice, temphr, tempmin, outNotFound = 0;

    p = *head;
    time_t t;
    if(option == 1)
    {
        printf("Log IN\nPlate No: ");
        scanf("%s", tempNo);
        printf("Driver ID: ");
        scanf("%s", tempID);
        //ends once profile is registered or transaction is ended
        if(traverseProfile(pHead, tempNo) == 1)
        {
            printf("Plate Number is not in our data base.\n\t1. End Transaction\n\t2. Register Profile\n");
            scanf("%d", &choice);
            if(option == 1)
                return 0;
            else if(option == 2)
                rgstr(&pHead, tempNo, tempID);
        }
        dscrpncyCheck(pHead, tempNo, tempID);
        //making new pointer
        new = (log *) malloc(sizeof(log));
        strcpy(new->plateNum, tempNo);
        strcpy(new->profileID, tempID);
        t = time(NULL);
        new->timeIn = *localtime(&t);
        new->next = NULL;
        if(traverseProfile(pHead, tempNo) == 2)
        {
            for(int i = 0; i < 20; i++)
            {
                //free spot
                if(car[i] == 0)
                {
                    //setup parking spot for return
                    new->status = i + 1;
                    car[i] = 1;
                    break;
                }
            }
        }
        else if(traverseProfile(pHead, tempNo) == 3)
        {
            for(int i = 0; i < 20; i++)
            {
                //free spot
                if(motor[i] == 0)
                {
                    //setup parking spot for return
                    new->status = i + 21;
                    motor[i] = 1;
                    break;
                }
            }
        }
        if(head == NULL)
        {
            *head = new;
            return (*head)->status + 1; 
        }
        //adding log details
        while(p->next!= NULL)
        {
            p = p->next;
        }
        if(p->next == NULL)
        {
            p->next = new;
            //RETURNS PARKING SPOT. 1 IS LOWEST. RETURN 0 IS LOG OUT 
            return p->status + 1;
        }
    }
    else if(option == 2)
    {
        do
        {
            printf("Log OUT\nPlate No: ");
            scanf("%s", tempNo);
            printf("Driver ID: ");
            scanf("%s", tempID);

            //CHECKS IF ALREADY LOGGED OUT

            if((strcmp(p->plateNum, tempNo) == 0) && p->status == 0)
            {
                q = p->next;
                while(q != NULL)
                {
                    if((strcmp(q->plateNum, tempNo) == 0) && q->status != 0)
                    {
                        p = q;
                    }
                    q = q->next;
                }
                if((p->status == 0 && q == NULL))
                {
                    printf("User already logged out. Exiting Log Out.\n");
                    return 0;
                }
            }
            while((strcmp(p->plateNum, tempNo) != 0) && p->next != NULL)
            {
                q = p->next;
                while(q != NULL)
                {
                    if((strcmp(q->plateNum, tempNo) == 0) && q->status != 0)
                    {
                        p = q;
                    }
                    q = q->next;
                }
                if((p->status == 0 && q == NULL))
                {
                    printf("User already logged out. Exiting Log Out.\n");
                    return 0;
                }
            }
            //CHECK FOR DISCREPANCY
            dscrpncyCheck(pHead, tempNo, tempID);
            //find platenumber to log out
            if(p->status != 0)
            {             
                t = time(NULL);
                p->timeOut = *localtime(&t);

                p->status = 0;

                //calculating balance
                printf("Total balance is: Php %.2f", (((p->timeOut.tm_hour*60 + p->timeOut.tm_min)/60) - (p->timeIn.tm_hour*60 + p->timeIn.tm_min)/60) * 0.5 //rate);

                return p->status;
                    
            }
            printf("Driver not logged in. \n1. End Transaction\n2. Log Out another driver\n");
            scanf("%d", &choice);
            if(choice == 1)
                return 0;
            else if(choice == 2)
                ;//DO NOTHING
                

        //Checks if car was even logged in (prevent security breaches)
        } while(1);
    }


}*/