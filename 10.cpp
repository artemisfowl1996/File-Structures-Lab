#include<iostream>
#include<stdlib.h>
using namespace std;

struct Node
{	
int elements[5];
Node* link[5];
Node* parent;
int level;
};
int cur_level=0;
Node *create_node()
{
Node *node=new Node;
for(int i=0;i<5;i++)
{
node->elements[i]=-1;
node->link[i]=NULL;
}
node->parent=NULL;
node->level=0;
return node;
}
Node * search(Node * root, int depth,int key)
{
Node *cur=root;
if(depth==0)
return root;
int i=0,j;
while(i<depth)
{
for(j=0;j<=4;j++)
{
if(cur->elements[j]==-1)
{
cur=cur->link[j-1];
break;
}
if(key<=cur->elements[j])
{
cur=cur->link[j];
break;
}
}
i++;
}
return cur;
}
int search(Node * root, int key, int index[],int & k)
{
Node * cur=root;
int i=0,j;
while(i<cur_level)
{
for(j=0;j<=4;j++)
{
if(cur->elements[j]==-1)
{
if(j==0)
return 0;
cur=cur->link[j-1];
index[k++]=j-1;
break;
}
if(key<=cur->elements[j])
{
index[k++]=j;
cur=cur->link[j];
break;
}
}
i++;
}
for(j=0;j<4;j++)
if(key==cur->elements[j])
{
index[k++]=j;
return 1;
}
return 0;
}
void update(Node * cur,int old_key,int new_key)
{
Node *par=cur->parent;
int i;
if(par==NULL)
return;
for(i=0;i<5;i++)
if(par->elements[i]==old_key)
break;
par->elements[i]=new_key;
if(par->elements[i+1]==-1)
update(par,old_key,new_key);
}
void display(Node * root)
{
Node *q[100];
Node *cur;
int r=-1,f=0,i=0,j=0;
q[++r]=root;
cout<<"\nthe tree:";
cout<<"\nlevel:"<<i<<endl;
while(r>=f)
{
cur=q[f++];
if(cur->level!=i)
cout<<"\nlevel:"<<++i<<endl;
for(j=0;j<4;j++)
{
if(cur->elements[j]!=-1)
{
cout<<" "<<cur->elements[j];
if(cur->link[j]!=NULL)
q[++r]=cur->link[j];
}
else
break;
}
cout<<"\t";
}
}
void update_level(Node *cur)
{
cur->level++;
for(int i=0;i<5;i++)
if(cur->link[i]!=NULL)
update_level(cur->link[i]);
}
Node *insert(Node *root, int depth,int key,Node *child)
{
int flag=0,i,j;
Node *cur=search(root,depth,key);
for(i=0;i<5;i++)
{
if(cur->elements[i]==-1)
break;
}
if(i==4)
flag=1;
for(j=i;j>0;j--)
{
if(key<cur->elements[j-1])
{
cur->elements[j]=cur->elements[j-1];
cur->link[j]=cur->link[j-1];
}
else
{
cur->elements[j]=key;
cur->link[j]=child;
if(child!=NULL)
child->parent=cur;
break;
}
}
if(j==0)
{
cur->elements[j]=key;
cur->link[j]=child;
if(child!=NULL)
child->parent=cur;
}
if(j!=0 && cur->elements[j+1]==-1)
update(cur,cur->elements[j-1],cur->elements[j]);
if(flag==1)
{
if(j==4)
update(cur,cur->elements[3],cur->elements[4]);
if(cur->level==0)
{
cur_level++;
Node *new_root=create_node();
new_root->elements[0]=cur->elements[4];
new_root->link[0]=cur;
cur->parent=new_root;
root=new_root;
update_level(cur);
}
Node *new_cur=create_node();
for(j=0;j<3;j++)
{
new_cur->elements[j]=cur->elements[j];
new_cur->link[j]=cur->link[j];
}
for(j=3;j<5;j++)
{
cur->elements[j-3]=cur->elements[j];
cur->elements[j]=-1;
cur->link[j-3]=cur->link[j];
cur->link[j]=NULL;
}
cur->elements[2]=-1;
cur->link[2]=NULL;
if(new_cur->link[0]!=NULL && new_cur->link[1]!=NULL && new_cur->link[2]!=NULL)
{
new_cur->link[0]->parent=new_cur;
new_cur->link[1]->parent=new_cur;
new_cur->link[2]->parent=new_cur;
}
new_cur->level=cur->level;
root=insert(root,new_cur->level-1, new_cur->elements[2],new_cur);
}
return root;
}
int main()
{
int choice,key,flag=0,k;
Node *root=create_node();
//clrscr();
for(;;)
{
cout<<"\n1:insert 2:search 3:display 4:exit\n";
cout<<"enter the choice:\n";
cin>>choice;
switch(choice)
{
case 1:cout<<"enter the key to be inserted:";
       cin>>key;
       root=insert(root,cur_level,key,NULL);
       break;
case 2:cout<<"enter the key to be searched:";
       cin>>key;
       int index[100];
       k=0;
       flag=search(root,key,index,k);
       if(flag)
       {
       cout<<"the element found!!\nthe path used is:0";
       for(int i=0;i<k-1;i++)
       cout<<" "<<index[i];
       }
       else
       cout<<"element not found!!\n";
       break;
case 3:display(root);
       break;
case 4:exit(0);
       break;
default:cout<<"wrong input!!";
}
}
return 0;
}
