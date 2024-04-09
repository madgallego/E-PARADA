#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//Handles parking animation depending on return of useLog. Please subtract 1 from designation for array operations
void peterParker(int designation, int car[20], int motor[20]);
//Presents lower parking spot for car and occupied spots
void carParkerlower(int car[20]);
//presents upper parking spot for car and occupied spots
void carParkerupper(int car[20]);
//presents lower parking spot for motor and occupied spots
void motorParkerlower(int motor[20]);
//presents upper parking spot for motor and occupied spots
void motorParkerupper(int motor[20]);
//prints upward arrow
void arrow(int artype, int designation, int vtype);
//prints downward arrow
void arrowD(int artype, int designation, int vtype);

int main()
{
    int car[20] = {0};
    int motor[20] = {0};
    motor[3] = 1;
    car[9] = 1;
    printf("car\n");
    peterParker(34, car, motor);

    return 0;
}

void peterParker(int designation, int car[20], int motor[20])
{
    time_t flash;
    int i = 0;
    //checks vehicle type
    if(designation <= 20) //CAR
    {
        flash = time(NULL);
        while(i < 5)
        {
            if((time(NULL) - flash) == 1)
            {
                //clear terminal
                printf("\e[1;1H\e[2J");
                carParkerupper(car);
                //prints either upward or downward arrow
                if(designation <= 10)
                    arrow(0, designation, 0);
                else
                    arrowD(0, designation, 0);
                carParkerlower(car);
                flash = time(NULL);
                while(1)
                {
                    if((time(NULL) - flash) == 1)
                    {
                        //clear terminal
                        printf("\e[1;1H\e[2J");
                        carParkerupper(car);
                        //print upward or downward arrow of type 1
                        if(designation <= 10)
                            arrow(1, designation, 0);
                        else
                            arrowD(1, designation, 0);
                        carParkerlower(car);
                        flash = time(NULL);
                        break;
                    }
                }
                i++;
            }
        }
    }
    else
    {
        //for motor
        designation -= 20;
        flash = time(NULL);
        while(i < 10)
        {
            if((time(NULL) - flash) == 1)
            {
                printf("\e[1;1H\e[2J");
                motorParkerupper(motor);
                if(designation <=10)
                    arrow(0, designation, 1);
                else
                    arrowD(0, designation, 1);
                motorParkerlower(motor);
                flash = time(NULL);
                while(1)
                {
                    if((time(NULL) - flash) == 1)
                    {
                        printf("\e[1;1H\e[2J");
                        motorParkerupper(motor);
                        if(designation<=10)
                            arrow(1, designation, 1);
                        else
                            arrowD(1, designation, 1);
                        motorParkerlower(motor);
                        flash = time(NULL);
                        break;
                    }
                }
                i++;
            }
        }

    }
}
void carParkerupper(int car[20])
{
    //UPPER PARKING SPOT
    printf("|==============================================================|\n");
    printf("|   ---   ---   ---   ---   ---   ---   ---   ---   ---   ---  |\n");

    for(int i = 0; i<3; i++)
    {
        if(i < 2)
        {
            printf("|  ");
            for(int j = 0; j<10; j++)
            {
                if(car[j] == 0)
                    printf("|   | ");
                else if(car[j] == 1)
                    printf("|===| ");
            }
            printf("|\n");            
        }
        else if(i == 2)
        {
            printf("|  ");
            for(int j = 1; j<11; j++)
                printf(" %2d   ", j);
            printf("|\n");
        }
    }
}
void carParkerlower(int car[20])
{
    //LOWER PARKING SPOT
    for(int i = 0; i < 3; i++)
    {
        if(i == 0)
        {
            printf("|  ");
            for(int j = 11; j < 21; j++)
            {
                printf(" %2d   ", j);
            }
            printf("|\n");
        }
        else
        {
            printf("|  ");
            for(int j = 10; j < 20; j++)
            {
                if(car[j] == 0)
                    printf("|   | ");
                else if(car[j] == 1)
                    printf("|===| ");
            }
            printf("|\n");
        }
    }
    printf("|==============================================================|\n");
    printf("|   ---   ---   ---   ---   ---   ---   ---   ---   ---   ---  |\n");
}
void motorParkerupper(int motor[20])
{
    //UPPER PARKING SPOT
    printf("|====================================================|\n");
    printf("|   --   --   --   --   --   --   --   --   --   --  |\n");
    for(int i = 0; i<3; i++)
    {
        if(i < 2)
        {
            printf("|  ");
            for(int j = 0; j<10; j++)
            {
                if(motor[j] == 0)
                    printf("|  | ");
                else if(motor[j] == 1)
                    printf("|==| ");
            }
            printf("|\n");            
        }
        else if(i == 2)
        {
            printf("|  ");
            for(int j = 1; j<11; j++)
                printf(" %2d  ", j);
            printf("|\n");
        }
    }
   
}
void motorParkerlower(int motor[20])
{
    //LOWER PARKING SPOT
    for(int i = 0; i < 3; i++)
    {
        if(i == 0)
        {
            printf("|  ");
            for(int j = 11; j < 21; j++)
            {
                printf(" %2d  ", j);
            }
            printf("|\n");
        }
        else
        {
            printf("|  ");
            for(int j = 10; j < 20; j++)
            {
                if(motor[j] == 0)
                    printf("|  | ");
                else if(motor[j] == 1)
                    printf("|==| ");
            }
            printf("|\n");
        }
    }
    printf("|   --   --   --   --   --   --   --   --   --   --  |\n");
    printf("|====================================================|\n");
}

