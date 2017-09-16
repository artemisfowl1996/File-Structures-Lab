#include<iostream>
#include<fstream>
#include<cstring>
#include<errno.h>
using namespace std;
int main()
{
	fstream f1,f2,f3;
	cout<<"Enter 2 files\n";
	char a1[25],a2[25];
	cin>>a1>>a2;
	char buf1[25],buf2[25];
	f1.open(a1,ios::in);
	f2.open(a2,ios::in);
	f3.open("output",ios::out);

	f1>>buf1;
	f2>>buf2;
	if(f1.eof())
	{
		cout<<a1<<"empty\n";
	}
	if(f2.eof())
	{
		cout<<a2<<"empty\n";
	}
	int flag=0;
	while((!f1.eof())&&(!f2.eof()))
	{
		if(strcmp(buf1,buf2)==0)
		{
			f3<<buf1<<endl;
			if(f3.fail()) cout<<"ERROR"<<endl;
			f1>>buf1;
			f2>>buf2;
			flag=1;
			
		}
		else if(strcmp(buf1,buf2)>0)
		{
			f2>>buf2;
			if(f2.eof())
			break;
		}
		else
		{
			f1>>buf1;
			if(f1.eof())
			break;
		}
	}
	if(flag==0)
	{
		cout<<"NO COMMON NAMES\n";
	}
	f1.close();
	f2.close();
	f3.close();
}
	
	
