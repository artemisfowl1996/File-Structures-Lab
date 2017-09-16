#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;
class student
{
	char name[20],usn[11],age[4],str[50],buf[50][20];
	int n;
	ifstream fin;
	ofstream fout;
	void pack();
	void unpack();
	int bin(char *key);
     public:
	student();
	~student();
	void add();
	void del();
	void search();
};
student::student()
{
	int i;
	n=0;
	fin.open("index");
	if(!fin.fail())
	{
		for(i=0;!fin.eof();i++)
		{
			fin>>buf[i];
			if(fin.fail())
				break;
		}
		n=i;
		fin.close();
	}
	fin.open("student");
	fout.open("student",ios::app);
}
void student::pack()
{
        strcpy(str,usn);
        strcat(str,"|");
        strcat(str,name);
        strcat(str,"|");
        strcat(str,age);
        strcat(str,"#");
}
void student::unpack()
{
        strcpy(usn,strtok(str,"|"));
        strcpy(name,strtok(NULL,"|"));
        strcpy(age,strtok(NULL,"#"));
}
void student::add()
{
	int i,j,pos;
	char *t, t1[20];
	cout<<"Enter USN :";
        cin>>usn;
        cout<<"Enter NAME:";
        cin>>name;
        cout<<"Enter AGE :";
        cin>>age;
        pack();
	pos=fout.tellp();
	fout<<str<<endl;
	fout.flush();
	if(n==0)
	{
		sprintf(buf[0],"%s|%d",usn,pos);
		n++;
	}
	else
	{
		for(i=0;i<n;i++)
		{
			strcpy(t1,buf[i]);
			t=strtok(buf[i],"|");
			if(strcmp(usn,t)<0)
			{
				sprintf(buf[i],"%s|%d",usn,pos);
				for(j=n-1;j>i;j--)
				{
					strcpy(buf[j+1],buf[j]);
				}
				strcpy(buf[i+1],t1);
				break;
			}
			else
				strcpy(buf[i],t1);
		}
		if(i==n)
		{
			sprintf(buf[i],"%s|%d",usn,pos);
		}
		cout<<"REC ADDED \n";
		n++;
	}
}
void student::search()
{
	char key[11],temp[20],*t;
	int mid,off;
	cout<<"enter key.. \n";
	cin>>key;
	if((mid=bin(key))==-1)
		cout<<"key not found\n";
	else
	{
		cout<<"FOUND!\n";
		strcpy(temp,buf[mid]);
		t=strtok(temp,"|");
		off=atoi(strtok(NULL,"\n"));
		fin.seekg(off,ios::beg);
		fin>>str;
		unpack();
		cout<<"NAME :" <<name<<endl;
		cout<<"USN  :"<<usn<<endl;
		cout<<"AGE  :"<<age<<endl;
	}
}
void student::del()
{
	char key[11];
	int mid,i;
	cout<<"enter key.. \n";
	cin>>key;
	if((mid=bin(key))==-1)
	{
		cout<<"key not found";
	}
	else
	{
		cout<<"indel\n";
		cout<<buf[mid]<<endl;
		cout<<n<<endl<<mid<<endl;
		while(mid<n-1)
		{
			strcpy(buf[mid],buf[mid+1]);
			mid++;
		}
		n--;
	}
}
int student::bin(char *key)
{
	int h,l,m;
	l=0;
	h=n-1;
	char *usn,temp[20];
	while(l<=h)
	{
		m=(l+h)/2;
		strcpy(temp,buf[m]);
		usn=strtok(temp,"|");
		if(strcmp(key,usn)==0)
		{
			return m;
		}
		else if(strcmp(key,usn)>0)
			l=m+1;
		else 
			h=m-1;
	}
	return -1;
}
		
	
student::~student()
{
	fout.close();
	fout.open("index");
	for(int i=0;i<n;i++)
	{
		fout<<buf[i]<<endl;
	}
	fout.close();
	fin.close();
}
int main()
{
        student s;
        int ch;
        do
        {
                cout<<"CHOOSE"<<endl<<"1.ADD\n2.SEARCH\n3.DELETE\n4.EXIT\n";
                cin>>ch;
                switch(ch)
                {
                        case 1: s.add();
                                break;
                               
                       	case 2: s.search();
				break;
			
			case 3: s.del();
				 break;
			case 4: break;
                        default : cout<<"\nwrong choice \n";
                                 break;
                }
        }while(ch!=4);
}
				
