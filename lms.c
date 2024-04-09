#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

#define pwd 100
#define bookname 100
#define authorsize 100
#define bookISBN 100
#define stdname 100
#define stdid 9
#define totalbooks 100
#define totalstds 100
#define datesize 20

// struct for Books.txt
struct book
{
    char title[bookname];
    char author[authorsize];
    char ISBN[bookISBN];
    int yop;
    int total;
    int available;

} booksample, bookedit, bklist[totalbooks];

// struct for Students.txt
struct student
{
    char firstname[stdname];
    char lastname[stdname];
    char std_id[stdid];
    int borrowed;
    double fines;
    double finespaid;
    double finesowed;
} stdsample, stdedit, stdlist[totalstds];

// struct for Dates.txt
struct Date
{
    char std_id[stdid];
    char title[bookname];
    char ISBN[bookISBN];
    char borrowDate[datesize];
    char returnDate[datesize];
    char act_return[datesize];
} dateedit;

// file pointers
FILE *stdPtr;
FILE *bookPtr;
FILE *datePtr;
FILE *tempstdPtr;
FILE *tempbookPtr;
FILE *tempdatePtr;

// login and interface functions
void login();
void lib_ui();
void std_ui();
// function prototypes
// search and display functions
void searchbk();
void searchstd();
int comparebk(const void *str1, const void *str2);
int comparestds(const void *str1, const void *str2);
void displaybk();
void displaystd();
//----------------------------------------------------------
// date handling functions
int isValidDate(const char *date);
int compareDates(const char *date1, const char *date2);
void getInputDate(const char *prompt, char *date);
void getInputDate(const char *prompt, char *date);
//------------------------------------------------------------
// penalty handling functions
double calculatePenalty(const char *expectedReturnDate, const char *actualReturnDate);
void calcpenaltyonly();
void viewpenalty();
void applypenalty();
void paypenalty();
//----------------------------------------------------------
// book handling functions
void borrowbk();
void returnbk();
void brwrtnbk();
//---------------------------------------------------------
// generates monthly report
void monthlyreport();

// main function
int main()
{
    // clear screen
    system("cls");
    fflush(stdin);
    // main choice that branches to student or admin
    int mainchoice;
    while (1)
    {
        printf("\t====================\n");
        puts("\t|                  |");
        printf("\t|      WELCOME     |\n");
        printf("\t|        TO        |\n");
        printf("\t|      LIBRARY     |\n");
        printf("\t|     MANAGEMENT   |\n");
        printf("\t|      SYSTEM      |\n");
        puts("\t|                  |");
        printf("\t====================\n\n");
        puts("\t<Select your option>");
        printf("\t[1] Admin Login\n\t[2] Student\n\t[0] Exit\n\n\t>");
        scanf("%d", &mainchoice);

        switch (mainchoice)
        {
        case 1:
            login(); // admin login
            break;

        case 2:
            std_ui(); // student accessible interface
            break;

        case 0:
            printf("\tExiting program ...\n");
            exit(0);

        default:
            printf("\tEnter a valid input!\n");
            break;
        }
    }
}

//-----------------------------------------------------------------------------------------------------
// Login and interface functions
//  for admins only, students do not need to login
void login()
{
    system("cls");
    int tries = 3; // set the password tries limit
    printf("\t--------------------\n");
    printf("\t|       ADMIN      |\n");
    printf("\t|       LOGIN      |\n");
    printf("\t--------------------\n\n");

    // will loop until tries are up and exit to main menu
    while (tries != 0)
    {
        fflush(stdin);
        char password[pwd];
        // SET YOUR PASSWORD HERE!!!!!!!!
        char key[pwd] = {"Unm123"};
        int i = 0;
        char ch;
        printf("\tEnter the password.\n\t");
        // this whole function hides the password when it is typed with '*'
        while (1)
        {
            ch = getch();
            if (ch == 13 || ch == 9) // if action is ENTER (13) or TAB (9)
            {
                password[i] = '\0'; // sets a terminating characer
                break;
            }
            else if (ch == 8) // backspace
            {
                if (i > 0)
                {
                    i--;
                    printf("\b \b"); // for backspace
                }
            }
            else
            {
                password[i++] = ch;
                printf("*"); // hides the password
            }
        }

        // this segment compares if the password is valid
        if (strcmp(key, password) == 0)
        {
            printf("\n\tCorrect Password!\n\tLogging in...\n\n");
            // pauses the screen
            Sleep(500);
            // if password valid, will direct to librarian page
            lib_ui();
        }
        else
        {
            tries--;
            system("cls");
            printf("\n\n\tInvaild Password!\n\tYou have %d tries left.\n\n", tries);
            // when invalid password is entered 3 times, will return to main interface
            if (tries == 0)
            {
                puts("\tReturning to main screen...\n\n");
            }
        }
    }
}

// librarian or admin interface
void lib_ui()
{
    system("cls");
    // choice to choose function
    int lib_choice;
    while (1)
    {
        puts("\n\n\t-------------------------------");
        puts("\t  Welcome, Librarian!");
        puts("\n\t  What would you like to do?");
        puts("\t-------------------------------\n");

        printf("\t[1] Search Book\t\t\t[2] Display Books\n\t[3] Search Student\t\t[4] Display Students\n\t[5] Calculate Penalty\t\t[6] Apply Penalty\n\t[7] Pay penalty\t\t\t[8] Borrow/Return Book\n\t[9] Generate Monthly Report\t[1O] Back to main menu\t\n\t[0] Exit\n\n\t>");
        scanf("%d", &lib_choice); // gets choice
        switch (lib_choice)
        {
        case 1:
            searchbk(); // search book
            break;

        case 2:
            displaybk(); // display all books
            break;

        case 3:
            searchstd(); // search student
            break;

        case 4:
            displaystd(); // displays all students
            break;

        case 5:
            calcpenaltyonly(); // calculate penalty ONLY
            break;

        case 6:
            applypenalty(); // applies penalty to corresponding student
            break;

        case 7:
            paypenalty(); // helps student pay their penalty
            break;

        case 8:
            brwrtnbk(); // borrow or return book for students
            break;

        case 9:
            monthlyreport(); // generates monthly report
            break;

        case 10:
            main(); // goes back to main interface
            break;

        case 0:
            puts("\tThank you.\n\tExiting program...\n");
            exit(0); // exits the whole program
            break;

        default:
            puts("\tEnter a valid input!");
            break;
        }
    }
}

// student interface, no login required because functions are basic and do not edit file materials
void std_ui()
{
    system("cls");
    // student choice to choose function
    int std_choice;
    while (1)
    {
        puts("\n\n\t-------------------------------");
        puts("\t  Welcome, Student!");
        puts("\n\t  What would you like to do?");
        puts("\t-------------------------------\n");

        printf("\t[1] Search Book\t\t\t[2] Display Books\n\t[3] Calculate Penalty\t\t[4] View Penalty\n\t[5] Back to main menu\t\t[0] Exit\n\n\t>");
        scanf("%d", &std_choice);
        switch (std_choice)
        {
        case 1:
            searchbk(); // search book
            break;

        case 2:
            displaybk(); // display book
            break;

        case 3:
            calcpenaltyonly(); // calculate penalty ONLY
            break;

        case 4:
            viewpenalty(); // view student penalty based on their student ID and last name
            break;

        case 5:
            main();
            break;

        case 0:
            puts("\tThank you.\n\tExiting program...\n");
            exit(0);
            break;

        default:
            puts("\tEnter a valid input!");
            break;
        }
    }
}

