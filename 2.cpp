#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
#define len 40
class student
{
	char usn[11];
	char name[25];
	char age[3];
	char buf[len];
	void pack();
	void unpack();
      public:
	void add();
	void display();
	void search();
	void modify();
};
void student::pack()
{
	strcpy(buf,usn);
	strcat(buf,"|");
	strcat(buf,name);
	strcat(buf,"|");
	strcat(buf,age);
	int i;
	for(i=strlen(buf);i<len;i++)
	strcat(buf,"#");
}
void student::unpack()
{
	strcpy(usn,strtok(buf,"|"));
	strcpy(name,strtok(NULL,"|"));
	strcpy(age,strtok(NULL,"#"));
}
void student::add()
{
	cout<<"Enter USN :";
	cin>>usn;
	cout<<"Enter NAME:";
	cin>>name;
	cout<<"Enter AGE :";
	cin>>age;
	pack();
	ofstream fout;
	fout.open("student",ios::app);
	fout<<buf<<endl;
	fout.close();
	cout<<"Student REC ADDED";
}
void student::display()
{
	ifstream fin;
	fin.open("student");
	while(!fin.eof())
	{
		fin>>buf;
		if(fin.fail())
		break;
		unpack();
		cout<<"\nUSN :"<<usn<<"\nNAME :"<<name<<"\nAGE :"<<age<<endl;
	}
	fin.close();
}
void student::search()
{
	char key[11];
	cout<<"\nEnter KEY:";
	cin>>key;
	ifstream fin;
	fin.open("student");
	while(!fin.eof())
	{
		fin>>buf;
		if(fin.fail())
		break;
		unpack();
		if(!strcmp(usn,key))
		{
			cout<<"\nUSN :"<<usn<<"\nNAME :"<<name<<"\nAGE :"<<age<<endl;
			fin.close();
			return;
		}
	}
	cout<<"\n NO REC FOUND";
	fin.close();
}
void student::modify()
{
			
	char key[11];
	cout<<"\nEnter KEY:";
	cin>>key;
	fstream f;
	f.open("student",ios::in|ios::out);
	while(!f.eof())
	{
		f>>buf;
		if(f.fail())
		break;
		unpack();
		if(!strcmp(usn,key))
		{
			cout<<"FOUND!!\n";
			cout<<"Enter NAME:";
			cin>>name;
			cout<<"Enter AGE :";
			cin>>age;
			pack();
			f.seekp((int)f.tellg()-len,ios::beg);
			f<<buf;
			f.close();
			return;
		}
	}
	cout<<"\n NO REC FOUND";
	f.close();
}
int main()
{
	student s;
	int ch;
	do
	{
		cout<<"CHOOSE"<<endl<<"1.ADD\n2.DISPLAY\n3.SEARCH\n4.MODIFY\n5.EXIT\n";
		cin>>ch;	
		switch(ch)
		{
			case 1: s.add();
				break;
			case 2: s.display();
				break;
			case 3: s.search();
				break;
			case 4: s.modify();
				break;
			case 5: break;
			default : cout<<"\nwrong choice \n";
				 break;
		}
	}while(ch!=5);
}	

	
	
