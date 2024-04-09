/* PROGRAMMING PROJECT FOR CS103
 ______     ____     ___     ____     ___     ____     ___
|  ____|   |  _ \   / _ \   |  _ \   / _ \   |  _ \   / _ \ 
| |___     | [_] | / /_\ \  | [_] | / /_\ \  | | | | / /_\ \
|  ___| [] |  __/  | ___  | |   _/  | ___  | | | | | | ___  | 
| |____    | |     | |  | | | |\ \  | |  | | | |_/ / | |  | |
|______|   |_|     |_|  |_| |_| \_\ |_|  |_| |___ /  |_|  |_|

Electronic Parking and Documentation Algorithm

 programmed by: JOLOC, GABARDA, GALLEGO, TABAYAG

 ACADEMIC YEAR 2023-2024
 CS103 MS ARLENE SATUITO

*/

#include <stdio.h>


//---------------------------------------------------------------------
//ALL FUNCTION HEADERS HERE!!!!

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




//-------------------------------------------------------------------------

int main (){
printf("hello World!");
 //hi from YNO




return 0;
}
