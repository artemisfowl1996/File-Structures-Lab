#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#define len 50

using namespace std;

class student{
  char name[10],usn[10],age[3],buf[len];
public:void pack();
void unpack();
void display();
void add();
void search();
void modify();
};

void student::pack(){
  strcpy(buf,name);
  strcat(buf,"|");
  strcat(buf,usn);
  strcat(buf,"|");
  strcat(buf,age);
  strcat(buf,"#");
}

void student::unpack(){
  strcpy(name,strtok(buf,"|"));
  strcpy(usn,strtok(NULL,"|"));
  strcpy(age,strtok(NULL,"#"));
}

void student::add(){
  ofstream fout;
  fout.open("3.txt",ios::out|ios::app);
  cout<<"enter student details\n";
  cout<<"name\t";
  cin>>name;
  cout<<"usn\t";
  cin>>usn;
  cout<<"age\t";
  cin>>age;
  pack();
  fout<<buf;
  fout.close();
  cout<<"RECORD ADDED"<<endl;
}

void student::display(){
  fstream fin;
  fin.open("3.txt",ios::in);
  while(!fin.eof()){
    fin.getline(buf,100,'#');
    if(fin.fail())break;
    unpack();
    cout<<"name\t"<<name<<"\n"<<"usn\t"<<usn<<"\n"<<"age\t"<<age<<"\n";
  }
  fin.close();
}

void student::search(){
  char key[10];
  int i=1;
  cout<<"ENTER THE KEY\n";
  cin>>key;
  fstream fin;
  fin.open("3.txt",ios::in);
  while(!fin.eof()){
    fin.getline(buf,100,'#');
    if(fin.fail())break;
    unpack();
    if(strcmp(key,usn)==0){
      i=0;
      cout<<"record found\n";
      cout<<"name\t"<<name<<"\n"<<"usn\t"<<usn<<"\n"<<"age\t"<<age<<"\n";
      fin.close();
    }
  }
  if(i==1){
    cout<<"record not found\n";
  }
}

void student::modify(){
  fstream fin,fout;
  fin.open("3.txt",ios::in);
  fout.open("stud.txt",ios::out|ios::app);
  char key[10];
  cout<<"enter the key\n";
  cin>>key;
  while(!fin.eof()){
    fin.getline(buf,100,'#');
    if(fin.fail())break;
    unpack();
    if(strcmp(key,usn)==0){
      cout<<"current details are\n";
      cout<<"name\t"<<name<<"\n"<<"usn\t"<<usn<<"\n"<<"age\t"<<age<<"\n";
      cout<<"enter the new details";
      cout<<"name\t";
      cin>>name;
      cout<<"usn\t";
      cin>>usn;
      cout<<"age\t";
      cin>>age;
    }
    pack();
    fout<<buf;
  }
  fin.close();
  fout.close();
  remove("3.txt");
  rename("stud.txt","3.txt");
}

int main(){
  student s;
  int i;
  while(1){
  cout<<"ENTER YOUR CHOICE\n1.ADD\n2.DISPLAY\n3.SEARCH\n4.MODIFY\n5.EXIT\n";
  cin>>i;
  switch(i){
    case 1:s.add();
    break;
    case 2:s.display();
    break;
    case 3:s.search();
    break;
    case 4:s.modify();
    break;
    case 5:exit(0);
  }
}
}
