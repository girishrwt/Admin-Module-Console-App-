#include<stdio.h>
#include<conio.h>
#include<windows.h>

// Function declaration 
void gotoxy(int x,int y);
void consoleColor(int ForgC,int BackC);
void textColor(int ForgC);
void sign_up();
void sign_in();
void adminSetting();
void changePassword();
void menu();
char* username();
char* password();
void window();


COORD coord={0,0};
struct login
{
	char username[15];
	char password[15];
	
};
struct login l;
FILE *login;
int pwd_counter=0;



/****************************** Main start *****************************/ 

int main()
{
	consoleColor(12,15);
	textColor(12);
	login=fopen("login.dat","rb");
	if(login==NULL)
	 sign_up();
	else
	 sign_in();
	 menu();
	return 0;
}

/****************************** main ends *******************************/

void window()
{
	int i;
	for(i=12;i<53;i++)
	{
		gotoxy(i,2);printf("\xB2");
		
	}
	for(i=2;i<25;i++)
	{
		gotoxy(53,i);printf("\xB2");
		
	}
	for(i=53;i>12;i--)
	{
		gotoxy(i,25);printf("\xB2");
		
	}
	for(i=25;i>2;i--)
	{
		gotoxy(12,i);printf("\xB2");
		
	}
	
}

void menu()
{
	int pos=20;
	char c;
	while(1)
	{
		system("cls");
		gotoxy(pos,6);printf("Press 0 for exit");
		gotoxy(pos,8);printf("press 1 for admin setting");
		gotoxy(pos,10);printf("Enter your choice :");
		c=getche();
		switch(c)
		{
			case '0': exit(0);
			case '1': adminSetting(); break;
			
		}
		
	}
	
}

void adminSetting()
{
	system("cls");
	int choice;
	int pos=20;
	gotoxy(pos,4);printf("======= Admin Setting ======");
	gotoxy(pos,6);printf("1. Change Password");
	gotoxy(pos,9);printf("Enter Your choice :");
	scanf("%d",&choice);
	if(choice==1)
	 changePassword();
	else
	 return;
	
}

void changePassword()
{
	system("cls");
	int pos=20;
	int flag=0;
	char old_password[15],new_password[15],confirm_password[15];
	gotoxy(pos,6);printf("CHANGING PASSWORD");
	gotoxy(pos,8);printf("Enter Old Password :");
	gotoxy(pos,10);printf("Enter New Password :");
	gotoxy(pos,12);printf("Re-Enter New Password :");
	gotoxy(pos+20,8);strcpy(old_password,password());
	gotoxy(pos+20,10);strcpy(new_password,password());
	gotoxy(pos+23,12);strcpy(confirm_password,password());
	if(strcmp(new_password,confirm_password)==0)
	{
		flag=5;
	}
	else
	{
		gotoxy(pos,15);printf("Password do not match");
		gotoxy(pos,17);printf("Press any key to contd...");getch();changePassword();
	}
	login=fopen("login.dat","rb+");
	if(login==NULL)
	{
		gotoxy(pos,14);printf("Unable to open file");getch();
		exit(1);
	}
	if(flag==5)
	{
	    while(fread(&l,sizeof(l),1,login)==1)
	    {
		    if(strcmp(l.password,old_password)==0)
		    {
		        strcpy(l.password,new_password);
		        rewind(login);
		        fwrite(&l,sizeof(l),1,login);
		        fclose(login);
		        flag=6;
		    }
	    }
	}
	if(flag==6)
	{
		gotoxy(pos,15);printf("Password Changed Successfully.");
		gotoxy(pos,17);printf("Press any key to contd...");getch();
		
	}
	else
	{
		gotoxy(pos,15);printf("Password changing process failed");
		gotoxy(pos,17);printf("    TRY AGAIN   ");getch();
		changePassword();
		
	}
	
}

