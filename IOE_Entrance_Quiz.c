#include <stdio.h>
#include<math.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

//For storing score of the user
typedef struct score_points
{
    int total;
    int correct;
}score;

//For storing user details
typedef struct user_account
{
    char name[50];
    int pin;
    score phy; //Application of nested structure
    score chem;
    score maths;
}user;

void display_start_msg()
{
    system("cls");
             printf("\t\t\tC PROGRAM QUIZ GAME\n");
             printf("\n\t\t\t   WELCOME ");
             printf("\n\t\t\t      to ");
             printf("\n\t\t\t   THE GAME ");
             printf("\n\t\t\t Ko Banchha Pulchowkian    ") ;
             printf("\n\t\t________________________________________\n\n");
}
void display_help_msg()
	{
	system("cls");
	helps:
    printf("\n\n                              HELP");
    printf("\n -------------------------------------------------------------------------");
    printf("\n ......................... IOE Entrance Quiz Game...........");
    printf("\n   Input right answers otherwise you can't gain the points...........");
    printf("\n >> After you are asked questions you will have 4 options in your screen");

    printf("\nEnter correct option to win points");
    printf("\n >> 1 marks is alloted for each correct answer");
    printf("\n >> You will asked a total of 10 questions");
    printf("\n >> No negative marking for wrong answers");
	printf("\n\n\t*********************BEST OF LUCK*********************************");
}
//User defined functions for different functionality of the game.
int login();
int signup();
void start(int);
void test(int);
void display_scores(int);
char display_questions(int, int, char []);
void review_questions(int, int, char []);
void update_score(char, int, int);

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Algorithm to randomize
void randomize(int arr[], int n) {
    srand(time(NULL)); // Defined in time.h
    int i;
    for(i = n-1; i > 0; i--) {
        int j = rand() % (i+1);
        swap(&arr[i], &arr[j]);
    }
}


int main()
{
    display_start_msg();

     char sub;
    main_menu:
     printf("LOGIN / SIGNIN: \n");
     printf(" Enter 'L' to Login. \n ");
     printf("Enter 'S' to Signup \n ");
     printf("Enter 'Q' to Exit Program \n ");
     putchar('>');
     sub = getchar();
     sub = toupper(sub); //Converts into uppercase if user enters lowercase character
     int key; //Serial key to locate the user in file


    switch(sub) //Switch case statement for navigation through options
    {
       case 'L':
       key = login(); //Log in function returns user's serial key to enter into the game
       break;

       case 'S':
       key = signup(); //Log in function returns user's serial key to enter into the game
       break;

       case 'Q':
       return 0; //Ends the program
       break;


       default:
       printf("error\n") ;
       goto main_menu; // Use of go to statement to take user to main menu
       break;

    }
    if (key ==100)
    {
    goto main_menu;
     }
    start(key); // Starts the actual quiz program.
    goto main_menu;// For showing the main menu after game is over
	return 0;
}
//Module for signup
int signup()
{
    system("cls");
    printf("\n--------SIGNUP---------\n\n");
    user u;
    FILE *fptr;
    fptr = fopen("userdata.txt","a+");
    int key = 0; // 
    while (!feof(fptr)) //for executing loop until end of file
    {
        //Displays Users already registered in the game.
        fread(&u,sizeof(user),1,fptr); // Fetching data into u from file
       printf(" %d  \t %s \t  %d \n",key, u.name, u.pin);
        key++; 
    }
    //printf("%d",key); // for checking key of the user

    printf("Enter User Name: 10 characters max, no spaces:");
    scanf("%s",u.name);
    printf("Enter Access Pin: 3-8 digits:");
    scanf("%d",&u.pin);

    u.phy.total = 0;
    u.phy.correct = 0;
    u.chem.total = 0;
    u.chem.correct = 0;
    u.maths.total = 0;
    u.maths.correct = 0;
// Application of block input output
    fwrite(&u,sizeof(user),1,fptr); // writes information of u into file pointed by fptr
    fclose(fptr);
    return key;
}
//Module for login
int login()
{
    system("cls");
    printf("\n--------LOGIN---------\n\n");
    user u; //Declaration of structure variable
    char name_taken[50];
    int pin_taken;
    FILE *fptr;
    fptr = fopen("userdata.txt","r");
    int key =0, tries=0;

    printf("Enter your user name:");
    scanf("%s",name_taken);
     while (!feof(fptr))
    {
        //Application of Block I/O
        fread(&u,sizeof(user),1,fptr); //fetches user's information from file into structure
        if(strcmp(u.name,name_taken)==0)
        {
            goto user_found; //Program is directed to ask pin of the user in 162
        }
        key++; // updates the user serial number
    }
    printf("User Name not found!!\n");
    fclose(fptr);
    return 100;
    
    user_found:
    printf("Enter access pin:");
    scanf("%d",&pin_taken);
    if(u.pin==pin_taken)
    {
        goto pin_matched;
    }
    printf("Incorrect pin!! \n");
    tries++;
    if ( tries<3)
    {
        goto user_found; // Program is again directed to user found for asking pin
    }
    else
    {
        fclose(fptr);
        return 100;
    }
    pin_matched:
    fclose(fptr);
    return key;
}

