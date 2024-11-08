#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

// Overview:
// Books: id, Title,Author,Price,Year Published,Pagecount,Genre,Summary,Edition,Copies
// Children's books: id, Title,Author,Price,Year Published,Pagecount,Genre,Summary,Edition,Target Age,Copies
// Cook books: id, Title,Author,Price,Year Published,Pagecount,Genre,Cuisine Type,Summary,Edition,Copies
// Graphic novels: id, Title,Author/Illustrator,Price,Year Published,Pagecount,Genre,Art Style,Summary,Issue,Edition,Copies
// Magazines: id, Title,Edition,Issue,Year Published,Month Published,Price,Page Count,Genre,Summary,Copies
// Puzzles & Games: id, Title,Author,Price,Year Published,Pagecount,Genre,Type,Summary,Edition,Copies

// Base class basicInformation
class BasicInformation
{
private:
    int id; 
    std::string title;
    int yearPublished;
    float price;
    int pageCount;
    std::string genre;
    std::string summary;
    std::string edition;
    int copies;
public:
    // Constructor sets all the values of the private member variables
    BasicInformation() {}
    BasicInformation(int i, std::string t, int y, float p, int pg, std::string g, std::string s, std::string e, int c) 
        : id(i), title(t), yearPublished(y), price(p), pageCount(pg), genre(g), summary(s), edition(e), copies(c) {}

    // Getter functions for all the private member variables 
    int getId() const { return id; }
    std::string getTitle() const { return title; }
    int getYearPublished() const { return yearPublished; }
    float getPrice() const { return price; }
    int getPageCount() const { return pageCount; }
    std::string getGenre() const { return genre; }
    std::string getSummary() const { return summary; }
    std::string getEdition() const { return edition; }
    int getCopies() const { return copies; }
};

class Book : public BasicInformation
{
private: 
    std::string author;
public:
    Book() {}
    Book(int i, std::string t, int y, float p, int pg, std::string g, std::string s, std::string e, int c, std::string a) 
    {
        BasicInformation(i, t, y, p, pg, g, s, e, c);
        author = a;
    }

    std::string getAuthor() const { return author; }

    void displayLongForm()
    {
        std::cout << "ID: " << this->getId() << " | Type: Book" << " | Title: " << this->getTitle() << " | Author: " << author << " | Price: $" << this->getPrice() << " | Year Published: " 
              << this->getYearPublished() << " | Page Count: " << this->getPageCount() << " | Genre: " << this->getGenre() << " | Summary: " << this->getSummary() << " | Edition: " << this->getEdition()
              << " | Copies: " << this->getCopies() << std::endl;
    }

    void displayShortForm()
    {
        std::cout << "Book; " << getTitle() << "; " << author << "; " << getYearPublished() << "; " << getCopies() << std::endl;
    }

    std::vector<Book> alphabetizeBook(std::vector<Book> books)
    {
    // Create a vector of type string called 'alphabetized' to store the book titles from 'books'
    std::vector<std::string> alphabetized;
    // Create a vector of type Book called 'alphabetizedBooks' to store the Books in alphabetized order
    std::vector<Book> alphabetizedBooks;

    // Populating 'alphabetized' with all the book titles in 'books'
    for(Book book:books)
        alphabetized.push_back(book.getTitle());

    // Performing alphabetical sorting on the strings in 'alphabetized'
    std::sort(alphabetized.begin(), alphabetized.end());

    // Nested for loop going through the size of 'books' twice
    // For every element in 'alphabetized', we loop through 'books' to find a book's title that equals the 
    // the current element in 'alphabetized' and add that book to vector 'alphabetizedBooks' then break out of the 
    // inner for loop to increment to the next element in 'alphabetized'
    for(int i=0; i<books.size(); i++)
    {
        for(int j=0; j<books.size(); j++)
        {
            if(books[j].getTitle() == alphabetized[i])
            {
                alphabetizedBooks.push_back(books[j]);
                break;
            }
        }
    }
    
    return alphabetizedBooks; // Vector 'alphabetizedBooks' is returned
    }

    // Returns a vector array with corresponding books that have the queried keyword in its title
    std::vector<Book> findQueriedBook(std::vector<Book> books, std::string keyword)
    {
        // Create a vector of type Book called 'queriedBooks' to store the Books with keyword
        std::vector<Book> queriedBooks;

        // For every book, we search for the keyword in the book title and if it is found
        // then the book is added to 'queriedBooks'
        for(Book book:books)
        {
            size_t found = book.getTitle().find(keyword);
            if(found!=std::string::npos)
                queriedBooks.push_back(book);
        }
        
        return queriedBooks; // Vector 'queriedBooks' is returned
    }
};

