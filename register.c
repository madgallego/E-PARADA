void rgstr(Profile ** head, char plate[], char id[]){
    Profile * new, * p;
    char type;

    p = *head;
    new = (Profile*)malloc(sizeof(Profile));
    while(p->nxtPtr != NULL){
        p = p->nxtPtr;
    }

    printf("Please indicate vehicle type(A=car, B=motorcycle): ");
    scanf(" %c", &type);

    if(p->nxtPtr == NULL){
        strcpy(new->plateNum, plate);
        strcpy(new->profileID, id);
        new->type = type;
        new->nxtPtr = NULL;
        p->nxtPtr = new;
    }
}