void start (int key)
{
    system("cls");
    display_start_msg();

    //extract user data
    user u;
    FILE *fptr;
    fptr = fopen("userdata.txt","r");
    fseek(fptr,key*sizeof(user),SEEK_SET);//SEEK_SET initializes pointer to 1st character, and user's key when multiplied with size of structure shifts the pointer to users data in file
    fread(&u,sizeof(user),1,fptr);
    fclose(fptr);
    printf("Hello %s, Welcome to the game. \n", u.name);

   //play options
    char sub;
    play_options:
    printf("\n ----------------------------\n");
    printf("\n Select your Choice \n");
    printf(" enter 'p' to start test \n ");
    printf("enter 's' to view score \n ");
    printf("enter 'r' to reset score \n ");
     printf("enter 'h' to get help \n ");
    printf("enter 'o' to logout \n ");
    putchar('>');
    sub = getchar();
    sub = toupper(sub);

    switch(sub) // using switch case to navigate
    {
       case 'P':
       test(key);
       break;

       case 'S':
       display_scores(key);
       break;

       case 'O':
       goto log_out;
       break;

       case 'R':
       update_score('!',99,key);
       printf("\nscore reset\n");
       display_scores(key);
       break;

       case 'H':
       display_help_msg();
       break;

       default:
       printf("error\n") ;
       goto play_options;
       break;
    }
    goto play_options;
    log_out:
    printf("Thanks for Playing \n");
  
}
void test(int key)
{
system("cls");
    printf(" \n----------TEST MODE-----------\n");

// Selection of subject
    char sub;
    char subject[20];
    select_sub:
    printf("Select  the Subject: \n");
    printf(" Enter 'P' for Physics \n ");
    printf(" Enter 'C' for Chemistry \n ");
    printf(" Enter 'M' for Mathematics \n ");
    putchar('>');
    sub = getchar();
    sub = tolower(sub);// using tolower function from ctype.h header file to lower the entered character
    switch(sub)
    {
       case 'p':
       strcpy(subject,"phy.txt");
       break;

       case 'c':
       strcpy(subject,"chm.txt");
       break;

       case 'm':
       strcpy(subject,"maths.txt");
       break;

       default:
       printf("Error! Enter a valid subject") ;
       goto select_sub;
       break;
    }
//Randomises order of Questions
    system("cls");
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    randomize (arr, 20);
    int correct = 0, j =0;
    int incorrect[10];
    char ans, ch;

//Asks first 10 questions in the file after suffling.[To get new qns for every game.]
    for(int i = 0; i<10; i++)
    {
       ch = display_questions(arr[i],i, subject); // correct ans is stored
       ans = getchar(); // Ans is asked from user
       ch = tolower(ch);
       // scanf("%c",&ans);
        if(ch == ans)
        {
            printf(" \n %c is correct!! \n\n",ch);
            correct++;
        }
        else
        {
            printf(" \n %c is wrong!! \n correct = %c \n\n",ans, ch);
            incorrect[j]=arr[i]; // To display later in review section
            j++;
        }
    }
    
//update score
update_score(sub,correct,key);
  
//display results
    system("cls");
    printf(" \n----------TEST OVER-----------\n");
    printf("\n\n Total questions Asked = 10 \n No of correct Questions = %d \n", correct);

//review mistakes
    char decision;
    review_mistakes:
    printf(" Do you want to review mistakes? (y/n):");
    decision = getchar();
    decision = tolower(decision);
    if( decision == 'y')
    {
        for ( int i =0; i < (10 - correct); i++)
        {
            review_questions(incorrect[i],i, subject);
        }
    }
    else if ( decision !='n' )
    {
        printf("Errror! Please press 'y' or 'n'. ");
        goto review_mistakes;
    }
}

