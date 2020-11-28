#include<iostream>
#include<cstdio>
#include<stdio.h>
#include<fstream>
#include<string.h>

using namespace std;
class fir
{
private:
char  crime_type[20], crime_place[20], name[50], address[50],
      colour[10], face[20], incharge_name[20], design[10];
enum  gender{FEMALE,MALE,ERROR};
int   fir_number, height, date,ch2;

public:
void get();
void put();
void insertion();
void display();

	int retfir_number()                 // function for returning fir number
	{
	return(fir_number) ;
	}

	char *retname()                   // function for returning criminal name
	{
	return (name);
	}
};

fstream fs,f,temp;

	void fir::get()
	{
	insertion();
	cout<<"\nEnter the type of crime:\t\t  ";
	cin>>crime_type;
	cout<<"\nEnter at which place crime took place \t\t ";
	cin>>crime_place;
	}


	void fir::put()
	{
	display();
	cout<<"\nType of crime          ==============>>>>> ";
	puts(crime_type);
	cout<<"\nPlace crime took place  =============>>>>> ";
	puts(crime_place);
	}


void fir::insertion()
{
int num=0;
gender choice=ERROR;

cout<<"\nEnter the FIR NUMBER :\t\t ";
cin>>fir_number;

cout<<"\nEnter the name of  criminal :\t\t ";
cin>>name;

cout<<"\nEnter gender(Female=1,Male=2 ) of the criminal:\t\t ";
cin>>num;
   switch(num)
   {
   case 1: choice = FEMALE;
   break;
   case 2: choice = MALE;
   break;
   default:
   cout<<"\nERROR";
   }
   switch(choice)
   {
   case FEMALE: cout<<"You've Entered that the criminal is Female\n ";
   break;
   case MALE:   cout<<"You 've Entered that the criminal is Male\n ";
   break;
   }

cout<<"\nEnter the height of criminal:\t\t ";
cin>>height;

cout<<"\nEnter the colour of the criminal:\t\t ";
cin>>colour;

cout<<"\nFace description of the criminal:\t\t ";
cin>>face;

cout<<"\nEnter the name of the officer who writing FIR \t\t";
cin>>incharge_name;

cout<<"\nEnter your designation: \t\t";
cin>>design;
}


void fir::display()
{
cout<<"\nFir Number                ==============>>>>> "
<<fir_number;

cout<<"\nName of criminal          ==============>>>>> ";
puts(name);

cout<<"\nComplextion of Criminal   ==============>>>>> ";
puts(colour);

cout<<"\nHeight of the criminal    ==============>>>>> ";
cout<<height;

cout<<"\nFace description          ==============>>>>> ";
puts(face);

cout<<"\nName of the officer       ==============>>>>> ";
puts(incharge_name);

cout<<"\nDesignation               ==============>>>>> ";
cout<<design;
}


     void write()
     {
     char ch;
     fir F;
     fs.open("firfile.dat", ios:: out| ios::binary);
     {
     do{
     F.get();
       cout<<"---------------Do you want to save records----------- \n";
       cin>>ch;
       if(ch=='y')
	  {
	  cout<<"#######-----Record have been saved-----#######\n";
	  fs.write((char*)&F,sizeof(F));
	  }
       else
	  {
	  cout<<"Again type ";
	  }
     cout<<"\ndo you want to add more records(n or y)";
     cin>>ch;
     }while(ch=='y'|| ch=='Y');
     }
     fs.close();
     }


void read()
{
fs.open("firfile.dat", ios:: in| ios::binary);
{

fir F;
   if(!fs)
   {
   cout<<"file reading error";
   return;
   }

while(fs.read((char*)&F,sizeof(F)))
{
cout<<"@@@@@@@@------RECORDS---------@@@@@@@@@";
F.put();
}
}
fs.close();
}


void search()
{
char k;
do{
int choice;
fs.open("firfile.dat",ios::in|ios::binary);
{
	cout<<"\nSearch on the basis of: \n -> 1.fir_number ,2.Name \n";
	cout<<"\nEnter your choice -:";
	cin>>choice;
  fir F;
	      switch(choice)
	      {

	 case 1:
		int num;
		cout<<"\nEnter the Fir number";
		cin>>num;
		while(fs.read((char*)&F,sizeof(F)))
		{
		if(F.retfir_number()==num)
		{
			F.put();
		       break;
		}
		else
		cout<<" no records present";
		}
		break;

	case 2:
		char mname[20];
		cout<<"\nEnter name ";
		cin>>mname;
		while(fs.read((char*)&F,sizeof(F)))
		{
			if(strcmp(F.retname(),mname)== 0)   // whose value to be compare will always
			{                                  // will be in right side
			F.put();
			break;
			}
		       else
		       cout<<"   cannot find  ";
		       }
		       break;

			default:
			cout<<"  wrong choice   ";
		       }

}
fs.close();
cout<<"  do you want to search more records(y or n)";
cin>>k;
}while(k=='y'||k=='Y');
}


