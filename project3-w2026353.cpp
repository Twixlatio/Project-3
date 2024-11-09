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

    virtual void displayLongForm() const = 0;
    virtual void displayShortForm() const = 0;

    

    virtual ~BasicInformation() = default;
};

class Book : public BasicInformation
{
private: 
    std::string type = "Book";
    std::string author;
public:
    Book(int i, std::string t, int y, float p, int pg, std::string g, std::string s, std::string e, int c, std::string a) : BasicInformation(i, t, y, p, pg, g, s, e, c)
    {
        author = a;
    }

    std::string getType() const { return type; }
    std::string getAuthor() const { return author; }

    void displayLongForm() const override
    {
        std::cout << "ID: " << getId() << " | Type: " << type << " | Title: " << getTitle() << " | Author: " << author << " | Price: $" << getPrice() << " | Year Published: " 
              << getYearPublished() << " | Page Count: " << getPageCount() << " | Genre: " << getGenre() << " | Summary: " << getSummary() << " | Edition: " << getEdition()
              << " | Copies: " << getCopies() << std::endl;
    }

    void displayShortForm() const override
    {
        std::cout << type << "; " << getTitle() << "; " << author << "; " << getYearPublished() << "; " << getCopies() << std::endl;
    }

    std::vector<Book> alphabetize(std::vector<Book> books)
    {
        // Create a temporary vector 'alphabetized' to store the sorted books
        std::vector<Book> alphabetized = books;

        // Use std::sort to sort the 'alphabetized' vector by the title field
        // use a lambda function for the std::sort comparator, compare object titles directly.
        std::sort(alphabetized.begin(), alphabetized.end(), [](const Book& a, const Book& b) {
            return a.getTitle() < b.getTitle(); // Compare books by title
        });

        return alphabetized; // The sorted vector is returned
    }

    // Returns a vector array with corresponding books that have the queried keyword in its title
    std::vector<Book> findQueried(std::vector<Book> books, std::string keyword)
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
    std::string type = "Magazine";
    std::string author;
    int issue;
    std::string monthPublished;
public:
    Magazine(int i, std::string t, int y, float p, int pg, std::string g, std::string s, std::string e, int c, std::string a, int is, std::string m) : BasicInformation(i, t, y, p, pg, g, s, e, c)
    {
        author = a;
        issue = is;
        monthPublished = m;
    }

    std::string getType() const { return type; }
    std::string getAuthor() const { return author; }
    int getIssue() const { return issue; }
    std::string getMonthPublished() const { return monthPublished; }

    void displayLongForm() const override
    {
        std::cout << "ID: " << getId() << " | Type: " << type << " | Title: " << getTitle() << " | Edition: " << getEdition() << " | Issue: " << 
              issue << " | Year Published: " << getYearPublished() << " | Month Published: " << monthPublished << " | Price: $" << 
              getPrice() << " | Page Count: " << getPageCount() << " | Genre: " << getGenre() << " | Summary: " << getSummary() 
              << " | Copies: " << getCopies() << std::endl;
    }

    void displayShortForm() const override
    {
        std::cout << type << "; " << getTitle() << "; " << getEdition() << "; " << issue << "; " << getYearPublished() << "; " << getCopies() << std::endl;
    }

    std::vector<Magazine> alphabetize(std::vector<Magazine> mags)
    {
        // Create a temporary vector 'alphabetized' to store the sorted books
        std::vector<Magazine> alphabetized = mags;

        // Use std::sort to sort the 'alphabetized' vector by the title field
        // use a lambda function for the std::sort comparator, compare object titles directly.
        std::sort(alphabetized.begin(), alphabetized.end(), [](const Magazine& a, const Magazine& b) {
            return a.getTitle() < b.getTitle(); // Compare books by title
        });

        return alphabetized; // The sorted vector is returned
    }
    