class Magazine : public BasicInformation
{
private: 
    std::string author;
    int issue;
    std::string monthPublished;
public:
    Magazine(int i, std::string t, int y, float p, int pg, std::string g, std::string s, std::string e, int c, std::string a, int is, std::string m) 
    {
        BasicInformation(i, t, y, p, pg, g, s, e, c);
        author = a;
        issue = is;
        monthPublished = m;
    }

    std::string getAuthor() const { return author; }
    int getIssue() const { return issue; }
    std::string getMonthPublished() const { return monthPublished; }

    void displayLongForm()
    {
        std::cout << "ID: " << getId() << " | Type: Magazine" << " | Title: " << getTitle() << " | Edition: " << getEdition() << " | Issue: " << 
              issue << " | Year Published: " << getYearPublished() << " | Month Published: " << monthPublished << " | Price: $" << 
              getPrice() << " | Page Count: " << getPageCount() << " | Genre: " << getGenre() << " | Summary: " << getSummary() 
              << " | Copies: " << getCopies() << std::endl;
    }

    void displayShortForm()
    {
        std::cout << "Magazine; " << getTitle() << "; " << getEdition() << "; " << issue << "; " << getYearPublished() << "; " << getCopies() << std::endl;
    }

    std::vector<Magazine> alphabetizeMag(std::vector<Magazine> mags)
    {
    // Create a vector of type string called 'alphabetized' to store the magazine titles from 'mags'
    std::vector<std::string> alphabetized;
    // Create a vector of type Magazine called 'alphabetizedMags' to store the Magazines in alphabetized order
    std::vector<Magazine> alphabetizedMags;

    // Populating 'alphabetized' with all the magazine titles
    for(Magazine mag:mags)
        alphabetized.push_back(mag.getTitle());

    // Performing alphabetical sorting on the strings in 'alphabetized'
    std::sort(alphabetized.begin(), alphabetized.end());

    // Nested for loop going through the size of 'mags' twice
    // For every element in 'alphabetized', we loop through 'mags' to find a magazines's title that equals the 
    // the current element in 'alphabetized' and add that magazine to vector 'alphabetizedMags' then break out of the 
    // inner for loop to increment to the next element in 'alphabetized'
    for(int i=0; i<mags.size(); i++)
    {
        for(int j=0; j<mags.size(); j++)
        {
            if(mags[j].getTitle() == alphabetized[i])
            {
                alphabetizedMags.push_back(mags[j]);
                break;
            }
        }
    }
    return alphabetizedMags; // Vector 'alphabetizedMags' is returned
    }
    
    // Returns a vector array with corresponding magazines that have the queried keyword in its title
    std::vector<Magazine> findQueriedMag(std::vector<Magazine> mags, std::string keyword)
    {
        // Create a vector of type Magazine called 'queriedMags' to store the Magazines with keyword
        std::vector<Magazine> queriedMags;

        // For every magazine, we search for the keyword in the magazine title and if it is found
        // then the magazine is added to 'queriedMags'
        for(Magazine mag:mags)
        {
            size_t found = mag.getTitle().find(keyword);
            if(found!=std::string::npos)
                queriedMags.push_back(mag);
        }

        return queriedMags; // Vector 'queriedMags' is returned
    }

    // Filters a vector of type Magazine with a specific title in a desceding order with the latest issue of that magazine displayed first 
    // and the oldest issue is last
    std::vector<Magazine> filterNewestIssue(std::vector<Magazine> magazines, std::string title)
    {
        // Creates a vector of type Magazine called titleMagazines to store the magazines with the same title of the parameter 'title'
        std::vector<Magazine> titleMagazines;
        for(Magazine magazine:magazines)
        {
            if(magazine.getTitle() == title)
                titleMagazines.push_back(magazine);
        }

        // Creates a vector of type int to store the numbers of the magazine issues
        std::vector<int> issues;
        for(Magazine magazine:titleMagazines)
            issues.push_back(magazine.getIssue());

        // Sort the numbers from greatest to least
        std::sort(issues.begin(), issues.end(), std::greater<int>());

        // Create a vector of type Magazine called sortedMagazines to store the final sorted magazines of a specific title from latest to oldest issue
        std::vector<Magazine> sortedMagazines;
        // For every element in issue starting from the first element to the last element, go through the magazines in titleMagazines 
        // and check if the issue of the magazine is the same as the value of issue at that index i and if it is add it to the sortedMagazines and loop
        for(int i = 0; i<issues.size(); i++)
        {
            for(Magazine magazine:titleMagazines)
            {
                if(magazine.getIssue() == issues[i])
                    sortedMagazines.push_back(magazine);
            }
        }
        
        return sortedMagazines; // Vector 'sortedMagazines' is returned
    }
};

class ChildrensBook : public BasicInformation
{
private: 
    std::string author;
    int targetAge;
public:
    ChildrensBook(int i, std::string t, int y, float p, int pg, std::string g, std::string s, std::string e, int c, std::string a, int ta) 
    {
        BasicInformation(i, t, y, p, pg, g, s, e, c);
        author = a;
        targetAge = ta;
    }

