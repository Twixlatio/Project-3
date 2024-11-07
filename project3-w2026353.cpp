#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

// TODO define your book structure or container
// Using a Book struct to store the information of every book
struct Book 
{
    int id;
    std::string title;
    std::string author;
    float price;
    int yearPublished;
    int pageCount;
    std::string genre;
    std::string summary;
    int copies;
    std::string edition;
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
        std::getline(ss, tmp, ',');
        copies = std::stoi(tmp);
        std::getline(ss, edition);

        // Declare and populate new Book Struct
        Book book = {id++, title, author, price, yearPublished, pageCount, genre, summary, copies, edition};
        // Add the book to the container
        books.push_back(book);
    }

    // close file and return vector of books
    file.close();
    return books;
}

// Using a Magazine class to store the information of every magazine
class Magazine
{
private:
    int id; // id starts right after the ids of the books
    std::string title;
    std::string edition;
    int issue;
    int yearPublished;
    std::string monthPublished;
    float price;
    int pageCount;
    std::string genre;
    std::string summary;
    int copies;

public:
    // Constructor sets all the values of the private member variables 
    Magazine(int i, std::string t, std::string e, int is, int y, std::string m, float p, int pg, std::string g, std::string s, int c) 
        : id(i), title(t), edition(e), issue(is), yearPublished(y), monthPublished(m), price(p), pageCount(pg), genre(g), summary(s), copies(c) {}
    
    // Getter functions for all the private member variables 
    int getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getEdition() const { return edition; }
    int getIssue() const { return issue; }
    int getYearPublished() const { return yearPublished; }
    std::string getMonthPublished() const { return monthPublished; }
    float getPrice() const { return price; }
    int getPageCount() const { return pageCount; }
    std::string getGenre() const { return genre; }
    std::string getSummary() const { return summary; }
    int getCopies() const { return copies; }

    // One setter function just to set the variable 'copies'
    void setCopies(int val) { copies = val; }
};

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
        Magazine magazine(id++, title, edition, issue, yearPublished, monthPublished, price, pageCount, genre, summary, copies);
        magazines.push_back(magazine);
    }

    // close file and return vector of magazines
    file.close();
    return magazines;
}

