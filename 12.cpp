#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#define LEN 40

using namespace std;

class student
{
   	 char name[25],usn[11],age[3],str[LEN];
    	char buf[100][LEN];
   	 int n,avail_list;
    	fstream file;
    	void pack();
    	void unpack();
   	 public:  student();
		~student();
             	void add();
           		  void del();
};

void student::pack()
{
    	strcpy(str,usn);
    	strcat(str,"|");
    	strcat(str,name);
   	 strcat(str,"|");
   	 strcat(str,age);
    	for(int i=strlen(str);i<LEN-1;i++)
        		strcat(str,"#");
}

void student::unpack()
{
   	 strcpy(usn,strtok(str,"|"));
    	strcpy(name,strtok(NULL,"|"));
    	strcpy(age,strtok(NULL,"#"));
}

student::student()
{
 	 int i;
 	 file.open("student.txt",ios::in);
  	for(i=0;;i++)
  	{
    		file>>buf[i];
   		 if(file.fail())
         			break;

    		if(i==0)
    		{
        			avail_list=atoi(buf[i]);
    		}
  	}
  	if(i==0)
  	{
    		 n=i+1;
     		avail_list=-1;
  	}
  	else
  	{
     		n=i;
  	}
  	file.close();
}

void student::add()
{
 	 cout<<"Enter USN: ";
  	cin>>usn;
  	cout<<"Enter name: ";
  	cin>>name;
 	 cout<<"Enter age: ";
  	cin>>age;
 	 pack();
 	 if(avail_list==-1)
  	{
    		 strcpy(buf[n++],str);
  	}
  	else
  	{
     		int temp=atoi(&(buf[avail_list][1]));
    		 strcpy(buf[avail_list],str);
     		avail_list=temp;
     		n++;
     	 }
	cout<<"Student record added\n";
}

void student::del()
{
  	char key[11];
	char temp_buf[LEN],*usn_ptr;
  	cout<<"Enter the USN to be deleted: ";
  	cin>>key;
  	for(int i=1;i<n;i++)
  	{

      		strcpy(temp_buf,buf[i]);
       		usn_ptr=strtok(temp_buf,"|");
      		if(!strcmp(key,usn_ptr))
            {
          			int temp=avail_list;
          			avail_list=i;
                    sprintf(buf[i],"*%d",temp);
          			cout<<"Student record deleted\n";
                    return;
       		}
    }
        	 cout<<"Student record not found\n";
  }
student :: ~student()
{
	int i;
	sprintf(buf[0],"%d",avail_list);
	file.open("student.txt",ios::out|ios::trunc);
	for(i=0;i<n;i++)
		file<<buf[i]<<endl;
	file.close();
}

int main()
{
   	int ch;
   	student s;
   	cout<<"1.Add 2.Delete 3.Exit\n";
  	while(1)
   	{
		cout<<"Enter the choice: ";
  		 cin>>ch;
		switch(ch)
   		{
           			case 1: s.add();
                   			break;
           			case 2: s.del();
  		                	 break;
           			case 3: return 0;
                   			break;
           			default : cout<<"Wrong choice!";
                     			break;
    		}
    	}
   	 return 0;
}
