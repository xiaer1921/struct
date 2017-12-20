#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
void bar()
{
    int count = 0;
    char buff[101];
    char index[5]="-\\|/";
    memset(buff, '\0' , sizeof(buff));

    while(count<=100)
    {
        if(count == 100)
           index[0]=' ';
        printf("[%-100s][%d%%]%c\r", buff,count, index[count%4]);
        fflush(stdout);
        buff[count] = '=';
        count++;
        usleep(100000);
    }
    printf("\n");
}

int main()
{
    bar();
    return 0;
}
