#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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

//prints logbook to logbook.txt
void printLog(log * head);

int main()
{
    //e
    log * head = (log*) malloc(sizeof(log));
}