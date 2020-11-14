#include <bits/stdc++.h>
#include "userdata.cpp"
// book management system. developed by Soumyadeep Ghosh  IT SEM 3 -DDU//


using namespace std;

class book
{
    friend class user;
    int b_id;
    string title;
    int price;
public:
    book()
    {
        b_id=0;
        title="Null";
        price=0;
    }

    //MEMBER FUNCTIONS
    int getdata();
    void putdata();
    void getbook();
    void putbook();
    void search_book(int id);
    bool ispresent(int id);
    void delete_book(int id);
    void modify_book(int id);
    void clear_records();

    bool isempty()
    {
        ifstream is("file1.DAT",ios::in | ios::ate);
        if(is.tellg()==0)
            return true;
        else
            return false;
    }

    int count_book(string s);
};


int main()
{
    book b1;
    int c,id;
    char ch,ch1;

    string str;
    while(c!=7)
    {
        cout<<"----------------Welcome to  Book Management System---------------"<<endl<<endl;
        cout<<"---------------------------------MENU---------------------------------"<<endl;
        cout<<"Enter the number corresponding to the option to perform that function"<<endl;
        cout<<"1. Enter new book record or modify existing record "<<endl<<"2. Display all the book details "<<endl<<"3. Search (by id)"<<endl<<"4. Delete a record "<<endl;
        cout<<"5. Clear records "<<endl<<"6. Check stock of a book "<<endl<<"7. Exit"<<endl;
        cout<<"------------------------------------------------------------------------"<<endl;
        while (!(std::cin >>c)) {
        cin.clear(); //clear bad input flag
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        cout << "Invalid input; please re-enter.\n";
        }
        switch(c)
        {
        case 1:
            system("cls");
            do
            {
                cout<<"------------------------------"<<endl;
                cout<<"Enter book details or ID OF THE BOOK TO BE MODIFIED "<<endl;
                cout<<"------------------------------"<<endl;
                b1.getbook();
                cout<<"Do you want to enter another book data (Y/N)"<<endl;
                cin>>ch;
                system("cls");
            }while( ch == 'Y' || ch == 'y' );
            break;

        case 2:
                system("cls");
                if( b1.isempty()==false)
                   {
                       b1.putbook();
                   }
                else
                    {
                        cout<<"OUTPUT"<<endl;
                        cout<<"Empty record"<<endl;
                    }
                break;

        case 3:
                system("cls");
                if(b1.isempty()==true)
                {
                    cout<<"OUTPUT"<<endl;
                    cout<<"Empty record"<<endl;
                }
                else
                {
                    cout<<"Enter the id of the book you want to search"<<endl;
                    cin>>id;
                    b1.search_book(id);
                }
                break;
        case 4:
                system("cls");
                if(b1.isempty()==true)
                {
                    cout<<"OUTPUT"<<endl;
                    cout<<"Empty record"<<endl;
                }
                else
                {
                    cout<<"-------------------------------------------"<<endl;
                    cout<<"Enter the id of the book you want to remove"<<endl;
                    cout<<"-------------------------------------------"<<endl;
                    cin>>id;
                    b1.delete_book(id);
                }
                break;
        case 5:
              if(b1.isempty()==true)
              {
                  system("cls");
                  cout<<"OUTPUT"<<endl;
                  cout<<"Empty record. Nothing to be cleared"<<endl;
                  break;
              }
              system("cls");
              cout<<"------------------------------------------------------------------------------------"<<endl;
              cout<<"This will permanently delete all the records. Are you sure you want to continue?(Y/N)"<<endl;
              cout<<"------------------------------------------------------------------------------------"<<endl;

              cin>>ch1;
              system("cls");
              if(ch1=='Y'||ch1=='y')
                {
                    b1.clear_records();
                    cout<<"THE EXISTING RECORDS WERE CLEARED!"<<endl;
                }
              else
                {
                      cout<<"OUTPUT"<<endl;
                    cout<<"The records were not deleted"<<endl<<endl;
                }
              break;
        case 6:
            system("cls");
            if(b1.count_book("a")==-1)
            {
                cout<<"OUTPUT"<<endl;
                cout<<"Empty record"<<endl;
                break;
            }
            cout<<"Enter the title of the book whose stock you want to check"<<endl;
            cin.ignore();
            getline(cin,str);
            system("cls");
            cout<<"OUTPUT"<<endl;
            cout<<"The number of books in stock are "<<b1.count_book(str)<<endl<<endl;
            break;

        case 7:
                cout<<"------------------------------------"<<endl;
                cout<<"Thank you for using this application."<<endl<<"------------------------------------"<<endl<<"Developed by Soumyadepp"<<endl;
                exit(0);
        default:
                system("cls");
                cout<<"invalid choice"<<endl;

                break;
        }
    }
    return 0;
}


