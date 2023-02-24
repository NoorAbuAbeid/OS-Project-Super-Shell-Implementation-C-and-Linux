#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>

#define MAX 1024

void Size_func(char*,int);//function to cacualte the size of file
void Max_func(char*,char*);//function for calcualte which file have max chars 
void merge_func1(char*,char*,char*);//function to merge two files and creat new file
void merge_func2(char*,char*);//function to merge 2 files and prints on screen

void main()
{
  int flag=1; // for endless loop
  char *command=(char*)malloc(sizeof(char) * 50);  //for commands
  int i,j,k;
  char newString[10][10]; // to know how many strings their are in the command
  while(flag)
   {

     printf("Shell3$** ");
     gets(command);
     strcat(command,"\0");
     j = 0; k = 0;
     for (i = 0; i <= (strlen(command)); i++)
      {
        if (command[i] == ' ' || command[i] == '\0')
           {
             newString[k][j] = '\0';
             k++;      //for next word(count number of words)
             j = 0;    //for next word, init index to 0
           }
        else
           {
             newString[k][j] = command[i];
             j++;
           }
       }//end of for
      int err=0; //to check if the user entered one of the commands that given in the question
      if(strcmp(newString[0],"Esc")==0 || strcmp(newString[0],"esc")==0)// if the user want to return to shell (main shell)
          exit(1);
      if(strcmp(newString[0],"Delete")==0 || strcmp(newString[0],"delete")==0)// if the user want to remove/delete a file
         {
           err=1;
           if (k==1 || k>2) //if the user entered just the word "delete" or enterd to many parameters..
           printf("Error\n");
           remove(newString[1]);
         }

      if(strcmp(newString[0],"Size")==0 || strcmp(newString[0],"size")==0)// size of file
       {
        err=1;
        Size_func(newString[1],k); //call Size_func()
       }

       if(strcmp(newString[0],"Find_Max")==0 )// max file
        {
          err=1;
          if (k==1 || k>3) //if the user entered just the word "Find_Max" or enterd to many parameters (more than two files..
           printf("Error\n");
           else Max_func(newString[1],newString[2]);
        }
         
      if(strcmp(newString[0],"Merge")==0 )
        { 
          err=1;
          if(k!=3 && k!=4)    //if the user didn't enter 3 files or 2 files
           printf("Error\n");
           else 
             {
                if(k==4) 
                 merge_func1(newString[1],newString[2],newString[3]);
                else 
                 merge_func2(newString[1],newString[2]);
             }//end of first else
           
          
        }

      
     if(!err)
     printf("Error\n"); //the user didn't enter one of the commands 
   }//end of while



}//end of main


void Size_func(char* file,int k)//function to cacualte the size of file
 {
   int fd; //to open file
   int rbytes; //for reading from the file
   char buff[MAX]; 
   
     if (k==1 || k>2) //if the user entered just the word "size" or enterd to many parameters..
       printf("Error\n");
     else{
     if( (fd=open( file, O_RDONLY, 0 ))== -1 )
      {
	   perror( "open");
	   exit(1);
      }

      if( ( rbytes = read( fd, buff, MAX) ) == -1 )    //read from file
		 { 
           perror( "read" ); 
           exit(1);
         }
        printf("Their is %d chars in this file.\n",rbytes); //call Size_func()
       }//end of else
 }


void Max_func(char* file1,char* file2)
 {
   int fd1,fd2; // for open files
   int r1,r2;  // for read files
   char buff1[MAX],buff2[MAX];

   if( (fd1=open( file1, O_RDONLY, 0 ))== -1 ) //open first file
     {
	   perror( "open");
	   exit(1);
     }

   if( (fd2=open( file2, O_RDONLY, 0 ))== -1 ) //open second file
     {
	   perror( "open");
	   exit(1);
     }

   if( ( r1 = read( fd1, buff1, MAX) ) == -1 )    //read first file
		 { 
           perror( "read" ); 
           exit(1);
         }

   if( ( r2 = read( fd2, buff2, MAX) ) == -1 )    //read second file
		 { 
           perror( "read" ); 
           exit(1);
         }
   if(r1==r2)
            printf("Same number of chars\n");
            else {
            if(r1>r2)
               printf("%s have max chars\n",file1);
            else  printf("%s have max of chars\n",file2); 
         }//end of first else

  close(fd1);
  close(fd2);
 }

