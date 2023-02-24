#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>


void main()
 {
   char* shell=(char*)malloc(sizeof(char) * 15);  //for shells
   int flag=1; //for Endless while
   int pid;
   while(flag)
    {
      printf("Enter shell1 to run linux commands without parameters\n");
      printf("Enter shell2 to run linux commands with parameters\n");
      printf("Enter shell3 to run commands to file editing\nShell$** ");
      gets(shell);
      strcat(shell,"\0");
      if(strcmp(shell,"exit")==0 || strcmp(shell,"Exit")==0)  //if the user want to exit from shell
       exit(1);
       if(( pid = fork()) == -1) 
       {
          perror( "fork() failed.");
          exit(1);
       }//end of fork

       if( pid == 0 ) //if the user want to open shellX
        {
            execl(shell, NULL );
            printf( "Not Support\n" );
            exit(1 );
        }//end of pid==0
        wait(NULL);

    }//end of while 
 }//end of main

