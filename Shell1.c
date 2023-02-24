#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>


void main()
{
  char command[10];
  char path[] ="/bin/";
  int pid;
  int flag=1;
  while(flag)
   { 
      printf("Shell1$** ");
      gets(command);
      strcat(command,"\0");
      if(strcmp(command,"Esc")==0 || strcmp(command,"esc")==0)
          exit(1);
       strcat(path,command); // /bin/command
      if(( pid = fork()) == -1) 
       {
          perror( "fork() failed.");
          exit(1);
       }

      if( pid == 0 )   {
         execl(path,command, NULL );
         printf( "Not Supported\n" );
         exit(1);
       }
       strcpy(path, "/bin/");     //we do this becuase path = /bin/command  (epos)
       wait(NULL);
   }//end of while
}//end of main
