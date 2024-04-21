#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAX 100

int traverseProfile(Profile * head, char plate[]);

struct node { //struct of Profile
	char plateNum [MAX];
	char profileID [MAX];
	char type;
    struct node * nxtPtr;
};// for records linked list
typedef struct node Profile;

int main (){

return 0;
}

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
