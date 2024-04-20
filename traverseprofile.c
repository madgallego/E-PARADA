#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAX 100

int traverseProfile(Profile * head, char plate[], char id[], char type);

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

int traverseProfile(Profile * head, char plate[], char id[], char type){
    Profile *p;

    p = head;
    while(p->nxtPtr != NULL){
        if((strcmp(plate, p->plateNum) != 0) && (strcmp(id, p->profileID) != 0)){
            return 0;
        }
        else{
            p = p->nxtPtr;
        }
    }
    
    if(p->nxtPtr == NULL)
        return 1;
}