void update_score( char sub, int correct, int key)
{
    user c;
    FILE *fptr;
    fptr = fopen("userdata.txt","r");
    int n =0;
    while (!feof(fptr))
    {
        fread(&c,sizeof(user),1,fptr); // To move pointer
        n++;
    }
    fseek(fptr,0,SEEK_SET); // To set the file pointer to begining
    user u[n]; // Array to store total no of users in file
    for (int i = 0; i < n; i++)
    {
        fread(&u[i],sizeof(user),n,fptr); // n signifies total no to data to be assigned to array variables
    }
    switch(sub)
    {
        //Only user's key is updated
       case 'p':
       u[key].phy.total +=10;
       u[key].phy.correct += correct;
       break;

       case 'c':
       u[key].chem.total +=10;
       u[key].chem.correct += correct;
       break;

       case 'm':
       u[key].maths.total +=10;
       u[key].maths.correct += correct;
       break;

       case '!':
        if (correct ==99)
        {
                u[key].phy.total = 0;
                u[key].phy.correct = 0;
                u[key].chem.total = 0;
                u[key].chem.correct = 0;
                u[key].maths.total = 0;
                u[key].maths.correct= 0;
        }
        break;
    }
    fclose(fptr);
    fptr = fopen("userdata.txt","w");
    fwrite(&u,sizeof(user),n,fptr);// file is overwritten with array of structure
    fclose(fptr);
}
//This module displays qn and returns correct option
char display_questions(int qn,int n, char subject[])
{
    FILE *fp;
    fp = fopen(subject,"r");
    char ch;
    ch = ' ';

// To move pointer to the desired qn
    for (int i = 0; i<qn; i++)
    {
        while (ch != '\n')
        {
            ch = fgetc(fp);
        }
          ch = ' ';
    }
    putchar('\n');

    // To skip 7)
    ch = fgetc(fp); 
    ch = fgetc(fp);
    
    printf("%d)",n+1);
    while ( ch != '!')
    {
        ch = fgetc(fp);
        if (ch == '.')
        {
          putchar('\n'); // Goes to new line when it detects.
          ch = fgetc(fp); // To move pointer through space
        }
        putchar(ch);
    }
    
    printf("\n Enter the option no. of the ans:");
    ch = fgetc(fp);
    fclose(fp);
    return ch;
}

void review_questions(int qn,int n, char subject[])
{
    FILE *fp;
    fp = fopen(subject,"r");
    char ch;
    ch = ' ';

    for (int i = 0; i<qn; i++)
    {
        while (ch != '\n')
        {
            ch = fgetc(fp);
        }
          ch = ' ';
    }
    putchar('\n');

    ch = fgetc(fp);
    ch = fgetc(fp);
    printf("%d)",n+1);
    while ( ch != '!')
    {
        ch = fgetc(fp);
        if (ch == '.')
        {
          putchar('\n'); // Goes to new line whenever it detects .
          ch = fgetc(fp);
        }
        putchar(ch);
    }
    ch = fgetc(fp);
    printf("\n correct = %c \n",ch);
    fclose(fp);
}

void display_scores(int key)
{
    system("cls");
    user u;
      //printf("\n %d \n",key);
      FILE *fptr;
      fptr = fopen("userdata.txt","r");
      fseek(fptr,key*sizeof(user),SEEK_SET);
      fread(&u,sizeof(user),1,fptr); 
      fclose(fptr);

      float accuracy;
      int total, correct;

      total = u.phy.total + u.chem.total + u.maths.total;
      correct = u.phy.correct + u.chem.correct + u.maths.correct;
      accuracy= (float)correct*pow(total, -1); // Use of power function from math.h header file.
      accuracy *=100;

      printf(" \n Name of the user: %s \n", u.name);

      printf("\n No of questions attempted for each subject: \n");
      printf(" Physics = %d \n Chemistry = %d \n Mathematics =%d \n",u.phy.total, u.chem.total, u.maths.total);

      printf("\nTotal number of questions attempted correctly for each subject: \n");
      printf(" Physics = %d \n Chemistry = %d \n Mathematics =%d \n",u.phy.correct, u.chem.correct,u.maths.correct);

      printf("\nTotal no of questions attepted= %d \n", total);

      printf("\nTotal no of questions attepted correctly = %d\n", correct);
      printf("Accuracy rate = %.2f %%\n", correct);

}