int book::getdata()
{
    int k;
    char choice;
    cout<<"--------------------------"<<endl;
    cout<<"Enter id,title, and price"<<endl;
    cout<<"--------------------------"<<endl;
    cin>>k;
    while(ispresent(k)==true)
    {
        cout<<"ID DUPLICACY DETECTED. Do you want to modify this file?"<<endl;
        cin>>choice;
        if(choice=='Y'||choice=='y')
        {
            modify_book(k);
            return 1;
        }
        else
            cin>>k;
    }
        b_id=k;
    cin.ignore();
    getline(cin,title);
    cin>>price;
    return 0;
}

void book::putdata()
{
    cout<<"Title : "<<title<<endl<<"ID : "<<b_id<<endl<<"Price : "<<price<<endl;
    cout<<endl<<endl;
}
void book::getbook()
{
    ofstream os("file1.DAT",ios::binary|ios::app|ios::out);
    if(getdata()==0)
    {
        os.write((char*)this,sizeof(*this));
    }
    os.close();
}

void book::putbook()
{
    ifstream is("file1.DAT",ios::binary | ios::in );
    if(!is)
    {
        cout<<"OUTPUT"<<endl;
        cout<<"Cannot open file"<<endl;
        exit(-1);
    }
    cout<<"OUTPUT"<<endl;
    is.read((char*)this,sizeof(*this));
    while(!is.eof())
    {
       putdata();
       is.read((char*)this,sizeof(*this));
    }
    is.close();
}

bool book::ispresent(int id)
{
    ifstream fin("file1.DAT",ios::binary | ios::in);
    if(!fin)
    {
        cout<<"OUTPUT"<<endl;
        cout<<"Cannot open file. FATAL ERROR! EXITING!"<<endl;
        exit(-1);
    }
    fin.read((char*)this,sizeof(*this));
    while(!fin.eof())
    {
        if(id==b_id)
        {
            return true;
        }
        fin.read((char*)this,sizeof(*this));
    }
    fin.close();
    return false;
}
void book::search_book(int id)
{
    ifstream is("file1.DAT",ios::binary | ios::in);

    if(!is)
    {
        cout<<"cannot open file"<<endl;
        exit(-1);
    }

    int counter=0;
    is.read((char*)this,sizeof(*this));
    while(!is.eof())
    {
        if(b_id==id)
        {
            putdata();
            counter++;
            break;
        }
        is.read((char*)this,sizeof(*this));
    }
    if(counter==0)
    {
        cout<<"Book not found"<<endl;
    }
    is.close();
}
void book::delete_book(int id)
{

    int flag = 0;

    ifstream ifs;
    ifs.open("file1.dat", ios::in | ios::binary);

    ofstream ofs;
    ofs.open("temp.dat", ios::out | ios::binary);

    while (!ifs.eof()) {

        ifs.read((char*)this, sizeof(*this));

        if (ifs) {

            if (id == b_id) {
                flag = 1;
                cout<<"OUTPUT"<<endl;
                cout << "The deleted record is \n";

                putdata();
            }
            else {
                ofs.write((char*)this, sizeof(*this));
            }
        }
    }

    ofs.close();
    ifs.close();

    // delete the old file
    remove("file1.dat");

    // rename new file to the older file
    rename("temp.dat", "file1.dat");

    if (flag == 1)
        cout << "\nrecord successfully deleted \n";
    else
        cout << "\nrecord not found \n";
}
int book::count_book(string st)
{
    ifstream fin("file1.DAT",ios::binary | ios::in);
    if(!fin)
    {
          cout<<"OUTPUT"<<endl;
        cout<<"Cannot open file. FATAL ERROR! EXITING!"<<endl;
        exit(-1);
    }
    if(isempty()==true)
    {
        return -1;
    }
    int counter=0;
    fin.read((char*)this,sizeof(*this));
    while(!fin.eof())
    {
        if(st.compare(title)==0)
        {
            counter++;
        }
        fin.read((char*)this,sizeof(*this));
    }
    fin.close();
    return counter;
}
void book::modify_book(int id)
{
    // code to update and modify
    // the content of the binary file
    int pos, flag = 0;

    // rno=9
    fstream fs;
    fs.open("file1.DAT",
            ios::in | ios::binary | ios::out);

    while (!fs.eof()) {

        pos = fs.tellg();

        fs.read((char*)this, sizeof(*this));
        if(fs) {


            if (id == b_id) {
                flag = 1;

                getdata();

                // placing the put(writing) pointer
                // at the starting of the  record
                fs.seekp(pos);

                // writing the object to the file
                fs.write((char*)this, sizeof(*this));

                // display the data
            }
        }
    }
       if(flag==1)
        cout<<"Data successfully updated"<<endl;
       else
        cout<<"Data not found"<<endl;
       fs.close();
}

void book::clear_records()
{
    ofstream os("file1.DAT",ios::binary | ios::trunc);
}
