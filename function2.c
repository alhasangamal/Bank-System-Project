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