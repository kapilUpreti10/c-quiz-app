#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <unistd.h>
typedef struct user_account
{
  char name[20];
  int pin;

} user;

// declaration of function prototype
void welcome_screen();
int signup();
int login();
void start(int);
void test(int);
char display_questions(int, int);
void randomize(int arr[], int n);
void review_questions(int, int, char[]);
void display_help_msg();

char subject[20]; // defining global variables

// starting main function
int main()
{

join_options:
  welcome_screen();
  char option;

  printf("\t\t\t\t\tLOGIN / SIGNIN: \n");
  printf(" \n\t\t\t\t\tEnter 'L' to Login. \n ");
  printf("\t\t\t\t\tEnter 'S' to Signup \n ");
  printf("\t\t\t\t\tEnter 'Q' to Exit Program \n ");

  printf("\n\t\t\t\t\t..................................\n");
  printf("\n\t\t\t\t\t");
  putchar('>');
  option = getchar();
  option = toupper(option); // Converts into uppercase if user enters lowercase character
  int key;                  // Serial key to locate the user in file

  switch (option)
  {
  case 'L':
    key = login();
    break;

  case 'S':
    key = signup();
    break;

  case 'Q':
    return 0; // End the program

    break;

  default:
    system("cls");
    printf("Error! please Enter valid input:: \n");
    printf("................................ \n");

    goto join_options; // to take user to the join_options
    break;
  }
  if (key == 100)
  {
    goto join_options;
  }

  start(key);
  goto join_options;

  return 0;
}

void welcome_screen()
{

  system("cls");
  printf("\t\t\t    $$$$        $$     $$   $$$$$$$$$$   $$$$$$$$$$$$    \n");
  printf("\t\t\t $$      $$$    $$     $$       $$               $$      \n");
  printf("\t\t\t $$   $$  $$    $$     $$       $$             $$        \n");
  printf("\t\t\t    $$$  $$     $$     $$       $$          $$            \n");
  printf("\t\t\t          $$    $$$$$$$$$   $$$$$$$$$$   $$$$$$$$$$$$     \n");

  printf("\n\t\t\t\t ****************************************");
  printf("\n\t\t\t\t *    WELCOME TO THE QUIZ GAME CHALLENGE   *");
  printf("\n\t\t\t\t ******************************************\n\n");
  printf("\t\t\tUnleash Your Inner Genius: Embark on a Thrilling Quiz Adventure!\n");
  printf(" \t\t\t---------------------------------------------------------------\n\n");
}
// sign up function for user registration
int signup()
{
  system("cls");
  printf("\n--------SIGNUP---------\n\n");
  user u;
  FILE *fp;
  fp = fopen("userdata.txt", "a+");
  int key = 0;
  while (fread(&u, sizeof(user), 1, fp) == 1)
  {
    key++;
    printf(" %d  %s \n", key, u.name); // display existing user account
  }
  // printf("%d",key);

  printf("enter user name: 10 characters max, no spaces:");
  scanf("%s", u.name);
  printf("enter access pin: 3-8 digits:");
  scanf("%d", &u.pin);

  fwrite(&u, sizeof(user), 1, fp);
  fclose(fp);
  return key;
}

// login function for login to the program

int login()
{
loginpage:
  system("cls");
  printf("\n\n\t\t\t\t\t--------LOGIN---------\n\n");
  user u;

  char name_taken[20];
  int pin_taken;

  FILE *fp;
  fp = fopen("userdata.txt", "r");

  int key = 0, tries = 0;
username:
  printf("\t\t\t\t\tEnter user name:");
  scanf("%s", name_taken);
  printf("\n\t\t\t\t\t Searching");
  for (int i = 0; i < 5; i++)
  {

    printf(".");
    usleep(5000); // sleep for 500 miliseconds
  }
  while (!feof(fp))
  {
    fread(&u, sizeof(user), 1, fp);

    if (strcmp(u.name, name_taken) == 0)
    {
      printf("\n\n\t\t\t\t\t User name found!!!!\n\n");

      goto user_found;
    }
    key++;
  }
  printf("\n\n\t\t\t\t\tuser name not found!!\n");
  printf("\t\t\t\t\t");
  getch();

  fclose(fp);
  return 100;

user_found:
  printf("\n\n\t\t\t\t\tEnter access pin:");
  scanf("%d", &pin_taken);
  printf("\n\t\t\t\t\t Signing");
  for (int i = 0; i < 5; i++)
  {

    printf(".");
    usleep(10000); // sleep for 500 miliseconds
  }

  if (u.pin == pin_taken)
  {
    printf("\n \t\t\t\t\tPIN matched!!!! \n");
    printf("\n \t\t\t\t\tPress any key to continue.");
    getch();
    goto pin_matched;
  }

  printf("\n\t\t\t\t\t Incorrect pin!! \n");
  tries++;
  if (tries < 3)
  {
    printf(" \n \t\t\t\t\t  %d times remaining ......\n ", 3 - tries);
    goto user_found;
  }
  else
  {
    printf("\n\t\t\t\t \t You input wrong PIN multiple times.!!! \n\n \n");
    printf("\n\t\t\t\t\t  press any key to continue...");
    getch();
    fclose(fp);
    return 100;
  }

pin_matched:
  fclose(fp);

  return key;
}

