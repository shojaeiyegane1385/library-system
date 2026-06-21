#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

enum BookStatus
{
    Available,
    Borrowed
};

class Report;

class Person
{
protected:
    string name;

public:
    Person(string n)
    {
        name = n;
    }

    virtual void showInfo() = 0;

    virtual ~Person()
    {
    }
};

class Book
{
private:
    int id;
    string title;
    string author;
    BookStatus status;

public:
    Book(int i, string t, string a)
    {
        id = i;
        title = t;
        author = a;
        status = Available;
    }

    ~Book()
    {
        cout << "\nBook Object Deleted\n";
    }

    int getId()
    {
        return id;
    }

    string getTitle()
    {
        return title;
    }

    string getAuthor()
    {
        return author;
    }

    BookStatus getStatus()
    {
        return status;
    }

    void borrowBook()
    {
        status = Borrowed;
    }

    void returnBook()
    {
        status = Available;
    }

    friend void displayBook(Book b);
    friend class Report;
};

void displayBook(Book b)
{
    cout << "\n------------------";
    cout << "\nID : " << b.id;
    cout << "\nTitle : " << b.title;
    cout << "\nAuthor : " << b.author;

    if (b.status == Available)
        cout << "\nStatus : Available";
    else
        cout << "\nStatus : Borrowed";

    cout << endl;
}

class Report
{
public:
    void showSecretInfo(Book b)
    {
        cout << "\n------ Report ------";
        cout << "\nBook ID : " << b.id;
        cout << "\nTitle : " << b.title << endl;
    }
};

class Member : public Person
{
private:
    int memberId;

public:
    Member(int id, string n)
        : Person(n)
    {
        memberId = id;
    }

    void showInfo()
    {
        cout << "\nMember ID : " << memberId;
        cout << "\nName : " << name << endl;
    }
};

class Library
{
private:
    vector<Book> books;

public:
    void addBook(Book b)
    {
        books.push_back(b);
    }

    void showBooks()
    {
        if (books.empty())
        {
            cout << "\nNo books available.\n";
            return;
        }

        for (int i = 0; i < books.size(); i++)
        {
            displayBook(books[i]);
        }
    }

    void saveToFile()
    {
        ofstream file("books.txt");

        for (int i = 0; i < books.size(); i++)
        {
            file << "ID : " << books[i].getId() << endl;
            file << "Book Name : " << books[i].getTitle() << endl;
            file << "Author : " << books[i].getAuthor() << endl;

            if (books[i].getStatus() == Available)
                file << "Status : Available" << endl;
            else
                file << "Status : Borrowed" << endl;

            file << "-------------------" << endl;
        }

        file.close();

        cout << "\nInformation saved successfully.\n";
    }

    void readFromFile()
    {
        ifstream file("books.txt");

        string line;

        cout << "\n===== File Content =====\n";

        while (getline(file, line))
        {
            cout << line << endl;
        }

        file.close();
    }

    void clearFile()
    {
        ofstream file("books.txt");

        file.close();

        cout << "\nFile cleared successfully.\n";
    }
};

int main()
{
    Library lib;
    Report report;

    int choice;

    do
    {
        cout << "\n===== Library System =====";
        cout << "\n1. Add Book";
        cout << "\n2. Show Books";
        cout << "\n3. Save To File";
        cout << "\n4. Member Information";
        cout << "\n5. Read File";
        cout << "\n6. Report";
        cout << "\n7. Clear File";
        cout << "\n0. Exit";
        cout << "\nChoice : ";

        cin >> choice;

        if (choice == 1)
        {
            int id;
            string title;
            string author;

            cout << "\nEnter Book ID : ";
            cin >> id;

            cin.ignore();

            cout << "Enter Book Name : ";
            getline(cin, title);

            cout << "Enter Author Name : ";
            getline(cin, author);

            Book b(id,title, author);

            lib.addBook(b);

            cout << "\nBook Added Successfully.\n";
        }

        else if (choice == 2)
        {
            lib.showBooks();
        }

        else if (choice == 3)
        {
            lib.saveToFile();
        }

        else if (choice == 4)
        {
            Member m(1, "yegane shojaei");
            m.showInfo();
        }

        else if (choice == 5)
        {
            lib.readFromFile();
        }

        else if (choice == 6)
        {
            Book b(20, "jafar nejad ghami","programming in c++");
            report.showSecretInfo(b);
        }

        else if (choice == 7)
        {
            lib.clearFile();
        }

        else if (choice == 0)
        {
            cout << "\nExiting Program...\n";
        }

    } while (choice != 0);

    return 0;
}