    // Returns a vector array with corresponding magazines that have the queried keyword in its title
    std::vector<Magazine> findQueried(std::vector<Magazine> mags, std::string keyword)
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
    std::string type = "Children's Book";
    std::string author;
    std::string targetAge;
public:
    ChildrensBook(int i, std::string t, int y, float p, int pg, std::string g, std::string s, std::string e, int c, std::string a, std::string ta) : BasicInformation(i, t, y, p, pg, g, s, e, c) 
    {
        author = a;
        targetAge = ta;
    }

    std::string getType() const { return type; }
    std::string getAuthor() const { return author; }
    std::string getTargetAge() const { return targetAge; }

    void displayLongForm() const override
    {
        std::cout << "ID: " << getId() << " | Type: " << type << " | Title: " << getTitle() << " | Author: " << author << " | Price: $" << 
              getPrice() << " | Year Published: " << getYearPublished() << " | Page Count: " << getPageCount() << " | Genre: " << getGenre() << " | Summary: " << getSummary() 
              << " | Edition: " << getEdition() << " | Target Age: " << targetAge << " | Copies: " << getCopies() << std::endl;
    }

    void displayShortForm() const override
    {
        std::cout << type << "; " << getTitle() << "; " << author << "; " << getYearPublished() << "; " << getCopies() << std::endl;
    }

    std::vector<ChildrensBook> alphabetize(std::vector<ChildrensBook> childrensBooks)
    {
        // Create a temporary vector 'alphabetized' to store the sorted books
        std::vector<ChildrensBook> alphabetized = childrensBooks;

        // Use std::sort to sort the 'alphabetized' vector by the title field
        // use a lambda function for the std::sort comparator, compare object titles directly.
        std::sort(alphabetized.begin(), alphabetized.end(), [](const ChildrensBook& a, const ChildrensBook& b) {
            return a.getTitle() < b.getTitle(); // Compare books by title
        });

        return alphabetized; // The sorted vector is returned
    }
    
    // Returns a vector array with corresponding magazines that have the queried keyword in its title
    std::vector<ChildrensBook> findQueried(std::vector<ChildrensBook> childrensBooks, std::string keyword)
    {
        // Create a vector of type Magazine called 'queriedMags' to store the Magazines with keyword
        std::vector<ChildrensBook> queriedCBooks;

        // For every magazine, we search for the keyword in the magazine title and if it is found
        // then the magazine is added to 'queriedMags'
        for(ChildrensBook cbook:childrensBooks)
        {
            size_t found = cbook.getTitle().find(keyword);
            if(found!=std::string::npos)
                queriedCBooks.push_back(cbook);
        }

        return queriedCBooks; // Vector 'queriedMags' is returned
    }
};

class PuzzlesAndGames : public BasicInformation
{
private: 
    std::string type = "Puzzle/Game Book";
    std::string author;
    std::string types;
public:
    PuzzlesAndGames(int i, std::string t, int y, float p, int pg, std::string g, std::string s, std::string e, int c, std::string a, std::string ty) : BasicInformation(i, t, y, p, pg, g, s, e, c)
    {
        author = a;
        types = ty;
    }

    std::string getType() const { return type; }
    std::string getAuthor() const { return author; }
    std::string getTypes() const { return types; }

    void displayLongForm() const override
    {
        std::cout << "ID: " << getId() << " | Type: " << type << " | Title: " << getTitle() << " | Author: " << author << " | Price: $" << 
              getPrice() << " | Year Published: " << getYearPublished() << " | Page Count: " << getPageCount() << " | Genre: " << getGenre() << " | Type: " 
              << types << " | Summary: " << getSummary() << " | Edition: " << getEdition() << " | Copies: " << getCopies() << std::endl;
    }

    void displayShortForm() const override
    {
        std::cout << type << "; " << getTitle() << "; " << author << "; " << getYearPublished() << "; " << getCopies() << std::endl;
    }