void merge_func1(char* file1,char* file2,char* file3)
{
   int fd1,fd2,fd3; // to open files
   int r1,r2;  // to read files
   char buff1[MAX],buff2[MAX];
   char str[] = { ' ','\n' }; //to use the function strcspn that returns the first apper of str in buff1/buff2
   int wbyte3; //to write in file3 
   int i,j,cnt1,cnt2;

   if( (fd1=open( file1, O_RDONLY, 0 ))== -1 ) //open first file
     {
	   perror( "open");
	   exit(1);
     }

   if( (fd2=open( file2, O_RDONLY, 0 ))== -1 ) //open second file
     {
	   perror( "open");
	   exit(1);
     }

   if( ( r1 = read( fd1, buff1, MAX) ) == -1 )    //read first file
		 { 
           perror( "read" ); 
           exit(1);
         }

   if( ( r2 = read( fd2, buff2, MAX) ) == -1 )    //read second file
		 { 
           perror( "read" ); 
           exit(1);
         }
   if((fd3 = open( file3, O_WRONLY | O_CREAT, 0664 ))==-1) //create file3.txt 
    {
      perror("open");
      exit(1);  
    }

 
	i = 0;
	j = 0;
	while (r1>0 || r2>0) //loop while end when on of the two files will end
	{

		if (r1 > 0) {//if rbytes for firsr file > rbytes for second file
			cnt1 = strcspn((buff1 + i), str); //return first appear of str in buff1
			if ((1 + cnt1 + i) < r1) {
				if ((wbyte3 = write(fd3, buff1 + i, cnt1 + 1)) == -1) {
					perror("write file3");
						exit(1);
				}
				if (wbyte3 != cnt1 + 1) {
					fprintf(stderr, "bad write in first if/n");
						exit(1);
				}
				i = cnt1 + i + 1;
			}
			else {
				if ((wbyte3 = write(fd3, buff1 + i, cnt1)) == -1) {
					perror("write file3");
						exit(1);
				}
				if (wbyte3 != cnt1) {
					fprintf(stderr, "bad write in first if/n");
						exit(1);
				}
				if ((r1 = read(fd1, buff1, MAX)) == -1) {
					perror("read file1");
						exit(1);
				}
				if (r1 > 0) {
					i = 0;
					if (buff1[i] == ' ' || buff1[i] == '\n') {
						cnt1 = 0;
					}
					else {
						cnt1 = strcspn(buff1 + i, str);
					}
					if ((wbyte3 = write(fd3, buff1 + i, cnt1 + 1)) == -1) {
						perror("write file3");
						exit(1);
					}
					if (wbyte3 != cnt1 + 1) {
						fprintf(stderr, "bad write in second if /n");
						exit(1);
					}
					i = cnt1 + i + 1;
				}
				else
				{
					if ((wbyte3 = write(fd3, str, 1)) == -1) {
						perror("write file3");
						exit(1);
					}
					if (wbyte3 != 1) {
						fprintf(stderr, "bad write in first if/n");
						exit(1);
					}

				}

			}//end of ((1 + cnt1 + i) < r1)
		}//enf of r1>0


		if (r2 > 0) {
			cnt2 = strcspn((buff2 + j), str);
			if ((1 + cnt2 + j) < r2) {
				if ((wbyte3 = write(fd3, buff2 + j, cnt2 + 1)) == -1) {
					perror("write file3");
						exit(1);
				}
				if (wbyte3 != cnt2 + 1) {
					fprintf(stderr, "bad write in first if/n");
						exit(1);
				}
				j = cnt2 + j + 1;
			}
			else {

				if ((wbyte3 = write(fd3, buff2 + j, cnt2)) == -1) {
					perror("write file3");
						exit(1);
				}
				if (wbyte3 != cnt2) {
					fprintf(stderr, "bad write in first if/n");
						exit(1);
				}

				if ((r2 = read(fd1, buff2, MAX)) == -1) {
					perror("read file1");
						exit(1);
				}
				if (r2 > 0) {
					j = 0;
					if (buff2[j] == ' ' || buff2[j] == '\n') {
						cnt2 = 0;
					}
					else {
						cnt2 = strcspn(buff2 + j, str);
					}
					if ((wbyte3 = write(fd3, buff2 + j, cnt2 + 1)) == -1) {
						perror("write file3");
						exit(1);
					}
					if (wbyte3 != cnt2 + 1) {
						fprintf(stderr, "bad write in second if /n");
						exit(1);
					}
					j = cnt2 + j + 1;
				}
				else
				{
					if ((wbyte3 = write(fd3, str, 1)) == -1) {
						perror("write file3");
						exit(1);
					}
					if (wbyte3 != 1) {
						fprintf(stderr, "bad write in first if/n");
						exit(1);
					}
				}
			}
		}//end of r2>0
	}//end of while

    close(fd1);
	close(fd2);
	close(fd3);
}