//-------------------------------------------------------------------------------------------

// search and display functions start here
// book search
void searchbk()
{
    system("cls");
    fflush(stdin);
    int searchchoice; // to search by book title or ISBN
    int srchbreak = 1;
    int check = 1; // 1 for not found, 0 for found
    char bkname[bookname];
    bookPtr = fopen("Books.txt", "r");

    if (bookPtr == NULL)
    {
        printf("Not found.\n\n");
        exit(1);
    }

    printf("Search a book by entering the book title or ISBN:\n"); // to search by book title
    gets(bkname);

    // reads the book file
    while (fscanf(bookPtr, "%[^,],%[^,],%[^,],%d,%d,%d\n", booksample.title, booksample.author, booksample.ISBN, &booksample.yop, &booksample.total, &booksample.available) != EOF)
    {
        if (strcasecmp(booksample.title, bkname) == 0 || (strcasecmp(booksample.ISBN, bkname) == 0)) // if book title is found
        {
            // prints out book details
            puts("=================================================");
            printf("\tBook Info:\n");
            puts("-------------------------------------------------");
            printf("\nName: %s\n", booksample.title);
            printf("Author: %s\n", booksample.author);
            printf("ISBN: %s\n", booksample.ISBN);
            printf("Year published: %d\n", booksample.yop);
            printf("Total Copies: %d\n", booksample.total);
            printf("Available Copies: %d\n\n", booksample.available);
            puts("=================================================");
            check = 0; // tells function that book is found
        }
    }

    if (check == 1) // if book not found
    {
        puts("No record found!");
    }

    fclose(bookPtr);
    // redirects to user interface
    printf("Press any key to go back to main menu.\n");
    getch();
    system("cls");
}

// student search
void searchstd()
{
    system("cls");
    char idkey[stdid];
    int srchbreak = 1;
    int check = 1; // 1 for not found, 0 for found

    stdPtr = fopen("Students.txt", "r");

    printf("\nEnter the student ID.\n>");
    scanf("%s", &idkey); // gets student ID

    if (stdPtr == NULL)
    {
        printf("Not found.\n\n"); // file not found
        exit(1);
    }

    while (fscanf(stdPtr, "%[^,],%[^,],%[^,],%d,%lf,%lf,%lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                  &stdsample.borrowed, &stdsample.fines, &stdsample.finespaid, &stdsample.finesowed) != EOF)
    {
        if (strcmp(stdsample.std_id, idkey) == 0) // if student ID found
        {
            // prints out student details
            puts("\n=================================================");
            printf("\tStudent Info:\n");
            puts("-------------------------------------------------");
            printf("\nStudent ID: %s\n", stdsample.std_id);
            printf("First Name: %s\n", stdsample.firstname);
            printf("Last Name: %s\n\n", stdsample.lastname);
            printf("Books Borrowed: %d\n", stdsample.borrowed);
            printf("Total Fines: %.2lf\n", stdsample.fines);
            printf("Fines Paid: %.2lf\n", stdsample.finespaid);
            printf("Fines Owed: %.2lf\n\n", stdsample.finesowed);
            puts("=================================================");
            check = 0; // tells the function student is found
        }
    }

    if (check == 1)
    {
        puts("No record found!"); // no such student found
    }

    fclose(stdPtr);
    printf("Press any key to go back to main menu.\n");
    getch();
    system("cls");
}

// this compares the book titles for qsort in the displaybk function
int comparebk(const void *str1, const void *str2)
{
    char *title1 = ((struct book *)str1)->title;
    char *title2 = ((struct book *)str2)->title;

    // Make copies of the titles to preserve the original case
    char copy1[bookname], copy2[bookname];
    strcpy(copy1, title1);
    strcpy(copy2, title2);

    // Convert both copies to lowercase for sorting
    for (int i = 0; copy1[i]; i++)
        copy1[i] = tolower(copy1[i]);

    for (int i = 0; copy2[i]; i++)
        copy2[i] = tolower(copy2[i]);

    // Compare the modified copies for sorting
    return strcmp(copy1, copy2);
}

// this compares the student names for qsort in the displaystd function
int comparestds(const void *str1, const void *str2)
{
    char *name1 = ((struct student *)str1)->firstname;
    char *name2 = ((struct student *)str2)->firstname;

    // make copies of the titles to save the original case
    char copy1[stdname], copy2[stdname];
    strcpy(copy1, name1);
    strcpy(copy2, name2);

    // cnvert both copies to lowercase for sorting
    for (int i = 0; copy1[i]; i++)
        copy1[i] = tolower(copy1[i]);

    for (int i = 0; copy2[i]; i++)
        copy2[i] = tolower(copy2[i]);

    // cmpare the modified copies for sorting
    return strcmp(copy1, copy2);
}

// displays all books in alpahbetical order
void displaybk()
{
    system("cls");
    fflush(stdin);

    int bkcount = 0; // gets number of books

    bookPtr = fopen("Books.txt", "r");

    if (bookPtr == NULL)
    {
        printf("Not found.\n\n");
        exit(1);
    }

    // reads the books file
    while (fscanf(bookPtr, "%[^,],%[^,],%[^,],%d,%d,%d\n", bklist[bkcount].title, bklist[bkcount].author, bklist[bkcount].ISBN, &bklist[bkcount].yop, &bklist[bkcount].total, &bklist[bkcount].available) != EOF)
    {
        bkcount++; // each time a line is read, bookcount increases
    }
    fclose(bookPtr);

    // no books found !
    if (bkcount == 0)
    {
        puts("No books found.\n");
        printf("Press any key to go back to main menu.");
        getch();
        system("cls");
    }
    else
    {
        // quicksort the book titles according to alphabetical order
        qsort(bklist, bkcount, sizeof(struct book), comparebk);
        puts("===========================");
        printf("\tBook List\n");
        puts("===========================");

        // for loop that prints out the book details
        for (int i = 0; i < bkcount; i++)
        {
            puts("---------------------------");
            printf("Name: %s\n", bklist[i].title);
            printf("Author: %s\n", bklist[i].author);
            printf("ISBN: %s\n", bklist[i].ISBN);
            printf("Year published: %d\n", bklist[i].yop);
            printf("Total Copies: %d\n", bklist[i].total);
            printf("Available Copies: %d\n", bklist[i].available);
            puts("---------------------------\n\n");
        }
        printf("Press any key to go back to the main menu.\n");
        getch();
        system("cls");
    }
}

// displays all students in alphabetical order
void displaystd()
{
    system("cls");
    fflush(stdin);

    int stdcount = 0; // gets number of students

    stdPtr = fopen("Students.txt", "r");

    if (stdPtr == NULL)
    {
        printf("Not found.\n\n");
        exit(1);
    }

    // reads student files
    while (fscanf(stdPtr, "%[^,],%[^,],%[^,],%d,%lf,%lf,%lf\n", stdlist[stdcount].firstname, stdlist[stdcount].lastname, stdlist[stdcount].std_id,
                  &stdlist[stdcount].borrowed, &stdlist[stdcount].fines, &stdlist[stdcount].finespaid, &stdlist[stdcount].finesowed) != EOF)
    {
        stdcount++;
    }

    // no students found!
    if (stdcount == 0)
    {
        puts("No students found.\n");
        printf("Press any key to go back to main menu.");
        getch();
        system("cls");
    }
    else
    {
        // quicksort the student names according to alphabetical order
        qsort(stdlist, stdcount, sizeof(struct student), comparestds);
        puts("===========================");
        printf("\tStudent List\n");
        puts("===========================");

        // for loop that prints out the student details
        for (int i = 0; i < stdcount; i++)
        {
            puts("---------------------------");
            printf("Student ID: %s\n", stdlist[i].std_id);
            printf("First Name: %s\n", stdlist[i].firstname);
            printf("Last Name: %s\n", stdlist[i].lastname);
            printf("Books Borrowed: %d\n", stdlist[i].borrowed);
            printf("Total Fines: %.2lf\n", stdlist[i].fines);
            printf("Fines Paid: %.2lf\n", stdlist[i].finespaid);
            printf("Fines Owed: %.2lf\n", stdlist[i].finesowed);
            puts("---------------------------\n\n");
        }
        printf("Press any key to go back to the main menu.\n");
        getch();
        system("cls");
    }
}

//------------------------------------------------------------------

// date handling functions start here
// checks if date content and format is correct
int isValidDate(const char *date)
{
    // check if the date string has the correct length: '2023-11-23' must have length of 10
    if (strlen(date) != 10)
    {
        return 0; // invalid length
    }

    int year, month, day;
    // obtains year, month, and day from the date string
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3)
    {
        return 0; // invalid if date cannot be obtained (due to wrong date format)
    }

    // check for valid month and day values
    if (month < 1 || month > 12 || day < 1 || day > 31)
    {
        return 0; // invalid month or day
    }

    // checks for months with 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    {
        return 0; // invalid day for the given month
    }

    // checks for February days and leap years
    if (month == 2)
    {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            if (day > 29)
            {
                return 0; // invalid day for February in a leap year
            }
        }
        else
        {
            if (day > 28)
            {
                return 0; // invalid day for February in a normal year
            }
        }
    }

    return 1; // date is valid
}

