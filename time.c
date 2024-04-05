#include<time.h>
#include<stdio.h>

int main()
{
    time_t timep;
    struct tm* ptr;
    time(&timep);
    ptr = localtime(&timep);
    printf("%d:%d", ptr->tm_hour, ptr->tm_min);

    return 0;
}