void merge_func2(char* file1 ,char* file2)
{ 
   int fd1,fd2; // to open files
   int r1,r2;  // to read files
   char buff1[MAX],buff2[MAX];
   char str[] = { ' ','\n' }; //to use the function strcspn that returns the first apper of str in buff1/buff2
   int wbyte3; //to write in file3 
   int i,j,cnt1,cnt2;


   if( (fd1=open( file1, O_RDONLY, 0 ))== -1 ) //open first file
     {
	   perror( "open");
	   exit(1);
     }

   if( (fd2=open( file2, O_RDONLY, 0 ))== -1 ) //open second file
     {
	   perror( "open");
	   exit(1);
     }

   if( ( r1 = read( fd1, buff1, MAX) ) == -1 )    //read first file
		 { 
           perror( "read" ); 
           exit(1);
         }

   if( ( r2 = read( fd2, buff2, MAX) ) == -1 )    //read second file
		 { 
           perror( "read" ); 
           exit(1);
         }

 
	i = 0;
	j = 0;
	while (r1>0 || r2>0) //loop while end when on of the two files will end
	{

		if (r1 > 0) {//if rbytes for firsr file > rbytes for second file
			cnt1 = strcspn((buff1 + i), str); //return first appear of str in buff1
			if ((1 + cnt1 + i) < r1) {
			        fflush(stdout); /* force it to go out */
                     write(1,buff1+i,cnt1+1);

				i = cnt1 + i + 1;
			}
			else {
                   fflush(stdout); /* force it to go out */
                     write(1,buff1+i,cnt1);
			
				if ((r1 = read(fd1, buff1, MAX)) == -1) {
					perror("read file1");
						exit(1);
				}
				if (r1 > 0) {
					i = 0;
					if (buff1[i] == ' ' || buff1[i] == '\n') {
						cnt1 = 0;
					}
					else {
						cnt1 = strcspn(buff1 + i, str);
					}
					fflush(stdout); /* force it to go out */
                     write(1,buff1+i,cnt1+1);
	
					i = cnt1 + i + 1;
				}
				else
				{
					
                        fflush(stdout); /* force it to go out */
                        write(1,str,1);

				}

			}//end of ((1 + cnt1 + i) < r1)
		}//enf of r1>0


		if (r2 > 0) {
			cnt2 = strcspn((buff2 + j), str);
			if ((1 + cnt2 + j) < r2) {
                    fflush(stdout); /* force it to go out */
                     write(1,buff2+j,cnt2+1); 
			
				j = cnt2 + j + 1;
			}
			else {

				   fflush(stdout); /* force it to go out */
                     write(1,buff2+j,cnt2); 
				

				if ((r2 = read(fd1, buff2, MAX)) == -1) {
					perror("read file1");
						exit(1);
				}
				if (r2 > 0) {
					j = 0;
					if (buff2[j] == ' ' || buff2[j] == '\n') {
						cnt2 = 0;
					}
					else {
						cnt2 = strcspn(buff2 + j, str);
					}
					   fflush(stdout); /* force it to go out */
                     write(1,buff2+j,cnt2+1); 
				
					j = cnt2 + j + 1;
				}
				else
				{
					
                     fflush(stdout); /* force it to go out */
                     write(1,str,1); 
					
				}
			}
		}//end of r2>0
	}//end of while
    printf("\n");
    close(fd1);
	close(fd2);

}

