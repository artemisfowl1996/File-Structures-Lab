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
	void read();
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
void student::read()
{
	int rrn;
	cout<<"RRN"<<endl;
	cin>>rrn;
	int n=0;
	int i;

	ifstream fin;
	fin.open("student");
	if(!fin.fail())
	{
		for(i=0;!fin.eof();i++)
		{
			fin>>buf;
			if(fin.fail())
				break;
		}	
		n=i-1;
		fin.close();
	}
	if(rrn>n)
	{
		cout<<"OUT OF RANGE";
		return;
	}
	ifstream f;
	int off=(len+1)*rrn;
	
	f.open("student");
	f.seekg(off,ios::beg);
	//f.seekg(off,ios::beg);
	f>>buf;
	unpack();
	cout<<"\nUSN:"<<usn<<endl<<"NAME:"<<name<<endl<<"AGE:"<<age<<endl;
}
int main()
{
        student s;
        int ch;
        do
        {
                cout<<"CHOOSE"<<endl<<"1.ADD\n2.READ\n3.EXIT\n";
                cin>>ch;
                switch(ch)
                {
                        case 1: s.add();
                                break;
                               
                        case 2: s.read();
				break;
			
			case 3: break;
                        default : cout<<"\nwrong choice \n";
                                 break;
                }
        }while(ch!=3);
}