// Function Prototypes
void displayAllBookInfo(Book book);
void displayAllMagInfo(Magazine magazine);
void displayPartialBookInfo(Book book);
void displayPartialMagInfo(Magazine magazine);
std::vector<Book> alphabetizeBook(std::vector<Book> books);
std::vector<Magazine> alphabetizeMag(std::vector<Magazine> mags);
std::vector<Book> findQueriedBook(std::vector<Book> books, std::string keyword);
std::vector<Magazine> findQueriedMag(std::vector<Magazine> mags, std::string keyword);
std::vector<Magazine> filterNewestIssue(std::vector<Magazine> magazines, std::string title);
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

    // the ID is set to the the size of the books vector because the magazines need to have unique IDs greater than the books
    ID = books.size();

    std::cout << "\n=== 2. Load the list of magazines from the `magazines.csv` file ===" << std::endl;
    // Calls function to load magazines from csv file into a vector called 'magazines' of the type Magazine 
    std::vector<Magazine> magazines = loadMagazinesFromCSV("magazines.csv", ID);

    std::cout << "\n=== 3. Print the full information of the first book in the list (ID=0) (ID, title, author, other metadata..., and number of copies) ===" << std::endl;
    // Displaying the full information of the book at index 0 in 'books'
    displayAllBookInfo(books[0]);

    std::cout << "\n=== 4. Print the full information of *any* Magazine in the list (ID, title, edition, other metadata..., and number of copies) ===" << std::endl;
    // Displaying the full information of the magazine at index 0 in 'magazines'
    displayAllMagInfo(magazines[0]);

    std::cout << "\n=== 5. Print the full list of books in short-form format ===" << std::endl;
    // Going through all the books in 'books' and displaying it in short-form format
    for(Book book:books)
        displayPartialBookInfo(book);

    std::cout << "\n=== 6. Print the full list of magazines in short-form format ===" << std::endl;
    // Going through all the magazines in 'magazines' and displaying it in short-form format
    for(Magazine magazine:magazines)
        displayPartialMagInfo(magazine);

    std::cout << "\n=== 7. Print the latest edition of the magazine 'Scientific Wonders' short-form format ===" << std::endl;
    // Storing the filtered vector of type Magazine into sortedScienceMags and displaying it in short-form format
    std::vector<Magazine> sortedScienceMags = filterNewestIssue(magazines, "Scientific Wonders");
    displayPartialMagInfo(sortedScienceMags[0]);

    std::cout << "\n=== 8. Print list in short-form format of all items that cost more than '$17.00' ===" << std::endl;
    // Going through all books and magazines and checking the condition that it costs more than 17 and displaying 
    // the information in short-form format if it is
    for(Book book:books)
    {
        if(book.price > 17)
            displayPartialBookInfo(book);
    }
    for(Magazine magazine:magazines)
    {
        if(magazine.getPrice() > 17)
            displayPartialMagInfo(magazine);
    }

    std::cout << "\n=== 9. Print list in short-form format of all items that belong to the 'Fantasy' genre ===" << std::endl;
    // Going through all books and magazines and checking the condition that it is a 'Fantasy' genre and displaying 
    // the information in short-form format if it is
    for(Book book:books)
    {
        if(book.genre == "Fantasy")
            displayPartialBookInfo(book);
    }
    for(Magazine magazine:magazines)
    {
        if(magazine.getGenre() == "Fantasy")
            displayPartialMagInfo(magazine);
    }

    std::cout << "\n=== 10. Print list in short-form format of all magazines with the title 'Culinary Trends', and are '11th' edition ===" << std::endl;
    // Going through all magazines and checking the condition that it titled 'Culinary Trends" and is a '11th' edition and displaying
    // the information in short-form format if it is
    for(Magazine magazine:magazines)
    {
        if(magazine.getTitle() == "Culinary Trends" && magazine.getEdition() == "11th")
            displayPartialMagInfo(magazine);
    }

    std::cout << "\n=== 11. Print list in short-form format of all items published between '1900' and '1950' ===" << std::endl;
    // Going through all books and magazines and checking the condition that it is published between 1900 and 1950 and displaying 
    // the information in short-form format if it is
    for(Book book:books)
    {
        if(book.yearPublished >= 1900 && book.yearPublished <= 1950)
            displayPartialBookInfo(book);
    }
    for(Magazine magazine:magazines)
    {
        if(magazine.getYearPublished() >= 1900 && magazine.getYearPublished() <= 1950)
            displayPartialMagInfo(magazine);
    }

    std::cout << "\n=== 12. Print list in short-form format of all 'paperback' Books authored by 'Suzanne Collins' ===" << std::endl;
    // Going through all books and checking the condition that it is a 'paperback' edition and by 'Suzanne Collins' and displaying 
    // the information in short-form format if it is
    for(Book book:books)
    {
        if((book.edition == "paperback" || book.edition == "Paperback") && book.author == "Suzanne Collins")
            displayPartialBookInfo(book);
    }

    std::cout << "\n=== 13. Print list in short-form format of all items whose titles contain the text 'and' ===" << std::endl;
    // Storing the books and magazines with titles containing the text 'and' in their respective vectors
    std::vector<Book> quieredBooks = findQueriedBook(books, "and");
    std::vector<Magazine> quieredMags = findQueriedMag(magazines, "and");
    
    // Going through all books and magazines in the quiered vectors and displaying the information in short-form format
    for(Book quieryBook:quieredBooks)
        displayPartialBookInfo(quieryBook);
    for(Magazine quieryMag:quieredMags)
        displayPartialMagInfo(quieryMag);

    std::cout << "\n=== 14. Print list in short-form format of all 'hardcover' Books ===" << std::endl;
    // Going through all books and checking the condition that it is a 'hardcover' edition and displaying 
    // the information in short-form format if it is
    for(Book book:books)
    {
        if(book.edition == "hardcover" || book.edition == "Hardcover")
            displayPartialBookInfo(book);
    }

    std::cout << "\n=== 15. Perform a 'sale' of all magazines with the title 'Culinary Trends', and are '11th' edition (remember to update 'sales.txt')===" << std::endl;
    // Going through all magazines and checking the condition that it titled 'Culinary Trends" and is a '11th' edition 
    // and performing a sale on the magazine if it is
    for(Magazine magazine:magazines)
    {
        if(magazine.getTitle() == "Culinary Trends" && magazine.getEdition() == "11th")
            magSale(magazines, magazine);
    }

    std::cout << "\n=== 16. Perform a 'sale' of all items published between '1900' and '1950' ===" << std::endl;
    // Going through all books and magazines and checking the condition that it is published between 1900 and 1950 and performing sales on them if it is
    for(Book book:books)
    {
        if(book.yearPublished >= 1900 && book.yearPublished <= 1950)
            bookSale(books, book);
    }
    for(Magazine magazine:magazines)
    {
        if(magazine.getYearPublished() >= 1900 && magazine.getYearPublished() <= 1950)
            magSale(magazines, magazine);
    }

    std::cout << "\n=== 17. Print the full info of all books in alphabetical order ===" << std::endl;
    // Sorting the books alphabetically and storing it in alphabetizedFullBooks and then displaying the full information 
    // of those books
    std::vector<Book> alphabetizedFullBooks = alphabetizeBook(books);
    for(Book alphaBook:alphabetizedFullBooks)
    {
        displayAllBookInfo(alphaBook);
    }

    std::cout << "\n=== 18. Print the full info for *all* magazines in alphabetical order, also sorted by latest issue first ===" << std::endl;
    // Sorting the magazines alphabetically first and storing it in alphabetizedFullMags
    std::vector<Magazine> alphabetizedFullMags = alphabetizeMag(magazines);

    // Store every unique title of the magazines in alphabetizedFullMags
    std::vector<std::string> titles;
    titles.push_back(alphabetizedFullMags[0].getTitle()); // storing the first title 
    std::string currentTitle = alphabetizedFullMags[0].getTitle(); // using currentTitle as a tracker to avoid adding repeated titles
    for(Magazine mag:alphabetizedFullMags)
    {
        // if the current mag title is not equal to the currentTitle then add the title of the mag and set the currentTitle to equal to 
        // the mag title then loop 
        if(mag.getTitle() != currentTitle)
        {
            titles.push_back(mag.getTitle());
            currentTitle = mag.getTitle();
        }
    }

    // Going through all the titles in 'titles' and performing a filter to sort it from latest to oldest issues and display the full
    // information of the magazine and loop
    std::vector<Magazine> alphabetizedAndLatest;
    for(std::string t:titles)
    {
        alphabetizedAndLatest = filterNewestIssue(magazines, t);
        for(Magazine mag:alphabetizedAndLatest)
            displayAllMagInfo(mag);
    }
}

