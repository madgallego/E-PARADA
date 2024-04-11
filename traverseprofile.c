#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAX 100

void traverseProfile(Profile * head, FILE * prnt);

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

int traverseProfile(Profile * head, char plate[], char id[]){
    Profile *p

    p = head;
    while(p->nxtPtr != NULL){
        if(plate == head->plateNum && id == head->profileID){
            return 0;
        }
        else{
            p = p->nxtPtr
        }
    }
    
    if(p->nxtPtr == NULL)
        return 1;
}
