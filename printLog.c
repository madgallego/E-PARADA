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

//prints logbook. Option 0 for print to screen(search logs for today), 1 for print to logbook.txt(end of execution)
void printLog(log * head, int option);

//prints current logged in users. Happens after every termination of useLog function(to update logbook displayed)
void currLog(log * head);
int main()
{
    //ensure that head is never lost
    log * head = (log*) malloc(sizeof(log));
    head->next = NULL;
    log *q, * p = head;
    //delete last log since it containts garbage
    while(p->next != NULL)
    {
        q = p;
        p = p->next;
    }
    if(p->next == NULL)
    {
        free(p);
        q->next = NULL;
    }
    printLog(head);
}

void printLog(log * head, int option)
{
    log * p = head;
    FILE * ptr = fopen("logboook.txt", "a");

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
    fclose(ptr);
    return;
}


void currLog(log * head)
{
    log * p = head;
    char timeIN[100];
    char timeOUT[100];
    printf("CURRENT LOGGED IN USERS\n");
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