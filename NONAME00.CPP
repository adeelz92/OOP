#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

class person
{
protected:
	char name[20];
	char cnic[20];
public:
	person();
	person(char[],char[]);
	virtual void dataEntry()=0;
	void print();
};

person::person()
{
	strcpy(name,"None");
	strcpy(cnic,"0");
}

person::person(char a[], char c[])
{
	strcpy(name,a);
	strcpy(cnic,c);
}

void person::dataEntry()
{
	cout<<"\nEnter the name :";
	gets(name);

   do
   {
   cout<<"\nEnter the CNIC (end with #):";
	gets(cnic);
   }
   while(cnic[13]!='#');

}

void person::print()
{
	cout<<"\nName :"; puts(name);
	cout<<"\nCNIC :"; puts(cnic);
}
////////////////////////////////////////////////////////////////////////////////

class account
{
protected:
	int acno;
	char type;
	float balance;
public:
	account();
	account(int,char,float);
	virtual void dataEntry()=0;
	void print();
	int* retacno();
	float* retbal();
	char* rettype();
};

account::account()
{
	acno=0;
	type='c';
	balance=0;
}

account::account(int a, char b, float c)
{
	acno=a;
	type=b;
	balance=c;
}

void account::dataEntry()
{
	cout<<"\nEnter the account no. :";
	cin>>acno;

   cout<<"\n**NOTE** For Current Account, minimum amount in the account is 1000 and 500 for saving \n";
	cout<<"\nEnter the type (c/s) :";
	cin>>type;
   do
   {
	cout<<"\nEnter the ammount :";
	cin>>balance;
   }while(balance<=0);
}

void account::print()
{
	cout<<"\nAccount no. :"<<acno;
	cout<<"\nType :"<<type;
	cout<<"\nBalance :"<<balance;
}


int* account::retacno()
{
	return &acno;
}
float* account::retbal()
{
	return &balance;
}

char* account::rettype()
{
	return &type;
}
////////////////////////////////////////////////////////////////////////////////
class person1:public person
{
protected:
	char addr[20];
	char prof[20];
	int age;
public:
	person1();
	person1(char[],char[],char[],char[],int);
   virtual void dataEntry()=0;
	void print();
};
person1::person1()
{
	strcpy(addr,"none");
	strcpy(prof,"none");
	age=0;
}

person1::person1(char a[], char b[], char c[], char d[],int e):person(a,b)
{
	strcpy(addr,c);
	strcpy(prof,d);
	age=e;
}

void person1::dataEntry()
{
	person::dataEntry();
	cout<<"\nEnter the address :";
	gets(addr);

	cout<<"\nEnter the profession :";
	gets(prof);

	cout<<"\nEnter the age :";
	cin>>age;
}

void person1::print()
{
	person::print();
	cout<<"\nAddress :"; puts(addr);
	cout<<"\nProfession :"; puts(prof);
	cout<<"\nAge :"<<age;
}
////////////////////////////////////////////////////////////////////////////////
class manager:public person
{
private:
	int pass;
public:
	manager();
	manager(int,char[],char[]);
	void dataEntry();
	void print();
	bool verify(manager);
};

manager::manager()
{
	pass=0;
}

manager::manager(int c, char a[], char b[]):person(a,b)
{
	pass=c;
}

void manager::dataEntry()
{
	cout<<"\nEnter the password :";
	cin>>pass;
}

void manager::print()
{
	cout<<"\nMANAGER'S DETAILS ";
	person::print();
}

bool manager::verify(manager a)
{
	if(a.pass==pass)
		return true;
	else return false;
}
////////////////////////////////////////////////////////////////////////////////
class officer: public person1, public account
{
private:
	int pass;
public:
	officer();
	officer(char [], char[] , char [], char [], int , int , char , float ,int );
   officer(int);
  	void dataEntry();
	void create();
	void modify();
   void report();
   void check();
   bool verify(officer);
};
officer::officer()
{
	pass=1234;
}

officer::officer(char a[], char b[], char c[], char d[], int e, int f, char g, float h,int i):person1(a,b,c,d,e),account(f,g,h)
{
	pass=i;
}

officer::officer(int x)
{
	pass=x;
}

void officer::dataEntry()
{
	cout<<"\nEnter the Officers Password :";
   cin>>pass;
}

bool officer::verify(officer a)
{
	if(a.pass==pass)
   return true;
   else return false;
}

