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
	int rec_count;
	int offt[100];
	
	void pack();
        void unpack();
      public:
	student();
        void add();
	void read();
};
student::student()
{
	fstream f;
	rec_count=1;
	offt[0]=0;
	f.open("student",ios::in|ios::out);
	f>>buf;
	if(!f.fail())
	{
		while(!f.eof())	
		{
			offt[rec_count++]=f.tellg();		
			f>>buf;
		}
	}
	f.close();
}
	

void student::pack()
{
        strcpy(buf,usn);
        strcat(buf,"|");
        strcat(buf,name);
        strcat(buf,"|");
        strcat(buf,age);
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
	offt[rec_count]=fout.tellp();
        fout.open("student",ios::app);
	offt[rec_count++]=fout.tellp();
        fout<<buf<<endl;
        fout.close();
        cout<<"Student REC ADDED";
}
void student::read()
{
	int rrn;
	cout<<"RRN"<<endl;
	cin>>rrn;
	int i;
	if(rrn>rec_count-1)
	{
		cout<<"OUT OF RANGE";
		return;
	}
	ifstream f;
	
	f.open("student");
	f.seekg(offt[rrn],ios::beg);
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

