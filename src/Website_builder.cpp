#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

class list
 {
 public:
   string tag_name;
   string tag;

 }list[10];

int number_of_tags=0;

ofstream fout,fout_elements;
ifstream fin_elements;
string filename;


void menu();
void openwebsite(string);
void openfile();
void menu();
void Elements();
void Elements_tag(string);
void Style();
string available_tags();
void Style_properties(string);
int show_options();
int add_option();
string get_property(int);

int main()
 {
   system("CLS");

   openfile();
   menu();

   return 0;
 }



 void menu()
  {
    int choice;
    system("CLS");

    fout.open(filename+".html", ios::out | ios::app);


    again:
    cout<<"\n 1) Enter Elements";
    cout<<"\n 2) Style Elements";
    cout<<"\n 3) Open Website";
    cout<<"\n 4) Exit";
    cout<<"\n\nEnter your choice: ";cin>>choice;

    switch(choice)
     {
      case 1:Elements();
             fout<<"\n</body>";
             fout.close();
             menu();
             break;

      case 2:Style();
             fout<<"\n</style>\n</head>";
             menu();
             break;

      case 3:fout<<"\n\n"<<"</html>";
             fout.close();
             openwebsite(filename);break;

      case 4:exit(0);

      default:cout<<"\n Invalid Choice. Enter again";goto again;
     }


    fout.close();
  }


  void Elements()
   {
     int choice;
     system("CLS");
     again:
     cout<<"\n 1) Enter a Heading";
     cout<<"\n 2) Enter a paragraph";
     cout<<"\n 3) Go back to Main Menu";
     cout<<"\n\nEnter your choice: ";cin>>choice;

     switch(choice)
      {
       case 1:Elements_tag("h1");Elements();break;
       case 2:Elements_tag("p");Elements();break;
       case 3:break;
       default:cout<<"\n Invalid Choice. Enter again";goto again;
      }

   }

  void Elements_tag(string tag)
   {
     system("CLS");
     string output,text;

      if (tag=="h1")
       { list[number_of_tags].tag_name="Heading"; list[number_of_tags].tag="h1";number_of_tags++; }

      else if (tag=="p")
       { list[number_of_tags].tag_name="Paragraph"; list[number_of_tags].tag="p";number_of_tags++; }

     ofstream fout1;
     fout1.open(filename+".html", ios::out | ios::app);

     cout<<"\n Enter text: ";
     cin.ignore(100, '\n');
     getline(cin,text);

     output="\n<"+tag+">\n"+ text +"\n</"+tag+">\n";
     fout1<<output;

     fout1.close();
   }



 void Style()
  {
    char ans;

    if (number_of_tags==0)
     {
       cout<<"\n Enter a element first. Going back to main menu...\n";
       system("PAUSE");
       cin.get();
       menu();
     }

    again:
    ofstream fout2;
    fout2.open(filename+".html", ios::out | ios::app);
    fout2<<"\n<head>\n<style>";
    fout2.close();

    system("CLS");
    Style_properties(available_tags());

    cout<<"\nStyle more Elements?(Y/N) ";cin>>ans;

    if (ans=='y' || ans=='Y')
     goto again;

  }


  string available_tags()
    {
      int choice;

      for (int j=0; j<number_of_tags; j++)
       {
         cout<<j+1<<") "<<list[j].tag_name<<endl;
       }

       cout<<"\n\nEnter your Choice: ";cin>>choice;
       cin.get();

      return list[choice-1].tag;
    }



  int show_options()
   {
      again:
      system("CLS");
      fin_elements.open("options.txt",ios::in);
      string options;
      int ans;
      ans=1;

     while (!fin_elements.eof())
      {
        getline(fin_elements,options);

        if (options!="")
        cout<<ans<<") "<<options<<endl;
        ans++;
      }

    cout<<"-1) Enter your own Property ";
    fin_elements.close();


    cout<<"\n\n\n Enter your Choice: ";cin>>ans;

     if (ans==-1)
     {
      add_option();
      goto again;
     }

     return ans;
   }


  int add_option()
   {
     fout_elements.open("options.txt",ios::out | ios::app);
     string options;

     cout<<"\n Enter Property: ";cin>>options;
     cin.get();

     fout_elements<<options<<"\n";

     fout_elements.close();

     return 0;
   }


  string get_property(int n)
   {
     string property;
     fin_elements.open("options.txt",ios::in);
     int count=1;

     while (!fin_elements.eof())
      {
         getline(fin_elements,property);
         cin.get();

         if (count==n)
          break;

         count++;
      }

      fin_elements.close();

     return property;
   }


  void Style_properties(string tag)
   {
    string properties,value;
    int choice,j;
    char ans;
    ofstream fout3;
    fout3.open(filename+".html", ios::out | ios::app);
    fout3<< ( "\n"+tag+"{") ;

     again:
     choice=show_options();
     properties=get_property(choice);

     cout<<"\n Enter value: ";
     getline(cin,value);
     cin.get();

     fout3<<properties+": "+value+";";

     cout<<"\nAdd more?(Y/N): ";cin>>ans;

     if (ans=='y' || ans=='Y')
     goto again;

     else
      { fout3<<"}";fout3.close();return; }
   }



 void openfile()
   {
      cout<<"\n Enter filename(no white spaces): ";getline(cin,filename);

      fout.open(filename+".html", ios::out | ios::trunc);

      fout<<"<html>\n<body>\n";

      fout.close();
   }



 void openwebsite(string filename)
  {
    string filepath="G:\\C++ workspace\\" + filename+ ".html";
    const char * c = filepath.c_str();
    LPCTSTR helpFile = c;
    ShellExecute(NULL, "open", helpFile, NULL, NULL, SW_SHOWNORMAL);
    system("PAUSE");
  }