void officer::create()
{
	person1::dataEntry();
	account::dataEntry();
	cout<<"\n\n\nAccount Created..";
}
void officer::modify()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nModify Account Holder Name : ";
	gets(name);
   do
   {
   cout<<"\nModify Cnic :";
	gets(cnic);
   }
   while(cnic[13]!='#');

   cout<<"\nModify Account number :";
   cin>>acno;

   cout<<"\nModify address :";
   gets(addr);

   cout<<"\nModify age :";
   cin>>age;

	cout<<"\nModify Type of Account : ";
	cin>>type;

	do
   {
	cout<<"\nEnter the modify balance ammount :";
	cin>>balance;
   }while(balance<=0);
}

void officer::report()
{
	cout<<acno<<"          "<<" "<<name<<"          "<<" "<<type<<"      "<<balance<<endl;
}

void officer::check()
{
	person1::print();
	account::print();
}
////////////////////////////////////////////////////////////////////////////////
class customer:public officer
{
public:
	customer();
	customer(char [], char[] , char [], char [],int , int , char , float ,int);
	void dataEntry()
	{}
	void deposit(float*);
	void draw(float*);
	void check();
};


customer::customer()
{}
customer::customer(char a[], char b[], char c[], char d[], int e, int f, char g, float h, int i):officer(a,b,c,d,e,f,g,h,i)
{}
void customer::deposit(float* a)
{
balance = balance + *a;
}



void customer::draw(float* a)
{
	balance=balance - *a;
}


void customer::check()
{
	officer::check();
}

////////////////////////////////////////////////////////////////////////////////

void write_account()
{
	officer* ofc= new officer;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ofc->create();
	outFile.write(reinterpret_cast<char *> (ofc), sizeof(officer));
	outFile.close();
}
////////////////////////////////////////////////////////////////////////////////

void display_sp(int* n)
{
	customer* ac=new customer;
   int *x;

	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
      x=ac->retacno();
    	while(inFile.read(reinterpret_cast<char *> (ac), sizeof(customer)))
	{
		if(*x==*n)
		{
			ac->check();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
      getch();
}

////////////////////////////////////////////////////////////////////////////////

void modify_account(int* n)
{
	bool found=false;
	officer *ac=new officer;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}

   int *x;
   x=ac->retacno();
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (ac), sizeof(officer));
		if(*x==*n)
		{  ac->check();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac->modify();
			int pos=(-1)*static_cast<int>(sizeof(officer));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (ac), sizeof(officer));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
      getch();
}

////////////////////////////////////////////////////////////////////////////////

void delete_account(int* n)
{
	officer* ac=new officer;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}

   int *x;
   x=ac->retacno();

	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (ac), sizeof(officer)))
	{
		if((*x)!=*n)
		{
			outFile.write(reinterpret_cast<char *> (ac), sizeof(officer));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

////////////////////////////////////////////////////////////////////////////////
void display_all()
{
      officer *ac= new officer;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME             Type       Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (ac), sizeof(officer)))
	{
		ac->report();
	}
   getch();
	inFile.close();
}
////////////////////////////////////////////////////////////////////////////////

