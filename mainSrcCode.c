/* PROGRAMMING PROJECT FOR CS103
 ______     ____     ___     ____     ___     ____     ___
|  ____|   |  _ \   / _ \   |  _ \   / _ \   |  _ \   / _ \ 
| |___     | [_] | / /_\ \  | [_] | / /_\ \  | | | | / /_\ \
|  ___| [] |  __/  | ___  | |   _/  | ___  | | | | | | ___  | 
| |____    | |     | |  | | | |\ \  | |  | | | |_/ / | |  | |
|______|   |_|     |_|  |_| |_| \_\ |_|  |_| |___ /  |_|  |_|

Electronic Parking and Documentation Algorithm

 programmed by: JOLOC, GABARDA, GALLEGO, TABAYAG

 ACADEMIC YEAR 2023-2024
 CS103 MS ARLENE SATUITO

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAX 100



//---------------------------------------------------------------------
//ALL FUNCTION HEADERS HERE!!!!

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

//traverses profile for finding plate Num and ID(???)
void traverseProfile(void);

//(unsure)Archives the discrepancy(??) or finds user ID
void dscrpncyCheck(void);

//creates new struct for new profile and store to a .txt file
void registerProfile(void);

//read profile records from file
Profile *create_list(FILE*inrec);

//to display data from records file on screen(temp function)
void display(Profile*head);

//Main function admin log in and for managing the program
void Administrator(Profile **head);

//used for logged ins and log outs. returns parking designation(car = 1-20, motor 21-40)
//return 0 for end transaction
int useLog(log *head, int option);


//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
//ALL STRUCTURES GO HERE
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







//-------------------------------------------------------------------------
int main (){
printf("hello World!");
 //hi from YNO




return 0;
}