    std::vector<PuzzlesAndGames> alphabetize(std::vector<PuzzlesAndGames> pAndGs)
    {
        // Create a temporary vector 'alphabetized' to store the sorted books
        std::vector<PuzzlesAndGames> alphabetized = pAndGs;

        // Use std::sort to sort the 'alphabetized' vector by the title field
        // use a lambda function for the std::sort comparator, compare object titles directly.
        std::sort(alphabetized.begin(), alphabetized.end(), [](const PuzzlesAndGames& a, const PuzzlesAndGames& b) {
            return a.getTitle() < b.getTitle(); // Compare books by title
        });

        return alphabetized; // The sorted vector is returned
    }
    
    // Returns a vector array with corresponding magazines that have the queried keyword in its title
    std::vector<PuzzlesAndGames> findQueried(std::vector<PuzzlesAndGames> pAndGs, std::string keyword)
    {
        // Create a vector of type Magazine called 'queriedMags' to store the Magazines with keyword
        std::vector<PuzzlesAndGames> queriedPAndGs;

        // For every magazine, we search for the keyword in the magazine title and if it is found
        // then the magazine is added to 'queriedMags'
        for(PuzzlesAndGames pAndG:pAndGs)
        {
            size_t found = pAndG.getTitle().find(keyword);
            if(found!=std::string::npos)
                queriedPAndGs.push_back(pAndG);
        }

        return queriedPAndGs; // Vector 'queriedMags' is returned
    }
};

class CookBook : public BasicInformation
{
private: 
    std::string type = "Cookbook";
    std::string author;
    std::string cuisineType;
public:
    CookBook(int i, std::string t, int y, float p, int pg, std::string g, std::string s, std::string e, int c, std::string a, std::string ct) : BasicInformation(i, t, y, p, pg, g, s, e, c)
    {
        author = a;
        cuisineType = ct;
    }

    std::string getType() const { return type; }
    std::string getAuthor() const { return author; }
    std::string getCuisineType() const { return cuisineType; }

    void displayLongForm() const override
    {
        std::cout << "ID: " << getId() << " | Type: " << type << " | Title: " << getTitle() << " | Author: " << author << " | Price: $" << 
              getPrice() << " | Year Published: " << getYearPublished() << " | Page Count: " << getPageCount() << " | Genre: " << getGenre() << " | Cuisine Type: " 
              << cuisineType << " | Summary: " << getSummary() << " | Edition: " << getEdition() << " | Copies: " << getCopies() << std::endl;
    }

    void displayShortForm() const override
    {
        std::cout << type << "; " << getTitle() << "; " << author << "; " << getYearPublished() << "; " << getCopies() << std::endl;
    }

    std::vector<CookBook> alphabetize(std::vector<CookBook> cookbooks)
    {
        // Create a temporary vector 'alphabetized' to store the sorted books
        std::vector<CookBook> alphabetized = cookbooks;

        // Use std::sort to sort the 'alphabetized' vector by the title field
        // use a lambda function for the std::sort comparator, compare object titles directly.
        std::sort(alphabetized.begin(), alphabetized.end(), [](const CookBook& a, const CookBook& b) {
            return a.getTitle() < b.getTitle(); // Compare books by title
        });

        return alphabetized; // The sorted vector is returned
    }
    
    // Returns a vector array with corresponding magazines that have the queried keyword in its title
    std::vector<CookBook> findQueried(std::vector<CookBook> cookbooks, std::string keyword)
    {
        // Create a vector of type Magazine called 'queriedMags' to store the Magazines with keyword
        std::vector<CookBook> queriedCookBooks;

        // For every magazine, we search for the keyword in the magazine title and if it is found
        // then the magazine is added to 'queriedMags'
        for(CookBook cookbook:cookbooks)
        {
            size_t found = cookbook.getTitle().find(keyword);
            if(found!=std::string::npos)
                queriedCookBooks.push_back(cookbook);
        }

        return queriedCookBooks; // Vector 'queriedMags' is returned
    }
};

