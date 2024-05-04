#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 100

//structure used for logbook. copied from logbooktest.c
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


//prints logbook. Option 0 for print to screen(search logs for today), 1 for print to logbook.txt(end of execution)
void printLog(log * head, int option, FILE * ptr);

//prints current logged in users. Happens after every termination of useLog function(to update logbook displayed)
void currLog(log * head);
//prints profile back to records.txt for updating. Called at the end of program before freeProfile
void archiveProf(Profile * head);

int main()
{
    //ensure that head is never lost
    log * head = NULL;
    //delete last log since it containts garbage
    printLog(head);
}

void printLog(log * head, int option, FILE * ptr)
{
    log * p = head;

    char timeIN[100];
    char timeOUT[100];

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
            fprintf(ptr, "| %s | %7s |\n", timeIN, timeOUT);
        }
        else
        {
            printf("| %s | ", timeIN);
            printf("%s | %s ", p->plateNum, p->profileID);
            //gets hour of time in
            //DI KO ALAM BAKIT PULA YUNG FORMAT SPECIFIER PERO NAGA WORK YAN I TESTED IT
            strftime(timeIN, sizeof(timeIN), "%I:%M%p", &p->timeIn);
            strftime(timeOUT, sizeof(timeOUT), "%I:%M%p", &p->timeOut);
            printf("| %s | %7s |\n", timeIN, timeOUT);
        }

        p = p->next;
    }

    return;
}


void currLog(log * head)
{
    log * p = head;
    char timeIN[100];
    char timeOUT[100];
    printf("CURRENT PARKED IN VEHICLES\n");
    if(p->next == NULL)
    {
        if(p->status != 0)
        {
            //gets date of timeIn
            strftime(timeIN, sizeof(timeIN), "%x", &p->timeIn);
            printf("| %s | ", timeIN);
            printf("%s | %s |\n", p->plateNum, p->profileID);
            return;
        }
        else
        {
            printf("No Parked in Vehicles as of Now\n\n");
            return;
        }
    }
    while(p->next != NULL)
    {
        if(p->status != 0)
        {
            //gets date of timeIn
            strftime(timeIN, sizeof(timeIN), "%x", &p->timeIn);
            printf("| %s | ", timeIN);
            printf("%s | %s |\n", p->plateNum, p->profileID);
            printf("\n");
        }

        p = p->next;
    }
    return;
}

void archiveProf(Profile * head)
{
    //reopen records.txt for rewriting (saving profiles)
    FILE * rec = fopen("records.txt", "w");
    Profile * p = head;
    while(p != NULL)
    {
        fprintf(rec, "%s %s %c\n", p->plateNum, p->profileID, p->type);
        p = p->next;
    }

    fclose(rec);
    return;
}
