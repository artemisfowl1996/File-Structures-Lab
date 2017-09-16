#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
void reverse(char a[])
{
	int len=strlen(a);
	int i,j;
	for(i=0,j=len-1;i<len/2;++i,--j)
	{
		swap(a[i],a[j]);
	}
}
void swap(char &a, char &b)
{
	char temp=a;
	a=b;
	b=temp;
}
	
int main()
{
	while(1)
	{
		char name[10];
		cin>>name;
		if(cin.fail())break;
		reverse(name);
		cout<<name<<endl;
	}
	
}