class GraphicNovels : public BasicInformation
{
private: 
    std::string type = "Graphic Novel";
    std::string author;
    std::string artStyle;
    int issue;
public:
    GraphicNovels(int i, std::string t, int y, float p, int pg, std::string g, std::string s, std::string e, int c, std::string a, std::string as, int is) : BasicInformation(i, t, y, p, pg, g, s, e, c)
    {
        author = a;
        artStyle = as;
        issue = is;
    }

    std::string getType() const { return type; }
    std::string getAuthor() const { return author; }
    int getIssue() const { return issue; }
    std::string getArtStyle() const { return artStyle; }

    void displayLongForm() const override
    {
        std::cout << "ID: " << getId() << " | Type: " << type << " | Title: " << getTitle() << " | Author/Illustrator: " << author << " | Price: $" << 
              getPrice() << " | Year Published: " << getYearPublished() << " | Page Count: " << getPageCount() << " | Genre: " << getGenre() << " | Art Style: " 
              << artStyle << " | Summary: " << getSummary() << " | Edition: " << getEdition() << " | Copies: " << getCopies() << std::endl;
    }

    void displayShortForm() const override
    {
        std::cout << type << "; " << getTitle() << "; " << author << "; " << issue << "; " << getYearPublished() << "; " << getCopies() << std::endl;
    }

    std::vector<GraphicNovels> alphabetize(std::vector<GraphicNovels> gNovels)
    {
        // Create a temporary vector 'alphabetized' to store the sorted books
        std::vector<GraphicNovels> alphabetized = gNovels;

        // Use std::sort to sort the 'alphabetized' vector by the title field
        // use a lambda function for the std::sort comparator, compare object titles directly.
        std::sort(alphabetized.begin(), alphabetized.end(), [](const GraphicNovels& a, const GraphicNovels& b) {
            return a.getTitle() < b.getTitle(); // Compare books by title
        });

        return alphabetized; // The sorted vector is returned
    }
    
    // Returns a vector array with corresponding magazines that have the queried keyword in its title
    std::vector<GraphicNovels> findQueried(std::vector<GraphicNovels> gNovels, std::string keyword)
    {
        // Create a vector of type Magazine called 'queriedMags' to store the Magazines with keyword
        std::vector<GraphicNovels> queriedNovels;

        // For every magazine, we search for the keyword in the magazine title and if it is found
        // then the magazine is added to 'queriedMags'
        for(GraphicNovels gNovel:gNovels)
        {
            size_t found = gNovel.getTitle().find(keyword);
            if(found!=std::string::npos)
                queriedNovels.push_back(gNovel);
        }

        return queriedNovels; // Vector 'queriedMags' is returned
    }
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

// Function to read magazines from a CSV file into a vector of Magazine objects
std::vector<ChildrensBook> loadChildrensBooksFromCSV(const std::string& filename, int id) {
    // declare your container that will hold your list of magazines
    std::vector<ChildrensBook> cbooks;

    // open file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return cbooks;
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    // load lines from the CSV file
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        // variables to hold data from CSV file
        std::string title,author,genre,summary,edition,targetAge,tmp;
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
        std::getline(ss, targetAge, ',');
        std::getline(ss, tmp, ',');
        copies = std::stoi(tmp);

        // creating the Magazine object with all the parameters and id increases by 1 after the value of id is stored in the object
        ChildrensBook cbook(id++, title, yearPublished, price, pageCount, genre, summary, edition, copies, author, targetAge);
        cbooks.push_back(cbook);
    }

    // close file and return vector of magazines
    file.close();
    return cbooks;
}