/*
function to compare two dates and return:
 -1 -> if date1 is earlier than date2
  0 -> if date1 is equal to date2
  1 -> if date1 is later than date2
*/
int compareDates(const char *date1, const char *date2)
{
    int year1, month1, day1;
    int year2, month2, day2;

    // gets multiple values for date format YYYY-MM-DD
    sscanf(date1, "%d-%d-%d", &year1, &month1, &day1);
    sscanf(date2, "%d-%d-%d", &year2, &month2, &day2);

    if (year1 < year2 || (year1 == year2 && (month1 < month2 || (month1 == month2 && day1 < day2))))
    {
        return -1; // date1 is earlier than date2
    }
    else if (year1 == year2 && month1 == month2 && day1 == day2)
    {
        return 0; // date1 is equal to date2
    }
    else
    {
        return 1; // date1 is later than date2
    }
}

// function to calculate penalty for late return
// penalty rate: RM 1.00 per late day
double calculatePenalty(const char *expectedReturnDate, const char *actualReturnDate)
{
    int yearExpected, monthExpected, dayExpected;
    int yearActual, monthActual, dayActual;

    // gets multiple values for date format YYYY-MM-DD
    sscanf(expectedReturnDate, "%d-%d-%d", &yearExpected, &monthExpected, &dayExpected);
    sscanf(actualReturnDate, "%d-%d-%d", &yearActual, &monthActual, &dayActual);

    // calculate the difference in days
    int daysLate = 0;
    if (yearActual > yearExpected || (yearActual == yearExpected && (monthActual > monthExpected || (monthActual == monthExpected && dayActual > dayExpected))))
    {
        // calculate the penalty only if the return is late
        int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        //calculate penalty by adding days until loop breaks (when all conditions are not met)
        while (yearExpected < yearActual || monthExpected < monthActual || dayExpected < dayActual)
        {
            daysLate++;
            dayExpected++;

            if (dayExpected > daysInMonth[monthExpected])
            {
                dayExpected = 1;
                monthExpected++;

                if (monthExpected > 12)
                {
                    monthExpected = 1;
                    yearExpected++;
                }
            }
        }
    }

    // penalty rate: RM 1 per late day, so late days is equal to penalty rate
    return daysLate;
}

// prompts for user input for date
void getInputDate(const char *prompt, char *date)
{
    do
    {
        printf("%s (YYYY-MM-DD): ", prompt);
        fgets(date, 12, stdin);           // 10 from the date format, 1 from '\0' and 1 from '\n'
        date[strcspn(date, "\n")] = '\0'; // removes the newline character produced by fgets

        if (!isValidDate(date))
        {
            printf("\nInvalid date format.\nPlease enter the date in YYYY-MM-DD format.\n\n"); // if date entered is not valid, while keep prompting until correct format is entered
        }
    } while (!isValidDate(date));
}

// this function ONLY calculates the penalty for the users
void calcpenaltyonly()
{
    system("cls");
    fflush(stdin);
    char returnDate[datesize], realreturnDate[datesize];
    double penalty = 0.0;                                                // set default value
    getInputDate("Enter your return date.", returnDate);                 // asks for return date
    getInputDate("Enter your (estimated) return date.", realreturnDate); // asks for estimated return date

    // when <0, it is late return
    if (compareDates(returnDate, realreturnDate) < 0)
    {
        // calculates penalty for late return
        penalty = calculatePenalty(returnDate, realreturnDate);
        printf("\nPenalty calculated for late return: RM %.2lf\n\n", penalty);
        puts("===================================================================");
        puts("|\t\t\t<NOTE>\t\t\t\t\t  |\n|\tThis function only calculates and views penalty fees,\t  |\n| Only librarians can apply penalty fees through another function!|");
        puts("===================================================================\n");
    }
    else
    {
        // tells user no penalty charged for early return
        puts("\nNo penalty incurred. Book returned on time.\n\n");
        puts("===================================================================");
        puts("|\t\t\t<NOTE>\t\t\t\t\t  |\n|\tThis function only calculates and views penalty fees,\t  |\n| Only librarians can apply penalty fees through another function!|");
        puts("===================================================================\n");
    }

    printf("Enter any key to go back to main menu.\n");
    getch();
    system("cls");
}