void delte()
{
   char a;
   char ch[20],found='y';
   int cho,num;
   int choice;
do{

		fs.open("firfile.dat",ios::in|ios::binary);
		temp.open("firtemp.dat",ios::out|ios::binary);
		fir F;
   if(!fs)
   {
   cout<<"file reading error";
   }

		cout<<"\ndelete on the basis of: \n -> 1.fir_number ,2.Name \n";
		cout<<"\nEnter your choice -:";
		cin>>cho;

		switch(cho)
		{
		case 1:
			cout<<"\nEnter the fir no. whose record to be deleted ";
			cin>>num;
			while(fs.read((char*)&F,sizeof(F)))
			{
				if(F.retfir_number()!=num)
				{
					temp.write((char*)&F,sizeof(F));
					break;
				}
			else
			found='n';
			}
			if(found=='n')
			cout<< "   record not found";
			break;

	case 2:
		cout<<"\nEnter the name of the criminal whose record to be deleted ";
		cin>>ch;
		while(fs.read((char*)&F,sizeof(F)))
		{
			if(strcmp(ch,F.retname())!=0)
			{
				temp.write((char*)&F,sizeof(F));
			break;
			}
		else
		found='n';
		}
		if(found=='n')
		cout<<"   record not found";
		break;
	      }
		fs.close();
		temp.close();

		remove("firfile.dat");
		rename("firtemp.dat","firfile.dat");

	cout<<"   do you want to delete more records(y or n)";
	cin>>a;
	}while(a=='y'||a=='Y');
}

void modify()
{
fs.open("firfile.dat",ios::in|ios :: out |ios::binary);
int fno;
cout<<"\nEnter fir no. whose record to be modified:";
cin>>fno;
int fir_count=0;
char found='N';
fir F;
while(fs.read((char*)&F,sizeof(F)))
		{
		if(F.retfir_number()==fno)
		{
			F.get();
		fs.seekg(fir_count*sizeof(F),ios::beg);
		fs.write((char*)&F,sizeof(F));
		found='Y';
		break;
		}
		fir_count++;
		}
		if (found=='Y')
		cout<<"\nrecord updated";
		else
		cout<<"\nrecords not foumd";
		fs.close();
		}




void sort_name()
{
fs.open("firfile.dat",ios::in|ios::binary);
fir F[100];

 if(!fs)
   {
   cout<<"file reading error";
   
   }

int n=0;
while(fs.read((char*)&F[n],sizeof(fir)))
n++;
fir f1;
int i,j;
for(i=1;i<n;i++){
for(j=0;i<n-i;j++){


if(F[j].retfir_number()>F[j+1].retfir_number())
{
f1=F[j];
F[j]=F[j+1];
F[j+1]=f1;
}
}}
fs.close();
fs.open("firfile.dat",ios::out|ios::binary);
i=0;
while(i<n)
{
fs.write((char*)&F[i],sizeof(fir));
++i;
}
cout<<"\n file sorted";
fs.close();
}


void sort_no()
{
fs.open("firfile.dat",ios::in|ios::binary);
fir F[10];

 if(!fs)
   {
   cout<<"file reading error";
   }

int n=0;
while(fs.read((char*)&F[n],sizeof(fir)))
n++;
fir f1;
int i,j;
for(i=1;i<n;i++)
for(j=0;i<n-i;j++)

if(F[j].retfir_number()>F[j+1].retfir_number())
{
f1=F[j];
F[j]=F[j+1];
F[j+1]=f1;
}
fs.close();
fs.open("firfile.dat",ios::out|ios::binary);
i=0;
while(i<n)
{
fs.write((char*)&F[i],sizeof(fir));
++i;
}
cout<<"\n file sorted";
fs.close();
}



int main()
{
	int x,y ;
	int ch,k;
do{
	cout<<"\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
		<<"@@@@@@@@@@@@@@@@  welcome  @@@@@@@@@@@@@@@@\n"
		<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
	cout<<"\n1.FILE A FIR\n";
	cout<<"\n2.CRIMINAL RECORDS\n";
	cout<<"\n3.EXIT\n";
	cout<<"\nenter your choice";
	cin>>x;
	switch(x)
	{

    case 1:
	{
       cout<<"\n-----------------FILE FILIING MENU-------------";
       write();
       break;
	 }

   case 2:
do{
      cout<<"\n\ncriminal record menu\n";
      cout<<"\n1.read\n";
      cout<<"\n2.search\n";
      cout<<"\n3.Delete\n";
      cout<<"\n4.Sort by name.\n";
      cout<<"\n5.Modify\n";
      cout<<"\n6.Quit\n";
      cout<<"\nEnter your choice : ";
      cin>>y;
      switch(y)
		{
			case 1:
			cout<<"\n------------displaying record-----------\n";
			read();
			break;

			case 2:
			cout<<"\n------------searching menu-----------\n";
			search();
			break;

			case 3:
			cout<<"\n-----------deleting menu-------------\n";
			delte();
			break;

			case 4:
			cout<<"\n--------------sorting----------------\n";
			sort_name();
			break;

			case 5:
			cout<<"\n-------------modify-----------------\n";
			modify();
			break;

			case 6:
			cout<<"\n EXIT";
			break;

			default:
			cout<<"wrong choice";
			break;
			}

}while(y!=6);
			case 3:
			exit(0);
			break;
		 }

}while(ch!=3);

}
