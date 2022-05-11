/*
Main menu for the application:
1-admin
    1-creat new customer account
    2-open existing account
    3-return to main menu
2-user
    1-Make transaction
    2-change password
    3-Get cash
    4-Deposit in Account
    5-Return to main menu
bonus:
make admin account with username and pass
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#define Max_LINE 1024

// Decrlare functions : addCustomer
int addCustomer(char *, char *);

// Creat customer Struct
typedef struct customer
{
    char accountID[11];
    char password[7];
    int state;
    char name[50];
    char address[50];
    int age;
    char nationalID[15];
    char G_nationalID[15];
    long long Balance;
    struct customer *next;
} Customer;

// define a main function with two parameters[argc: represent the number of files transferred to main(), argv: represent the files name transferred to main()]
int main(int argc, char *argv[])
{
    int option;
    int option2;
    FILE *fp;
    char filename1[21] = "customer.dat";   // file name for customer data
    char filename2[21] = "recordInfo.txt"; // file name for record data
    // call the system time
    struct tm *timeinfo;
    time_t rawtime;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    if (argc > 1)
    {
        strcpy(filename1, argv[1]);
    }
    fp = fopen(filename1, "ab+"); // open the file in binary mode
    if (fp == NULL)               // if the file is not found
    {
        printf("File not found\n");
        exit(0);
    }
    if (fclose(fp) != 0) // if the file is not closed
    {
        printf("File not closed\n");
        exit(0);
    }

    fp = fopen(filename2, "a+"); // open the file in append mode
    if (fp == NULL)              // if the file is not found
    {
        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
        Sleep(2000);
        exit(0);
    }

    fseek(fp, 0L, SEEK_END); // move the file pointer to the end of the file
    if (ftell(fp) == 0)
        fprintf(fp, "Customer activity recordings!!!\n");

    if (fclose(fp) != 0) // if the file is not closed
    {
        printf("Error closing file!");
        exit(0);
    }
    while (1)
    {
        system("cls");
        printf("\t\t\tWelcome to the Bank System!!\n\nLocal time: %s\n\n", asctime(timeinfo));
        printf("\t\t\tMain Menu\n\n");
        printf("********************************************************************************\n");
        printf("1- Admin\n");
        printf("2- Client\n");
        printf("3- Exit\n");
        printf("********************************************************************************\n");
        while (scanf("%d", &option) != 1 || option < 1 || option > 3) /* Display menu and get user entry - check user entry validity*/
        {
            printf("Please enter again and make sure it is valid input\n");
            fflush(stdin);
        }
        switch (option)
        {
        case 1:
        {
            while (option2 != 3)
            {
                system("cls");
                printf("\t\t\tWelcome to bank system!!!\n\nLocal time is: %s \n", asctime(timeinfo)); /*show local time*/
                printf("Choose the mode!\n");
                printf("***********************************************************************\n");
                printf("1- Create a customer account!\n");
                printf("2- open existing account\n");
                printf("3- return to main menu\n");
                printf("***********************************************************************\n\n");
                while (scanf("%d", &option2) != 1 || option2 < 1 || option2 > 3) /* Display menu and get user entry - check user entry validity*/
                {
                    printf("Please enter again and make sure it is valid input\n");
                    fflush(stdin);
                }
                switch (option2)
                {
                case 1:
                    addCustomer(filename1, filename2);
                    break;
                case 2:
                    logCustomer(filename1, filename2);
                    break;
                }
            }
        }
        break;
        case 2:
            proc_client(filename1, filename2);
            break;
        case 3:
        {
            printf("\n\nThank you for using the bank system!!!\n\n");
            Sleep(1500);
            exit(0);
        }
        }
    }
}

