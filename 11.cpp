#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;

#define SIZE 50

int hash(const char *name)
{
	return (name[0]*name[1])%SIZE;
}
class student
{
	char name[30],usn[11],age[3];
	public : 
		student() { strcpy(usn,"*"); }
		void getData(char *_name);
		void putData();
		int isEmpty();
		int found(char *_name);
		void writeToFile();
};

void student::getData(char *_name)
{
	strcpy(name,_name);
	cout<<"Enter USN : ";
	cin>>usn;
	cout<<"Enter AGE : ";
	cin>>age;
}
void student::putData()
{
	cout<<"NAME:"<<name<<"\nUSN:"<<usn<<"\nAGE:"<<age<<endl;
}
int student::isEmpty()
{
	if(strcmp(usn,"*")==0)
		return 1;
	return 0;
}
int student::found(char *_name)
{
	if(strcmp(name,_name)==0)
		return 1;
	return 0;
}
void student::writeToFile()
{
	ofstream file("record.txt",ios::app);
	file<<usn<<"|"<<name<<"|"<<age<<endl;
	file.close();
}
int main()
{
	student s[SIZE];
	int choice=1,h;
	char _name[20];
	ofstream file("record.txt",ios::app);
	file.close();
	while(choice)
	{
		cout<<"\n1. Insert Record\n2. Get Record.\n3. EXIT\nEnter your choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1 : cout<<"Enter a name : ";
					 cin>>_name;
					 h=hash(_name);
					 while(!s[h].isEmpty())
						 h=(h+1)%SIZE;
					 s[h].getData(_name);
					 s[h].writeToFile();
					 cout<<"\nHash value : "<<h<<"\nDONE. Record entered.\n";
					 break;
			case 2 : cout<<"Enter the name of whose record is to be fetched : ";
					 cin>>_name;
					 h=hash(_name);
					 cout<<"\nHash value : "<<h<<endl;
					 while(!s[h].isEmpty())
					 {
						 if(s[h].found(_name))
						 {
							cout<<"Record found : \n";
							s[h].putData();
							break;
						 }
						 h=(h+1)%SIZE;
					 }
					 if(s[h].isEmpty())
						cout<<"\nRecord not found!";
					 break;
			case 3 : return 0;
			default : cout<<"\nInvalid choice\n";
		}
	}
	return 0;
}