    std::string getAuthor() const { return author; }
    int getTargetAge() const { return targetAge; }
};

class PuzzlesAndGames : public BasicInformation
{
private: 
    std::string author;
    std::string type;
public:
    PuzzlesAndGames(int i, std::string t, int y, float p, int pg, std::string g, std::string s, std::string e, int c, std::string a, std::string ty) 
    {
        BasicInformation(i, t, y, p, pg, g, s, e, c);
        author = a;
        type = ty;
    }

    std::string getAuthor() const { return author; }
    std::string getType() const { return type; }
};

class CookBook : public BasicInformation
{
private: 
    std::string author;
    std::string cuisineType;
public:
    CookBook(int i, std::string t, int y, float p, int pg, std::string g, std::string s, std::string e, int c, std::string a, std::string ct) 
    {
        BasicInformation(i, t, y, p, pg, g, s, e, c);
        author = a;
        cuisineType = ct;
    }

    std::string getAuthor() const { return author; }
    std::string getCuisineType() const { return cuisineType; }
};

class GraphicNovels : public BasicInformation
{
private: 
    std::string author;
    std::string artStyle;
    int issue;
public:
    GraphicNovels(int i, std::string t, int y, float p, int pg, std::string g, std::string s, std::string e, int c, std::string a, std::string as, int is) 
    {
        BasicInformation(i, t, y, p, pg, g, s, e, c);
        author = a;
        artStyle = as;
        issue = is;
    }

    std::string getAuthor() const { return author; }
    int getIssue() const { return issue; }
    std::string getArtStyle() const { return artStyle; }
};

// Function to read books from a CSV file into a vector of Book structs
// update the return type if you choose to use a different container
std::vector<Book> loadBooksFromCSV(const std::string& filename, int id) {
    // declare your container that will hold your list of books
    std::vector<Book> books;

    // open file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return books;
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    // load lines from the CSV file
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        // variables to hold data from CSV file
        std::string title,author,genre,summary,edition,tmp;
        float price;
        int yearPublished, pageCount, copies;

        // Read and parse each field
        std::getline(ss, title, ',');
        std::getline(ss, author, ',');
        std::getline(ss, tmp, ',');
        price = std::stod(tmp);
        std::getline(ss, tmp, ',');
        yearPublished = std::stoi(tmp);
        std::getline(ss, tmp, ',');
        pageCount = std::stoi(tmp);
        std::getline(ss, genre, ',');
        std::getline(ss, summary, ',');
        std::getline(ss, edition, ',');
        copies = std::stoi(tmp);

        //Title,Author,Price,Year Published,Pagecount,Genre,Summary,Edition,Copies
        //To Kill a Mockingbird,Harper Lee,10.99,1960,281,Fiction,A novel about racial injustice in the Deep South.,hardcover,1

        // Declare and populate new Book Struct
        Book book(id++, title, yearPublished, price, pageCount, genre, summary, edition, copies, author);
        // Add the book to the container
        books.push_back(book);
    }

    // close file and return vector of books
    file.close();
    return books;
}

// Function to read magazines from a CSV file into a vector of Magazine objects
std::vector<Magazine> loadMagazinesFromCSV(const std::string& filename, int id) {
    // declare your container that will hold your list of magazines
    std::vector<Magazine> magazines;

    // open file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return magazines;
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    // load lines from the CSV file
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        // variables to hold data from CSV file
        std::string title,author,genre,summary,edition,monthPublished,tmp;
        float price;
        int yearPublished, pageCount, copies, issue;

        // Read and parse each field
        std::getline(ss, title, ',');
        std::getline(ss, edition, ',');
        std::getline(ss, tmp, ',');
        issue = std::stoi(tmp);
        std::getline(ss, tmp, ',');
        yearPublished = std::stoi(tmp);
        std::getline(ss, monthPublished, ',');
        std::getline(ss, tmp, ',');
        price = std::stod(tmp);
        std::getline(ss, tmp, ',');
        pageCount = std::stoi(tmp);
        std::getline(ss, genre, ',');
        std::getline(ss, summary, ',');
        std::getline(ss, tmp, ',');
        copies = std::stoi(tmp);

        // creating the Magazine object with all the parameters and id increases by 1 after the value of id is stored in the object
        Magazine magazine(id++, title, yearPublished, price, pageCount, genre, summary, edition, copies, author, issue, monthPublished);
        magazines.push_back(magazine);
    }

    // close file and return vector of magazines
    file.close();
    return magazines;
}

class ISellable {
public:
    // getCurrentPrice returns the current price of the item
    virtual float getCurrentPrice() const = 0;
    // sell performs a single "sale" of an item, and returns true if the sale was successful
    // this will return false if the sale fails due to insufficient number of items in inventory
    virtual bool sell() = 0;
};

