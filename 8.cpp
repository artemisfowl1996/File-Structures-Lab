#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
int findmin(char buf[][25],int mn[])
{
	int min;
	min=0;
	for(min=0;min<8;min++)
	{
		if(mn[min])
		break;
	}
	int i;
	for(i=min+1;i<8;i++)
	{
		if(strcmp(buf[min],buf[i])>0&&mn[i])
		{
			min=i;
		}
	}
	return min;
}
	
int main()
{
	char buf[8][25];
	char prev[25]="";
	int mn[8]={1,1,1,1,1,1,1,1};
	char file1[25];
	int of=8;
	int i;
	ifstream fin[8];
	ofstream fout;
	fout.open("out8.txt");
	for(i=0;i<8;i++)
	{
		sprintf(file1,"file%d",i+1);
		fin[i].open(file1);
		fin[i]>>buf[i];
	}
	while(of)
	{
		int m;
		m=findmin(buf,mn);
		if(!strcmp(prev,buf[m]))
		{	
			fin[m]>>buf[m];
			if(fin[m].fail())
			{
				mn[m]=0;
				of--;
			}
		}
		else
		{
			strcpy(prev,buf[m]);
			fout<<buf[m]<<endl;
			fin[m]>>buf[m];
			if(fin[m].fail())
			{
				mn[m]=0;
				of--;
			}
		}
	}
}
			
