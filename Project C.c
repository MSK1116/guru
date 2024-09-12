#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

// Structure declaration

struct teacher
{
    int id, salary;
    char name[100], sub[50];
} temp, tech[100];
// Functions declartaion
int menu(struct teacher tech[], struct teacher temp);
int input(struct teacher tech[], struct teacher temp);
int chk_id(struct teacher tech[], int, int);
void display(struct teacher tech[], struct teacher temp);
void save(struct teacher tech[], int);
void query(struct teacher tech[], struct teacher temp);
void reset(struct teacher tech[], struct teacher temp);
void report(struct teacher tech[], struct teacher temp);
int verify(struct teacher tech[], struct teacher temp, char[]);
void verify_mod();
int loading();

// main
void main()
{
    system("color f9");
    char pwd[50];
    printf("\nWelcome to Guru Prabandhan C Program...\n");
    printf("\nEnter 4-digit PIN to start or enter 1111 if your'e new ");

    scanf("%s", &pwd);
    verify(tech, temp, pwd);
}

// menu for the user
int menu(struct teacher tech[], struct teacher temp)
{
    loading();

    system("cls");
    system("color fa");
    int prg_no;
    printf("\nEnter program number to execute\n");
    printf("\nPress 1 to add teachers information");
    printf("\nPress 2 to display teachers information");
    printf("\nPress 3 to search for teachers by ID");
    printf("\nPress 4 to generate summary");
    printf("\nPress 5 to reset the database");
    printf("\nPress 6 to change the password");
    printf("\nPress 7 to exit\n");
    scanf("%d", &prg_no);

    switch (prg_no)
    {
    case 1:
        system("color f3");
        input(tech, temp);
        break;
    case 2:
        system("color f1");
        display(tech, temp);
        break;
    case 3:
        query(tech, temp);
        break;
    case 4:
        system("color f8");
        report(tech, temp);
        break;
    case 5:
        system("color f4");
        reset(tech, temp);
        break;
    case 6:
        system("color fc");
        printf("\nRequesting...");
        verify_mod();
        break;
    case 7:
        system("cls");
        system("color f6");
        printf("Thank you for using Guru Prabandhan. \nIf you have any query or suggestion feel free to reach me on contact@msmahato.com.np\n");
        exit(0);
        break;
    default:
        system("cls");
        printf("Enter the valid program\n");
        menu(tech, temp);
        break;
    }
}

// to take the information from user when password is correct
int input(struct teacher tech[], struct teacher temp)
{
    int n, i, prg_no, temp_id;
    printf("Enter the no of teachers \n");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\nEnter the details of teacher:%d", i + 1);
        printf("\nID :");
        scanf("%d", &temp_id);
        tech[i].id = chk_id(tech, temp_id, n);
        printf("\nname :");
        fflush(stdin);
        scanf("%[^\n]", &tech[i].name);
        printf("\nSalary :");
        scanf("%d", &tech[i].salary);
        printf("\nSubject :");
        fflush(stdin);
        scanf("%[^\n]", &tech[i].sub);
    }
    save(tech, n);
    menu(tech, temp);
}

// to save the entered information from structure to disk
void save(struct teacher tech[], int n)
{
    FILE *info;
    info = fopen("info.txt", "r+");
    int old_no_teacher, i;
    fscanf(info, "%d", &old_no_teacher);
    fseek(info, 0, SEEK_SET);
    fprintf(info, "%d\n", old_no_teacher + n);
    fclose(info);

    info = fopen("info.txt", "a");

    for (i = 0; i < n; i++)
    {
        fprintf(info, "%d %s\n%d %s\n", tech[i].id, tech[i].name, tech[i].salary, tech[i].sub);
    }

    fclose(info);
    printf("\n Information was saved");
}