void sign_in()
{
	system("cls");
	window();
	int pos=20;
	int flag=0;
	char user[15];
	char pwd[15];
	gotoxy(pos,4);printf("===== LogIn process =====");
	gotoxy(pos,6);printf("UserName :");
	gotoxy(pos,8);printf("Password :");
	gotoxy(pos+10,6);strcpy(user,username());
	gotoxy(pos+10,8);strcpy(pwd,password());
	login=fopen("login.dat","rb");
	while(fread(&l,sizeof(l),1,login)==1)
	{
		if(strcmp(l.username,user)==0 && strcmp(l.password,pwd)==0)
		{
			flag=1;
		}
	}
	fclose(login);
	if(flag==1)
	{
		gotoxy(pos,10);printf("Login successfull");
		getch();
	}
	else
	{
		gotoxy(pos,10);printf("Invalid username and Password");
		gotoxy(pos,12);printf("Press any key to contd...");
		getch();
		pwd_counter++;
		if(pwd_counter==3)
		{
			gotoxy(pos+10,14);printf("You attempts too much.");
			getch();exit(0);
		}
		else
		{
		  sign_in();	
		}
		
	}
}

void sign_up()
{
	system("cls");
	window();
	int flag=0;
	int g;
	char pwd[15];
	char confirmPwd[15];
	int pos=20;
	gotoxy(pos,4);printf("====== Setup Account =====");
	gotoxy(pos,6);printf("UserName :");
	gotoxy(pos,8);printf("Password :");
	gotoxy(pos,10);printf("Confirm Password :");
	gotoxy(pos+10,6);strcpy(l.username,username());
	gotoxy(pos+10,8);strcpy(pwd,password());	
	gotoxy(pos+18,10);strcpy(confirmPwd,password());
	if(strcmp(pwd,confirmPwd)==0)
	{
		strcpy(l.password,pwd);
		gotoxy(pos+2,12);printf("Your Account has been created");
		gotoxy(pos,15);printf("Your username is %s",l.username);
		gotoxy(pos,16);printf("Your Password is %s",l.password);
		getch();
		flag=2;
	}
	else
	{
		gotoxy(pos+2,12);printf("Password do not match");
		gotoxy(pos+2,14);printf("Press any key to contd...");
		getch();
		sign_up();
	}
	if(flag==2)
	{
		login=fopen("login.dat","ab+");
		if(login==NULL)
		{
			gotoxy(pos,20);printf("Cant open File");
			exit(1);
			
		}
		fwrite(&l,sizeof(l),1,login);
		fclose(login);
	}
}

char* username()
{
	int pos=20;
	char *username;
	char usr[15];
	int i=0;
	while(1)
     {
         usr[i]=getche();
         if(usr[i]==13) { break; }
         else if(usr[i]==32)
         {
         	printf("\b \b");
         	
         }
         else if(usr[i]==8)
         {
             if(i!=0)
             {
	             printf(" \b");
	             i--;
	         } 
			 else
			 {
			 	//printf(" \a");
			 	gotoxy(pos+9,6);printf(":");
		     }
	         
         }
         else
         {
         	usr[i];
            i++;
         }
     }
     usr[i]='\0';
     username=usr;
     return username;
}

char* password()
{
	char *password;
	char pwd[15];

	int i=0;
	while(1)
	{
		pwd[i]=getch();
		if(pwd[i]==13) break;
		else if(pwd[i]==32)
		{
			printf(" \b");
		}
		else if(pwd[i]==8)
		{
			if(i!=0)
			{
				printf("\b \b");
				i--;
			}
			else
			{
				printf("\a");
			}
		}
		else
		{
			printf("*");
			i++;
		}	
	}
	pwd[i]='\0';
	password=pwd;
	return password;
}

void textColor(int ForgC)
{
	WORD wColor;//We will need this handle to get the current text attributes
	HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(GetConsoleScreenBufferInfo(hStdOut,&csbi))
	{
		wColor=(csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut,wColor);
		
	}
	
}

void consoleColor(int ForgC,int BackC)
{
	COORD coord;
    WORD wColor=((BackC & 0x0F)<<4) + (ForgC & 0x0F);
    HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut,wColor);
    DWORD count;   //This is a structure containing all the console info
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut,&csbi))
    {
        FillConsoleOutputCharacter(hStdOut,(TCHAR)32,csbi.dwSize.X * csbi.dwSize.Y,coord,&count);
        FillConsoleOutputAttribute(hStdOut,csbi.wAttributes,csbi.dwSize.X * csbi.dwSize.Y,coord,&count);
        SetConsoleCursorPosition(hStdOut,coord);
    }
}

void gotoxy(int x,int y)
{
	coord.X=x;
	coord.Y=y;
	HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdOut,coord);
	
}
