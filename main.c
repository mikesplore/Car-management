#include<stdio.h>
#include "book.h"
#include<stdlib.h>
 
#include <time.h>
#include<string.h>
int rando();

int main(){
    struct Student students;
    struct admin admins;
    int choice,option;
    int otp=rando();
    int ch;
   
	
	
	printf("                                                                          *\n");
	printf("                                                                         *\n");
	printf("                                                                       ***\n");
	printf("                                                                     *****\n");
	printf("                                                                   **WELCOME*\n");
	printf("                                                                 ****TO****\n");
	printf("                                                                   **OUR**\n");
	printf("                                                                   **LIBRARY**\n");
	printf("                                                                   *****\n");
	printf("                                                               *********\n");
	printf("                                                               *********\n");
    printf("                                                               *********\n");
   
  	
	
	char name[50],password[20],staff_no[20];
	char name1[50],password1[20],staff_no1[20];
	char name2[50],password2[20],studentId[20];
	
	 repeat:
	 	menu:
   printf("\t\t\t\t\t\t\t\t1.Staff Log In.\n\t\t\t\t\t\t\t\t2.Student Log In.\n\t\t\t\t\t\t\t\t3.Exit\n");
   scanf("%d",&option);
   
   if(option==1){
   	start:
   	printf("\t\t\t\t\t\t\t\tEnter your sign up details.\n");
   	printf("\t\t\t\t\t\t\t\tEnter your name: ");
   	getchar();
   	fgets(name,50,stdin);
   	printf("\t\t\t\t\t\t\t\tEnter your staff number eg.staff/TUM/0000: ");
   	
   	fgets(staff_no,20,stdin);
   	
   	printf("\t\t\t\t\t\t\t\tEnter your password: ");
   	fgets(password,20,stdin);
   	printf("\t\t\t\t\t\t\t\tYou have successfully created an accont.\n");
   	printf("\n\t\t\t\t\t\t\t\tTo Log in enter your sign up details.\n");
   	
   
   	printf("\t\t\t\t\t\t\t\tEnter your name: ");
   	getchar();
   	fgets(name1,50,stdin);
   	printf("\t\t\t\t\t\t\t\tEnter your staff number: ");
   	fgets(staff_no1,20,stdin);
   	printf("\t\t\t\t\t\t\t\tEnter your password: ");
   	fgets(password1,20,stdin);
   	
   	
   	if(strcmp(staff_no1,staff_no)==0 && strcmp(password1,password)==0){
   		printf("\t\t\t\t\t\t\t\tYou have successfully created an accont.\n");
   		printf("\t\t\t\t\t\t\t\tLog In Successfull.\n");
   		name1[strcspn(name1,"\n")]='\0';
   		printf("\n\t\t\t\t\t\t\t\tHello %s, your 4 digit OTP is %d\n\n",name1,otp);
   		
   		printf("\n\t\t\t\t\t\t\t\tWelcome %s, choose one of the following: \n\n",name1);
   		
	   }
   	else {
   		
   		printf("\t\t\t\t\t\t\t\tYou have entered wrong staff number or password.\n");
   		goto start;
   		
	   }
   }
   
   else if(option==2){
   	star:
   	printf("\t\t\t\t\t\t\t\tEnter your sign up details.\n");
   	printf("\t\t\t\t\t\t\t\tEnter your name: ");
   	getchar();
   	fgets(name2,50,stdin);
   	printf("\t\t\t\t\t\t\t\tEnter your student number eg.BSCS/000J/YYYY: ");
   	fgets(studentId,20,stdin);
   	printf("\t\t\t\t\t\t\t\tEnter your password: ");
   	fgets(password2,20,stdin);
   	printf("\t\t\t\t\t\t\t\tYou have successfully created an accont.\n");
   	printf("\n\t\t\t\t\t\t\t\tTo Log in enter your sign up details.\n");
   	
   
   	printf("\t\t\t\t\t\t\t\tEnter your name: ");
   	getchar();
   	fgets(students.name,50,stdin);
   	printf("\t\t\t\t\t\t\t\tEnter your student number: ");
   	fgets(students.studentId,20,stdin);
   	printf("\t\t\t\t\t\t\t\tEnter your password: ");
   	fgets(students.password,20,stdin);
   
   	printf("\t\t\t\t\t\t\t\tYou have successfully created an accont.\n");
   	
   	if(strcmp(students.studentId,studentId)==0 && strcmp(students.password,password2)==0){
   		
   		printf("\t\t\t\t\t\t\t\tLog In Successfull.\n");
   		students.name[strcspn(students.name ,"\n")]='\0';
   		printf("\n\t\t\t\t\t\t\t\tHello %s, your 4 digit OTP is %d\n\n",students.name,otp);
   		
   		printf("\n\t\t\t\t\t\t\t\tWelcome %s, choose one of the following: \n\n",students.name);
	   }
   	else {
   		
   		printf("\t\t\t\t\t\t\t\tYou have entered wrong name or student number or password.\n");
   		goto star;
   		
	   }
   	
   }
   
   else if(option==3){
   				printf("************************************\n");
                printf("********Thank you for using the library management system! Exiting *******\n");
                printf("************************************\n");
                
                exit(0);
   	
   }
   
   else{
   	
   	goto repeat;
   	
   }
   
        
    do{
    	back:
    	restart:
        printf("\n");
        
        printf("                    1. Register new book              2. Delete book\n");
        
        printf("                    3. Check available books          4. Borrow book\n");
        
        printf("                    5. Return a book                  6. Check borrowed books\n");
        
        printf("                                    7. Exit the system                    \n");

        
        printf("                                    Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
           if(option==2){
           	printf("\t\t\t\t\t\t\t\tYou are not allowed to use this service.\n");
           	goto back;
		   }
           if (authentication(otp)){
           registerNewBook();
           }else{
            printf("Bye!");

           }
           

            break;

            case 2:
            	if(option==2){
            		printf("\t\t\t\t\t\t\t\tYou are nt allowed to use this service.\n");
            		
            		goto restart;
				}
           if (authentication(otp)){
           deleteBook();
           }else{
            printf("Bye!");

           }
            break;

            case 3:
                
           checkAvailableBooks();
           
                break;

            case 4:
              if (authentication(otp)){
           borrowBook();
           }else{
            printf("Bye!");

           }
                break;

            case 5:
                if (authentication(otp)){
           returnBook();
           }else{
            printf("Bye!");

           }
                break;
                  

            case 6:
            checkBorrowedBooks(); 
            break;   

            case 7:
				
				printf("To go back to menu press 1, to exit press 2: ");
				scanf("%d",&ch);
				if (ch==1){
					goto menu;
				}
				else {
				printf("\t\t************************************\n");
                printf("\t\t**********Thank you for using the library management system! Exiting *******\n");
                printf("\t\t************************************\n");
                
                exit(0);	
					
				}
             
                default:
                printf("Invalid choice.\n");
                break;
        }
    } while(choice != 7); // Terminate loop when choice is 7

   return 0;
}