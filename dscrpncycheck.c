#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAX 100

void dscrpncyCheck(Profile * profile, char plate[], char id[]);

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

void dscrpncyCheck(Profile * head, char plate[], char id[]){
    FILE * ifp = fopen("dscrpncy.txt","a");
    Profile * p;
    int option;

    p = head;
    while(p->nxtPtr != NULL){
        if((strcmp(plate, p->plateNum) == 0) && (strcmp(id, p->profileID) == 0)){
            printf("Parking Details Complete!\nSuccessfully Recorded");
            break;
        }
        else if((strcmp(plate, p->plateNum) == 0) && (strcmp(id, p->profileID) != 0)){
            printf("Driver Profile does not match in Database\n");
            printf("\n1. End Transaction\n2. Archive Transaction to Discrepancy File\n");
            scanf("%d", &option);
            if(option == 1){
                break;
            }
            else if(option == 2){
                fprintf(ifp, "Plate Number: %s | Profile ID: %s -> Discrepancy: %s\n", p->plateNum, p->profileID, id);
                break;
            }
        }
        else{
            p = p->nxtPtr;
        }
    }
    fclose(ifp);
}