// Function Prototypes
int bookSale(std::vector<Book> &books, Book book);
int magSale(std::vector<Magazine> &mags, Magazine mag);
void logBook(std::vector<Book> books, Book book);
void logMag(std::vector<Magazine> mags, Magazine mag);

int main() {
    // Every time the program is started, the data in sales.txt is cleared and the file is closed
    std::ofstream saleFile("sales.txt", std::ios::out);
    if(saleFile.is_open())
    {
        saleFile.close();
    }

    // the ID starts at 0
    static int ID = 0;

    std::cout << "=== 1. Load the list of books from the `books.csv` file using a function. ===" << std::endl;
    // Calls function to load books from csv file into a vector called 'books' of the type Book 
    std::vector<Book> books = loadBooksFromCSV("books.csv", ID);

    for(Book book:books)
        book.displayLongForm();

    // the ID is set to the the size of the books vector because the magazines need to have unique IDs greater than the books
    ID = books.size();

    std::cout << "\n=== 2. Load the list of magazines from the `magazines.csv` file ===" << std::endl;
    // Calls function to load magazines from csv file into a vector called 'magazines' of the type Magazine 
    std::vector<Magazine> magazines = loadMagazinesFromCSV("magazines.csv", ID);

    for(Magazine mag:magazines)
        mag.displayLongForm();

}

/*
// Performing sale of book if there is atleast one copy of that book
int bookSale(std::vector<Book> &books, Book book)
{
    // If there is atleast one copy of the book the number of copies of that book is subtracted by 1, 
    // the logBook() function is called, and display a confirmation message that the book is sold. If it can't be sold 
    // and error message is displayed and exit.
    if(book.copies > 0)
    {
        book.copies -= 1;
        logBook(books, book);
        std::cout << "SOLD: " << "Book; " << book.title << "; " << book.author << "; " << book.yearPublished << "; " << book.copies << std::endl;
    }
    else
    {
        std::cout << "ERROR: 0 copies of Book; " << book.title << "; " << book.author << "; " << book.yearPublished << "; " << book.copies << " available" << std::endl;
        return -1;
    }
    return -1;
}

// Performing sale of magazine if there is atleast one copy of that book
int magSale(std::vector<Magazine> &mags, Magazine mag)
{
    // If there is atleast one copy of the magazine the number of copies of that magazine is subtracted by 1, 
    // the logMag() function is called, and display a confirmation message that the magazine is sold. If it can't be sold 
    // and error message is displayed and exit.
    if(mag.getCopies() > 0)
    {
        mag.setCopies((mag.getCopies() - 1));
        logMag(mags, mag);
        std::cout << "SOLD: " << "Magazine; " << mag.getTitle() << "; " << mag.getEdition() << "; " << mag.getIssue() << "; " 
                  << mag.getYearPublished() << "; " << mag.getCopies() << std::endl;
    }
    else
    {
        std::cout << "ERROR: 0 copies of Magazine; " << mag.getTitle() << "; " << mag.getEdition() << "; " << mag.getIssue() << "; " 
                  << mag.getYearPublished() << "; " << mag.getCopies() << " available" << std::endl;
        return -1;
    }
    return -1;
}

// Logging the sales record of books in a txt file called 'sales.txt'
void logBook(std::vector<Book> books, Book book)
{
    // Opening the saleFile called 'sales.txt' in append mode to save the record of every sale in one program run
    // but it is cleared out at the beginning of each program run in main()
    std::ofstream saleFile("sales.txt", std::ios::app);

    // If saleFile is open, log the sale in the format TYPE; TITLE; AUTHOR; YEAR PUBLISHED; COPIES; $PRICE
    if(saleFile.is_open())
    {
        saleFile << "Book; " << book.title << "; " << book.author << "; " << book.yearPublished << "; " << book.copies << "; $" << book.price << std::endl;
    }
    // saleFile is closed
    saleFile.close();
}

// Logging the sales record of magazines in a txt file called 'sales.txt'
void logMag(std::vector<Magazine> mags, Magazine mag)
{
    // Opening the saleFile called 'sales.txt' in append mode to save the record of every sale in one program run
    // but it is cleared out at the beginning of each program run in main()
    std::ofstream saleFile("sales.txt", std::ios::app);

    // If saleFile is open, log the sale in the format TYPE; TITLE; EDITION; ISSUE; YEAR PUBLISHED; COPIES; $PRICE
    if(saleFile.is_open())
    {
        saleFile << "Magazine; " << mag.getTitle() << "; " << mag.getEdition() << "; " << mag.getIssue() << "; " 
                 << mag.getYearPublished() << "; " << mag.getCopies() << "; $" << mag.getPrice() << std::endl;
    }
    saleFile.close();
}
*/
