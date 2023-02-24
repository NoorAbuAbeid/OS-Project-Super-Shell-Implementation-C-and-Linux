#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>

void print_func();

void main()
{
  char *command=(char*)malloc(sizeof(char) * 50);  //for commands
  char path[] ="/bin/";
  int flag=1; // for endless loop
  int i,j,k;
  int pid; //for fork
  char newString[10][10]; // to know how many strings their are in the command

  while(flag)
   {
     printf("Shell2$** ");
     gets(command);
     strcat(command,"\0");
     j = 0; k = 0;
    for (i = 0; i <= (strlen(command)); i++)
      {
       if (command[i] == ' ' || command[i] == '\0')
        {
         newString[k][j] = '\0';
         k++;      //for next word
         j = 0;    //for next word, init index to 0
        }
        else
         {
           newString[k][j] = command[i];
           j++;
          }
        }//end of for
  if(strcmp(newString[0],"Esc")==0 || strcmp(newString[0],"esc")==0)// if the user want to return to shell (main shell)
          exit(1);
      strcat(path, newString[0]);//put command in path ---> /bin/command
      if(k==1)//if the user entered just the command (without parameters) or didn't enter any command
            {
             printf("Not Supported\n");
            }//end of k==1
       else {
       if(( pid = fork()) == -1)
          {
             perror( "fork() failed.");
             exit(1);
          }//end of fork
        if(pid == 0)
         {
          if (k == 2) //if the user entered only one parameter
           {
             execl(path, newString[0], newString[1], NULL);
            print_func();
           }//end of k==2
           if (k == 3) //if the user entered two  parameters
            {
               execl(path, newString[0], newString[1], newString[2], NULL);
              print_func();
            }//end of k==3
           if (k == 4) //if the user entered three parameters
            {
               execl(path, newString[0], newString[1], newString[2], newString[3], NULL);
              print_func();
            }//end of k==4
         }//end of pid==0
        }//end of else
       strcpy(path, "/bin/");     //we do this becuase path = /bin/command  (epos)
       wait(NULL);
   }//end of while


}//end of main



void print_func()
 {
    printf( "Not Supported\n" );
    exit(1);
 }// end of function