int addCustomer(char *filename1, char *filename2)
{
    int k, i, p;
    Customer account, person;
    FILE *fp;
    struct tm *timeinfo;
    time_t rawtime;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    printf("Now you are creating a customer account, please input information as asked:\n\n");
    fflush(stdin);
    printf("Please enter your name: ");
    while (gets(person.name) == 0 || strlen(person.name) > 50)
    {
        printf("Please enter again and make sure it is valid name\n");
        printf("Please enter your name: ");
        fflush(stdin);
    }
    printf("Please enter your address: ");
    while (gets(person.address) == 0 || strlen(person.address) > 50)
    {
        printf("Please enter again and make sure it is valid address\n");
        printf("Please enter your address: ");
        fflush(stdin);
    }
    printf("Please enter your age: ");
    while (scanf("%d", &person.age) == 0 || person.age < 18 || person.age > 100)
    {
        printf("Please enter again and make sure it is valid age\n");
        printf("Please enter your age: ");
        fflush(stdin);
    }
    fflush(stdin);
    if (person.age < 21)
    {
        printf("Please enter your G-national ID: ");
        while (gets(person.G_nationalID) == 0 || strlen(person.G_nationalID) != 14)
        {
            printf("Please enter again and make sure it is valid G-national ID\n");
            printf("Please enter your G-national ID: ");
            fflush(stdin);
        }
    }

    else
    {
        fflush(stdin);
        printf("Please enter your national ID: ");
        while (gets(person.nationalID) == 0 || strlen(person.nationalID) != 14)
        {
            printf("Please enter again and make sure it is valid national ID\n");
            printf("Please enter your national ID: ");
            fflush(stdin);
        }
    }
    fflush(stdin);
    printf("Please enter your balance: ");
    while (scanf("%lld", &person.Balance) == 0 || person.Balance < 0)
    {
        printf("Please enter again and make sure it is valid balance\n");
        printf("Please enter your balance: ");
        fflush(stdin);
    }
    fflush(stdin);
    printf("Please enter your Password: ");
    while (gets(person.password) == 0 || strlen(person.password) > 6)
    {
        printf("Please enter again and make sure it is valid password\n");
        printf("Please enter your Password: ");
        fflush(stdin);
    }
    fp = fopen(filename1, "ab+");
    if (fp == NULL)
    {
        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
        Sleep(2000);
        exit(0);
    }

    srand(time(0)); /*crate a random card ID*/
    for (i = 0; i < 8; i++)
    {
        k = rand() % 10;
        sprintf(&person.accountID[i], "%d", k); /*change int number into char type*/
    }
    while (fread(&account, sizeof(Customer), 1, fp) == 1)
    {                                                         /*search through and check if the card ID is unique*/
        if (strcmp(account.accountID, person.accountID) != 0) /*continue searching if card ID dose not match*/
            continue;
        else /*recreate a new card ID if find a same one*/
        {
            fseek(fp, 0L, SEEK_SET);
            for (i = 0; i < 8; i++)
            {
                k = rand() % 10;
                sprintf(&person.accountID[i], "%d", k);
            }
        }
    }

    person.state = 0;
    person.next = NULL;
    fseek(fp, 0L, SEEK_END);                  /*find the end of file*/
    fwrite(&person, sizeof(Customer), 1, fp); /*refresh the information*/
    if (fclose(fp) != 0)                      /*close the file and check*/
    {
        printf("Error closing file!");
        exit(0);
    }

    fp = fopen(filename2, "a+");
    if (fp == NULL) /*Test the success of opening the file*/
    {
        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
        Sleep(2000);
        exit(0);
    }

    fseek(fp, 0L, SEEK_END);

    fprintf(fp, "%s: Account is biuld with Password %s in %s", person.accountID, person.password, asctime(timeinfo));
    if (fclose(fp) != 0)
    {
        printf("Error closing file!");
        exit(0);
    }

    printf("Card id is: %s\n", person.accountID);
    printf("Password is: %s\n", person.password);
    printf("\nSuccessfully Created Customer Account\n");
    getch();
    return 0;
}