void arrow(int artype, int designation, int vtype)
{
    int spaces = 0;
    //type 1 of arrow (arrow type printed alternately per sec)
    if(artype == 0)
    {
        //car
        if(vtype == 0)
        {
            spaces = 5 *(designation) + (designation - 1);
            for(int i = 0; i < spaces; i++)
                printf(" ");
            printf("^\n");
            for(int i = 0; i < spaces - 1; i++)
                printf(" ");
            printf("/_\\\n");
            for(int i = 0; i <spaces/2; i++)
                printf("=>");
            printf("=|\n\n\n");
        }
        else if(vtype == 1)
        {
            spaces = 3 *(designation) + 2 *(designation - 1);
            printf(" ");
            for(int i = 0; i<spaces; i++)
                printf(" ");
            printf("/\\\n");
            printf(" ");
            for(int i = 0; i<spaces; i++)
                printf(" ");
            printf("||\n");
            for(int i = 0; i<spaces/2 + 1; i++)
                printf("=>");
            printf("=|\n");
        }
    }
    else if(artype == 1)
    {
        //car
        if(vtype == 0)
        {
            spaces = 5 *(designation) + (designation - 1);
            for(int i = 0; i < spaces; i++)
                printf(" ");
            printf("A\n");
            for(int i = 0; i < spaces - 1; i++)
                printf(" ");
            printf("/ \\\n");
            for(int i = 0; i <spaces/2; i++)
                printf(">=");
            printf(">!\n\n\n");
        }
        else if(vtype == 1)
        {
            spaces = 3 *(designation) + 2 *(designation - 1);
            printf(" ");
            for(int i = 0; i<spaces; i++)
                printf(" ");
            printf("/\\\n");
            printf(" ");
            for(int i = 0; i<spaces; i++)
                printf(" ");
            printf("!!\n");
            for(int i = 0; i<spaces/2 + 1; i++)
                printf(">=");
            printf(">!\n");
        }
    }
}
void arrowD(int artype, int designation, int vtype)
{
    int spaces = 0;
    designation -= 10;
    //type 1 of arrow (arrow type printed alternately per sec)
    if(artype == 0)
    {
        //car
        if(vtype == 0)
        {
            spaces = 5 *(designation) + (designation - 1);
            printf("\n\n\n");
            for(int i = 0; i <spaces/2; i++)
                printf("=>");
            printf("=|\n");
            for(int i = 0; i < spaces - 1; i++)
                printf(" ");
            printf("\\-/\n");
            for(int i = 0; i < spaces; i++)
                printf(" ");
            printf("V\n");
            
        }
        else if(vtype == 1)
        {
            spaces = 3 *(designation) + 2 *(designation - 1);
            printf("\n\n\n");
            for(int i = 0; i<spaces/2 + 1; i++)
                printf("=>");
            printf("|\n");
            printf(" ");
            for(int i = 0; i<spaces; i++)
                printf(" ");
            printf("||\n");
            printf(" ");
            for(int i = 0; i<spaces; i++)
                printf(" ");
            printf("\\/\n");
        }
    }
    else if(artype == 1)
    {
        //car
        if(vtype == 0)
        {
            spaces = 5 *(designation) + (designation - 1);
            printf("\n\n\n");
            for(int i = 0; i <spaces/2; i++)
                printf(">=");
            printf(">!\n");
            for(int i = 0; i < spaces - 1; i++)
                printf(" ");
            printf("\\-/\n");
            for(int i = 0; i < spaces; i++)
                printf(" ");
            printf("V\n");

        }
        else if(vtype == 1)
        {
            spaces = 3 *(designation) + 2 *(designation - 1);
            printf("\n\n\n");
            for(int i = 0; i<spaces/2 + 1; i++)
                printf(">=");
            printf("!\n");
            for(int i = 0; i<spaces; i++)
                printf(" ");
            printf(" ");
            printf("!!\n");
            printf(" ");
            for(int i = 0; i<spaces; i++)
                printf(" ");
            printf("\\/\n");
        }
    }
}