// to display teacher information in proper table format
void display(struct teacher tech[], struct teacher temp)
{
    FILE *info;
    info = fopen("info.txt", "r");
    int id, salary, no_of_std, n = 0, i, j;
    char name[100], sub[50];
    system("cls");

    fscanf(info, "%d", &no_of_std);

    for (n = 0; n < no_of_std; n++)
    {
        fscanf(info, "%d %[^\n]\n%d %[^\n]\n", &tech[n].id, &tech[n].name, &tech[n].salary, &tech[n].sub);
    }
    for (i = 0; i < no_of_std; i++)
    {
        for (j = i + 1; j < no_of_std; j++)
        {
            if (tech[i].id > tech[j].id)
            {
                temp = tech[i];
                tech[i] = tech[j];
                tech[j] = temp;
            }
        }
    }
    if (no_of_std >= 1)
    {
        printf("Displaying the sorted list of teachers \n");
        printf("+------+------------------+-------------+-------------------+\n");
printf("| ID   | NAME             | SALARY      | SUBJECT           |\n");
printf("+------+------------------+-------------+-------------------+\n");

for (n = 0; n < no_of_std; n++) {
    printf("| %-4d | %-16s | %-11d | %-17s |\n", tech[n].id, tech[n].name, tech[n].salary, tech[n].sub);
    printf("+------+------------------+-------------+-------------------+\n");
}
    }
    else
    {
        printf("\n we couldn't find any data.");
    }

    fclose(info);
    printf("Enter any key to return home page \n");
    getch();
    menu(tech, temp);
}

// to serach for the teacher according to the teacher ID
void query(struct teacher tech[], struct teacher temp)
{
    int no_of_std, n, flag = 0, get_id;
    FILE *info;
    info = fopen("info.txt", "r");
    fscanf(info, "%d", &no_of_std);
    for (n = 0; n < no_of_std; n++)
    {
        fscanf(info, "%d %[^\n]\n%d %[^\n]\n", &tech[n].id, &tech[n].name, &tech[n].salary, &tech[n].sub);
    }
    printf("Enter the valid ID to search in directory\n");
    scanf("%d", &get_id);
    for (n = 0; n < no_of_std; n++)
    {
        if (tech[n].id == get_id)
        {
            printf("%d\t %s\t %d\t %s", tech[n].id, tech[n].name, tech[n].salary, tech[n].sub);
            printf("\n-----------------------------------------------------------\n");
            flag++;
        }
    }

    if (flag < 1)
    {
        printf("Couldn't find the teacher of ID: %d\n", get_id);
    }

    printf("\nEnter any key to return home page\n");
    getch();
    menu(tech, temp);
}


// to generate summary of all the informations saved in raw file
void report(struct teacher tech[], struct teacher temp)
{
    int n = 0, sum = 0, no_of_std, high_salary = 0, least_salary = 100000;

    FILE *info;
    info = fopen("info.txt", "r");
    fscanf(info, "%d", &no_of_std);
    FILE *summary;
    summary = fopen("summary.txt", "w");
    if (no_of_std >= 1)
    {
        for (n = 0; n < no_of_std; n++)
        {
            fscanf(info, "%d %[^\n]\n%d %[^\n]\n", &tech[n].id, &tech[n].name, &tech[n].salary, &tech[n].sub);
        }
        fclose(info);
        fprintf(summary, "Guru Prabandhan C\nSummary of data saved on disk\n");
        fprintf(summary, "Name of teacher & their subject\n");

        for (n = 0; n < no_of_std; n++)
        {
            sum = sum + tech[n].salary;
        }

        for (n = 0; n < no_of_std; n++)
        {

            if (tech[n].salary > high_salary)
            {
                high_salary = tech[n].salary;
            }

            if (tech[n].salary < least_salary)
            {
                least_salary = tech[n].salary;
            }
            fprintf(summary, "\n%d. %s(%s) Salary: %d", tech[n].id, tech[n].name, tech[n].sub, tech[n].salary);
            fprintf(summary, "\n----------------------------------");
        }
        fprintf(summary, "\nThe total expenditure on salary is %d\n Where highest paid salary is %d and least paid salary is %d", sum, high_salary, least_salary);
        fclose(summary);
        printf("The summary has been exported... Press any key to return home\n");
        getch();
        menu(tech, temp);
    }
    else
    {
        fprintf(summary, "%s", "No any data is saved in directory!");
        fclose(summary);
        printf("No any data is saved in directory!\n");
        printf(" Press any key to return home \n");
        getch();
        menu(tech, temp);
    }
}