int logCustomer(char *filename1, char *filename2)
{
    FILE *fp;

    time_t rawtime;
    struct tm *timeinfo;
    int i, option = 0, len, flag = 0, flag2 = 0, flag3 = 0;
    long long wMoney = 0, t_Money = 0;
    Customer account, selfAccount, transAccount, *current, *prev, *head, tempAccount;
    char search[9], pass[7], transId[12], searchId[12], buf[Max_LINE], state;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    printf("Please Enter Card Number: ");
    while (scanf("%s", search) == 0 || strlen(search) != 8) /*Test the entry of the persons name*/
    {
        printf("Please try again and make sure the card number are equal to 8-digit\n");
        printf("Please Enter Card Number: ");
        fflush(stdin);
    }
    printf("Please Enter Passsword: ");
    while (scanf("%s", pass) == 0 || strlen(pass) != 6) /*Test the entry of the persons name*/
    {
        printf("Please try again and make sure the password number are equal to 6-digit\n");
        printf("Please Enter Passsword: ");
        fflush(stdin);
    }
    fflush(stdin);
    fp = fopen(filename1, "rb+"); /*open the file in rb+ mode*/
    if (fp == NULL)               /*Test the success of opening the file*/
    {
        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
        Sleep(2000);
        exit(0);
    }
    fseek(fp, 0L, SEEK_SET);
    while (fread(&account, sizeof(Customer), 1, fp) == 1)
    { /*read until find same account or to the end of file*/
        if (strcmp(account.accountID, search) != 0)
        {
            continue;
        }
        else
        {
            flag = 1; /*No existing accounts*/
            break;
        }
    }
    if (flag == 1)
    {
        if (strcmp(account.password, pass) == 0)
        {
            printf("Log in successfully!\n");
            Sleep(1000);
            fp = fopen(filename2, "a+");
            if (fp == NULL) /*Test the success of opening the file*/
            {
                printf("\n\nThere was a problem opening the file, please restart the program\n\n");
                Sleep(2000);
                exit(0);
            }

            fseek(fp, 0L, SEEK_END); /*write activity recording to file4*/
            fprintf(fp, "%s: Account has log in at %s", account.accountID, asctime(timeinfo));
            if (fclose(fp) != 0)
            {
                printf("Error closing file!");
                exit(0);
            }

            while (option != 7)
            {
                fflush(stdin);
                option = 0;
                system("cls");
                printf("Activities you could choose:\n");
                printf("*************************************************************************\n");
                printf("1.Get Cash.\n");
                printf("2.Access to account information.\n");
                printf("3.Transfer money to others.\n");
                printf("4.Access to activities record.\n");
                printf("5.Deposit in Account.\n");
                printf("6.Change Stutus.\n");
                printf("7.Log out.\n");
                printf("*************************************************************************\n");
                while (scanf("%d", &option) != 1 && (option < 1 || option > 6)) /* Display menu and get user entry - check user entry validity*/
                {
                    printf("Invalid entry\n\n");
                    fflush(stdin);
                }
                switch (option)
                {
                case 1:
                {
                    printf("Please enter the Password again:\n\n\t");
                    while (scanf("%s", pass) == 0 || strlen(pass) != 6) /*Test the entry of the persons name*/
                    {
                        printf("Please try again and make sure the Password number are equal to 6-digit\n\n\t");
                        printf("Please enter the Password again:\n\n\t");
                        fflush(stdin);
                    }
                    if (strcmp(account.password, pass) != 0)
                    {
                        printf("Sorry! The Password you entered is wrong, try agian!!\n");
                        Sleep(2000);
                        break;
                    }
                    if (account.state != 0)
                    {
                        printf("Sorry, this account has been blocked!!!\nActivities are baned!\nPress any button to continue!\n");
                        getch();
                        return 0;
                    }
                    printf("\n\tYou have %lli $ left!\n\n", account.Balance);
                    printf("Please enter the amount you want to withdrwal!\n\n\t");
                    while (scanf("%lli", &wMoney) != 1 || wMoney > account.Balance || wMoney < 0)
                    { /*withdrawl money should be larger than 0 $*/
                        printf("Sorry, The Balance is not enough!!\n");
                        printf("Please enter the amount you want to withdrwal!\n\n\t");
                        fflush(stdin);
                    }

                    fp = fopen(filename1, "r+b");
                    if (fp == NULL) /*Test the success of opening the file*/
                    {
                        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
                        Sleep(2000);
                        exit(0);
                    }
                    fseek(fp, 0L, SEEK_SET);
                    while (fread(&selfAccount, sizeof(Customer), 1, fp) == 1)
                    { /*read until find same account or to the end of file*/
                        if (strcmp(selfAccount.accountID, search) != 0)
                        {
                            continue;
                        }
                        else
                        {
                            break;
                        }
                    }
                    account.Balance = account.Balance - wMoney;         /*refresh information in the temporary structure*/
                    selfAccount.Balance = selfAccount.Balance - wMoney; /*change the balance and next write it in the file*/
                    fseek(fp, -sizeof(Customer), SEEK_CUR);
                    fwrite(&selfAccount, sizeof(Customer), 1, fp); /*refresh the information*/
                    if (fclose(fp) != 0)
                    {
                        printf("Error closing file!");
                        exit(0);
                    }

                    fp = fopen(filename2, "a+");
                    if (fp == NULL) /*Test the success of opening the file*/
                    {
                        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
                        Sleep(2000);
                        exit(0);
                    }
                    fprintf(fp, "%s: Account withdrawled %lli at %s", selfAccount.accountID, wMoney, asctime(timeinfo));
                    if (fclose(fp) != 0)
                    {
                        printf("Error closing file!");
                        exit(0);
                    }
                    printf("Withdrawl successfully!!!\nYou have %lli $ left!\n", selfAccount.Balance);
                    Sleep(2000);
                    break;
                }
                case 2:
                {
                    printf("Please enter the Password again:\n\n\t");
                    while (scanf("%s", pass) == 0 || strlen(pass) != 6) /*Test the entry of the persons name*/
                    {
                        printf("Please try again and make sure the password number are equal to 6-digit");
                        printf("Please enter the Password again:\n");
                        fflush(stdin);
                    }
                    if (strcmp(account.password, pass) != 0)
                    {
                        printf("Sorry! The Password you entered is wrong, try agian!!\n\t");
                        Sleep(2000);
                        break;
                    }
                    if (account.age > 21)
                        if (account.state != 0)
                            printf("\nInformation is listed below:\nThe id of card: %s\nAccount name: %s\nAccount balance: %lli\nThe NationalID: %s\nThe address: %s\nStutus: %s", account.accountID, account.name, account.Balance, account.nationalID, account.address, "Blocked");
                        else
                            printf("\nInformation is listed below:\nThe id of card: %s\nAccount name: %s\nAccount balance: %lli\nThe NationalID: %s\nThe address: %s\nStutus: %s", account.accountID, account.name, account.Balance, account.nationalID, account.address, "Active");
                    else if (account.state != 0)
                        printf("\nInformation is listed below:\nThe id of card: %s\nAccount name: %s\nAccount balance: %lli\nThe G_NationalID: %s\nThe address: %s\nStutus: %s", account.accountID, account.name, account.Balance, account.G_nationalID, account.address, "Blocked");
                    else
                        printf("\nInformation is listed below:\nThe id of card: %s\nAccount name: %s\nAccount balance: %lli\nThe G_NationalID: %s\nThe address: %s\nStutus: %s", account.accountID, account.name, account.Balance, account.G_nationalID, account.address, "Active");
                    printf("\n\nPress any button to return last interface!\n");
                    getch();
                    break;
                }
                case 3:
                {
                    flag = 0;
                    printf("Please enter the Password again:\n");
                    while (scanf("%s", pass) == 0 || strlen(pass) != 6)
                    { /*Test the entry of the persons name*/
                        printf("Please try again and make sure the Possword number are equal to 6-digit\n");
                        printf("Please enter the Password again:\n");
                        fflush(stdin);
                    }
                    if (strcmp(account.password, pass) != 0)
                    {
                        printf("Sorry! The password you entered is wrong, account will log out!\n");
                        Sleep(2000);
                        break;
                    }
                    if (account.state != 0)
                    {
                        printf("Sorry, this account has been blocked!!!\nActivities are baned!\nPress any button to continue!\n");
                        getch();
                        return 0;
                    }
                    printf("You have %lli $ left!\n\n", account.Balance);

                    printf("Please enter the card id you want to transfer!!!\n\n\t");
                    while (scanf("%s", transId) != 1 || strlen(transId) != 8)
                    {
                        printf("Sorry, please check if you entered a 8-digit number !!\n");
                        Sleep(1000);
                        fflush(stdin);
                    }

                    fp = fopen(filename1, "r+b"); /*open the file in rb+ mode*/
                    if (fp == NULL)               /*Test the success of opening the file*/
                    {
                        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
                        Sleep(2000);
                        exit(0);
                    }
                    fseek(fp, 0L, SEEK_SET);
                    while (fread(&transAccount, sizeof(Customer), 1, fp) == 1)
                    { /*read until find same account or to the end of file*/
                        if (strcmp(transAccount.accountID, transId) != 0)
                        {
                            continue;
                        }
                        else
                        {
                            flag = 1; /*No existing accounts*/
                            break;
                        }
                    }
                    if (fclose(fp) != 0)
                    {
                        printf("Error closing file!");
                        exit(0);
                    }
                    if (flag == 0)
                    {
                        printf("Sorry, no such an account exists!!!Try again!\n");
                        break;
                    }

                    printf("Please enter the money you want to transer:\n\t\t");
                    while (scanf("%lli", &t_Money) != 1 || t_Money > account.Balance || t_Money < 0)
                    {
                        printf("Sorry,The Balance is not enough!!\n");
                        printf("Please enter the money you want to transer:\n");
                        fflush(stdin);
                    }

                    fp = fopen(filename1, "r+b");
                    if (fp == NULL) /*Test the success of opening the file*/
                    {
                        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
                        Sleep(2000);
                        exit(0);
                    }

                    fseek(fp, 0L, SEEK_SET);
                    while (fread(&selfAccount, sizeof(Customer), 1, fp) == 1)
                    { /*read until find same account or to the end of file*/
                        if (strcmp(selfAccount.accountID, account.accountID) != 0)
                        {
                            continue;
                        }
                        else
                        {
                            break;
                        }
                    }
                    account.Balance = account.Balance - t_Money; /*refresh information in the temporary structure*/
                    selfAccount.Balance = selfAccount.Balance - t_Money;

                    fseek(fp, -sizeof(Customer), SEEK_CUR);
                    fwrite(&selfAccount, sizeof(Customer), 1, fp); /*refresh the information*/

                    fseek(fp, 0L, SEEK_SET);
                    while (fread(&transAccount, sizeof(Customer), 1, fp) == 1)
                    { /*read until find same account or to the end of file*/
                        if (strcmp(transAccount.accountID, transId) != 0)
                        {
                            continue;
                        }
                        else
                        {
                            break;
                        }
                    }
                    transAccount.Balance = transAccount.Balance + t_Money;
                    fseek(fp, -sizeof(Customer), SEEK_CUR);
                    fwrite(&transAccount, sizeof(Customer), 1, fp); /*refresh the information*/

                    if (fclose(fp) != 0)
                    {
                        printf("Error closing file!");
                        exit(0);
                    }

                    fp = fopen(filename2, "a+");
                    if (fp == NULL) /*Test the success of opening the file*/
                    {
                        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
                        Sleep(2000);
                        exit(0);
                    }

                    fprintf(fp, "%s: Thansfer %lli $ to %s at %s", selfAccount.accountID, t_Money, transAccount.accountID, asctime(timeinfo));
                    fprintf(fp, "%s: Receive %lli $ from %s at %s", transAccount.accountID, t_Money, selfAccount.accountID, asctime(timeinfo));
                    if (fclose(fp) != 0)
                    {
                        printf("Error closing file!");
                        exit(0);
                    }
                    printf("Success to transfer the money %lli $, press any button to return!\n", t_Money);
                    getch();
                    break;
                }
                case 4:
                {
                    printf("Please enter the password again:\n\n\t");
					while (scanf("%s", pass) == 0 || strlen(pass) != 6) /*Test the entry of the persons name*/
					{
						printf("Please try again and make sure the pin number are equal to 6-digit");
						fflush(stdin);
					}
					if (strcmp(account.password, pass) != 0)
					{
						printf("Sorry! The pin you entered is wrong, account will log out!\n");
						Sleep(2000);
						break;
					}
					fp = fopen(filename2, "r");
					fseek(fp, 0L, SEEK_SET);

					for (i = 0; i < 9; i++)
						searchId[i] = 0;
					while (1)
					{
						flag3 = 0;
						if (fgets(searchId, 9, fp) && strcmp(searchId, account.accountID) == 0)
							flag3 = 1;
						fseek(fp, -8L, SEEK_CUR);
						fgets(buf, Max_LINE, fp);
						len = strlen(buf);
						if (len == 7)
							break;
						buf[len - 1] = '\0';
						if (flag3 == 1)
							printf("%s\n", buf);
					}

					if (fclose(fp) != 0)
					{
						printf("Error closing file!");
						exit(0);
					}
					printf("Press any button to continue!\n");
					getch();
					break;
                }
                case 5:
                {
                    printf("Please enter the Password again:\n\n\t");
                    while (scanf("%s", pass) == 0 || strlen(pass) != 6) /*Test the entry of the persons name*/
                    {
                        printf("Please try again and make sure the Password number are equal to 6-digit\n\n\t");
                        printf("Please enter the Password again:\n\n\t");
                        fflush(stdin);
                    }
                    if (strcmp(account.password, pass) != 0)
                    {
                        printf("Sorry! The Password you entered is wrong, try agian!!\n");
                        Sleep(2000);
                        break;
                    }
                    if (account.state != 0)
                    {
                        printf("Sorry, this account has been blocked!!!\nActivities are baned!\nPress any button to continue!\n");
                        getch();
                        return 0;
                    }
                    printf("\n\tYou have %lli $ left!\n\n", account.Balance);
                    printf("Please enter the amount you want to Deposit!\n");
                    while (scanf("%lli", &wMoney) != 1 || wMoney > account.Balance || wMoney < 0)
                    { /*withdrawl money should be larger than 0 $*/
                        printf("Sorry, The Balance is not enough!!\n");
                        printf("Please enter the amount you want to Deposit!\n");
                        fflush(stdin);
                    }

                    fp = fopen(filename1, "r+b");
                    if (fp == NULL) /*Test the success of opening the file*/
                    {
                        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
                        Sleep(2000);
                        exit(0);
                    }
                    fseek(fp, 0L, SEEK_SET);
                    while (fread(&selfAccount, sizeof(Customer), 1, fp) == 1)
                    { /*read until find same account or to the end of file*/
                        if (strcmp(selfAccount.accountID, search) != 0)
                        {
                            continue;
                        }
                        else
                        {
                            break;
                        }
                    }
                    account.Balance = account.Balance + wMoney;         /*refresh information in the temporary structure*/
                    selfAccount.Balance = selfAccount.Balance + wMoney; /*change the balance and next write it in the file*/
                    fseek(fp, -sizeof(Customer), SEEK_CUR);
                    fwrite(&selfAccount, sizeof(Customer), 1, fp); /*refresh the information*/
                    if (fclose(fp) != 0)
                    {
                        printf("Error closing file!");
                        exit(0);
                    }

                    fp = fopen(filename2, "a+");
                    if (fp == NULL) /*Test the success of opening the file*/
                    {
                        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
                        Sleep(2000);
                        exit(0);
                    }
                    fprintf(fp, "%s: Account Deposit %lli at %s", selfAccount.accountID, wMoney, asctime(timeinfo));
                    if (fclose(fp) != 0)
                    {
                        printf("Error closing file!");
                        exit(0);
                    }
                    printf("Deposit successfully!!!\nYou have %lli $ left!\n", selfAccount.Balance);
                    Sleep(2000);
                    break;
                }
                case 6:
                {
                    if ((fp = fopen(filename1, "rb")) == NULL)
                    {
                        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
                        Sleep(2000);
                        return 0;
                    }
                    fseek(fp, 0, SEEK_END);
                    if (ftell(fp) == 0)
                    {
                        printf("Empty file!! \n");
                        Sleep(2000);
                        return 0;
                    }
                    fseek(fp, 0, SEEK_SET);

                    prev = (Customer *)malloc(sizeof(Customer));
                    head = prev;
                    while (feof(fp) == 0)
                    {
                        current = (Customer *)malloc(sizeof(Customer));
                        if (head == NULL)
                            head = current;
                        else
                        {
                            prev->next = current;
                        }
                        current->next = NULL;
                        fread(current, sizeof(Customer), 1, fp);
                        prev = current;
                    }
                    if (fclose(fp) != 0)
                    {
                        printf("Error closing file!");
                        exit(0);
                    }

                    flag = 0;
                    printf("Please enter the 8-digit card id you want to access:\n\t\t");
                    while (scanf("%s", search) == 0 || strlen(search) != 8)
                    {
                        printf("Please try again and make sure the card number are equal to 8-digit\n");
                        fflush(stdin);
                    }

                    current = head->next;
                    while (current != NULL)
                    {
                        if (strcmp(current->accountID, search) == 0)
                        {
                            flag = 1;
                            break;
                        }
                        current = current->next;
                    }

                    if (flag == 1)
                    {
                        if (current->state == 0)
                            printf("The state of this account is active, press 'B' to block this account!\nPress 'R' to return\n");
                        else
                            printf("The state of this account is blocked, press 'U' to unblock this account! Press 'R' to return\n");

                        fflush(stdin);
                        while (scanf("%c", &state) != 1 || (state != 'B' && state != 'U' && state != 'R'))
                        {
                            fflush(stdin);
                            printf("Invalid entry, try agian!\n");
                        }
                        if (state == 'B')
                            current->state = 1;
                        else if (state == 'U')
                            current->state = 0;
                        else
                            break;

                        if (current->state == 1)
                            printf("This account has been blocked successfully!!\n");
                        else if (current->state == 0)
                            printf("This account has been unblocked successfully!!\n");

                        fp = fopen(filename1, "rb+");
                        fseek(fp, 0L, SEEK_SET);
                        while (fread(&tempAccount, sizeof(Customer), 1, fp) == 1)
                        { /*read until find same account or to the end of file*/
                            if (strcmp(tempAccount.accountID, search) != 0)
                            {
                                continue;
                            }
                            else
                            {
                                break;
                            }
                        }
                        fseek(fp, -sizeof(Customer), SEEK_CUR);
                        fwrite(current, sizeof(Customer), 1, fp);

                        if (fclose(fp) != 0)
                        {
                            printf("Error closing file!");
                            exit(0);
                        } /*close the file*/

                        fp = fopen(filename2, "a");
                        if (fp == NULL) /*Test the success of opening the file*/
                        {
                            printf("\n\nThere was a problem opening the file, please restart the program\n\n");
                            Sleep(2000);
                            exit(0);
                        }
                        if (current->state != 0)
                            fprintf(fp, "%s: This account is blocked in %s", current->accountID, asctime(timeinfo));
                        if (current->state == 0)
                            fprintf(fp, "%s: This account is unblocked in %s", current->accountID, asctime(timeinfo));
                        if (fclose(fp) != 0)
                        {
                            printf("Error closing file!");
                            exit(0);
                        } /*close the file*/
                    }
                    printf("Press any button to return\n");
                    getch();
                    break;
                }
                }
            }
        }
    }
    return 0;
}