void deposit_withdraw(int* n, int option)
{
	float t;
	bool found=false;
	customer* ac=new customer;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}

   int *x;
   x=ac->retacno();

	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (ac), sizeof(customer));
		if(*x==*n)
		{
			if(option==1)
			{
         	ac->check();
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
            do
            {
				cout<<"\n\nEnter The amount to be deposited";
				cin>>t;
            }while(t<=0);

				ac->deposit(&t);
			}
			if(option==2)
			{
         	ac->check();
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
            do
            {
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>t;
            }while(t<=0);

				float *bal=ac->retbal();
            *bal= *bal - t;
            char *z=ac->rettype();
				if((*bal<500 && *z=='s') || (*bal<1000 && *z=='c'))
					cout<<"Insufficienct balance";
				else
					ac->draw(&t);
			}
			int pos=(-1)*static_cast<int>(sizeof(*ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (ac), sizeof(customer));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
      getch();
}

void intro()
{
	cout<<"\n\t\t********************************************";
	cout<<"\n\t\tObject Oriented Programming Semester Project\n";
   cout<<"\t\t********************************************";

   cout<<"\n\n\n\t\t\t   ======================";
   cout<<"\n\t\t\t   BANK MANAGEMENT SYSTEM";
   cout<<"\n\t\t\t   ======================";

   cout<<"\n\n\n\n\t\t\t   BY:\n";
   cout<<"\t\t\t      NC HASAN IQBAL\n";
   cout<<"\t\t\t      NC AQSA QAMAR\n";
   cout<<"\t\t\t      NC SABA NAWAZ";
}

////////////////////////////////////////////////////////////////////////////////

void main()
{
   intro();
  	getch();

	char ch;
	int num;
	do
	{
		system("cls");
      cout<<"\n\n\n\t#########";
		cout<<"\n\tMAIN MENU";
      cout<<"\n\t#########";

		cout<<"\n\n\t01. MANAGER";
		cout<<"\n\n\t02. OFFICER";
		cout<<"\n\n\t03. CUSTOMER";
		cout<<"\n\n\t04. EXIT";
		cout<<"\n\n\tSelect Your Option (1-4) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			{
         	cout<<"\n\t\t**************************";
				cout<<"\n\t\tWELCOME TO MANAGER SECTION";
            cout<<"\n\t\t**************************\n";

				manager a(12345,"Bilal Rauf","3740511111111");
            manager b;

				b.dataEntry();

				char x;

				if(b.verify(a)==true)
				{
            	a.print();
            	cout<<"\nPress 1 to get REPORT of bank accounts. ";
					cin>>x;

					if(x=='1')
               {
               	display_all();
               }
					else
               			cout<<"\nInvalid Entry!!";
				}
				else
            		cout<<"\nInvalid Password!!!";
                  getch();
						break;
         }
		case '2':
			{
         	cout<<"\n\t\t**************************";
				cout<<"\n\t\tWELCOME TO OFFICER SECTION";
            cout<<"\n\t\t**************************\n";

				officer a(54321);
				officer b;
            b.dataEntry();

				if(a.verify(b)==true)
				{
					char x;
               cout<<"\n\n\n\t=============";
					cout<<"\n\tOFFICERS MENU";
               cout<<"\n\t=============";

					cout<<"\n\n\t01. NEW ACCOUNT";
					cout<<"\n\n\t02. MODIFY ACCOUNT";
					cout<<"\n\n\t03. CLOSE ACCOUNT";
               cout<<"\n\n\t04. EXIT";

					cout<<"\n\n\tSelect Your Option (1-4) ";
					cin>>x;
					system("cls");

					if(x=='1')
						write_account();
					else if(x=='2')
					{
						cout<<"\n\n\tEnter The account No. : "; cin>>num;
						modify_account(&num);
					}
					else if(x=='3')
					{
						cout<<"\n\n\tEnter The account No. : "; cin>>num;
						delete_account(&num);
					}
               else if(x=='4')
               	break;

					else
						cout<<"\nInvalid Entry!!!";

				}
				else
					cout<<"\nInvalid Password!!!";
               getch();
               break;

			}

		case '3':
			{
				char x;
            cout<<"\n\t\t***************************";
				cout<<"\n\t\tWELCOME TO CUSTOMER SECTION";
            cout<<"\n\t\t***************************";
            cout<<"\n\n\n\t==============";
				cout<<"\n\tCUSTOMERS MENU";
            cout<<"\n\t==============";
				cout<<"\n\n\t01. DEPOSIT AMMOUNT";
				cout<<"\n\n\t02. WITHDRAW ACCOUNT";
				cout<<"\n\n\t03. BALANCE ENQUIRY";
				cout<<"\n\n\t04. EXIT";
				cout<<"\n\n\tSelect Your Option (1-4) ";
					cin>>x;
					system("cls");

				if(x=='1')
				{
					cout<<"\n\n\tEnter The account No. : "; cin>>num;
					deposit_withdraw(&num, 1);
				}
				else if(x=='2')
				{
					cout<<"\n\n\tEnter The account No. : "; cin>>num;
					deposit_withdraw(&num, 2);
				}
				else if(x=='3')
				{
					cout<<"\n\n\tEnter The account No. : "; cin>>num;
					display_sp(&num);
				}
				else if(x=='4')
					break;

				break;
			}

				case '4':
					cout<<"\n\n\tThanks for using bank managemnt system";
               getch();
					break;
        }
	}while(ch!='4');


getch();
}
////////////////////////////////////////////////////////////////////////////////