// Displays the full book information in the format KEY: VALUE | for book
void displayAllBookInfo(Book book)
{
    std::cout << "ID: " << book.id << " | Type: Book" << " | Title: " << book.title << " | Author: " << book.author << " | Price: $" << book.price << " | Year Published: " 
              << book.yearPublished << " | Page Count: " << book.pageCount << " | Genre: " << book.genre << " | Summary: " << book.summary << " | Edition: " << book.edition
              << " | Copies: " << book.copies << std::endl;
}

// Displays the full magazine information in the format KEY: VALUE | for magazine
void displayAllMagInfo(Magazine magazine)
{
    std::cout << "ID: " << magazine.getId() << " | Type: Magazine" << " | Title: " << magazine.getTitle() << " | Edition: " << magazine.getEdition() << " | Issue: " << 
              magazine.getIssue() << " | Year Published: " << magazine.getYearPublished() << " | Month Published: " << magazine.getMonthPublished() << " | Price: $" << 
              magazine.getPrice() << " | Page Count: " << magazine.getPageCount() << " | Genre: " << magazine.getGenre() << " | Summary: " << magazine.getSummary() 
              << " | Copies: " << magazine.getCopies() << std::endl;
}

// Displays the partial book information in the format TYPE; TITLE; AUTHOR; YEAR PUBLISHED; COPIES for book 
void displayPartialBookInfo(Book book)
{
    std::cout << "Book; " << book.title << "; " << book.author << "; " << book.yearPublished << "; " << book.copies << std::endl;
}

// Displays the partial magazine information in the format TYPE; TITLE; EDITION; ISSUE; YEAR PUBLISHED; COPIES for magazine
void displayPartialMagInfo(Magazine magazine)
{
    std::cout << "Magazine; " << magazine.getTitle() << "; " << magazine.getEdition() << "; " << magazine.getIssue() << "; " 
    << magazine.getYearPublished() << "; " << magazine.getCopies() << std::endl;
}

// Returns a vector array with corresponding books that has been alphabetized by title
std::vector<Book> alphabetizeBook(std::vector<Book> books)
{
    // Create a vector of type string called 'alphabetized' to store the book titles from 'books'
    std::vector<std::string> alphabetized;
    // Create a vector of type Book called 'alphabetizedBooks' to store the Books in alphabetized order
    std::vector<Book> alphabetizedBooks;

    // Populating 'alphabetized' with all the book titles in 'books'
    for(Book book:books)
        alphabetized.push_back(book.title);

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
            if(books[j].title == alphabetized[i])
            {
                alphabetizedBooks.push_back(books[j]);
                break;
            }
        }
    }
    
    return alphabetizedBooks; // Vector 'alphabetizedBooks' is returned
}

// Returns a vector array with corresponding magazines that has been alphabetized by title
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

// Returns a vector array with corresponding books that have the queried keyword in its title
std::vector<Book> findQueriedBook(std::vector<Book> books, std::string keyword)
{
    // Create a vector of type Book called 'queriedBooks' to store the Books with keyword
    std::vector<Book> queriedBooks;

    // For every book, we search for the keyword in the book title and if it is found
    // then the book is added to 'queriedBooks'
    for(Book book:books)
    {
        size_t found = book.title.find(keyword);
        if(found!=std::string::npos)
            queriedBooks.push_back(book);
    }
    
    return queriedBooks; // Vector 'queriedBooks' is returned
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