// start function to choose the option
void start(int key)
{
  system("cls");
  welcome_screen();

  // Extract user data
  user u;
  FILE *fp;
  fp = fopen("userdata.txt", "r");
  if (fp == NULL)
  {
    printf("\n \t\t\t\t\tError opening file..\n");
    exit(1);
  }

  fseek(fp, key * sizeof(user), SEEK_SET);
  // fscanf(fp,"%s",u.name);
  fread(&u, sizeof(user), 1, fp);
  fclose(fp);

  printf("\n \t\t\t\t\tHello %s \n", u.name);
  // Choosing options of the game
  char option;
play_options:
  printf("\n \t\t\t\t\t----------------------------\n");
  printf("\n\n \t\t\t\t\t Select your Choice \n");
  printf("\n\t\t\t\t\t Enter '1' to start test \n ");
  printf("\t\t\t\t\t Enter '2' to get help \n ");
  printf("\t\t\t\t\t Enter '3' to logout \n ");
  printf("\n\t\t\t\t\t -------------------------------------------------\n");
  printf("\t\t\t\t\t ");
  putchar('>');
  scanf(" %d", &option);

  switch (option)
  {
  case 1:
    test(key);
    break;

  case 2:
    display_help_msg();
    goto play_options;
    break;

  case 3:
    goto logout;
    break;

  default:
    break;
  }

logout:
  printf("done\n");
  // printf("%d",key);
  // return 0;
}

// Function to start the test
void test(int key)
{
  system("cls");
  printf(" \n\n\t\t\t\t\t ----------TEST MODE-----------\n");

  int sub;

select_sub:
  printf("\n\t\t\t\t\t Select  the subject: \n");
  printf("\t\t\t\t\t Enter '1' for PHYSICS \n ");
  printf("\t\t\t\t\t Enter '2' for CHEMISTRY \n ");
  printf("\t\t\t\t\t Enter '3' for MATHEMATICS \n ");
  printf("\t\t\t\t\t _____________________________________________________________\n");
  printf("\n\t\t\t\t\t ");
  putchar('>');
  fflush(stdin);
  scanf("%d", &sub);

  switch (sub)
  {
  case 1:
    strcpy(subject, "phy.txt");
    break;

  case 2:
    strcpy(subject, "chem.txt");
    break;

  case 3:
    strcpy(subject, "math.txt");
    break;

  default:
    printf("\n\t\t\t\t\t Error!!! Please Enter valid input\n");
    goto select_sub;
    break;
  }

  // randomise qn pattern
  system("cls");
  // printf("line 310\n");
  int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  randomize(arr, 20);

  int correct = 0, j = 0;
  int incorrect[10];
  char ans, ch;

  //  printf("%s \n",subject);
  printf("\n\t\t\t\t\t Press any key to start the test.\n");
  getch();
  // start asking questions
  for (int i = 0; i < 10; i++)
  {
    if (i > 0)
    {
      printf("Press any key for next Questions");
      getch();
    }
    system("cls");
    printf("\n\n\n\n\n");
    ch = display_questions(arr[i], i);
    //  ans = getche();
    scanf(" %c", &ans);
    //  printf("%c",ans);
    //  getch();
    ch = tolower(ch);
    if (ch == ans)
    {
      printf(" \n\n\t\t\t\t\t  Bravo! Correct!! \n\n");
      correct++;
    }
    else
    {
      printf(" \n\t\t\t\t\t OPPS!! wrong answer!!  \n\n");
      incorrect[j] = arr[i];
      j++;
    }
    // if(i=9)
    // {
    //   printf("Press any key to review the test..\n\n\n");
    //   getch();
    // }
  }

  // display results
  system("cls");
  printf(" \n\t\t\t\t\t----------TEST OVER-----------\n");
  printf("\n\n\t\t\t\t\tTotal questions = 10 \n");
  printf("\t\t\t\t\tTotal Correct = %d \n", correct);

  // review mistakes
  char dec;
review_mistakes:
  printf(" \n\t\t\t\t\t Do you want to review mistakes? (y/n):");
  scanf(" %c", &dec);
  system("cls");
  // dec = getchar();
  dec = tolower(dec);
  if (dec == 'y')
  {
    for (int i = 0; i < (10 - correct); i++)
    {
      review_questions(incorrect[i], i, subject);
    }

    printf("\n\n\nPress any key to go into the HOME menu:\n\n\n");
    getch();
  }
  else if (dec != 'n')
  {
    printf("errror! press 'y' or 'n' ");

    goto review_mistakes;
  }
}

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}
void randomize(int arr[], int n)
{
  srand(time(NULL));
  int i;
  for (i = n - 1; i > 0; i--)
  {
    int j = rand() % (i + 1);
    swap(&arr[i], &arr[j]);
  }
}

char display_questions(int qn, int n)
{
  FILE *fp;

  fp = fopen(subject, "r");
  if (fp == NULL)
  {
    printf("Error opening file");
    printf("line no 371");
    return 1; // Return an error code to indicate the issue
  }
  char ch;
  ch = ' ';

  for (int i = 0; i < qn; i++)
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
  printf("%d)", n + 1);
  while (ch != '!')
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
void review_questions(int qn, int n, char subject[])
{
  FILE *fp;
  fp = fopen(subject, "r");
  char ch;
  ch = ' ';

  for (int i = 0; i < qn; i++)
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
  printf("%d)", n + 1);
  while (ch != '!')
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
  printf("\n correct = %c \n", ch);
  fclose(fp);
}
void display_help_msg()
{
  system("cls");
  // helps:
  printf("\n\n                         ******** HELP *********");
  printf("\n -------------------------------------------------------------------------");
  printf("\n ......................... IOE Entrance Quiz Game........................\n\n");
  printf("\n >>You will asked a total of 10 questions");
  printf("\n >>One Question will be Displayed at a Time");
  printf("\n >>After you are asked questions you will have 4 options in your screen");
  printf("\n >>Input right answers otherwise you can't gain the points...........");
  printf("\n >>You can check your Score at Last");
  printf("\n >>You can Review your mistakes if you want");

  printf("\n\n\t*********************BEST OF LUCK*********************************");
  printf("\n\n\n Press any key to move into the HOME \n");
  getch();
}