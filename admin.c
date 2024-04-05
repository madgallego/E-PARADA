#include <stdio.h>
#define MAX 100

typedef struct {
	char user[MAX];
	char passkey[MAX];

} Admin;

struct node {
	char plateNum [MAX];
	char profileID [MAX];
	char type;
    struct node * nxtPtr;
} typedef struct node Profile;

void animate (){}
void prntMap (){}

void traverseProfile(void){}
void dscrpncyCheck(void){}

int Administrator(void){
    Admin admin;
    int option;
    char plateNum[MAX];

    printf("Admin: ");
    scanf("%s", admin.user);
    printf("Password: ");
    scanf("%s", admin.passkey);

    printf("\n1. PMS\n2. Search Profile\n");
    scanf("%d", option);
    if(option == 1){
        printf("\nChoose Action:\n1. Park In\n2. Park Out\n");
        scanf("%d", option);
        if(option == 1){
            traverseProfile();
        }
        else if(option == 2){
            dscrpncyCheck();
        }
    } 
    else if(option == 2){
        printf("Enter Plate Number: ");
        scanf("%s", plateNum);
    }
}

int main(){
    Administrator();
}