// asks students for ID and last name to view their own penalty details
void viewpenalty()
{
    system("cls");
    fflush(stdin);

    char idkey[stdid];
    char lastnamekey[stdname];

    int stdstatus = 1; // 1 for not found, 0 for found

    stdPtr = fopen("Students.txt", "r");
    if (stdPtr == NULL)
    {
        printf("Error: Students.txt not found.\n");
        exit(1);
    }

    // gets student ID
    printf("Enter the Student ID number:\n");
    gets(idkey);
    fflush(stdin);

    while (fscanf(stdPtr, "%[^,],%[^,],%[^,],%d,%lf,%lf,%lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                  &stdsample.borrowed, &stdsample.fines, &stdsample.finespaid, &stdsample.finesowed) != EOF)
    {
        if (strcmp(stdsample.std_id, idkey) == 0) // if ID entered is found
        {
            stdstatus = 0;

            // asks for student last name
            printf("Enter your last name to confirm your identity:\n");
            gets(lastnamekey);

            if (strcasecmp(stdsample.lastname, lastnamekey) == 0) // last name should match with ID to see their own penalty details
            {
                puts("===========================================");
                printf("\tStudent Details:\n");
                puts("-------------------------------------------");
                printf("Name: %s %s\n", stdsample.firstname, stdsample.lastname);
                printf("Student ID: %s\n", stdsample.std_id);
                printf("Borrowed Books: %d\n", stdsample.borrowed);
                printf("Total Fines: RM %.2lf\n", stdsample.fines);
                printf("Fines Paid: RM %.2lf\n", stdsample.finespaid);
                printf("Fines Owed: RM %.2lf\n", stdsample.finesowed);
                puts("===========================================");
            }
            else
            {
                // details do not match
                printf("Details do not match. Exiting...\n");
                fclose(stdPtr);
                return;
            }
        }
    }

    fclose(stdPtr);

    // no student ID found
    if (stdstatus == 1)
    {
        printf("Student not found.\n");
    }

    printf("\nEnter any key to continue.\n");
    getch();
    system("cls");
}

// this function applies the penalty to a student if needed by the librarian
void applypenalty()
{
    system("cls");
    fflush(stdin);

    char idkey[stdid];
    double penaltyAmount;

    int stdstatus = 1;

    stdPtr = fopen("Students.txt", "r");
    tempstdPtr = fopen("stdtemp.txt", "w");

    if (stdPtr == NULL || tempstdPtr == NULL)
    {
        printf("Error: Unable to open files.\n");
        exit(1);
    }

    rewind(stdPtr); // reset pointer to beginning
    printf("Enter the Student ID number:\n");
    gets(idkey);
    fflush(stdin);

    while (fscanf(stdPtr, "%[^,],%[^,],%[^,],%d,%lf,%lf,%lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                  &stdsample.borrowed, &stdsample.fines, &stdsample.finespaid, &stdsample.finesowed) != EOF)
    {
        if (strcmp(stdsample.std_id, idkey) == 0) // student ID found
        {
            // tells function student exists
            stdstatus = 0;

            printf("Enter the penalty amount to apply:\n");

            // checks if input is a double
            if (scanf("%lf", &penaltyAmount) != 1)
            {
                printf("Invalid input. Penalty amount must be a valid number!\n");
                fclose(stdPtr);
                fclose(tempstdPtr);
                return;
            }

            // checks if the double is negative or zero
            if (penaltyAmount < 0)
            {
                printf("Invalid input. Penalty amount must be a non-negative number.\n");
                fclose(stdPtr);
                fclose(tempstdPtr);
                return;
            }

            // update fines and fines owed for the found student
            stdedit.fines = stdsample.fines + penaltyAmount;
            stdedit.finesowed = stdsample.finesowed + penaltyAmount;

            // prints out the updated details
            puts("===========================================");
            printf("\tUpdated Student Details:\n");
            puts("-------------------------------------------");
            printf("Name: %s %s\n", stdsample.firstname, stdsample.lastname);
            printf("Student ID: %s\n", stdsample.std_id);
            printf("Borrowed Books: %d\n", stdsample.borrowed);
            printf("Total Fines: RM %.2lf\n", stdedit.fines);
            printf("Fines Paid: RM %.2lf\n", stdsample.finespaid);
            printf("Fines Owed: RM %.2lf\n", stdedit.finesowed);
            puts("===========================================\n");
            fprintf(tempstdPtr, "%s,%s,%s,%d,%.2lf,%.2lf,%.2lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                    stdsample.borrowed, stdedit.fines, stdsample.finespaid, stdedit.finesowed);
        }
        else
        {
            // write the current student details to the temporary file
            fprintf(tempstdPtr, "%s,%s,%s,%d,%.2lf,%.2lf,%.2lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                    stdsample.borrowed, stdsample.fines, stdsample.finespaid, stdsample.finesowed);
        }
    }

    fclose(stdPtr);
    fclose(tempstdPtr);

    // if student not found
    if (stdstatus == 1)
    {
        printf("Student not found.\n");
        // clears the stdtemp file
        tempstdPtr = fopen("stdtemp.txt", "w");
        fclose(tempstdPtr);
    }
    else
    {
        // update original file with temporary file
        stdPtr = fopen("Students.txt", "w");
        tempstdPtr = fopen("stdtemp.txt", "r");

        while (fscanf(tempstdPtr, "%[^,],%[^,],%[^,],%d,%lf,%lf,%lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                      &stdsample.borrowed, &stdsample.fines, &stdsample.finespaid, &stdsample.finesowed) != EOF)
        {
            fprintf(stdPtr, "%s,%s,%s,%d,%.2lf,%.2lf,%.2lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                    stdsample.borrowed, stdsample.fines, stdsample.finespaid, stdsample.finesowed);
        }

        fclose(stdPtr);
        fclose(tempstdPtr);

        // wipe out stdtemp.txt
        tempstdPtr = fopen("stdtemp.txt", "w");
        fclose(tempstdPtr);

        printf("Penalty Applied Successfully!\n");
    }

    printf("\nEnter any key to continue.\n");
    getch();
    system("cls");
}

// this function pays penalty for students, operated by librarian
void paypenalty()
{
    system("cls");
    fflush(stdin);

    char idkey[stdid];
    double amountPaid;

    int stdstatus = 1;

    stdPtr = fopen("Students.txt", "r");
    if (stdPtr == NULL)
    {
        printf("Error: Students.txt not found.\n");
        exit(1);
    }
    tempstdPtr = fopen("stdtemp.txt", "w");
    if (tempstdPtr == NULL)
    {
        printf("Error: Unable to open temporary file.\n");
        exit(1);
    }

    rewind(stdPtr); // set file pointer to the beginning

    printf("Enter the Student ID number:\n");
    gets(idkey);
    fflush(stdin);

    while (fscanf(stdPtr, "%[^,],%[^,],%[^,],%d,%lf,%lf,%lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                  &stdsample.borrowed, &stdsample.fines, &stdsample.finespaid, &stdsample.finesowed) != EOF)
    {
        if (strcmp(stdsample.std_id, idkey) == 0) // Student ID found
        {
            stdstatus = 0; // tells function student exists
            printf("\nStudent found!\n");
            printf("Amount currently owed: RM %.2lf\n\n", stdsample.finesowed); // shows the current amount owed by student

            printf("Enter the amount to be paid:\n");

            // checks if the calue entered is of double type
            if (scanf("%lf", &amountPaid) != 1)
            {
                printf("Invalid input. Payment amount must be a valid number!\n");
                fclose(stdPtr);
                fclose(tempstdPtr);
                return;
            }

            // amount paid should be positive and not exceed the amount of fines owed
            if (amountPaid <= 0 || amountPaid > stdsample.finesowed)
            {
                printf("\nInvalid amount.\nPayment must not be negative or payment amount should not exceed fines owed.\n");
                fclose(stdPtr);
                fclose(tempstdPtr);
                return;
            }

            // update fines paid and fines owed
            stdedit.finespaid = stdsample.finespaid + amountPaid;
            stdedit.finesowed = stdsample.finesowed - amountPaid;

            // prints out the updated student detailsw
            puts("===========================================");
            printf("\tUpdated Student Details:\n");
            puts("-------------------------------------------");
            printf("Name: %s %s\n", stdsample.firstname, stdsample.lastname);
            printf("Student ID: %s\n", stdsample.std_id);
            printf("Borrowed Books: %d\n", stdsample.borrowed);
            printf("Total Fines: RM %.2lf\n", stdsample.fines);
            printf("Fines Paid: RM %.2lf\n", stdedit.finespaid);
            printf("Fines Owed: RM %.2lf\n", stdedit.finesowed);
            puts("===========================================\n");

            Sleep(300);
            printf("Payment recorded successfully!\n");

            // display updated information
            printf("\nAmount paid: RM %.2lf\n", amountPaid);
            printf("Remaining amount owed: RM %.2lf\n", stdedit.finesowed);

            // update temporary file
            fprintf(tempstdPtr, "%s,%s,%s,%d,%.2lf,%.2lf,%.2lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                    stdsample.borrowed, stdsample.fines, stdedit.finespaid, stdedit.finesowed);
        }
        else
        {
            // copy unchanged records to temporary file
            fprintf(tempstdPtr, "%s,%s,%s,%d,%.2lf,%.2lf,%.2lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                    stdsample.borrowed, stdsample.fines, stdsample.finespaid, stdsample.finesowed);
        }
    }

    fclose(stdPtr);
    fclose(tempstdPtr);

    fflush(stdin);

    // if student not found
    if (stdstatus == 1)
    {
        printf("Student not found.\n");
        // clears the stdtemp data
        tempstdPtr = fopen("stdtemp.txt", "w");
        fclose(tempstdPtr);
    }

    // update the original file with the temporary file if student found
    if (stdstatus == 0)
    {
        stdPtr = fopen("Students.txt", "w");
        fclose(stdPtr);

        stdPtr = fopen("Students.txt", "a");
        tempstdPtr = fopen("stdtemp.txt", "r");

        while (fscanf(tempstdPtr, "%[^,],%[^,],%[^,],%d,%lf,%lf,%lf\n", stdedit.firstname, stdedit.lastname, stdedit.std_id,
                      &stdedit.borrowed, &stdedit.fines, &stdedit.finespaid, &stdedit.finesowed) != EOF)
        {
            fprintf(stdPtr, "%s,%s,%s,%d,%.2lf,%.2lf,%.2lf\n", stdedit.firstname, stdedit.lastname, stdedit.std_id,
                    stdedit.borrowed, stdedit.fines, stdedit.finespaid, stdedit.finesowed);
        }

        fclose(stdPtr);
        fclose(tempstdPtr);

        // wipe out stdtemp data
        tempstdPtr = fopen("stdtemp.txt", "w");
        fclose(tempstdPtr);
    }

    printf("\nEnter any key to continue.\n");
    getch();
    system("cls");
}

//------------------------------------------------------------------------------------

// book handling functions start here
// borrow book
void borrowbk()
{
    system("cls");
    fflush(stdin);

    int bkstatus = 1;  // 0 if book found
    int stdstatus = 1; // 0 if student found
    char idkey[stdid];
    char bkname[bookname];
    char borrowDate[datesize], returnDate[datesize]; // borrow and return dates

    stdPtr = fopen("Students.txt", "r");
    if (stdPtr == NULL)
    {
        printf("Error: Students.txt not found.\n");
        exit(1);
    }

    bookPtr = fopen("Books.txt", "r");
    if (bookPtr == NULL)
    {
        printf("Error: Books.txt not found.\n");
        exit(1);
    }

    datePtr = fopen("Dates.txt", "r");
    if (datePtr == NULL)
    {
        printf("Error: Dates.txt not found.\n");
        exit(1);
    }

    tempstdPtr = fopen("stdtemp.txt", "a");
    tempbookPtr = fopen("booktemp.txt", "a");
    tempdatePtr = fopen("datetemp.txt", "a");

    if (tempstdPtr == NULL || tempbookPtr == NULL || tempdatePtr == NULL)
    {
        printf("Error: Unable to open temporary files.\n");
        exit(1);
    }

    printf("Enter the Student ID number:\n");
    gets(idkey);
    fflush(stdin);

    // Reset file pointers to the beginning
    rewind(stdPtr);
    rewind(bookPtr);
    rewind(datePtr);

    while (fscanf(stdPtr, " %[^,],%[^,],%[^,],%d,%lf,%lf,%lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                  &stdsample.borrowed, &stdsample.fines, &stdsample.finespaid, &stdsample.finesowed) != EOF)
    {
        if (strcmp(stdsample.std_id, idkey) == 0) // student found
        {
            stdstatus = 0;
            printf("Enter the name or ISBN of the book to be borrowed:\n");
            gets(bkname);
            fflush(stdin);

            while (fscanf(bookPtr, " %[^,],%[^,],%[^,],%d,%d,%d\n", booksample.title, booksample.author, booksample.ISBN, &booksample.yop, &booksample.total, &booksample.available) != EOF)
            {
                if (strcasecmp(booksample.title, bkname) == 0 || strcasecmp(booksample.ISBN, bkname) == 0) // book found
                {
                    bkstatus = 0;
                    printf("\nBook found!\n");
                    Sleep(300);

                    // Check if the student has already borrowed the same book
                    while (fscanf(datePtr, " %[^,],%[^,],%[^,],%[^,],%[^,],%s\n", dateedit.std_id, dateedit.title, dateedit.ISBN, dateedit.borrowDate, dateedit.returnDate, dateedit.act_return) != EOF)
                    {
                        // this condition only allows 1 student to borrow ONLY 1 copy of a book
                        if ((strcasecmp(dateedit.std_id, idkey) == 0) && ((strcasecmp(dateedit.title, bkname) == 0) || (strcasecmp(dateedit.ISBN, bkname) == 0)) && (strcasecmp(dateedit.act_return, "NULL") == 0))
                        {
                            printf("Error: This student has already borrowed this book.\nStudents can only borrow one copy of each book.\n");
                            fclose(stdPtr);
                            fclose(bookPtr);
                            fclose(datePtr);
                            fclose(tempstdPtr);
                            fclose(tempbookPtr);
                            fclose(tempdatePtr);
                            fflush(stdin);

                            // clears all temp files
                            tempbookPtr = fopen("booktemp.txt", "w");
                            fclose(tempbookPtr);
                            tempstdPtr = fopen("stdtemp.txt", "w");
                            fclose(tempstdPtr);
                            tempdatePtr = fopen("datetemp.txt", "w");
                            fclose(tempdatePtr);

                            printf("\nEnter any key to continue.\n");
                            getch();
                            system("cls");
                            return; // exit the function
                        }
                    }

                    // checks if the books are in stock
                    if (booksample.available > 0)
                    {
                        // gets borrow and return dates from the user
                        getInputDate("Enter borrow date", borrowDate);
                        struct tm tmBorrowDate = {0};
                        sscanf(borrowDate, "%d-%d-%d", &tmBorrowDate.tm_year, &tmBorrowDate.tm_mon, &tmBorrowDate.tm_mday);
                        tmBorrowDate.tm_year -= 1900;
                        tmBorrowDate.tm_mon -= 1;

                        // add 7 days to borrowDate
                        time_t borrowTime = mktime(&tmBorrowDate);
                        borrowTime += 7 * 24 * 60 * 60; // 7 days in seconds

                        // convert the result back to a formatted string
                        struct tm *tmReturnDate = localtime(&borrowTime);
                        strftime(returnDate, 20, "%Y-%m-%d", tmReturnDate);

                        // update dates.txt file, replace the real return date with 'NULL'
                        fprintf(tempdatePtr, "%s,%s,%s,%s,%s,NULL\n", stdsample.std_id, booksample.title, booksample.ISBN, borrowDate, returnDate);

                        // continue with book borrowing process
                        printf("Book Available!\n");
                        printf("Borrowing book...\n");
                        Sleep(300);
                        printf("Book borrowed successfully!\n");

                        // update book and student information
                        bookedit.available = booksample.available - 1;
                        stdedit.borrowed = stdsample.borrowed + 1;

                        // prints out updated book info
                        puts("------------------------------");
                        puts("\tUpdated Book Info:");
                        puts("------------------------------");
                        printf("\nName: %s\n", booksample.title);
                        printf("Author: %s\n", booksample.author);
                        printf("ISBN: %s\n", booksample.ISBN);
                        printf("Year published: %d\n", booksample.yop);
                        printf("Total Copies: %d\n", booksample.total);
                        printf("Available Copies: %d\n\n", bookedit.available);
                        printf("Borrowed by student: %s %s\n", stdsample.firstname, stdsample.lastname);
                        printf("Student ID: %s\n\n", stdsample.std_id);
                        puts("------------------------------");

                        // update temporary files
                        fprintf(tempbookPtr, "%s,%s,%s,%d,%d,%d\n", booksample.title, booksample.author, booksample.ISBN, booksample.yop, booksample.total, bookedit.available);
                        fprintf(tempstdPtr, "%s,%s,%s,%d,%.2lf,%.2lf,%.2lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                                stdedit.borrowed, stdsample.fines, stdsample.finespaid, stdsample.finesowed);
                    }
                    else
                    {
                        // tells the user that the book is not available
                        printf("Sorry, this book is out of stock.\n");
                        fprintf(tempbookPtr, "%s,%s,%s,%d,%d,%d\n", booksample.title, booksample.author, booksample.ISBN, booksample.yop, booksample.total, booksample.available);
                        fprintf(tempstdPtr, "%s,%s,%s,%d,%.2lf,%.2lf,%.2lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                                stdsample.borrowed, stdsample.fines, stdsample.finespaid, stdsample.finesowed);
                    }
                }
                else
                {
                    // copies unchanged data
                    fprintf(tempbookPtr, "%s,%s,%s,%d,%d,%d\n", booksample.title, booksample.author, booksample.ISBN, booksample.yop, booksample.total, booksample.available);
                }
            }
        }
        else
        {
            // copies unchanged data
            fprintf(tempstdPtr, "%s,%s,%s,%d,%.2lf,%.2lf,%.2lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                    stdsample.borrowed, stdsample.fines, stdsample.finespaid, stdsample.finesowed);
        }
    }

    fclose(bookPtr);
    fclose(stdPtr);
    fclose(tempbookPtr);
    fclose(tempstdPtr);
    fclose(datePtr);
    fclose(tempdatePtr);

    fflush(stdin);

    // if student not found
    if (stdstatus == 1)
    {
        printf("Student not found.\n");
        // clear all temp files
        tempbookPtr = fopen("booktemp.txt", "w");
        fclose(tempbookPtr);
        tempstdPtr = fopen("stdtemp.txt", "w");
        fclose(tempstdPtr);
        tempdatePtr = fopen("datetemp.txt", "w");
        fclose(tempdatePtr);
    }

    // student found but book not found
    if (bkstatus == 1 && stdstatus == 0)
    {
        printf("\nThis book is not found in the records.\n");
        // clear all temp files
        tempbookPtr = fopen("booktemp.txt", "w");
        fclose(tempbookPtr);
        tempstdPtr = fopen("stdtemp.txt", "w");
        fclose(tempstdPtr);
        tempdatePtr = fopen("datetemp.txt", "w");
        fclose(tempdatePtr);
    }

    // student and book found
    if (bkstatus == 0 && stdstatus == 0)
    {
        // update original files with temporary files
        bookPtr = fopen("Books.txt", "w");
        fclose(bookPtr);
        stdPtr = fopen("Students.txt", "w");
        fclose(stdPtr);

        bookPtr = fopen("Books.txt", "a");
        tempbookPtr = fopen("booktemp.txt", "r");

        // update Books.txt
        while (fscanf(tempbookPtr, " %[^,],%[^,],%[^,],%d,%d,%d\n", bookedit.title, bookedit.author, bookedit.ISBN, &bookedit.yop, &bookedit.total, &bookedit.available) != EOF)
        {
            fprintf(bookPtr, "%s,%s,%s,%d,%d,%d\n", bookedit.title, bookedit.author, bookedit.ISBN, bookedit.yop, bookedit.total, bookedit.available);
        }

        fclose(bookPtr);
        fclose(tempbookPtr);

        fflush(stdin);

        //--------------------------------------
        tempbookPtr = fopen("booktemp.txt", "w");
        fclose(tempbookPtr);

        stdPtr = fopen("Students.txt", "a");
        tempstdPtr = fopen("stdtemp.txt", "r");

        // update Students.txt
        while (fscanf(tempstdPtr, " %[^,],%[^,],%[^,],%d,%lf,%lf,%lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                      &stdsample.borrowed, &stdsample.fines, &stdsample.finespaid, &stdsample.finesowed) != EOF)
        {
            fprintf(stdPtr, "%s,%s,%s,%d,%.2lf,%.2lf,%.2lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                    stdsample.borrowed, stdsample.fines, stdsample.finespaid, stdsample.finesowed);
        }

        fclose(stdPtr);
        fclose(tempstdPtr);

        fflush(stdin);

        //-------------------------------------
        tempstdPtr = fopen("stdtemp.txt", "w");
        fclose(tempstdPtr);

        datePtr = fopen("Dates.txt", "a");
        tempdatePtr = fopen("datetemp.txt", "r");

        // update  Dates.txt
        while (fscanf(tempdatePtr, " %[^,],%[^,],%[^,],%[^,],%[^,],%s", dateedit.std_id, dateedit.title, dateedit.ISBN, dateedit.borrowDate, dateedit.returnDate, dateedit.act_return) != EOF)
        {
            fprintf(datePtr, "%s,%s,%s,%s,%s,%s\n", dateedit.std_id, dateedit.title, dateedit.ISBN, dateedit.borrowDate, dateedit.returnDate, dateedit.act_return);
        }

        fclose(datePtr);
        fclose(tempdatePtr);

        fflush(stdin);

        tempdatePtr = fopen("datetemp.txt", "w");
        fclose(tempdatePtr);
    }

    printf("\nEnter any key to continue.\n");
    getch();
    system("cls");
}

void returnbk()
{
    system("cls");
    fflush(stdin);

    char idkey[10];
    char bkname[50];
    char returnDate[20];

    int stdstatus = 1; // 0 if found
    int bkstatus = 1;  // 0 if found

    stdPtr = fopen("Students.txt", "r");
    if (stdPtr == NULL)
    {
        printf("Error: Students.txt not found.\n");
        exit(1);
    }

    bookPtr = fopen("Books.txt", "r");
    if (bookPtr == NULL)
    {
        printf("Error: Books.txt not found.\n");
        exit(1);
    }

    datePtr = fopen("Dates.txt", "r");
    if (datePtr == NULL)
    {
        printf("Error: Dates.txt not found.\n");
        exit(1);
    }

    tempstdPtr = fopen("stdtemp.txt", "a");
    tempbookPtr = fopen("booktemp.txt", "a");
    tempdatePtr = fopen("datetemp.txt", "a");

    if (tempstdPtr == NULL || tempbookPtr == NULL || tempdatePtr == NULL)
    {
        printf("Error: Unable to open temporary files.\n");
        exit(1);
    }

    printf("Enter the Student ID number:\n");
    gets(idkey);
    fflush(stdin);

    // reset the file pointers to the beginning
    rewind(stdPtr);
    rewind(bookPtr);
    rewind(datePtr);

    while (fscanf(stdPtr, "%[^,],%[^,],%[^,],%d,%lf,%lf,%lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                  &stdsample.borrowed, &stdsample.fines, &stdsample.finespaid, &stdsample.finesowed) != EOF)
    {
        if (strcmp(stdsample.std_id, idkey) == 0) // student found
        {
            stdstatus = 0;
            printf("Enter the name or ISBN of the book to be returned:\n");
            gets(bkname);
            fflush(stdin);

            while (fscanf(bookPtr, "%[^,],%[^,],%[^,],%d,%d,%d\n", booksample.title, booksample.author, booksample.ISBN, &booksample.yop, &booksample.total, &booksample.available) != EOF)
            {
                if (strcasecmp(booksample.title, bkname) == 0 || strcasecmp(booksample.ISBN, bkname) == 0) // book found
                {
                    printf("\nBook found!\n");
                    Sleep(300);

                    while (fscanf(datePtr, "%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", dateedit.std_id, dateedit.title, dateedit.ISBN, dateedit.borrowDate, dateedit.returnDate, dateedit.act_return) != EOF)
                    {
                        // this condition checks if the student has already borrowed the book and NOT YET returned it
                        if ((strcasecmp(dateedit.std_id, idkey) == 0) && ((strcasecmp(dateedit.title, bkname) == 0) || (strcasecmp(dateedit.ISBN, bkname) == 0)) && (strcasecmp(dateedit.act_return, "NULL") == 0))
                        {
                            bkstatus = 0;
                            printf("Details matched!\n\n");
                            Sleep(300);

                            // Get return date from the user
                            getInputDate("Enter return date", returnDate);

                            if (compareDates(dateedit.borrowDate, returnDate) > 0)
                            {
                                printf("Your dates are not in sequential order!");
                                return;
                            }

                            // calculate the penalty if return date is later than the supposed return date
                            double penalty = 0.0;
                            if (compareDates(dateedit.returnDate, returnDate) < 0)
                            {
                                // Calculate penalty for late return (assuming $1 per late day)
                                penalty = calculatePenalty(dateedit.returnDate, returnDate);
                                printf("Penalty for late return: RM %.2lf\n", penalty);
                            }

                            // update book and student information
                            bookedit.available = booksample.available + 1;
                            stdedit.borrowed = stdsample.borrowed - 1;
                            stdedit.fines = stdsample.fines + penalty;
                            stdedit.finesowed = stdedit.fines - stdsample.finespaid;
                            // print details
                            puts("------------------------------");
                            puts("\tUpdated Book Info:");
                            puts("------------------------------");
                            printf("\nName: %s\n", booksample.title);
                            printf("Author: %s\n", booksample.author);
                            printf("ISBN: %s\n", booksample.ISBN);
                            printf("Year published: %d\n", booksample.yop);
                            printf("Total Copies: %d\n", booksample.total);
                            printf("Available Copies: %d\n\n", bookedit.available);
                            printf("Returned by student: %s %s\n", stdsample.firstname, stdsample.lastname);
                            printf("Student ID: %s\n", stdsample.std_id);
                            printf("Penalty (if applicable): %.2lf\n\n", penalty);
                            puts("------------------------------");
                            // update temporary files
                            fprintf(tempbookPtr, "%s,%s,%s,%d,%d,%d\n", booksample.title, booksample.author, booksample.ISBN, booksample.yop, booksample.total, bookedit.available);
                            fprintf(tempstdPtr, "%s,%s,%s,%d,%.2lf,%.2lf,%.2lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                                    stdedit.borrowed, stdedit.fines, stdsample.finespaid, stdedit.finesowed);

                            fprintf(tempdatePtr, "%s,%s,%s,%s,%s,%s\n", dateedit.std_id, dateedit.title, dateedit.ISBN, dateedit.borrowDate, dateedit.returnDate, returnDate);

                            printf("Book returned successfully!\n");
                        }
                        else
                        {
                            // copies unchanged data
                            fprintf(tempdatePtr, "%s,%s,%s,%s,%s,%s\n", dateedit.std_id, dateedit.title, dateedit.ISBN, dateedit.borrowDate, dateedit.returnDate, dateedit.act_return);
                        }
                    }
                }
                else
                {
                    // copies unchanged data
                    fprintf(tempbookPtr, "%s,%s,%s,%d,%d,%d\n", booksample.title, booksample.author, booksample.ISBN, booksample.yop, booksample.total, booksample.available);
                }
            }
        }
        else
        {
            // copies unchanged data
            fprintf(tempstdPtr, "%s,%s,%s,%d,%.2lf,%.2lf,%.2lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                    stdsample.borrowed, stdsample.fines, stdsample.finespaid, stdsample.finesowed);
        }
    }

    fclose(bookPtr);
    fclose(stdPtr);
    fclose(tempbookPtr);
    fclose(tempstdPtr);
    fclose(datePtr);
    fclose(tempdatePtr);

    fflush(stdin);

    // student not found
    if (stdstatus == 1)
    {
        printf("Student not found.\n");
        tempbookPtr = fopen("booktemp.txt", "w");
        fclose(tempbookPtr);
        tempstdPtr = fopen("stdtemp.txt", "w");
        fclose(tempstdPtr);
        tempdatePtr = fopen("datetemp.txt", "w");
        fclose(tempdatePtr);
    }

    // student found, book not found
    if (bkstatus == 1 && stdstatus == 0)
    {
        printf("No matching book found for the given student ID.\n");
        tempbookPtr = fopen("booktemp.txt", "w");
        fclose(tempbookPtr);
        tempstdPtr = fopen("stdtemp.txt", "w");
        fclose(tempstdPtr);
        tempdatePtr = fopen("datetemp.txt", "w");
        fclose(tempdatePtr);
    }

    // student and book found, and borrowing conditions met
    // update original files with temporary files
    if (bkstatus == 0 && stdstatus == 0)
    {
        bookPtr = fopen("Books.txt", "w");
        fclose(bookPtr);
        stdPtr = fopen("Students.txt", "w");
        fclose(stdPtr);
        datePtr = fopen("Dates.txt", "w");
        fclose(datePtr);

        bookPtr = fopen("Books.txt", "a");
        tempbookPtr = fopen("booktemp.txt", "r");

        // update Books.txt
        while (fscanf(tempbookPtr, "%[^,],%[^,],%[^,],%d,%d,%d\n", bookedit.title, bookedit.author, bookedit.ISBN, &bookedit.yop, &bookedit.total, &bookedit.available) != EOF)
        {
            fprintf(bookPtr, "%s,%s,%s,%d,%d,%d\n", bookedit.title, bookedit.author, bookedit.ISBN, bookedit.yop, bookedit.total, bookedit.available);
        }

        fclose(bookPtr);
        fclose(tempbookPtr);

        tempbookPtr = fopen("booktemp.txt", "w");
        fclose(tempbookPtr);

        //---------------------------------------------

        stdPtr = fopen("Students.txt", "a");
        tempstdPtr = fopen("stdtemp.txt", "r");

        // update Students.txt
        while (fscanf(tempstdPtr, "%[^,],%[^,],%[^,],%d,%lf,%lf,%lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                      &stdsample.borrowed, &stdsample.fines, &stdsample.finespaid, &stdsample.finesowed) != EOF)
        {
            fprintf(stdPtr, "%s,%s,%s,%d,%.2lf,%.2lf,%.2lf\n", stdsample.firstname, stdsample.lastname, stdsample.std_id,
                    stdsample.borrowed, stdsample.fines, stdsample.finespaid, stdsample.finesowed);
        }

        fclose(stdPtr);
        fclose(tempstdPtr);

        tempstdPtr = fopen("stdtemp.txt", "w");
        fclose(tempstdPtr);

        //---------------------------------------------

        datePtr = fopen("Dates.txt", "a");
        tempdatePtr = fopen("datetemp.txt", "r");

        // update Dates.txt
        while (fscanf(tempdatePtr, "%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", dateedit.std_id, dateedit.title, dateedit.ISBN, dateedit.borrowDate, dateedit.returnDate, dateedit.act_return) != EOF)
        {
            fprintf(datePtr, "%s,%s,%s,%s,%s,%s\n", dateedit.std_id, dateedit.title, dateedit.ISBN, dateedit.borrowDate, dateedit.returnDate, dateedit.act_return);
        }

        fclose(datePtr);
        fclose(tempdatePtr);

        tempdatePtr = fopen("datetemp.txt", "w");
        fclose(tempdatePtr);
    }

    printf("\nEnter any key to continue.\n");
    getch();
    system("cls");
}

// this handles the borrow and return book functions in a switch
void brwrtnbk()
{
    system("cls");
    fflush(stdin);
    int brwrtn;
    printf("\n[1] Borrow Book\n[2] Return Book\n[0] Cancel\n\n>");
    scanf("%d", &brwrtn);

    switch (brwrtn)
    {
    case 1:
        borrowbk();
        break;

    case 2:
        returnbk();
        break;

    case 0:
        printf("\nEnter any key to continue.\n");
        getch();
        system("cls");
        break;

    default:
        printf("Enter a valid input!\n");
        system("cls");

        break;
    }
}

//--------------------------------------------------------------------------
// generates montly report
void monthlyreport()
{
    system("cls");
    fflush(stdin);
    // enumerate months as numbers
    enum months
    {
        January = 1,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December
    };

    // set array for months
    const char *months_str[] = {
        "January", "February", "March", "April", "May", "June", "July",
        "August", "September", "October", "November", "December", NULL};

    int monthNumber; // for enum months
    int year;
    int totalBooksBorrowed = 0;
    int totalBooksReturned = 0;
    int totalBooksToReturn = 0;
    double totalFinesCollected = 0;
    double finespending = 0;

    // open student file for reading
    stdPtr = fopen("students.txt", "r");
    if (stdPtr == NULL)
    {
        perror("Error opening students.txt");
        exit(1);
    }

    // open book file for reading
    bookPtr = fopen("books.txt", "r");
    if (bookPtr == NULL)
    {
        perror("Error opening books.txt");
        fclose(stdPtr);
        exit(1);
    }

    datePtr = fopen("Dates.txt", "r");
    if (datePtr == NULL)
    {
        perror("Error opening dates.txt");
        fclose(stdPtr);
        exit(1);
    }

    // loop through student records
    while (fscanf(stdPtr, "%[^,],%[^,],%[^,],%d,%lf,%lf,%lf\n",
                  stdsample.firstname, stdsample.lastname, stdsample.std_id,
                  &stdsample.borrowed, &stdsample.fines, &stdsample.finespaid, &stdsample.finesowed) == 7)
    {
        // update totalBooksBorrowed
        totalBooksBorrowed += stdsample.borrowed;
        totalFinesCollected += stdsample.finespaid;
        finespending += stdsample.finesowed;
    }

    while (fscanf(datePtr, "%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", dateedit.std_id, dateedit.title, dateedit.ISBN, dateedit.borrowDate, dateedit.returnDate, dateedit.act_return) != EOF)
    {
        if (strcmp(dateedit.act_return, "NULL") != 0)
        {
            totalBooksReturned++;
        }
    }

    // loop through book records
    fseek(bookPtr, 0, SEEK_SET);
    while (fscanf(bookPtr, "%[^,],%[^,],%[^,],%d,%d,%d\n",
                  booksample.title, booksample.author, booksample.ISBN, &booksample.yop,
                  &booksample.total, &booksample.available) != EOF)
    {
        // update totalBooksToReturn
        totalBooksToReturn += booksample.total - booksample.available;
    }

    // close files
    fclose(stdPtr);
    fclose(bookPtr);
    fclose(datePtr);
    // print the monthly report
    printf("Select the current month (1-12):\n\n[1] January\t[7] July\n[2] February\t[8] August\n[3] March\t[9]September\n[4] April\t[10] October\n[5] May\t\t[11] November\n[6] June\t[12] December\n\n>");

    // validates user input for month selection
    if (scanf("%d", &monthNumber) != 1 || monthNumber < January || monthNumber > December)
    {
        printf("\nInvalid month selection.\nReturning to main menu...\n");
        Sleep(500);
        system("cls");
        return;
    }

    // gets the month name based on the selected month number
    const char *selectedMonth = months_str[monthNumber - 1];

    // gets the year
    printf("Enter the current year:\n");
    // validates year input
    if (scanf("%4d", &year) != 1)
    {
        printf("\nInvalid year input.\nReturning to month selection...\n");
        Sleep(500);
        system("cls");
        return;
    }

    puts("Generating Montly report....\n\n");
    Sleep(500);
    system("cls");
    puts("\t\t========================================================");
    printf("\t\t\tMonthly Report for %s %d\n", selectedMonth, year);
    puts("\t\t--------------------------------------------------------");

    printf("\t\t\tTotal Books Borrowed: %d\n", totalBooksBorrowed);
    printf("\t\t\tTotal Books Returned: %d\n", totalBooksReturned);
    printf("\t\t\tTotal Books to be returned: %d\n", totalBooksToReturn);
    printf("\t\t\tTotal Fines Collected: %.2f\n", totalFinesCollected);
    printf("\t\t\tTotal Fines to be paid: %.2f\n", finespending);
    puts("\t\t========================================================");

    printf("\nEnter any key to continue.\n");
    getch();
    system("cls");
}