// Function to read magazines from a CSV file into a vector of Magazine objects
std::vector<PuzzlesAndGames> loadPAndGFromCSV(const std::string& filename, int id) {
    // declare your container that will hold your list of magazines
    std::vector<PuzzlesAndGames> pAndGs;

    // open file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return pAndGs;
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    // load lines from the CSV file
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        // variables to hold data from CSV file
        std::string title,author,genre,type,summary,edition,tmp;
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
        std::getline(ss, type, ',');
        std::getline(ss, summary, ',');
        std::getline(ss, edition, ',');
        std::getline(ss, tmp, ',');
        copies = std::stoi(tmp);

        // creating the Magazine object with all the parameters and id increases by 1 after the value of id is stored in the object
        PuzzlesAndGames pAndG(id++, title, yearPublished, price, pageCount, genre, summary, edition, copies, author, type);
        pAndGs.push_back(pAndG);
    }

    // close file and return vector of magazines
    file.close();
    return pAndGs;
}

std::vector<CookBook> loadCookbooksFromCSV(const std::string& filename, int id) {
    // declare your container that will hold your list of magazines
    std::vector<CookBook> cookbooks;

    // open file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return cookbooks;
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    // load lines from the CSV file
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        // variables to hold data from CSV file
        std::string title,author,genre,cuisineType,summary,edition,tmp;
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
        std::getline(ss, cuisineType, ',');
        std::getline(ss, summary, ',');
        std::getline(ss, edition, ',');
        std::getline(ss, tmp, ',');
        copies = std::stoi(tmp);

        // creating the Magazine object with all the parameters and id increases by 1 after the value of id is stored in the object
        CookBook cookbook(id++, title, yearPublished, price, pageCount, genre, summary, edition, copies, author, cuisineType);
        cookbooks.push_back(cookbook);
    }

    // close file and return vector of magazines
    file.close();
    return cookbooks;
}

