#include <stdio.h>
#include <string.h>

int main()
{
    char str1[10];
    char str2[15];
    sprintf(str1, "%d %d %d",1 , 2 ,3 );

    sprintf(str2, "def");

    strcat(str1, ":");
    
    printf("str1 depois de strcat(str1, \":\"):\n%s", str1);
    
    strcat(str1, str2);
    
    printf("\nstr1 depois de strcat(str1, str2):\n%s\n\n", str1);
    
    return 0;
}