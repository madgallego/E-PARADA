#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

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
struct node { //struct of Profile
	char plateNum [MAX];
	char profileID [MAX];
	char type;
    struct node * nxtPtr;
};// for records linked list
typedef struct node Profile;
//RETURNS PARKING DESIGNATION. 
//FOR USING: KEEP TRACK OF LOG HEAD AND PROFILE HEAD
//CAR ARRAY IN MAIN (SIZE 20) PASS AS IS, SAME WITH MOTOR (SIZE 20)
//OPTION FOR LOG IN OR LOG OUT
int useLog(log **head, Profile * pHead, int * car, int * motor, int option);


//FUNCTION REQUIREMENTS
//-------------------------------------------------------------
//please define with return int (0 for no prob,1 for no Plate Num)
int traverseProfile(Profile * head, char plate[]);
//please define with void return and void parameters
void registerProfile(void);

void dscrpncyCheck(Profile * profile, char plate[], char id[]);
///----------------------------------------------------------==


int main()
{
    //ARRAYS TO BE USED FOR CHECKING MAX CAP AND FOR PRINTING
    int car[20] = {0}; //CHANGE SIZE IF NEEDED
    int motor[20] = {0}; //CHANGE SIZE IF NEEDED

    //declare logbook
    log * head = NULL;
    Profile * phead = NULL;
    //sample use of useLog
    int x = useLog(&head, phead, car, motor, 1);


    return 0;
}

//option if log in (1) or log out (2)
int useLog(log **head, Profile * pHead, int * car, int * motor, int option)
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
                registerProfile(/*parameters here*/);
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
                printf("Total balance is: Php %.2f", (((p->timeOut.tm_hour*60 + p->timeOut.tm_min)/60) - (p->timeIn.tm_hour*60 + p->timeIn.tm_min)/60) * 0.5 /*rate*/);

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


}