std::vector<GraphicNovels> loadGraphicNovelsFromCSV(const std::string& filename, int id) {
    // declare your container that will hold your list of magazines
    std::vector<GraphicNovels> graphicNovels;

    // open file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return graphicNovels;
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    // load lines from the CSV file
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        // variables to hold data from CSV file
        std::string title,author,genre,artStyle,summary,edition,tmp;
        float price;
        int yearPublished, pageCount, issue, copies;

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
        std::getline(ss, artStyle, ',');
        std::getline(ss, summary, ',');
        std::getline(ss, tmp, ',');
        issue = std::stoi(tmp);
        std::getline(ss, edition, ',');
        std::getline(ss, tmp, ',');
        copies = std::stoi(tmp);

        // creating the Magazine object with all the parameters and id increases by 1 after the value of id is stored in the object
        GraphicNovels graphicNovel(id++, title, yearPublished, price, pageCount, genre, summary, edition, copies, author, artStyle, issue);
        graphicNovels.push_back(graphicNovel);
    }

    // close file and return vector of magazines
    file.close();
    return graphicNovels;
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

    std::cout << "=== 1. Load Items From Files ===" << std::endl;
    std::vector<BasicInformation*> allItems;
    BasicInformation* temp;
    // Calls function to load books from csv file into a vector called 'books' of the type Book 
    std::vector<Book> books = loadBooksFromCSV("books.csv", ID);
    for(Book &book:books)
    {
        temp = &book;
        allItems.push_back(temp);
    }
    ID = allItems.size();
    std::vector<ChildrensBook> childrensBooks = loadChildrensBooksFromCSV("childrens-books.csv", ID);
    for(ChildrensBook &book:childrensBooks)
    {
        temp = &book;
        allItems.push_back(temp);
    }
    ID = allItems.size();
    std::vector<PuzzlesAndGames> puzzlesAndGames = loadPAndGFromCSV("puzzles-games.csv", ID);
    for(PuzzlesAndGames &book:puzzlesAndGames)
    {
        temp = &book;
        allItems.push_back(temp);
    }
    ID = allItems.size();
    std::vector<CookBook> cookBooks = loadCookbooksFromCSV("cookbooks.csv", ID);
    for(CookBook &book:cookBooks)
    {
        temp = &book;
        allItems.push_back(temp);
    }
    ID = allItems.size();
    std::vector<GraphicNovels> graphicNovels = loadGraphicNovelsFromCSV("graphic-novels.csv", ID);
    for(GraphicNovels &novel:graphicNovels)
    {
        temp = &novel;
        allItems.push_back(temp);
    }
    ID = allItems.size();
    std::vector<Magazine> magazines = loadMagazinesFromCSV("magazines.csv", ID);
    for(Magazine &mag:magazines)
    {
        temp = &mag;
        allItems.push_back(temp);
    }
    ID = allItems.size();

    // std::cout << "\n=== 2. Print full info for all items using a single std container to demonstrate polymorphism ===" << std::endl;
    // for(auto* item:allItems)
    // {
    //     item->displayLongForm();
    // }

    // std::cout << "\n=== 3. Print all items that cost less than $11.00 in short form format ===" << std::endl;
    // for(auto& item:allItems)
    // {
    //     if(item->getPrice() < 11)
    //         item->displayShortForm();
    // }
    
    std::cout << "\n=== 4. Print all items that were published after `2010`, and cost less than $15, and contain the word `and` in the title or summary ===" << std::endl;
    for(auto& item:allItems)
    {
        if(item->getYearPublished() > 2010 && item->getPrice() < 15 && item.findQueried(allItems, "and"))
            item->displayShortForm();
    }
    //std::vector<GraphicNovels> findQueried(std::vector<GraphicNovels> gNovels, std::string keyword)
    //look into how to make findQueried, alphabetize and filter latest issue part of base class 
    
    /*
    std::cout << "=== 5. Print all items that were published before the year 1900 or cost more than $100 ===" << std::endl;
    for(auto& item:allItems)
    {
        if(item.getYearPublished() < 1900 || item.getPrice() > 100)
            item->displayShortForm();
    }

    std::cout << "=== 6. Print all Books and Childrens Books that were published between the years 2018 and 2021, do not include out of stock items ===" << std::endl;
    for(auto& item:allItems)
    {
        if((item.getType() == "Book" || item.getType() == "Children's Book") && (item.getYearPublished() >= 2018 && item.getYearPublished() <= 2021) && item.getCopies() != 0)
            item->displayShortForm();
    }

    std::cout << "=== 7. Print alphabetized list of all items, sorted further by latest issue/edition (for magazines/graphic novels/cookbooks/puzzle books) ===" << std::endl;

    std::cout << "=== 8. Perform a single 'Sale()' of each item which was published before 1900, or cost more than $100 ===" << std::endl;

    std::cout << "=== 9. Perform a 'Sale()' of all items in the inventory by utilizing the `ISellable` interface, using this provided code as-is ===" << std::endl;
    */
}

std::vector<BookInformation*> findQueried(std::vector<BookInformation*> allItems, std::string keyword)
{
        // Create a vector of type Book called 'queriedBooks' to store the Books with keyword
    std::vector<BookInformation*> queriedItems;
    BookInformation* temp;

        // For every book, we search for the keyword in the book title and if it is found
        // then the book is added to 'queriedBooks'
    for(auto& item:allItems)
    {
        size_t found = item->getTitle().find(keyword);
        if(found!=std::string::npos)
            temp = &item;
            queriedItems.push_back(item);
    }
        
    return queriedItems; // Vector 'queriedBooks' is returned
}

/* Professor Comments:
due to a mistake in magSale() on line 562 where you subtract 1 from the number of copies for the magazines, 
except you are operating on a *copy* of the magazine object instead of a reference, updating line 555 to use
a reference "Magazine &mag" and changing your "for" iterator in main() on line 320 to operate on references: 
"for(Magazine &magazine:magazines)" fixes the bug. you have an identical issue with bookSale()
*/

/*
// Performing sale of book if there is atleast one copy of that book
int bookSale(std::vector<Book> &books, Book &book)
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
int magSale(std::vector<Magazine> &mags, Magazine &mag)
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