int proc_client(char *filename1, char *filename2)
{
    FILE *fp;

    time_t rawtime;
    struct tm *timeinfo;
    int i, option = 0, len, flag = 0, flag2 = 0, flag3 = 0;
    long long wMoney = 0, t_Money = 0;
    Customer account, selfAccount, transAccount;
    char search[9], pass[7], changePin1[7], changePin2[7], transId[12], searchId[12], buf[Max_LINE], state;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    printf("Please Enter Card Number: ");
    while (scanf("%s", search) == 0 || strlen(search) != 8) /*Test the entry of the persons name*/
    {
        printf("Please try again and make sure the card number are equal to 8-digit\n");
        printf("Please Enter Card Number: ");
        fflush(stdin);
    }
    printf("Please Enter Passsword: ");
    while (scanf("%s", pass) == 0 || strlen(pass) != 6) /*Test the entry of the persons name*/
    {
        printf("Please try again and make sure the password number are equal to 6-digit\n");
        printf("Please Enter Passsword: ");
        fflush(stdin);
    }
    fflush(stdin);
    fp = fopen(filename1, "rb+"); /*open the file in rb+ mode*/
    if (fp == NULL)               /*Test the success of opening the file*/
    {
        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
        Sleep(2000);
        exit(0);
    }
    fseek(fp, 0L, SEEK_SET);
    while (fread(&account, sizeof(Customer), 1, fp) == 1)
    { /*read until find same account or to the end of file*/
        if (strcmp(account.accountID, search) != 0)
        {
            continue;
        }
        else
        {
            flag = 1; /*No existing accounts*/
            break;
        }
    }
    if (flag == 1)
    {
        if (strcmp(account.password, pass) == 0)
        {
            printf("Log in successfully!\n");
            Sleep(1000);
            fp = fopen(filename2, "a+");
            if (fp == NULL) /*Test the success of opening the file*/
            {
                printf("\n\nThere was a problem opening the file, please restart the program\n\n");
                Sleep(2000);
                exit(0);
            }

            fseek(fp, 0L, SEEK_END); /*write activity recording to file4*/
            fprintf(fp, "%s: Account has log in at %s", account.accountID, asctime(timeinfo));
            if (fclose(fp) != 0)
            {
                printf("Error closing file!");
                exit(0);
            }

            while (option != 5)
            {
                fflush(stdin);
                option = 0;
                system("cls");
                printf("Activities you could choose:\n");
                printf("*************************************************************************\n");
                printf("1.Get Cash.\n");
                printf("2.Transfer money to others.\n");
                printf("3.Deposit in Account.\n");
                printf("4.Change Password.\n");
                printf("5.Log out.\n");
                printf("*************************************************************************\n");
                while (scanf("%d", &option) != 1 && (option < 1 || option > 6)) /* Display menu and get user entry - check user entry validity*/
                {
                    printf("Invalid entry\n\n");
                    fflush(stdin);
                }
                switch (option)
                {
                case 1:
                {
                    printf("Please enter the Password again:\n\n\t");
                    while (scanf("%s", pass) == 0 || strlen(pass) != 6) /*Test the entry of the persons name*/
                    {
                        printf("Please try again and make sure the Password number are equal to 6-digit\n\n\t");
                        printf("Please enter the Password again:\n\n\t");
                        fflush(stdin);
                    }
                    if (strcmp(account.password, pass) != 0)
                    {
                        printf("Sorry! The Password you entered is wrong, try agian!!\n");
                        Sleep(2000);
                        break;
                    }
                    if (account.state != 0)
                    {
                        printf("Sorry, this account has been blocked!!!\nActivities are baned!\nPress any button to continue!\n");
                        getch();
                        return 0;
                    }
                    printf("\n\tYou have %lli $ left!\n\n", account.Balance);
                    printf("Please enter the amount you want to withdrwal!\n\n\t");
                    while (scanf("%lli", &wMoney) != 1 || wMoney > account.Balance || wMoney < 0)
                    { /*withdrawl money should be larger than 0 $*/
                        printf("Sorry, The Balance is not enough!!\n");
                        printf("Please enter the amount you want to withdrwal!\n\n\t");
                        fflush(stdin);
                    }

                    fp = fopen(filename1, "r+b");
                    if (fp == NULL) /*Test the success of opening the file*/
                    {
                        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
                        Sleep(2000);
                        exit(0);
                    }
                    fseek(fp, 0L, SEEK_SET);
                    while (fread(&selfAccount, sizeof(Customer), 1, fp) == 1)
                    { /*read until find same account or to the end of file*/
                        if (strcmp(selfAccount.accountID, search) != 0)
                        {
                            continue;
                        }
                        else
                        {
                            break;
                        }
                    }
                    account.Balance = account.Balance - wMoney;         /*refresh information in the temporary structure*/
                    selfAccount.Balance = selfAccount.Balance - wMoney; /*change the balance and next write it in the file*/
                    fseek(fp, -sizeof(Customer), SEEK_CUR);
                    fwrite(&selfAccount, sizeof(Customer), 1, fp); /*refresh the information*/
                    if (fclose(fp) != 0)
                    {
                        printf("Error closing file!");
                        exit(0);
                    }

                    fp = fopen(filename2, "a+");
                    if (fp == NULL) /*Test the success of opening the file*/
                    {
                        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
                        Sleep(2000);
                        exit(0);
                    }
                    fprintf(fp, "%s: Account withdrawled %lli at %s", selfAccount.accountID, wMoney, asctime(timeinfo));
                    if (fclose(fp) != 0)
                    {
                        printf("Error closing file!");
                        exit(0);
                    }
                    printf("Withdrawl successfully!!!\nYou have %lli $ left!\n", selfAccount.Balance);
                    Sleep(2000);
                    break;
                }
                case 2:
                {
                    flag = 0;
                    printf("Please enter the Password again:\n");
                    while (scanf("%s", pass) == 0 || strlen(pass) != 6)
                    { /*Test the entry of the persons name*/
                        printf("Please try again and make sure the Possword number are equal to 6-digit\n");
                        printf("Please enter the Password again:\n");
                        fflush(stdin);
                    }
                    if (strcmp(account.password, pass) != 0)
                    {
                        printf("Sorry! The password you entered is wrong, account will log out!\n");
                        Sleep(2000);
                        break;
                    }
                    if (account.state != 0)
                    {
                        printf("Sorry, this account has been blocked!!!\nActivities are baned!\nPress any button to continue!\n");
                        getch();
                        return 0;
                    }
                    printf("You have %lli $ left!\n\n", account.Balance);

                    printf("Please enter the card id you want to transfer!!!\n\n\t");
                    while (scanf("%s", transId) != 1 || strlen(transId) != 8)
                    {
                        printf("Sorry, please check if you entered a 8-digit number !!\n");
                        Sleep(1000);
                        fflush(stdin);
                    }

                    fp = fopen(filename1, "r+b"); /*open the file in rb+ mode*/
                    if (fp == NULL)               /*Test the success of opening the file*/
                    {
                        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
                        Sleep(2000);
                        exit(0);
                    }
                    fseek(fp, 0L, SEEK_SET);
                    while (fread(&transAccount, sizeof(Customer), 1, fp) == 1)
                    { /*read until find same account or to the end of file*/
                        if (strcmp(transAccount.accountID, transId) != 0)
                        {
                            continue;
                        }
                        else
                        {
                            flag = 1; /*No existing accounts*/
                            break;
                        }
                    }
                    if (fclose(fp) != 0)
                    {
                        printf("Error closing file!");
                        exit(0);
                    }
                    if (flag == 0)
                    {
                        printf("Sorry, no such an account exists!!!Try again!\n");
                        break;
                    }

                    printf("Please enter the money you want to transer:\n\t\t");
                    while (scanf("%lli", &t_Money) != 1 || t_Money > account.Balance || t_Money < 0)
                    {
                        printf("Sorry,The Balance is not enough!!\n");
                        printf("Please enter the money you want to transer:\n");
                        fflush(stdin);
                    }

                    fp = fopen(filename1, "r+b");
                    if (fp == NULL) /*Test the success of opening the file*/
                    {
                        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
                        Sleep(2000);
                        exit(0);
                    }

                    fseek(fp, 0L, SEEK_SET);
                    while (fread(&selfAccount, sizeof(Customer), 1, fp) == 1)
                    { /*read until find same account or to the end of file*/
                        if (strcmp(selfAccount.accountID, account.accountID) != 0)
                        {
                            continue;
                        }
                        else
                        {
                            break;
                        }
                    }
                    account.Balance = account.Balance - t_Money; /*refresh information in the temporary structure*/
                    selfAccount.Balance = selfAccount.Balance - t_Money;

                    fseek(fp, -sizeof(Customer), SEEK_CUR);
                    fwrite(&selfAccount, sizeof(Customer), 1, fp); /*refresh the information*/

                    fseek(fp, 0L, SEEK_SET);
                    while (fread(&transAccount, sizeof(Customer), 1, fp) == 1)
                    { /*read until find same account or to the end of file*/
                        if (strcmp(transAccount.accountID, transId) != 0)
                        {
                            continue;
                        }
                        else
                        {
                            break;
                        }
                    }
                    transAccount.Balance = transAccount.Balance + t_Money;
                    fseek(fp, -sizeof(Customer), SEEK_CUR);
                    fwrite(&transAccount, sizeof(Customer), 1, fp); /*refresh the information*/

                    if (fclose(fp) != 0)
                    {
                        printf("Error closing file!");
                        exit(0);
                    }

                    fp = fopen(filename2, "a+");
                    if (fp == NULL) /*Test the success of opening the file*/
                    {
                        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
                        Sleep(2000);
                        exit(0);
                    }

                    fprintf(fp, "%s: Thansfer %lli $ to %s at %s", selfAccount.accountID, t_Money, transAccount.accountID, asctime(timeinfo));
                    fprintf(fp, "%s: Receive %lli $ from %s at %s", transAccount.accountID, t_Money, selfAccount.accountID, asctime(timeinfo));
                    if (fclose(fp) != 0)
                    {
                        printf("Error closing file!");
                        exit(0);
                    }
                    printf("Success to transfer the money %lli $, press any button to return!\n", t_Money);
                    getch();
                    break;
                }
                case 3:
                {
                    printf("Please enter the Password again:\n\n\t");
                    while (scanf("%s", pass) == 0 || strlen(pass) != 6) /*Test the entry of the persons name*/
                    {
                        printf("Please try again and make sure the Password number are equal to 6-digit\n\n\t");
                        printf("Please enter the Password again:\n\n\t");
                        fflush(stdin);
                    }
                    if (strcmp(account.password, pass) != 0)
                    {
                        printf("Sorry! The Password you entered is wrong, try agian!!\n");
                        Sleep(2000);
                        break;
                    }
                    if (account.state != 0)
                    {
                        printf("Sorry, this account has been blocked!!!\nActivities are baned!\nPress any button to continue!\n");
                        getch();
                        return 0;
                    }
                    printf("\n\tYou have %lli $ left!\n\n", account.Balance);
                    printf("Please enter the amount you want to Deposit!\n");
                    while (scanf("%lli", &wMoney) != 1 || wMoney > account.Balance || wMoney < 0)
                    { /*withdrawl money should be larger than 0 $*/
                        printf("Sorry, The Balance is not enough!!\n");
                        printf("Please enter the amount you want to Deposit!\n");
                        fflush(stdin);
                    }

                    fp = fopen(filename1, "r+b");
                    if (fp == NULL) /*Test the success of opening the file*/
                    {
                        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
                        Sleep(2000);
                        exit(0);
                    }
                    fseek(fp, 0L, SEEK_SET);
                    while (fread(&selfAccount, sizeof(Customer), 1, fp) == 1)
                    { /*read until find same account or to the end of file*/
                        if (strcmp(selfAccount.accountID, search) != 0)
                        {
                            continue;
                        }
                        else
                        {
                            break;
                        }
                    }
                    account.Balance = account.Balance + wMoney;         /*refresh information in the temporary structure*/
                    selfAccount.Balance = selfAccount.Balance + wMoney; /*change the balance and next write it in the file*/
                    fseek(fp, -sizeof(Customer), SEEK_CUR);
                    fwrite(&selfAccount, sizeof(Customer), 1, fp); /*refresh the information*/
                    if (fclose(fp) != 0)
                    {
                        printf("Error closing file!");
                        exit(0);
                    }

                    fp = fopen(filename2, "a+");
                    if (fp == NULL) /*Test the success of opening the file*/
                    {
                        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
                        Sleep(2000);
                        exit(0);
                    }
                    fprintf(fp, "%s: Account Deposit %lli at %s", selfAccount.accountID, wMoney, asctime(timeinfo));
                    if (fclose(fp) != 0)
                    {
                        printf("Error closing file!");
                        exit(0);
                    }
                    printf("Deposit successfully!!!\nYou have %lli $ left!\n", selfAccount.Balance);
                    Sleep(2000);
                    break;
                }
                case 4:
                {
                    printf("Please enter the password again:\n");
                    while (scanf("%s", pass) == 0 || strlen(pass) != 6) /*Test the entry of the persons name*/
                    {
                        printf("Please try again and make sure the password number are equal to 6-digit\n");
                        printf("Please enter the password again:\n");
                        fflush(stdin);
                    }
                    if (strcmp(account.password, pass) != 0)
                    {
                        printf("Sorry! The pin you entered is wrong, account will log out!\n");
                        Sleep(2000);
                        break;
                    }

                    printf("Please enter a new 6-digit pin!!\n");
                    while (scanf("%s", changePin1) == 0 || strlen(changePin1) != 6)
                    {
                        printf("Please try again and make sure the new pin is 6-digit!\n");
                        fflush(stdin);
                        Sleep(1000);
                        system("cls");
                        printf("Please input your pin in 6-digit numbers:\n\n\t");
                    }
                    if (strcmp(changePin1, account.password) == 0)
                    {
                        printf("The new pin is the same as the old one, try again!\n");
                        Sleep(1500);
                        break;
                    }
                    printf("Please enter the pin agian!!!\n");
                    if (scanf("%s", changePin2) != 1 || strcmp(changePin2, changePin1) != 0)
                    {
                        printf("Error,The two input pins are not the same!!!Have another try next time!!\n");
                        fflush(stdin);
                        Sleep(1500);
                        break;
                    }
                    strcpy(account.password, changePin1); /*refresh information in the temporary structure*/

                    fp = fopen(filename1, "rb+");
                    if (fp == NULL) /*Test the success of opening the file*/
                    {
                        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
                        Sleep(2000);
                        exit(0);
                    }

                    fseek(fp, 0L, SEEK_SET);
                    while (fread(&selfAccount, sizeof(Customer), 1, fp) == 1)
                    { /*read until find same account or to the end of file*/
                        if (strcmp(selfAccount.accountID, search) != 0)
                        {
                            continue;
                        }
                        else
                        {
                            break;
                        }
                    }

                    strcpy(selfAccount.password, changePin1);
                    fseek(fp, -sizeof(Customer), SEEK_CUR);
                    fwrite(&selfAccount, sizeof(Customer), 1, fp); /*refresh the information*/
                    if (fclose(fp) != 0)
                    {
                        printf("Error closing file!");
                        exit(0);
                    }

                    fp = fopen(filename2, "a");
                    if (fp == NULL) /*Test the success of opening the file*/
                    {
                        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
                        Sleep(2000);
                        exit(0);
                    }

                    fprintf(fp, "%s: Account has changed the password in %s", selfAccount.accountID, asctime(timeinfo));
                    if (fclose(fp) != 0)
                    {
                        printf("Error closing file!");
                        exit(0);
                    }

                    printf("The Password has been changed successfully!!\n");
                    Sleep(1500);
                    break;
                }
                }
            }
        }
    }
    return 0;
}
