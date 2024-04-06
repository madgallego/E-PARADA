#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 100

typedef struct logbook{
    char plateNum[MAX];
    char profileID[MAX];
    //unsure!!
    //char type;

    //0 for logged in, 1 for logged out
    int status;
    
    struct tm timeIn;
    struct tm timeOut;
    struct logbook * next;
}log;

void useLog(log *head, int option);


//FUNCTION REQUIREMENTS
//-------------------------------------------------------------
//please define with return int (0 for no prob,1 for no Plate Num)
void traverseProfile(void);
//please define with void return and void parameters
void registerProfile(void);
//please define with return int and parameter of profile ID. RETURN 0 IF NO ERROR, 1 IF NO ID
void dscrpncyCheck(void);
///----------------------------------------------------------==


int main()
{
    
    log newLog; 


    return 0;
}

//option if log in (1) or log out (2)
void useLog(log *head, int option)
{
    log * p, *new;
    char tempNo[MAX];
    char tempID[MAX];
    int choice, temphr, tempmin, outNotFound = 0;
    p = head;
    time_t t;
    if(option == 1)
    {
        printf("Log IN\nPlate No: ");
        scanf("%s", tempNo);
        printf("Driver ID: ");
        scanf("%s", tempID);
        //ends once profile is registered or transaction is ended
        while(traverseProfile(/*parameters here*/) == 1)
        {
            printf("Plate Number is not in our data base.\n\t1. End Transaction\n\t2. Register Profile\n");
            scanf("%d", &choice);
            if(option == 1)
                return;
            else if(option == 2)
                registerProfile(/*parameters here*/);
        }
        while(dscrpncyCheck(/* PROFILE ID HERE. OTHER PARAMETERS UNKOWN*/) == 1)
        {
            printf("Profile ID not found in the data base");
            printf("1. End Transaction. \n2. Archive\n");
            scanf("%d", &choice);
            if(choice == 1)
                return;


            /*Archive feature not added yet
            
            if(choice == 2)
            {
                archive();
                break;??
            }    
            */
        }
        //adding log details
        while(p->next != NULL)
        {
            p = p->next;
            if(p->next == NULL)
            {
                new = (log *) malloc(sizeof(log));
                
                strcpy(new->plateNum, tempNo);
                strcpy(new->profileID, tempID);
                
                t = time(NULL);
                new->timeIN = localtime(&t);
                new->status = 0;
                new->next = NULL;
                p->next = new;
                return;
            }
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

            //MANUAL TIME OUT!! CHANGE TO COMMENT IF NEEDED
            printf("Time Out(MILITARY TIME): ");
            scanf("%d: %d", &temphr, &tempmin);


            //CHECKS IF ALREADY LOGGED OUT
            while((strcmp(p->plateNum, tempNo) != 0) && p->next != NULL)
            {
                p = p->next;
                if((strcmp(p->plateNum, tempNo) == 0) && p->status == 1)
                {
                    printf("User already logged out. Exiting Log Out.\n");
                    return;
                }
            }

            //resets p back to head
            p = head;

            //CHECK FOR DISCREPANCY
            while(dscrpncyCheck(/* PROFILE ID HERE. OTHER PARAMETERS UNKOWN*/) == 1)
            {
                printf("Profile ID not found in the data base");
                printf("1. End Transaction. \n2. Archive\n");
                scanf("%d", &choice);
                if(choice == 1)
                    return;
                /*Archive feature not added yet
            
                if(choice == 2)
                {
                    archive();??
                    break;
                }
                */
            }
            //find platenumber to log out
            while((strcmp(p->plateNum, tempNo) != 0) && p->next != NULL)
            {
                p = p->next;
                //driver found
                if(strcmp(p->plateNum, tempNo) == 0)
                {
                    p->status = 1;
                    
                    t = time(NULL);
                    p->timeOut = localtime(&t);
                    //change timeOut to admin input (comment if not necessary)
                    p->timeOut.tm_hour = temphr;
                    p->timeOut.tm_min = tempmin;

                    //calculating balance
                    printf("Total balance is: Php %.2f", (((temphr*60 + tempmin)/60) - (p->timeIn.tm_hour*60 + p->timeIn.tm_min)) * 0.5 /*rate*/);
                    return;
                    
                }
            }
            printf("Driver not logged in.");
        //Checks if car was even logged in (prevent security breaches)
        } while (outNotFound == 0);
        
        
        
    }


}