// to reset the database
void reset(struct teacher tech[], struct teacher temp)
{
    FILE *a;
    a = fopen("info.txt", "w");
    fclose(a);
    system("cls");
    printf("The content of the file has been erased\nPress any key to return home");
    getch();
    menu(tech, temp);
}


// to check password & handle the security feature like resetting database for too many wrong attempt
int verify(struct teacher tech[], struct teacher temp, char pass[])
{
    int prg_no;
    char pwd[50];
    static int count = 0;
    char response;
    FILE *auth;
    auth = fopen("auth.sec", "r");
    fscanf(auth, "%s", &pwd);
    if (strcmp(pwd, pass) == 0)
    {
        system("color 09");
        menu(tech, temp);
    }
    else
    {
        system("color f4");
        printf("\nAuthentication failed!\nEnter correct password: ");
        fflush(stdin);
        scanf("%s", pass);
        count++;
        if (count > 3 && count < 5)
        {
            printf("Too many attempt were made (2 left), Do you want to reset databse?\n(CAUTION! All data created will be lost)\nPress any key to retry password or press Y to reset\n ");
            response = getch();
            if (tolower(response) == 'y')
            {
                FILE *b;
                b = fopen("auth.sec", "w");
                fprintf(b, "%s", "1111");
                fclose(b);
                reset(tech, temp);
            }
            else
            {
                verify(tech, temp, pass);
            }
        }
        if (count > 5)
        {
            printf("We couldn't log you in.. Sorry!");
            exit(0);
        }
        verify(tech, temp, pass);
    }
}

// function to change password
void verify_mod()
{
    int flag = 0, i;
    char old_pwd[50], new_pwd[50], temp[50];
    FILE *auth;
    auth = fopen("auth.sec", "r");
    fflush(stdin);
    fscanf(auth, "%s", temp);
    fclose(auth);
    printf("Enter your correct old 4-digit password\n");
    scanf("%s", old_pwd);
    if (strcmp(temp, old_pwd) != 0)
    {
        printf("Incorrect password \n");
        verify_mod();
    }
    else
    {
    re:
        flag = 0;
        printf("\nEnter new 4-digit password password \n");
        scanf("%s", new_pwd);
        for (i = 0; new_pwd[i] != '\0'; i++)
        {
            flag++;
        }
        printf("%d", flag);
        if (flag == 4)
        {

            FILE *auth;
            auth = fopen("auth.sec", "w");
            fprintf(auth, "%s", new_pwd);
            printf("\nYour password was changed");
            exit(0);
        }
        else
        {
            printf("\nnew password must be of 4 digit");
            goto re;
        }
    }
}
// to check for entered teacher's ID, Whether it is inputted previously or not (It check in both structure & file)
int chk_id(struct teacher tech[], int temp_id, int ar_size)
{
    struct teacher
    {
        int id, salary;
        char name[100], sub[50];
    } temp[100];
    int no_of_std, n, flag = 0;
    FILE *info;
    info = fopen("info.txt", "r");
    fscanf(info, "%d", &no_of_std);

    for (n = 0; n < ar_size; n++)
    {
        if (tech[n].id == temp_id)
        {
            flag++;
        }

    }

    for (n = 0; n < no_of_std; n++)
    {
        fscanf(info, "%d %[^\n]\n%d %[^\n]\n", &temp[n].id, &temp[n].name, &temp[n].salary, &temp[n].sub);
    }

    for (n = 0; n < no_of_std; n++)
    {
        if (temp[n].id == temp_id)
        {
            flag++;
        }
    }
    if (flag > 0)
    {
        printf("This ID has already been taken\n Enter new ID:");
        scanf("%d", &temp_id);
        chk_id(tech, temp_id, ar_size);
    }
    else
    {
        return temp_id;
    }



}

// Display loading screen while switching function.
int loading()
{
    char loading[10] = "Loading";
    int i;

    for (i = 0; loading[i] != '\0'; i++)
    {
        Sleep(300);
        printf("%c", loading[i]);
    }

    for (i = 0; i < 15; i++)
    {
        printf(".");
    }
    Sleep(900);
    for (i = 0; i < 10; i++)
    {

        printf("..");
    }
    return 0;
}

