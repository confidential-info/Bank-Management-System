#include <iostream>
#include<fstream>
#include<cstdlib>
using namespace std;
class account_query
{
	int account_number,pin;
	char firstName[10];
	char lastname[10];
	float total_balance;
	public:
		void read_rec();
		void read_data();
		void show_data();
		void write_rec();
		void search_rec();
		void draw();
		void money_deposit();
		void balance();
		void change_pin();
		void modify();
		int ret_account();
		int ret_pin();
}A;
void account_query::write_rec()
{
	ofstream outfile;
	outfile.open("record.bank",ios::binary|ios::app);
	read_data();
	outfile.write((char*)&A,sizeof(A));
	outfile.close();
	cout<<"Record added"<<endl;
}
void account_query::read_data()
{
	cout<<"\nEnter Account Number:";
	cin>>account_number;
	cout<<"Enter First Name:";
	cin>>firstName;
	cout<<"Enter Last Name:";
	cin>>lastname;
	cout<<"Enter pin:";
	cin>>pin;
	cout<<"Enter Balance:";
	cin>>total_balance;
	cout<<endl;
}
void account_query::show_data()
{
    cout<<"Account Number:"<<account_number<<endl;
	cout<<"First Name:"<<firstName<<endl;
	cout<<"Last Name:"<<lastname<<endl;
	cout<<"Current Balance:Rs."<<total_balance<<endl;
	cout<<"-------------------------------------------------------"<<endl;
}
void account_query::read_rec()
{
    int flag=0;
    ifstream infile;
    infile.open("record.bank",ios::in|ios::binary);
    while(infile.read((char*)&A,sizeof(A)))
    {
        A.show_data();
        flag++;
    }
    if(flag==0)
        cout<<"Empty file"<<endl;
    infile.close();
}
void account_query::draw()
{
    float money;
    cout<<"Current balance:"<<total_balance<<endl;
    cout<<"Enter amount to withdraw:";
    cin>>money;
    total_balance=total_balance-money;
    cout<<"New balance="<<total_balance<<endl;
}
void account_query::money_deposit()
{
    float money;
    cout<<"Current balance:"<<total_balance<<endl;
    cout<<"Enter amount to deposit:";
    cin>>money;
    total_balance=total_balance+money;
    cout<<"New balance="<<total_balance<<endl;
}
void account_query::balance()
{
    cout<<"Current balance:"<<total_balance<<endl;
}
void account_query::change_pin()
{
    cout<<"Enter new pin:";
    cin>>pin;
}
void account_query::modify()
{
    cout<<"Account has following data:"<<endl;
    show_data();
    cout<<"Enter details to be modified:"<<endl;
    cout<<"  New account no. (write old no. for no change)=";
    cin>>account_number;
    cout<<"  New first name (write old name for no change)=";
    cin>>firstName;
    cout<<"  New last name (write old name for no change)=";
    cin>>lastname;
    cout<<"  New balance (write old amount for no change)=";
    cin>>total_balance;
}
int account_query::ret_account()
{
    return account_number;
}
int account_query::ret_pin()
{
    return pin;
}
void delete_rec()
{
    int account,n=0;
    ifstream infile;
    infile.open("record.bank",ios::in|ios::binary);
    ofstream outfile;
    outfile.open("temp",ios::out|ios::binary);
	if(!infile)
	{
		cout<<"\nError in opening! File not found !!"<<endl;
		return;
	}
	infile.seekg(0,ios::end);
	int count=infile.tellg()/sizeof(A);
	cout<<"\n There are "<<count<<" record in the file"<<endl;
    cout<<"Enter the account no. to be deleted:";
    cin>>account;
    infile.seekg(0);
    while(infile)
    {
        infile.read((char*)&A,sizeof(A));
        if(A.ret_account()!=account)
        {
            outfile.write((char*)&A,sizeof(A));
        }
        else
            n=1;
    }
    if(n==0)
        cout<<"Record not found"<<endl;
    if(n==1)
        cout<<"Record deleted"<<endl;
    infile.close();
    outfile.close();
    remove("record.bank");
    rename("temp","record.bank");
}
void withdraw()
{
    int account,pinn,flag=0;
	fstream iofile;
	iofile.open("record.bank",ios::in|ios::out|ios::binary);
	if(!iofile)
	{
		cout<<"\nError in opening! File not found !!"<<endl;
		return;
	}
	iofile.seekg(0,ios::end);
	int count=iofile.tellg()/sizeof(A);
	cout<<"\n There are "<<count<<" record in the file";
	cout<<"\n Enter account number to edit:";
	cin>>account;
	iofile.seekg(0,ios::beg);
	while(!iofile.eof())
    {
        long pos=iofile.tellg();
        iofile.read((char*)&A,sizeof(A));
        if(A.ret_account()==account)
        {
            for(int i=3;i>0;i--)
            {
                cout<<"Enter pin:";
                cin>>pinn;
                iofile.seekg(pos);
                if(A.ret_pin()==pinn)
                {
                    A.draw();
                   iofile.seekg(pos);
                   iofile.write((char*)&A,sizeof(A));
                   flag++;
                   break;
                }
                else
                {
                   cout<<"Wrong pin"<<endl;
                   cout<<i-1<<" turns left"<<endl;
                }
            }
            break;
        }
    }
    if(flag==0)
        cout<<"Record not found"<<endl;
    iofile.close();
}
void deposit()
{
    int account,pinn,flag=0;
	fstream iofile;
	iofile.open("record.bank",ios::in|ios::out|ios::binary);
	if(!iofile)
	{
		cout<<"\nError in opening! File not found !!"<<endl;
		return;
	}
	iofile.seekg(0,ios::end);
	int count=iofile.tellg()/sizeof(A);
	cout<<"\n There are "<<count<<" record in the file";
	cout<<"\n Enter account number to edit:";
	cin>>account;
	iofile.seekg(0);
	while(!iofile.eof())
    {
        long pos=iofile.tellg();
        iofile.read((char*)&A,sizeof(A));
        if(A.ret_account()==account)
        {
            for(int i=3;i>0;i--)
            {
                cout<<"Enter pin:";
                cin>>pinn;
                iofile.seekg(pos);
                if(A.ret_pin()==pinn)
                {
                   A.money_deposit();
                   iofile.seekg(pos);
                   iofile.write((char*)&A,sizeof(A));
                   flag++;
                   break;
                }
                else
                {
                   cout<<"Wrong pin"<<endl;
                   cout<<i-1<<" turns left"<<endl;
                }
            }
            break;
        }
    }
    if(flag==0)
        cout<<"Record not found"<<endl;
    iofile.close();
}
void inquiry()
{
    int account,flag=0,pinn;
    ifstream infile;
	infile.open("record.bank",ios::in|ios::binary);
	if(!infile)
	{
		cout<<"\nError in opening! File not found !!"<<endl;
		return;
	}
	infile.seekg(0,ios::end);
	int count=infile.tellg()/sizeof(A);
	cout<<"\n There are "<<count<<" record in the file";
	cout<<"\n Enter account number to edit:";
	cin>>account;
	infile.seekg(0);
	while(infile)
    {
        long pos=infile.tellg();
        infile.read((char*)&A,sizeof(A));
        if(A.ret_account()==account)
        {
            for(int i=3;i>0;i--)
            {
                cout<<"Enter the pin:";
                cin>>pinn;
                infile.seekg(pos);
                if(A.ret_pin()==pinn)
                {
                    A.balance();
                    flag++;
                    break;
                }
                else
                {
                    cout<<"Wrong pin"<<endl;
                    cout<<i-1<<" turns left"<<endl;
                }
            }
            break;
        }
    }
    if(flag==0)
        cout<<"Record not found"<<endl;
    infile.close();
}
void change()
{
    int account,flag=0,pinn;
    fstream iofile;
	iofile.open("record.bank",ios::in|ios::out|ios::binary);
	if(!iofile)
	{
		cout<<"\nError in opening! File not found !!"<<endl;
		return;
	}
	iofile.seekg(0,ios::end);
	int count=iofile.tellg()/sizeof(A);
	cout<<"\n There are "<<count<<" record in the file";
	cout<<"\n Enter account number to edit:";
	cin>>account;
	iofile.seekg(0);
	while(!iofile.eof())
    {
        long pos=iofile.tellg();
        iofile.read((char*)&A,sizeof(A));
        if(A.ret_account()==account)
        {
            for(int i=3;i>0;i--)
            {
                cout<<"Enter pin:";
                cin>>pinn;
                iofile.seekg(pos);
                if(A.ret_pin()==pinn)
                {
                   A.change_pin();
                   iofile.seekg(pos);
                   iofile.write((char*)&A,sizeof(A));
                   flag++;
                   break;
                }
                else
                {
                   cout<<"Wrong pin"<<endl;
                   cout<<i-1<<" turns left"<<endl;
                }
            }
            break;
        }
    }
    if(flag==0)
        cout<<"Record not found"<<endl;
    iofile.close();
}
void edit_rec()
{
    int account,n=0,pinn;
	fstream iofile;
	iofile.open("record.bank",ios::in|ios::out|ios::binary);
	if(!iofile)
	{
		cout<<"\nError in opening! File not found !!"<<endl;
		return;
	}
	iofile.seekg(0,ios::end);
	int count=iofile.tellg()/sizeof(A);
	cout<<"\n There are "<<count<<" record in the file";
	cout<<"\n Enter account number to edit:";
	cin>>account;
	iofile.seekg(0);
	while(!iofile.eof())
    {
        long pos=iofile.tellg();
        iofile.read((char*)&A,sizeof(A));
        if(A.ret_account()==account)
        {
            for(int i=3;i>0;i--)
            {
                cout<<"Enter pin:";
                cin>>pinn;
                iofile.seekg(pos);
                if(A.ret_pin()==pinn)
                {
                    A.modify();
                    iofile.seekg(pos);
                    iofile.write((char*)&A,sizeof(A));
                    n++;
                    break;
                }
                else
                {
                    cout<<"Wrong pin"<<endl;
                    cout<<i-1<<" turns left"<<endl;
                }
            }
            break;
        }
    }
    if(n==0)
        cout<<"Record not found"<<endl;
    iofile.close();
}
void admin(),user();
int main()
{
    int choice;
	while(true)
	{
	    system("cls");
	    cout<<"\t\t\t\t***Account Information System***"<<endl;
		cout<<"Select one option below";
		cout<<"\nt1-->ADMIN";
		cout<<"\nt2-->USER";
		cout<<"\nt3-->Exit";
		cout<<"\nEnter your choice:";
		cin>>choice;
		switch(choice)
		{
        case 1:
            system("cls");
            admin();
            break;
        case 2:
            system("cls");
            user();
            break;
        case 3:
            exit(0);
        default:
            cout<<"Invalid option"<<endl;
            break;
		}
		system("pause");
	}
    return 0;
}
void admin()
{
    int n,password=1234,pass;
    char x='y';
    for(int i=3;i>0;i--)
    {
        cout<<"Enter the password:";
        cin>>pass;
        if(pass==password)
        {
            while(x=='y')
            {
                system("cls");
                cout<<"Select one option below:";
                cout<<"\nt1-->Create record";
                cout<<"\nt2-->Show all records";
                cout<<"\nt3-->Delete record";
                cout<<"\nt4-->Go back";
                cout<<"\nEnter your choice:";
                cin>>n;
                switch(n)
                {
                case 1:
                    system("cls");
                    A.write_rec();
                    break;
                case 2:
                    system("cls");
                    A.read_rec();
                    break;
                case 3:
                    system("cls");
                    delete_rec();
                    break;
                case 4:
                    x='n';
                    break;
                default:
                    cout<<"\nEnter correct choice";
                }
                system("pause");
            }
            break;
        }
        else
        {
            cout<<"Incorrect password"<<endl;
            cout<<i-1<<" chances left"<<endl;
        }
    }
}
void user()
{
    int n;
    char x='y';
    while(x=='y')
    {
        system("cls");
        cout<<"Select one option below:";
        cout<<"\nt1-->Withdraw money";
        cout<<"\nt2-->Deposit money";
        cout<<"\nt3-->Balance inquiry";
        cout<<"\nt4-->Change pin";
        cout<<"\nt5-->Update record";
        cout<<"\nt6-->Go back";
        cout<<"\nEnter your choice:";
        cin>>n;
        switch(n)
        {
        case 1:
            system("cls");
            withdraw();
            break;
        case 2:
            system("cls");
            deposit();
            break;
        case 3:
            system("cls");
            inquiry();
            break;
        case 4:
            system("cls");
            change();
            break;
        case 5:
            system("cls");
            edit_rec();
            break;
        case 6:
            x='n';
            break;
        default:
            cout<<"\nEnter correct choice";
        }
        system("pause");
    }
}
