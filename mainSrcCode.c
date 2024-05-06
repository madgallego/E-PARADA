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
#define MAX_ADMINS 5 //Limiting to 5 admins
#define SECURITY_KEY "12345678" // Example 8-digit security key for resetting password

/*-------------------------------ALL STRUCTURE DEFINITION HERE!!!!--------------------------------------*/
typedef struct { //struct of Admin
	char user[MAX];
	char passkey[MAX];
} Admin;
typedef struct Profile {
    char plateNum[MAX];
    char profileID[MAX];
    char type;  // 'A' for cars, 'B' for motorcycles
    struct Profile *nxtPtr;
} Profile;
typedef struct log {
    char plateNum[MAX];
    char profileID[MAX];
    struct tm timeIn;
    struct tm timeOut;
    int status;
    struct log *next;
} log;

/*-------------------------------ALL FUNCTION PROTOTYPES HERE!!!!--------------------------------------*/
/*-------TERMINAL LAYOUT FUNCTIONS---------*/
//Clears Terminal using REGEX string
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
//Converts letters to uppercase
void convert_to_uppercase(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {// Replace newline with null-terminator
        str[len - 1] = '\0';}
    while (*str) {
        *str = toupper((unsigned char) *str); // Convert character to uppercase
        str++; // Move to the next character
    }
}
//Resets passkey
int resetPasskey(const char *filename, Admin admin[], int admin_count) {
    
    char username[MAX];
    space_up(2);
    space_left(20);
    printf("Admin: ");
    scanf("%s", username); 
    // Check if the username exists in the admin array
    int user_found = 0;
    for (int i = 0; i < admin_count; i++) {
        if (strcmp(admin[i].user, username) == 0) {
            user_found = 1;
            char new_passkey[MAX];
            space_left(20);// Prompt for a new passkey
            printf("Enter a new passkey for user '%s': ", username);
            scanf("%s", new_passkey);
            strcpy(admin[i].passkey, new_passkey);  // Update the passkey
            break;
        }
    }
    if (user_found==0) {//user not found
        space_up(1);
        space_left(20);
        printf("Error: User '%s' not found.\n\n", username);
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
//Security feature; Sign in with passwords or security key
int SignIn() {
    FILE *file = fopen("passkey.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open 'passkey.txt'.\n");
        return 1;  // Error opening file
    }

    Admin admin[MAX_ADMINS];
    int admin_count = 0;
    Admin entered_user;
    int attempts = 0;
    int authenticated = 0;
    char choice;
    char security_key[9];
    int reset_result;


    // Read the admin security details from the file
    while (admin_count < MAX_ADMINS && fscanf(file, "%s %s", admin[admin_count].user, admin[admin_count].passkey) == 2) {
        admin_count++;
    }

    fclose(file);


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
    // Handle failed login attempts
    while(1)
    {
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
        printf("2. Reset Password using Security Key\n\n");
        space_left(25);
        printf("Choice: ");
        scanf(" %c", &choice);
        space_left(20);
        printf("================================================\n");

        if (choice == '1') {
            return 1;  // Exit program
        } else if (choice == '2') {
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
                
                reset_result = resetPasskey("passkey.txt", admin, admin_count);
                if (reset_result == 0) {
                    return 2;
                } else {
                    space_left(20);
                    printf("Error resetting password.\n");
                    space_left(20);
                    printf("================================================\n");
                    return 1;
                }
            } else {
                space_up(1);
                space_left(20);
                printf("INCORRECT SECURITY KEY\n\n");
                space_left(20);
                printf("================================================\n");
                return 1;  // Exit program due to incorrect security key
            }
        }
        else
        {
            space_left(20);
            printf("Invalid choice\n");
            delay(3);
        }
    }
    return 1;  // Default return for unexpected behavior
}
//Read records.txt to Profile linked list
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
//creates new struct for new profile (records.txt file appended)
int rgstr(Profile ** head, const char plate[], const char id[]){
    FILE * inrec = fopen("records.txt","a");
    Profile * new, * p;
    char type;

    p = *head;
    new = (Profile*)malloc(sizeof(Profile));
    while(p->nxtPtr != NULL){
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
    
    if(p->nxtPtr == NULL){
        strcpy(new->plateNum, plate);
        strcpy(new->profileID, id);
        new->type = type;
        new->nxtPtr = NULL;
        p->nxtPtr = new;
    }

    fprintf(inrec, "\n%s %s %c", new->plateNum, new->profileID, type);

    fclose(inrec);
    return 0;
}
//Function to traverse profiles to check plate num and identify vehicle type
int traverseProfile(Profile * head, const char plate[]){
  Profile *p = head;
    while (p != NULL) {
        if (strcmp(p->plateNum, plate) == 0) {
            if (p->type == 'A') {
                return 2;  // Car
            } else if (p->type == 'B') {
                return 3;  // Motorcycle
            } else {
                fprintf(stderr, "Error: Unknown vehicle type for profile %s.\n", plate);
            }
        }
        p = p->nxtPtr;
    }
    return 1;  // Profile not found
}
//Checks for profile id of plate num. Archives discrpency if profile id does not match
void dscrpncyCheck(Profile * head, const char plate[], const char id[]){
    FILE * ifp = fopen("discrepancy.txt","a");
    Profile * p=head;
    char option;
    int discrepancy_found = 1;
    // Traverse the linked list to find the matching plate number and profile ID.
    while (p != NULL) {
        if (strcmp(plate, p->plateNum) == 0) {
            if (strcmp(id, p->profileID) == 0) {
                space_up(1);
                space_left(20);
                printf("Parking Details Complete! Successfully Recorded.\n");
                discrepancy_found = 0;
                break;
            } else {
                // Discrepancy found: same plate number but different profile ID.
                while(1)
                {
                    space_left(20);
                    printf("Driver Profile does not match in Database.\n");
                    space_left(20);
                    printf("1. End Transaction\n");
                    space_left(20);
                    printf("2. Archive Transaction to Discrepancy File\n");
                    space_left(20);
                    printf("Choice: ");
                    scanf(" %c", &option);

                    if (option == '2') {
                        fprintf(ifp, "Plate Number: %s | Expected Profile ID: %s | Discrepancy: %s\n", 
                                plate, p->profileID, id);
                        printf("Discrepancy archived in 'discrepancy.txt'.\n");
                        break;
                    }
                    else if(option == '1')
                        break;
                    else
                    {
                        space_left(20);
                        printf("Option not recognized\n");
                    }
                }
                discrepancy_found = 0;
                break;
            }
        }

        p = p->nxtPtr;
    }

    if (discrepancy_found) {
        printf("No matching plate number found in the profile database.\n");
    }

    fclose(ifp);
}
//Function to delete a specified profile in records
int deleteProfile(FILE * ifp, Profile**head, char plate[]){//function to delete profile in records
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
//Function for directing through the rest of the program features
int Administrator(Profile **head){
    Profile *p = *head;
    char option;
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
    space_left(25);
    printf("3. Register Profile\n");
    space_left(25);
    printf("4. Delete Profile\n");
    space_left(25);
    printf("5. Check Logs\n");
    space_left(25);
    printf("6. Exit\n");
    space_up(2);
    space_left(25);
    printf("Choice: ");
    scanf(" %c", &option);

    if(option == '1'){ //PMS instructions
        while(1){
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
            scanf(" %c", &option);

            if(option == '1'){
                return 2;
            }
            else if(option == '2'){
                return 3;
            }
            else
            {
                space_left(25);
                printf("Input not recognized. Please try again. Thank you");
                delay(1);
            }         
        }
    }          
    else if(option == '2'){ //Search Profile Instructions
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
        convert_to_uppercase(plate);

        while (p != NULL) { // Traverse the linked list
            if (strcmp(plate, p->plateNum) == 0) { // If plate number is found
                space_left(25);
                printf("Search Result for Plate Num. %s\n\n", p->plateNum);
                space_left(25);
                printf("ID: %s\n", p->profileID);
                space_left(25);
                printf("Vehicle Type: %c\n\n", p->type);
                space_left(20);
                printf("================================================\n\n");
                space_left(25);
                printf("1. End Search\n");
                space_left(25);
                printf("2. Delete Profile\n");
                space_up(2);
                space_left(25);
                printf("Choice: ");
                scanf("%d", &option);
                if (option == 1)
                    return 4;//default return
                else if(option == 2){
                    space_up(2);
                    space_left(25);
                    printf("Are you sure you want to delete this profile? (1: No, 2: Yes): ");
                    scanf("%d", &option);
                    if (option == 1)
                        return 4;//default return
                    else if (option == 2){
                        FILE * inrec = fopen("records.txt","w");
                        deleteProfile(inrec, head, plate);
                        clearTerminal();
                        space_left(20);
                        printf("================================================\n");
                        space_left(36);
                        printf("DELETE PROFILE\n");
                        space_left(20);
                        printf("================================================\n");
                        space_up(2);
                        space_left(25);
                        printf("Deleting Profile...");
                        delay(3);
                        space_up(2);
                        space_left(25);
                        printf("Successfully Deleted!\n");                     
                        space_up(2);
                        space_left(20);
                        printf("================================================\n");
                        fclose(inrec);
                        return 4;//default return
                    }
                    else{
                        printf("Invalid Option\n");
                        return 4;//default return
                    }
                }
                else{
                    printf("Invalid Option\n");
                    return 4;//default return
                }
            }else {
                p = p->nxtPtr; // Continue to the next node
            }
        }
        if (p == NULL) { // Plate number not found
            space_up(1);
            space_left(25);
            printf("Plate number not found.\n");
            space_left(25);
            printf("1. End Transaction\n");
            space_left(25);
            printf("2. Register Profile\n\n");
            space_left(25);
            printf("Choice: ");
            scanf(" %c", &option);
            space_left(20);
            printf("================================================\n");
            if(option=='1'){
                return 0;
            }else if(option == '2'){
                return 1;
            }     
        }
    }
    else if(option == '3')//register profile
    {
        return 1;
    }
    else if(option == '4')//delete profile
    {
      return 5;
    
    }
    else if(option == '5')//check logs
    {
        space_up(1);
        space_left(25);
        printf("Printing logs for today...");
        delay(3);
        clearTerminal();
        return 6;
    }
    else if(option == '6');
        return -1;
    space_left(25);
    printf("Invalid Option. Please try again. Thank you.\n");
    delay(2);
    clearTerminal();
    return 7;//Invalid option or default return 
}
//Handles all park ins and park outs. Returns parking spot for park ins or 0 for park out and error
int usePark(log **loghead, Profile * profiles, int * car, int * motor, int option){
    log *p = *loghead;
    log *new_log;
    int rgsterd = 0;
    char tempNo[MAX];
    char tempID[MAX];
    char choice;
    int found = 0;  // Flag to check if the vehicle is in the list
    time_t t;

    if(option == 1){ //park in
        do{
            clearTerminal();
            space_up(3);
            space_left(20);
            printf("================================================\n");
            space_left(40);
            printf("PARK IN\n");
            space_left(20);
            printf("================================================\n\n");
            space_left(25);
            printf("Plate No: ");
            scanf("%s", tempNo);
            convert_to_uppercase(tempNo);
            if(traverseProfile(profiles, tempNo) == 1){ //Profile not found
                while(1)
                {
                    space_left(25);
                    printf("Plate Number is not in our data base.\n");
                    space_left(30);
                    printf("1. End Transaction\n");
                    space_left(30);
                    printf("2. Register Profile\n");
                    space_left(30);
                    printf("3. Try Again\n");
                    space_left(25);
                    printf("Choice: ");
                    scanf(" %c", &choice);
                    if(choice == '1')
                        return 0;
                    else if(choice == '2')
                    {
                        clearTerminal();
                        space_up(3);
                        space_left(20);
                        printf("================================================\n");
                        space_left(36);
                        printf("REGISTER PROFILE\n");
                        space_left(20);
                        printf("================================================\n");
                        space_up(2);
                        space_left(25);
                        printf("Enter New Profile ID: ");
                        scanf("%s", tempID);
                        convert_to_uppercase(tempID);
                        rgstr(&profiles, tempNo, tempID);//register profile to data file
                        rgsterd = 1;
                        break;
                    }
                    else if(choice == '3')
                        break; //try again
                    else
                    {
                        space_left(25);
                        printf("Input not recognized. Try again\n\n");
                    }
                }
            }
        }while(traverseProfile(profiles, tempNo) == 1);

        if(rgsterd == 0) //this section of the code will be skipped if the user registed a new profile to park in
        {
            space_left(25);
            printf("Enter Driver ID: ");
            scanf("%s", tempID);
            convert_to_uppercase(tempID);
        }
        // Check for discrepancies
        dscrpncyCheck(profiles, tempNo, tempID);
        // Create a new log entry
        new_log = (log *)malloc(sizeof(log));
        
        strcpy(new_log->plateNum, tempNo);
        strcpy(new_log->profileID, tempID);
        t = time(NULL);
        new_log->timeIn = *localtime(&t);
        new_log->next = NULL;

        // Assign parking spot based on vehicle type
        int parking_status = traverseProfile(profiles, tempNo);
        if (parking_status == 2) {  // Car
            for (int i = 0; i < 20; i++) {
                if (car[i] == 0) {  // Free spot found
                    new_log->status = i + 1;
                    car[i] = 1;
                    break;
                }
            }
        } else if (parking_status == 3) {  // Motorcycle
            for (int i = 0; i < 20; i++) {
                if (motor[i] == 0) {  // Free spot found
                    new_log->status = i + 21;
                    motor[i] = 1;
                    break;
                }
            }
        }

        // Insert the new log entry into the linked list
        if (*loghead == NULL) {
            *loghead = new_log;
        } else {
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = new_log;
        }

        return new_log->status;  // Return the parking spot
    } 
    else if (option == 2) {  // Park-out
        while (1) {
            clearTerminal();
            space_up(3);
            space_left(20);
            printf("================================================\n");
            space_left(40);
            printf("PARK OUT\n");
            space_left(20);
            printf("================================================\n\n");
            space_left(25);
            printf("Plate No: ");
            scanf("%s", tempNo);
            convert_to_uppercase(tempNo);
            space_left(25);
            printf("Driver ID: ");
            scanf("%s", tempID);
            convert_to_uppercase(tempID);

            // Reset `p` to the head of the log list
            p = *loghead;


            // Traverse to find the corresponding plate number
            while (p != NULL) {
                if (strcmp(p->plateNum, tempNo) == 0) {
                    if((strcmp(p->profileID, tempID) != 0))
                    {
                        while(1)
                        {
                            space_up(1);
                            space_left(20);
                            printf("ID during park out is not the same as ID during park in\n");
                            space_left(25);
                            printf("1. End Transaction\n");
                            space_left(25);
                            printf("2. Park Out anyway.\n");
                            space_left(25);
                            printf("Choice: ");
                            scanf(" %c", &choice);
                            if(choice == '1')
                                return 0;
                            else if(choice == '2')
                                break;
                            else
                            {
                                space_left(20);
                                printf("Invalid Input. Try Again\n");
                            }
                        }
                    }
                    if ((p->status != 0)) {
                        t = time(NULL);
                        p->timeOut = *localtime(&t);
                        if(p->status <= 20) //checks if it is car
                            car[p->status - 1] = 0; //reset parking spot to 0 (empty)
                        else//motor
                            motor[p->status - 1] = 0;
                        p->status = 0;  // Mark as parked out

                        // Calculate parking fee (sample rate)
                        double total_minutes = ((((p->timeOut.tm_mday - p->timeIn.tm_mday) * 24) + p->timeOut.tm_hour )* 60 + p->timeOut.tm_min) - 
                                               (p->timeIn.tm_hour * 60 + p->timeIn.tm_min);
                        double total_hours = total_minutes / 60.0;
                        double fee = total_hours * 0.5;  // Example rate: Php 0.5 per hour
                        
                        space_up(2);
                        space_left(25);
                        printf("Total balance is: Php %.2f\n", fee);

                        found = 1;  // Vehicle was found and marked as parked out
                        break;
                    }
                    
                }

                p = p->next;
            }

            if (!found) {
                space_up(1);
                space_left(20);
                printf("Vehicle not found in the parking log or already parked out.\n");
                space_left(25);
                printf("1. End Transaction\n");
                space_left(25);
                printf("2. Park Out Another Vehicle\n");
                space_left(20);
                printf("Choice: ");
                scanf(" %c", &choice);
                if (choice == '1') {
                    return 0;
                }
            } else {
                break;  // Vehicle found and successfully parked out
            }
        }
    }
    return 0;  // Default return value (e.g., if option is invalid)
}
/*-----------PARKING ANNIMATION FUNCTIONS-----------------*/
//Presents lower parking spot for car and occupied spots
void carParkerlower(int car[20])
{
    //LOWER PARKING SPOT
    for(int i = 0; i < 3; i++)
    {
        space_left(20);
        if(i == 0)
        {
            printf("|  ");
            for(int j = 11; j < 21; j++)
            {
                printf(" %2d   ", j);
            }
            printf("|\n");
        }
        else
        {
            printf("|  ");
            for(int j = 10; j < 20; j++)
            {
                if(car[j] == 0)
                    printf("|   | ");
                else if(car[j] == 1)
                    printf("|===| ");
            }
            printf("|\n");
        }
    }
    space_left(20);
    printf("|==============================================================|\n");
    space_left(20);
    printf("|   ---   ---   ---   ---   ---   ---   ---   ---   ---   ---  |\n");
}
//presents upper parking spot for car and occupied spots
void carParkerupper(int car[20])
{
    //UPPER PARKING SPOT
    space_up(2);
    space_left(20);
    printf("|==============================================================|\n");
    space_left(20);
    printf("|   ---   ---   ---   ---   ---   ---   ---   ---   ---   ---  |\n");

    for(int i = 0; i<3; i++)
    {
        space_left(20);
        if(i < 2)
        {
            printf("|  ");
            for(int j = 0; j<10; j++)
            {
                if(car[j] == 0)
                    printf("|   | ");
                else if(car[j] == 1)
                    printf("|===| ");
            }
            printf("|\n");            
        }
        else if(i == 2)
        {
            printf("|  ");
            for(int j = 1; j<11; j++)
                printf(" %2d   ", j);
            printf("|\n");
        }
    }
}
//presents lower parking spot for motor and occupied spots
void motorParkerlower(int motor[20])
{
    //LOWER PARKING SPOT
    for(int i = 0; i < 3; i++)
    {
        space_left(20);
        if(i == 0)
        {
            printf("|  ");
            for(int j = 11; j < 21; j++)
            {
                printf(" %2d  ", j);
            }
            printf("|\n");
        }
        else
        {
            printf("|  ");
            for(int j = 10; j < 20; j++)
            {
                if(motor[j] == 0)
                    printf("|  | ");
                else if(motor[j] == 1)
                    printf("|==| ");
            }
            printf("|\n");
        }
    }
    space_left(20);
    printf("|   --   --   --   --   --   --   --   --   --   --  |\n");
    space_left(20);
    printf("|====================================================|\n");
}
//presents upper parking spot for motor and occupied spots
void motorParkerupper(int motor[20])
{
    //UPPER PARKING SPOT
    space_up(2);
    space_left(20);
    printf("|====================================================|\n");
    space_left(20);
    printf("|   --   --   --   --   --   --   --   --   --   --  |\n");
    for(int i = 0; i<3; i++)
    {
        space_left(20);
        if(i < 2)
        {
            printf("|  ");
            for(int j = 0; j<10; j++)
            {
                if(motor[j] == 0)
                    printf("|  | ");
                else if(motor[j] == 1)
                    printf("|==| ");
            }
            printf("|\n");            
        }
        else if(i == 2)
        {
            printf("|  ");
            for(int j = 1; j<11; j++)
                printf(" %2d  ", j);
            printf("|\n");
        }
    }
   
}
//prints upward arrow
void arrow(int artype, int designation, int vtype)
{
    int spaces = 0;
    //type 1 of arrow (arrow type printed alternately per sec)
    if(artype == 0)
    {
        //car
        if(vtype == 0)
        {
            space_left(20);
            spaces = 5 *(designation) + (designation - 1);
            for(int i = 0; i < spaces; i++)
                printf(" ");
            printf("^\n");
            space_left(20);
            for(int i = 0; i < spaces - 1; i++)
                printf(" ");
            printf("/_\\\n");
            space_left(20);
            for(int i = 0; i <spaces/2; i++)
                printf("=>");
            printf("=|\n\n\n");
        }
        else if(vtype == 1)
        {
            spaces = 3 *(designation) + 2 *(designation - 1);
            space_left(20);
            printf(" ");
            for(int i = 0; i<spaces; i++)
                printf(" ");
            printf("/\\\n");
            space_left(20);
            printf(" ");
            for(int i = 0; i<spaces; i++)
                printf(" ");
            printf("||\n");
            space_left(20);
            for(int i = 0; i<spaces/2 + 1; i++)
                printf("=>");
            printf("=|\n");
        }
    }
    else if(artype == 1)
    {
        //car
        if(vtype == 0)
        {
            spaces = 5 *(designation) + (designation - 1);
            space_left(20);
            for(int i = 0; i < spaces; i++)
                printf(" ");
            printf("A\n");
            space_left(20);
            for(int i = 0; i < spaces - 1; i++)
                printf(" ");
            printf("/ \\\n");
            space_left(20);
            for(int i = 0; i <spaces/2; i++)
                printf(">=");
            printf(">!\n\n\n");
        }
        else if(vtype == 1)
        {
            spaces = 3 *(designation) + 2 *(designation - 1);
            space_left(20);
            printf(" ");
            for(int i = 0; i<spaces; i++)
                printf(" ");
            printf("/\\\n");
            space_left(20);
            printf(" ");
            for(int i = 0; i<spaces; i++)
                printf(" ");
            printf("!!\n");
            space_left(20);
            for(int i = 0; i<spaces/2 + 1; i++)
                printf(">=");
            printf(">!\n");
        }
    }
}
//prints downward arrow
void arrowD(int artype, int designation, int vtype)
{
    int spaces = 0;
    designation -= 10;
    //type 1 of arrow (arrow type printed alternately per sec)
    if(artype == 0)
    {
        //car
        if(vtype == 0)
        {
            spaces = 5 *(designation) + (designation - 1);
            space_up(3);
            space_left(20);
            for(int i = 0; i <spaces/2; i++)
                printf("=>");
            printf("=|\n");
            space_left(20);
            for(int i = 0; i < spaces - 1; i++)
                printf(" ");
            printf("\\-/\n");
            space_left(20);
            for(int i = 0; i < spaces; i++)
                printf(" ");
            printf("V\n");
            
        }
        else if(vtype == 1)
        {
            spaces = 3 *(designation) + 2 *(designation - 1);
            space_up(3);
            space_left(20);
            for(int i = 0; i<spaces/2 + 1; i++)
                printf("=>");
            printf("|\n");
            space_left(20);
            printf(" ");
            for(int i = 0; i<spaces; i++)
                printf(" ");
            printf("||\n");
            space_left(20);
            printf(" ");
            for(int i = 0; i<spaces; i++)
                printf(" ");
            printf("\\/\n");
        }
    }
    else if(artype == 1)
    {
        //car
        if(vtype == 0)
        {
            spaces = 5 *(designation) + (designation - 1);
            space_up(3);
            space_left(20);
            for(int i = 0; i <spaces/2; i++)
                printf(">=");
            printf(">!\n");
            space_left(20);
            for(int i = 0; i < spaces - 1; i++)
                printf(" ");
            printf("\\-/\n");
            space_left(20);
            for(int i = 0; i < spaces; i++)
                printf(" ");
            printf("V\n");

        }
        else if(vtype == 1)
        {
            spaces = 3 *(designation) + 2 *(designation - 1);
            space_up(3);
            space_left(20);
            for(int i = 0; i<spaces/2 + 1; i++)
                printf(">=");
            printf("!\n");
            space_left(20);
            for(int i = 0; i<spaces; i++)
                printf(" ");
            printf(" ");
            printf("!!\n");
            space_left(20);
            printf(" ");
            for(int i = 0; i<spaces; i++)
                printf(" ");
            printf("\\/\n");
        }
    }
}
//Handles parking animation and display
void peterParker(int designation, int car[20], int motor[20])
{
    time_t flash;
    int i = 0;
    //checks vehicle type
    if(designation <= 20) //CAR
    {
        flash = time(NULL);
        while(i < 5)
        {
            if((time(NULL) - flash) == 1)
            {
                //clear terminal
                clearTerminal();
                carParkerupper(car);
                //prints either upward or downward arrow
                if(designation <= 10)
                    arrow(0, designation, 0);
                else
                    arrowD(0, designation, 0);
                carParkerlower(car);
                flash = time(NULL);
                while(1)
                {
                    if((time(NULL) - flash) == 1)
                    {
                        //clear terminal
                        clearTerminal();
                        carParkerupper(car);
                        //print upward or downward arrow of type 1
                        if(designation <= 10)
                            arrow(1, designation, 0);
                        else
                            arrowD(1, designation, 0);
                        carParkerlower(car);
                        flash = time(NULL);
                        break;
                    }
                }
                i++;
            }
        }
    }
    else
    {
        //for motor
        designation -= 20;
        flash = time(NULL);
        while(i < 10)
        {
            if((time(NULL) - flash) == 1)
            {
                clearTerminal();
                motorParkerupper(motor);
                if(designation <=10)
                    arrow(0, designation, 1);
                else
                    arrowD(0, designation, 1);
                motorParkerlower(motor);
                flash = time(NULL);
                while(1)
                {
                    if((time(NULL) - flash) == 1)
                    {
                        clearTerminal();
                        motorParkerupper(motor);
                        if(designation<=10)
                            arrow(1, designation, 1);
                        else
                            arrowD(1, designation, 1);
                        motorParkerlower(motor);
                        flash = time(NULL);
                        break;
                    }
                }
                i++;
            }
        }

    }
}
//prints logbook. Option 0 for print to screen(search logs for today), 1 for print to logbook.txt(end of execution)
void printLog(log * head, int option, FILE * ptr)
{
    log * p = head;

    char timeIN[100];
    char timeOUT[100];

    if(p == NULL && option == 0)
    {
        space_up(3);
        space_left(31);
        printf("No logs for today.\n");
        space_up(3);
    }
    //p!= NULL because it needs to print until the last log
    while(p != NULL)
    {
        //gets date of timeIn
        strftime(timeIN, sizeof(timeIN), "%x", &p->timeIn);
        //runs if option is 1
        if(option)
        {
            fprintf(ptr, "| %s | ", timeIN);
            fprintf(ptr, "%s | %s ", p->plateNum, p->profileID);
            //gets hour of time in
            //DI KO ALAM BAKIT PULA YUNG FORMAT SPECIFIER PERO NAGA WORK YAN I TESTED IT
            strftime(timeIN, sizeof(timeIN), "%I:%M%p", &p->timeIn);
            strftime(timeOUT, sizeof(timeOUT), "%I:%M%p", &p->timeOut);
            if(p->status != 0)
                fprintf(ptr, "| %s |   N/A   |\n", timeIN);
            else
                fprintf(ptr, "| %s | %7s |\n", timeIN, timeOUT);
        }
        else
        {
            space_left(35);
            printf("LOGS FOR TODAY\n");
            space_left(20);
            printf("================================================\n\n");
            space_left(20);
            printf("| %s | ", timeIN);
            printf("%s | %s ", p->plateNum, p->profileID);
            //gets hour of time in
            //DI KO ALAM BAKIT PULA YUNG FORMAT SPECIFIER PERO NAGA WORK YAN I TESTED IT
            strftime(timeIN, sizeof(timeIN), "%I:%M%p", &p->timeIn);
            strftime(timeOUT, sizeof(timeOUT), "%I:%M%p", &p->timeOut);
            if(p->status != 0)
                printf("| %s |   N/A   |\n", timeIN);
            else
                printf("| %s | %7s |\n", timeIN, timeOUT);
        }

        p = p->next;
    }
    return;
}
//prints current logged in users. Happens after every termination of useLog function(to update logbook displayed)
void currLog(log * head)
{
    log * p = head;
    char timeIN[100];
    char timeOUT[100];
    space_left(31);
    printf("CURRENT PARKED IN VEHICLES\n");
    space_left(20);
    printf("================================================\n");
    space_left(30);
    printf("    DATE     PLATE     ID   \n");

    if(p == NULL)
    {
        space_left(27);
        printf("No Vehicles Parked in as of Today\n\n");
        return;
    }
    else if(p->next == NULL)
    {
        if(p->status != 0)
        {
            //gets date of timeIn
            space_left(30);
            strftime(timeIN, sizeof(timeIN), "%x", &p->timeIn);
            printf("| %s | ", timeIN);
            printf("%s | %s |\n", p->plateNum, p->profileID);
            return;
        }
        else
        {
            space_left(27);
            printf("No Parked in Vehicles as of Now\n\n");
            return;
        }
    }
    while(p != NULL)
    {
        if(p->status != 0)
        {
            space_left(30); //gets date of timeIn            
            strftime(timeIN, sizeof(timeIN), "%x", &p->timeIn);
            printf("| %s | ", timeIN);
            printf("%s | %s |\n", p->plateNum, p->profileID);
        }
        p = p->next;

    }
    return;
}
//prints profile linked list back to records.txt. Called at the end of program before freeProfile.
void archiveProf(Profile * head)
{
    //reopen records.txt for rewriting (saving profiles)
    FILE * rec = fopen("records.txt", "w");
    Profile * p = head;
    while(p != NULL)
    {
        fprintf(rec, "%s %s %c\n", p->plateNum, p->profileID, p->type);
        p = p->nxtPtr;
    }

    fclose(rec);
    return;
}
//free the allocated space in linked list
void freeProfile(Profile ** head){
    Profile * p;
    while(*head != NULL){
        p = *head;
        *head = (*head)->nxtPtr;
        free(p);
    }
}
//frees log linked list to prevent memory leak
void freeLog(log * head)
{
    log * p, * tmp;
    p = head;
    while(p != NULL)
    {
        tmp = p;
        p = p->next;
        free(tmp);
    }
    return;
}

/*-------------------------------- PROGRAM EXECUTIONS START HERE!!!!--------------------------------------*/
int main(){
    // Open necessary files and check for errors
    FILE *inrec = fopen("records.txt", "r");

    FILE *inlog = fopen("logbook.txt", "a");

    FILE *indisc = fopen("discrepancy.txt", "a");
    if (inrec == NULL || inlog == NULL || indisc == NULL) {
       printf("Error opening files.\n");
       return 1; // Exit on error
    }
    
    //VARIABLE DECLARATIONS AND INITIALIZATIONS
    int sign_in_result;
    int option;
    char choice;
    char id[MAX];
    char plate[MAX];
    int car[20] = {0};//set car parking space to empty
    int motor[20] = {0};//set motor parking space to empty
    Profile *profile;
    log *loghead = NULL;
    
    do {
        sign_in_result = SignIn();
        
        if (sign_in_result == 0) {// Successful login            
            break;
        } else if (sign_in_result == 1) {// Exit program due to unsuccessful login or incorrect security key            
            space_left(20);
            printf("Exiting program...");
            delay(4);
            clearTerminal();
            return 1;
        }
        space_up(1);// Reset the password using security key
        space_left(20);
        printf("================================================\n\n");
        space_left(20);
        printf("Password has been reset successfully.\n");
        delay(2);
    } while (sign_in_result == 2);  // Continue if password reset was successful and retry login
    profile = create_list(inrec); //Create a profile list from records file
    fclose(inrec);
    // Main program loop, ends at 5 PM or by choice
    while(1)
    {
        do
        {
            currLog(loghead);
            option = Administrator(&profile); // Get user input for next action
        } while (option == 7);
        
           
        //0: exit program 1: register profile 2: park in 3: park out

        switch (option) {
            case -1:
                break;
            case 0:
                break;
            case 1: //Register new profile
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
                printf("Enter Plate Number: ");
                scanf("%s", plate);
                convert_to_uppercase(plate);
                space_left(20);
                printf("Enter ID: ");
                scanf("%s", id);
                convert_to_uppercase(id);
                if(rgstr(&profile, plate, id)==0){
                    space_up(1);
                    space_left(20);
                    printf("Registered Successfully!\n");
                }break;// Register a new profile
            
            case 2: //Park in
                while (1) {
                    int spot;
                    // Try to park in, check for errors
                    spot = usePark(&loghead, profile, car, motor, 1);
                    if (spot == 0) { // Error encountered
                        space_left(20);
                        printf("Error: Profile not found or other issue. Please resolve.\n");
                        delay(3);
                        break;
                    }
                    // If successful, inform the user about the parking spot
                    delay(3);
                    space_left(20);
                    printf("Thank you for parking with us. Please proceed to parking spot %d. (20+ is for motorcycles only)\n", spot);
                    delay(3);
                    // Proceed with parking
                    peterParker(spot, car, motor);
                    delay(1);

                    break; // Exit the loop after successful park-in
                }
                break;

            case 3: // Park out
                if (usePark(&loghead, profile, car, motor, 2) == 0);
                delay(3);
                clearTerminal();
                break;
            case 4: //search profile
                break;

            case 5:
                while(1){
                    clearTerminal();
                    space_left(20);
                    printf("================================================\n");
                    space_left(36);
                    printf("DELETE PROFILE\n");
                    space_left(20);
                    printf("================================================\n");
                    space_up(2);
                    space_left(25);
                    printf("Enter Plate Number: ");
                    scanf("%s", plate);
                    convert_to_uppercase(plate);
                    FILE * inrec = fopen("records.txt","w");
                    int delResult = 0;
                    delResult = deleteProfile(inrec, &profile, plate);
                    space_up(2);
                    space_left(25);
                    printf("Deleting Profile...");
                    delay(3);
                    if (delResult == 0){
                        space_up(2);
                        space_left(25);
                        printf("Profile Not Found");
                        space_up(2);
                        space_left(25);
                        printf("1. End Delete\n");
                        space_left(25);
                        printf("2. Try Again\n");
                        space_up(2);
                        space_left(25);
                        printf("Choice: ");
                        scanf("%d", &option);
                        if(option == 1){
                            space_up(2);
                            space_left(20);
                            printf("================================================\n");
                            fclose(inrec);
                            break;
                        }
                        else if(option == 2){
                            space_up(2);
                            space_left(25);
                            printf("Please Wait...");
                            delay(1);
                            continue;
                        }
                    }
                    else if(delResult == 1){
                        space_up(2);
                        space_left(25);
                        printf("Successfully Deleted!\n");
                        space_up(2);
                        space_left(20);
                        printf("================================================\n");
                        fclose(inrec);
                        break;
                    }
                }
                break;
            case 6: //prints all the logs
                printLog(loghead, 0, inlog);
                break;

            default:
                printf("Invalid option. Please choose 2 for park-in or 3 for park-out.\n");
                break;
        }

        // Check if user wants to perform another action
        while(option != -1)
        {
            space_up(3);
            space_left(20); 
            printf("Do Another Action?  (1: No, 2: Yes): ");
            scanf(" %c", &choice);
            if(choice == '1')
            {
                space_left(20);
                printf("Exiting program...");
                delay(3);
                clearTerminal();
                space_left(20);
                printf("Printing Logs for today...\n");
                delay(2);
                clearTerminal();
                printLog(loghead, 0, inlog);
                printLog(loghead, 1, inlog);
                break;
            }
            //Temporary for checking
            else if(choice == '2')
            {
                space_up(1);
                space_left(20);
                printf("Returning to Main Menu...");
                delay(3);
                clearTerminal();
                break;
            }
            else
            {
                space_left(20);
                printf("Input not recognized. Try again");
                delay(1);
            }
        }
        if(choice == '1' || option == -1)//Program exits
            break;
    }
    //file pointers shoud be passed from main since we opened them here

    printLog(loghead, 1, inlog);

    archiveProf(profile);

    freeLog(loghead);
    freeProfile(&profile);

    fclose(inlog);
    fclose(indisc);
    
    return 0;
}//main function