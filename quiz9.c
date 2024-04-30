#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
#include<ctype.h>
#include <time.h>

typedef struct score_points
{
    int all;
    int acc;
}score;
typedef struct user_account
{
    char name[10];
    int pin;
    score chm;
    score thm;
    score com;
}user;

void display_start_msg()
{
    system("cls");
             printf("\t\t\tC PROGRAM QUIZ GAME\n");
             printf("\n\t\t\t   WELCOME ");
             printf("\n\t\t\t      to ");
             printf("\n\t\t\t   THE GAME ");
             printf("\n\t\t\t IOE QUIZ GAME   ") ;
             printf("\n\t\t________________________________________\n\n");
}
void display_help_msg()
	{
	system("cls");
	helps:
    printf("\n\n                              HELP");
    printf("\n -------------------------------------------------------------------------");
    printf("\n ......................... C program Quiz Game...........");
    printf("\n   Input right answers otherwise you can't gain the points...........");
    printf("\n >> After you are asked questions you will have 4 options in your screen");

    printf("\nEnter correct option to win points");
    printf("\n >> 5 marks is alloted for each correct answer");
    printf("\n >> Tou will asked a totl of 20 questions");
    printf("\n >> No negative marking for wrong answers");
	printf("\n\n\t*********************BEST OF LUCK*********************************");
}

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
void randomize(int arr[], int n) {
    srand(time(NULL));
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
    join_options:
    printf("LOGIN / SIGNIN: \n");
    printf(" enter 'l' to login \n ");
    printf("enter 's' to signup \n ");
    printf("enter 'q' to exit program \n ");
    putchar('>');
    sub = getch();
    sub = toupper(sub);
    int key;

    switch(sub)
    {
       case 'L':
       key = login();
       break;

       case 'S':
       key = signup();
       break;

       case 'Q':
       return 0;
       break;


       default:
       printf("error\n") ;
       goto join_options;
       break;

    }
    if (key ==100)
    {
        goto join_options;
    }
    start(key);
    goto join_options;
	return 0;
}

int signup()
{
    system("cls");
    printf("\n--------SIGNUP---------\n\n");
    user u;
    FILE *fptr;
    fptr = fopen("userdata.txt","a+");
    int key =0;
    while (!feof(fptr))
    {
        fread(&u,sizeof(user),1,fptr);
       // printf(" %d  %s  %d \n",key, u.name, u.pin);
        key++;
    }
    //printf("%d",key);

    printf("enter user name: 10 characters max, no spaces:");
    scanf("%s",u.name);
    printf("enter access pin: 3-8 digits:");
    scanf("%d",&u.pin);

    u.chm.all = 0;
    u.chm.acc = 0;
    u.thm.all = 0;
    u.thm.acc = 0;
    u.com.all = 0;
    u.com.acc = 0;

    fwrite(&u,sizeof(user),1,fptr);
    fclose(fptr);
    return key;
}

int login()
{
    system("cls");
    printf("\n--------LOGIN---------\n\n");
    user u;
    char name_taken[20];
    int pin_taken;
    FILE *fptr;
    fptr = fopen("userdata.txt","r");
    int key =0, tries=0;

    printf("enter user name:");
    scanf("%s",name_taken);
     while (!feof(fptr))
    {
        fread(&u,sizeof(user),1,fptr);
        if(strcmp(u.name,name_taken)==0)
        {
            goto user_found;
        }
        key++;
    }
    printf("user name not found!!\n");
    fclose(fptr);
    return 100;
    
    user_found:
    printf("enter access pin:");
    scanf("%d",&pin_taken);
    if(u.pin==pin_taken)
    {
        goto pin_matched;
    }
    printf("incorrect pin!! \n");
    tries++;
    if ( tries<3)
    {
        goto user_found;
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
    fseek(fptr,key*sizeof(user),SEEK_SET);
    fread(&u,sizeof(user),1,fptr);
    fclose(fptr);
    printf("Hello %s \n", u.name);

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
    sub = getch();
    sub = toupper(sub);

    switch(sub)
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

// select subject
    char sub;
    char subject[20];
    select_sub:
    printf("select  the subject: \n");
    printf(" enter 'P' for computer \n ");
    printf("enter 'T' for thermodynamics \n ");
    printf("enter 'C' for chemistry \n ");
    putchar('>');
    sub = getch();
    sub = tolower(sub);
    switch(sub)
    {
       case 'p':
       strcpy(subject,"com.txt");
       break;

       case 'c':
       strcpy(subject,"chm.txt");
       break;

       case 't':
       strcpy(subject,"thm.txt");
       break;

       default:
       printf("error") ;
       goto select_sub;
       break;
    }


//randomise qn pattern
    system("cls");
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    randomize (arr, 20);
    int correct = 0, j =0;
    int incorrect[10];
    char ans, ch;

//start asking questions
    for(int i = 0; i<10; i++)
    {
       ch = display_questions(arr[i],i, subject);
       ans = getch();
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
            incorrect[j]=arr[i];
            j++;
        }
    }
    
//update score
update_score(sub,correct,key);
  
//display results
    system("cls");
    printf(" \n----------TEST OVER-----------\n");
    printf("\n\n total questions = 10 \n total correct = %d \n", correct);

//review mistakes
    char dec;
    review_mistakes:
    printf(" do you want to review mistakes? (y/n):");
    dec = getchar();
    dec = tolower(dec);
    if( dec == 'y')
    {
        for ( int i =0; i < (10 - correct); i++)
        {
            review_questions(incorrect[i],i, subject);
        }
    }
    else if ( dec !='n' )
    {
        printf("errror! press 'y' or 'n' ");
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
        fread(&c,sizeof(user),1,fptr);
        n++;
    }
    fseek(fptr,0,SEEK_SET);
    user u[n];
    for (int i = 0; i < n; i++)
    {
        fread(&u[i],sizeof(user),n,fptr);
    }
    switch(sub)
    {
       case 'p':
       u[key].com.all +=10;
       u[key].com.acc += correct;
       break;

       case 'c':
       u[key].chm.all +=10;
       u[key].chm.acc += correct;
       break;

       case 't':
       u[key].thm.all +=10;
       u[key].thm.acc += correct;
       break;

       case '!':
        if (correct ==99)
        {
                u[key].chm.all = 0;
                u[key].chm.acc = 0;
                u[key].thm.all = 0;
                u[key].thm.acc = 0;
                u[key].com.all = 0;
                u[key].com.acc = 0;
        }
        break;
    }
    fclose(fptr);
    fptr = fopen("userdata.txt","w");
    fwrite(&u,sizeof(user),n,fptr);
    fclose(fptr);
}

char display_questions(int qn,int n, char subject[])
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
          putchar('\n');
          ch = fgetc(fp);
        }
        putchar(ch);
    }
    
    printf("\n enter the option no of the ans:");
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
          putchar('\n');
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

      total = u.chm.all + u.thm.all + u.com.all;
      correct = u.chm.acc + u.thm.acc + u.com.acc;
      accuracy = correct*pow(total, -1);
      accuracy *=100;

      printf(" \n User: %s \n", u.name);
      printf("\n qn attempted per subject: \n");
      printf(" chm = %d \n thermo = %d \n computer =%d \n",u.chm.all, u.thm.all, u.com.all);
      printf("\ntotal correct: \n");
      printf(" chm = %d \n thermo = %d \n computer =%d \n",u.chm.acc, u.thm.acc, u.com.acc);
      printf("\ntotal attepted= %d \n", total);
      printf("total correct = %d\n", correct);
      printf("accurate rate = %.2f %%\n", accuracy);

}

