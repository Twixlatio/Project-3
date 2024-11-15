#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <typeinfo>

class ISellable {
public:
    // getCurrentPrice returns the current price of the item
    virtual float getCurrentPrice() const = 0;
    // sell performs a single "sale" of an item, and returns true if the sale was successful
    // this will return false if the sale fails due to insufficient number of items in inventory
    virtual bool sell() = 0;
};

// Base class BasicInformation inherits from ISellable interface and stores shared attributes of all written material, getter functions, a setter function, virtual functions, 
// and filter functions for access of derived class objects 
class BasicInformation : public ISellable
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
    float getPrice() const { return round(price * 100) / 100; }
    int getPageCount() const { return pageCount; }
    std::string getGenre() const { return genre; }
    std::string getSummary() const { return summary; }
    std::string getEdition() const { return edition; }
    int getCopies() const { return copies; }
    virtual int getIssue() const = 0;

    // One setter function needed to set copies after selling a copy of a written material
    void setCopies(int c) { copies = c; }

    // virtual functions utilized for overriding in each derived class for each unique output message
    virtual void displayLongForm() const = 0;
    virtual void displayShortForm() const = 0;
    virtual std::string getType() const = 0;

    // function utlilized to return whether a keyword is found in the string that is checked
    bool findQueried(std::string string, std::string keyword)
    {
        size_t found = string.find(keyword);
        if(found!=std::string::npos)
            return true;
        else
            return false;
    }

    // used to log information of the sold written material in file sales.txt
    void log(std::string message)
    {
        // Opening the saleFile called 'sales.txt' in append mode to save the record of every sale in one program run
        // but it is cleared out at the beginning of each program run in main()
        std::ofstream saleFile("sales.txt", std::ios::app);

        // If saleFile is open, log the sale with the message given and the price of the written material that called the function
        if(saleFile.is_open())
        {
            saleFile << message << getPrice() << std::endl;
        }
        saleFile.close();
    }

    // Overrides getCurrentPrice() function in ISellable interface
    float getCurrentPrice() const override 
    {
        return getPrice();
    }

    // Overrides the sell() function in ISellable interface, but do not want to use this and rather use the override of the sell() function
    // in the derived class. This function is here only to avoid error because all functions in Isellable must be overriden.
    bool sell() override
    {
        std::cout << "Wrong method";
        return false;
    }

    // Used to alphabetize a vector of type BasicInformation* and return it
    static std::vector<BasicInformation*> alphabetize(std::vector<BasicInformation*> materials)
    {
        // Create a temporary vector 'alphabetized' to store the sorted materials
        std::vector<BasicInformation*> alphabetized = materials;

        // Use std::sort to sort the 'alphabetized' vector by the title field
        // use a lambda function for the std::sort comparator, compare object titles directly.
        std::sort(alphabetized.begin(), alphabetized.end(), [](const BasicInformation* a, const BasicInformation* b) {
            return a->getTitle() < b->getTitle(); // Compare materials by title
        });

        return alphabetized; // The sorted vector is returned
    }

    // Used to filter the newest issue of a vector of type BasicInformation* by title and return it
    static std::vector<BasicInformation*> filterNewestIssue(std::vector<BasicInformation*> materials, std::string title)
    {
        // Creates a vector of type BasicInformation* called titleMaterials to store the materials with the same title of the parameter 'title'
        std::vector<BasicInformation*> titleMaterials;
        for(BasicInformation* material:materials)
        {
            if(material->getTitle() == title)
                titleMaterials.push_back(material);
        }

        // Creates a vector of type int to store the numbers of the material's issues
        std::vector<int> issues;
        for(BasicInformation* material:titleMaterials)
        {
            issues.push_back(material->getIssue());
        }

        // Sort the numbers from greatest to least
        std::sort(issues.begin(), issues.end(), std::greater<int>());

        // Create a vector of type BasicInformation* called sortedMaterials to store the final sorted materials of a specific title from latest to oldest issue
        std::vector<BasicInformation*> sortedMaterials;
        // For every element in issue starting from the first element to the last element, go through the materials in titleMaterials 
        // and check if the issue of the magazine is the same as the value of issue at that index i and if it is add it to the sortedMaterials and loop
        for(int i = 0; i<issues.size(); i++)
        {
            for(BasicInformation* material:titleMaterials)
            {
                if(material->getIssue() == issues[i])
                    sortedMaterials.push_back(material);
            }
        }
        
        return sortedMaterials; // Vector 'sortedMaterials' is returned
    }

    // Used to filter the newest edition of a vector of type BasicInformation* by title and return it
    static std::vector<BasicInformation*> filterNewestEdition(std::vector<BasicInformation*> materials, std::string title)
    {
        // Creates a vector of type BasicInformation* called titleMaterials to store the materials with the same title of the parameter 'title'
        std::vector<BasicInformation*> titleMaterials;
        for(BasicInformation* material:materials)
        {
            if(material->getTitle() == title)
                titleMaterials.push_back(material);
        }

        // Creates a vector of type int to store the numbers of the material's editions
        std::vector<int> editions;
        for(BasicInformation* material:titleMaterials)
        {
            editions.push_back((material->getEdition())[0]);
        }
        
        // Sort the numbers from greatest to least
        std::sort(editions.begin(), editions.end(), std::greater<int>());

        // Create a vector of type BasicInformation* called sortedMaterials to store the final sorted materials of a specific title from latest to oldest issue
        std::vector<BasicInformation*> sortedMaterials;
        // For every element in issue starting from the first element to the last element, go through the materials in titleMaterials 
        // and check if the issue of the material is the same as the value of issue at that index i and if it is add it to the sortedMaterials and loop
        for(int i = 0; i<editions.size(); i++)
        {
            for(BasicInformation* material:titleMaterials)
            {
                if((material->getEdition())[0] == editions[i])
                    sortedMaterials.push_back(material);
            }
        }
        
        return sortedMaterials; // Vector 'sortedMagazines' is returned
    }

    // Used to alphabetize and filter the issue of vector of type BasicInformation* and return it
    static std::vector<BasicInformation*> alphaAndFilterIssue(std::vector<BasicInformation*> materials)
    {
        std::vector<BasicInformation*> alphabetizedFullMats = alphabetize(materials);

        // Store every unique title of the materials in alphabetizedFullMats
        std::vector<std::string> titles;
        titles.push_back(alphabetizedFullMats[0]->getTitle()); // storing the first title 
        std::string currentTitle = alphabetizedFullMats[0]->getTitle(); // using currentTitle as a tracker to avoid adding repeated titles
        for(BasicInformation* mat:alphabetizedFullMats)
        {
            // if the current material title is not equal to the currentTitle then add the title of the material and set the currentTitle to equal to 
            // the material title then loop 
            if(mat->getTitle() != currentTitle)
            {
                titles.push_back(mat->getTitle());
                currentTitle = mat->getTitle();
            }
        }

        // Going through all the titles in 'titles' and performing a filter to sort it from latest to oldest issues and display the full
        // information of the material and loop
        std::vector<BasicInformation*> alphabetizedAndLatest;
        std::vector<BasicInformation*> returned;
        for(std::string t:titles)
        {
            alphabetizedAndLatest = filterNewestIssue(materials, t);
            for(BasicInformation* mat:alphabetizedAndLatest)
                returned.push_back(mat);
        }
        return returned;
    }

    // Used to alphabetize and filter the edition of vector of type BasicInformation* and return it
    static std::vector<BasicInformation*> alphaAndFilterEdition(std::vector<BasicInformation*> materials)
    {
        std::vector<BasicInformation*> alphabetizedFullMats = alphabetize(materials);

        // Store every unique title of the materials in alphabetizedFullMats
        std::vector<std::string> titles;
        titles.push_back(alphabetizedFullMats[0]->getTitle()); // storing the first title 
        std::string currentTitle = alphabetizedFullMats[0]->getTitle(); // using currentTitle as a tracker to avoid adding repeated titles
        for(BasicInformation* mat:alphabetizedFullMats)
        {
            // if the current mag title is not equal to the currentTitle then add the title of the material and set the currentTitle to equal to 
            // the material title then loop 
            if(mat->getTitle() != currentTitle)
            {
                titles.push_back(mat->getTitle());
                currentTitle = mat->getTitle();
            }
        }

        // Going through all the titles in 'titles' and performing a filter to sort it from latest to oldest editions and display the full
        // information of the material and loop
        std::vector<BasicInformation*> alphabetizedAndLatest;
        std::vector<BasicInformation*> returned;
        for(std::string t:titles)
        {
            alphabetizedAndLatest = filterNewestEdition(materials, t);
            for(BasicInformation* mat:alphabetizedAndLatest)
                returned.push_back(mat);
        }
        return returned;
    }

    virtual ~BasicInformation() = default;
};

// Derived class Book inherits from BasicInformation and mostly overrides functions from the base class to display its unique information
class Book : public BasicInformation
{
private: 
    std::string type = "Book";
    std::string author;
public:
    // Constructor that calls the constructor of the base class to set those shared member variables and sets the unique one(s) for this class itself as well
    Book(int i, std::string t, int y, float p, int pg, std::string g, std::string s, std::string e, int c, std::string a) : BasicInformation(i, t, y, p, pg, g, s, e, c)
    {
        author = a;
    }

    // Getter functions 
    std::string getType() const override { return type; }
    std::string getAuthor() const { return author; }
    int getIssue() const override { return 0; }

    // Summary: displayLongForm(), displayShortForm() and sell() are overrided with an implementation specific to this class to display different and unique information
    // for this class
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

    float getCurrentPrice() const override 
    {
        return getPrice();
    }

    bool sell() override
    {
        if(getCopies() > 0)
        {
            setCopies((getCopies() - 1));
            log(type + "; " + getTitle() + "; " + author + "; " + std::to_string(getYearPublished()) + "; " + std::to_string(getCopies()) + "; $");
            std::cout << "SOLD: ";
            displayShortForm();
            return true;
        }
        else
        {
            std::cout << "ERROR: no copies of " << getTitle() << " remaining. " << std::endl;
            return false;
        }
    }
};

// Derived class Magazine inherits from BasicInformation and mostly overrides functions from the base class to display its unique information
class Magazine : public BasicInformation
{
private: 
    std::string type = "Magazine";
    std::string author;
    int issue;
    std::string monthPublished;
public:
    // Constructor that calls the constructor of the base class to set those shared member variables and sets the unique one(s) for this class itself as well
    Magazine(int i, std::string t, int y, float p, int pg, std::string g, std::string s, std::string e, int c, std::string a, int is, std::string m) : BasicInformation(i, t, y, p, pg, g, s, e, c)
    {
        author = a;
        issue = is;
        monthPublished = m;
    }

    // Getter functions 
    std::string getType() const override { return type; }
    std::string getAuthor() const { return author; }
    int getIssue() const override { return issue; }
    std::string getMonthPublished() const { return monthPublished; }

    // Summary: displayLongForm(), displayShortForm() and sell() are overrided with an implementation specific to this class to display different and unique information
    // for this class
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

    float getCurrentPrice() const override 
    {
        return getPrice();
    }

    bool sell() override
    {
        if(getCopies() > 0)
        {
            setCopies((getCopies() - 1));
            log(type + "; " + getTitle() + "; " + getEdition() + "; " + std::to_string(issue) + "; " +  std::to_string(getYearPublished()) + "; " + std::to_string(getCopies()) + "; $");
            std::cout << "SOLD: ";
            displayShortForm();
            return true;
        }
        else
        {
            std::cout << "ERROR: no copies of " << getTitle() << " remaining. " << std::endl;
            return false;
        }
    }
};

// Derived class ChildrensBook inherits from BasicInformation and mostly overrides functions from the base class to display its unique information
class ChildrensBook : public BasicInformation
{
private: 
    std::string type = "Children's Book";
    std::string author;
    std::string targetAge;
public:
    // Constructor that calls the constructor of the base class to set those shared member variables and sets the unique one(s) for this class itself as well
    ChildrensBook(int i, std::string t, int y, float p, int pg, std::string g, std::string s, std::string e, int c, std::string a, std::string ta) : BasicInformation(i, t, y, p, pg, g, s, e, c) 
    {
        author = a;
        targetAge = ta;
    }

    // Getter functions 
    std::string getType() const override { return type; }
    std::string getAuthor() const { return author; }
    std::string getTargetAge() const { return targetAge; }
    int getIssue() const override { return 0; }

    // Summary: displayLongForm(), displayShortForm() and sell() are overrided with an implementation specific to this class to display different and unique information
    // for this class
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

    float getCurrentPrice() const override 
    {
        return getPrice();
    }

    bool sell() override
    {
        if(getCopies() > 0)
        {
            setCopies((getCopies() - 1));
            log(type + "; " + getTitle() + "; " + author + "; " + std::to_string(getYearPublished()) + "; " + std::to_string(getCopies()) + "; $");
            std::cout << "SOLD: ";
            displayShortForm();
            return true;
        }
        else
        {
            std::cout << "ERROR: no copies of " << getTitle() << " remaining. " << std::endl;
            return false;
        }
    }
};

// Derived class PuzzlesAndGames inherits from BasicInformation and mostly overrides functions from the base class to display its unique information
class PuzzlesAndGames : public BasicInformation
{
private: 
    std::string type = "Puzzle/Game Book";
    std::string author;
    std::string types;
public:
    // Constructor that calls the constructor of the base class to set those shared member variables and sets the unique one(s) for this class itself as well
    PuzzlesAndGames(int i, std::string t, int y, float p, int pg, std::string g, std::string s, std::string e, int c, std::string a, std::string ty) : BasicInformation(i, t, y, p, pg, g, s, e, c)
    {
        author = a;
        types = ty;
    }

    // Getter functions 
    std::string getType() const override { return type; }
    std::string getAuthor() const { return author; }
    std::string getTypes() const { return types; }
    int getIssue() const override { return 0; }

    // Summary: displayLongForm(), displayShortForm() and sell() are overrided with an implementation specific to this class to display different and unique information
    // for this class
    void displayLongForm() const override
    {
        std::cout << "ID: " << getId() << " | Type: " << type << " | Title: " << getTitle() << " | Author: " << author << " | Price: $" << 
              getPrice() << " | Year Published: " << getYearPublished() << " | Page Count: " << getPageCount() << " | Genre: " << getGenre() << " | Type: " 
              << types << " | Summary: " << getSummary() << " | Edition: " << getEdition() << " | Copies: " << getCopies() << std::endl;
    }

    void displayShortForm() const override
    {
        std::cout << type << "; " << getTitle() << "; " << getEdition() << "; " << author << "; " << getYearPublished() << "; " << getCopies() << std::endl;
    }

    float getCurrentPrice() const override 
    {
        return getPrice();
    }

    bool sell() override
    {
        if(getCopies() > 0)
        {
            setCopies((getCopies() - 1));
            log(type + "; " + getTitle() + "; " + getEdition() + "; " + author + "; " +  std::to_string(getYearPublished()) + "; " + std::to_string(getCopies()) + "; $");
            std::cout << "SOLD: ";
            displayShortForm();
            return true;
        }
        else
        {
            std::cout << "ERROR: no copies of " << getTitle() << " remaining. " << std::endl;
            return false;
        }
    }
};

// Derived class CookBook inherits from BasicInformation and mostly overrides functions from the base class to display its unique information
class CookBook : public BasicInformation
{
private: 
    std::string type = "Cookbook";
    std::string author;
    std::string cuisineType;
public:
    // Constructor that calls the constructor of the base class to set those shared member variables and sets the unique one(s) for this class itself as well
    CookBook(int i, std::string t, int y, float p, int pg, std::string g, std::string s, std::string e, int c, std::string a, std::string ct) : BasicInformation(i, t, y, p, pg, g, s, e, c)
    {
        author = a;
        cuisineType = ct;
    }

    // Getter functions 
    std::string getType() const override { return type; }
    std::string getAuthor() const { return author; }
    std::string getCuisineType() const { return cuisineType; }
    int getIssue() const override { return 0; }

    // Summary: displayLongForm(), displayShortForm() and sell() are overrided with an implementation specific to this class to display different and unique information
    // for this class
    void displayLongForm() const override
    {
        std::cout << "ID: " << getId() << " | Type: " << type << " | Title: " << getTitle() << " | Author: " << author << " | Price: $" << 
              getPrice() << " | Year Published: " << getYearPublished() << " | Page Count: " << getPageCount() << " | Genre: " << getGenre() << " | Cuisine Type: " 
              << cuisineType << " | Summary: " << getSummary() << " | Edition: " << getEdition() << " | Copies: " << getCopies() << std::endl;
    }

    void displayShortForm() const override
    {
        std::cout << type << "; " << getTitle() << "; " << author << "; " << getEdition() << "; " << getYearPublished() << "; " << getCopies() << std::endl;
    }

    float getCurrentPrice() const override 
    {
        return getPrice();
    }

    bool sell() override
    {
        if(getCopies() > 0)
        {
            setCopies((getCopies() - 1));
            log(type + "; " + getTitle() + "; " + author + "; " + getEdition() + "; " +  std::to_string(getYearPublished()) + "; " + std::to_string(getCopies()) + "; $");
            std::cout << "SOLD: ";
            displayShortForm();
            return true;
        }
        else
        {
            std::cout << "ERROR: no copies of " << getTitle() << " remaining. " << std::endl;
            return false;
        }
    }
};

// Derived class GraphicNovels inherits from BasicInformation and mostly overrides functions from the base class to display its unique information
class GraphicNovels : public BasicInformation
{
private: 
    std::string type = "Graphic Novel";
    std::string author;
    std::string artStyle;
    int issue;
public:
    // Constructor that calls the constructor of the base class to set those shared member variables and sets the unique one(s) for this class itself as well
    GraphicNovels(int i, std::string t, int y, float p, int pg, std::string g, std::string s, std::string e, int c, std::string a, std::string as, int is) : BasicInformation(i, t, y, p, pg, g, s, e, c)
    {
        author = a;
        artStyle = as;
        issue = is;
    }

    // Getter functions 
    std::string getType() const override { return type; }
    std::string getAuthor() const { return author; }
    int getIssue() const override { return issue; }
    std::string getArtStyle() const { return artStyle; }

    // Summary: displayLongForm(), displayShortForm() and sell() are overrided with an implementation specific to this class to display different and unique information
    // for this class
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

    float getCurrentPrice() const override 
    {
        return getPrice();
    }

    bool sell() override
    {
        if(getCopies() > 0)
        {
            setCopies((getCopies() - 1));
            log(type + "; " + getTitle() + "; " + author + "; " + std::to_string(issue) + "; " +  std::to_string(getYearPublished()) + "; " + std::to_string(getCopies()) + "; $");
            std::cout << "SOLD: ";
            displayShortForm();
            return true;
        }
        else
        {
            std::cout << "ERROR: no copies of " << getTitle() << " remaining. " << std::endl;
            return false;
        }
    }
};

// Function to read books from a CSV file into a vector of Book objects
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
        std::getline(ss, tmp, ',');
        copies = std::stoi(tmp);

        // Declare and populate new Book object
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

// Function to read children's books from a CSV file into a vector of ChildrensBook objects
std::vector<ChildrensBook> loadChildrensBooksFromCSV(const std::string& filename, int id) {
    // declare your container that will hold your list of children's books
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

        // creating the ChildrensBook object with all the parameters and id increases by 1 after the value of id is stored in the object
        ChildrensBook cbook(id++, title, yearPublished, price, pageCount, genre, summary, edition, copies, author, targetAge);
        cbooks.push_back(cbook);
    }

    // close file and return vector of children's books
    file.close();
    return cbooks;
}

// Function to read puzzles and games books from a CSV file into a vector of PuzzlesAndGames objects
std::vector<PuzzlesAndGames> loadPAndGFromCSV(const std::string& filename, int id) {
    // declare your container that will hold your list of puzzles and games books
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

        // creating the PuzzlesAndGames object with all the parameters and id increases by 1 after the value of id is stored in the object
        PuzzlesAndGames pAndG(id++, title, yearPublished, price, pageCount, genre, summary, edition, copies, author, type);
        pAndGs.push_back(pAndG);
    }

    // close file and return vector of puzzles and games books
    file.close();
    return pAndGs;
}

// Function to read cookbooks from a CSV file into a vector of CookBook objects
std::vector<CookBook> loadCookbooksFromCSV(const std::string& filename, int id) {
    // declare your container that will hold your list of cookbooks
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

        // creating the CookBook object with all the parameters and id increases by 1 after the value of id is stored in the object
        CookBook cookbook(id++, title, yearPublished, price, pageCount, genre, summary, edition, copies, author, cuisineType);
        cookbooks.push_back(cookbook);
    }

    // close file and return vector of cookbooks
    file.close();
    return cookbooks;
}

// Function to read graphic novels from a CSV file into a vector of GraphicNovels objects
std::vector<GraphicNovels> loadGraphicNovelsFromCSV(const std::string& filename, int id) {
    // declare your container that will hold your list of graphic novels
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

        // creating the GraphicNovels object with all the parameters and id increases by 1 after the value of id is stored in the object
        GraphicNovels graphicNovel(id++, title, yearPublished, price, pageCount, genre, summary, edition, copies, author, artStyle, issue);
        graphicNovels.push_back(graphicNovel);
    }

    // close file and return vector of graphic novels
    file.close();
    return graphicNovels;
}

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
    // NOTE: the following comment explanation is basically the same logic for the other types of objects as well
    // Calls function to load books from csv file into a vector called 'books' of the type Book 
    std::vector<Book> books = loadBooksFromCSV("books.csv", ID);
    // Creates a BasicInformation* vector called booksPtr
    std::vector<BasicInformation*> booksPtr;
    for(Book &book:books) // loops through all books in books and sets a reference BasicInforamtion* to the object and pushes it into the booksPtr and allItems
    {
        temp = &book;
        booksPtr.push_back(temp);
        allItems.push_back(temp);
    }
    ID = allItems.size(); // this allows for the next vector containing the next object type to start at an id after the previous vector
    std::vector<ChildrensBook> childrensBooks = loadChildrensBooksFromCSV("childrens-books.csv", ID);
    std::vector<BasicInformation*> childrensBooksPtr;
    for(ChildrensBook &book:childrensBooks)
    {
        temp = &book;
        childrensBooksPtr.push_back(temp);
        allItems.push_back(temp);
    }
    ID = allItems.size();
    std::vector<PuzzlesAndGames> puzzlesAndGames = loadPAndGFromCSV("puzzles-games.csv", ID);
    std::vector<BasicInformation*> puzzlesAndGamesPtr;
    for(PuzzlesAndGames &book:puzzlesAndGames)
    {
        temp = &book;
        puzzlesAndGamesPtr.push_back(temp);
        allItems.push_back(temp);
    }
    ID = allItems.size();
    std::vector<CookBook> cookBooks = loadCookbooksFromCSV("cookbooks.csv", ID);
    std::vector<BasicInformation*> cookBooksPtr;
    for(CookBook &book:cookBooks)
    {
        temp = &book;
        cookBooksPtr.push_back(temp);
        allItems.push_back(temp);
    }
    ID = allItems.size();
    std::vector<GraphicNovels> graphicNovels = loadGraphicNovelsFromCSV("graphic-novels.csv", ID);
    std::vector<BasicInformation*> graphicNovelsPtr;
    for(GraphicNovels &novel:graphicNovels)
    {
        temp = &novel;
        graphicNovelsPtr.push_back(temp);
        allItems.push_back(temp);
    }
    ID = allItems.size();
    std::vector<Magazine> magazines = loadMagazinesFromCSV("magazines.csv", ID);
    std::vector<BasicInformation*> magazinesPtr;
    for(Magazine &mag:magazines)
    {
        temp = &mag;
        magazinesPtr.push_back(temp);
        allItems.push_back(temp);
    }
    ID = allItems.size();

    std::cout << "\n=== 2. Print full info for all items using a single std container to demonstrate polymorphism ===" << std::endl;
    for(auto* item:allItems) // displays full information of all items
    {
        item->displayLongForm();
    }

    std::cout << "\n=== 3. Print all items that cost less than $11.00 in short form format ===" << std::endl;
    for(auto& item:allItems)
    {
        if(item->getPrice() < 11) // checks if the item is less than $11 and displays in short-form
            item->displayShortForm();
    }
    
    std::cout << "\n=== 4. Print all items that were published after `2010`, and cost less than $15, and contain the word `and` in the title or summary ===" << std::endl;
    for(auto& item:allItems)
    {
        // checks if the item is published after 2010, cost less than $15, and either the title or summary have the keyword 'and'
        if(item->getYearPublished() > 2010 && item->getPrice() < 15 && (item->findQueried(item->getTitle(), "and") || item->findQueried(item->getSummary(), "and")))
            item->displayShortForm();
    }
    
    std::cout << "\n=== 5. Print all items that were published before the year 1900 or cost more than $100 ===" << std::endl;
    for(auto& item:allItems)
    {
        if(item->getYearPublished() < 1900 || item->getPrice() > 100) // checks if item is published before 1900 or cost more than $100
            item->displayShortForm();
    }

    std::cout << "\n=== 6. Print all Books and Childrens Books that were published between the years 2018 and 2021, do not include out of stock items ===" << std::endl;
    for(auto& item:allItems)
    {
        // checks if item is a Book or Children's book, published between year 2018-2021 and is in stock 
        if((item->getType() == "Book" || item->getType() == "Children's Book") && (item->getYearPublished() > 2018 && item->getYearPublished() < 2021) && item->getCopies() != 0)
            item->displayShortForm();
    }

    std::cout << "\n=== 7. Print alphabetized list of all items, sorted further by latest issue/edition (for magazines/graphic novels/cookbooks/puzzle books) ===" << std::endl;
    std::vector<BasicInformation*> alphabetizedItems;
    // NOTE: the following comment explanation is basically the same logic for the other types of objects as well
    // alphabetize the bookPtr which comprises of BookInformation* pointers to the book object
    booksPtr = BasicInformation::alphabetize(booksPtr); 
    for(auto* item:booksPtr) // go through each item in booksPtr and add the alphabetized vector into alphabetizedItems
        alphabetizedItems.push_back(item);

    childrensBooksPtr = BasicInformation::alphabetize(childrensBooksPtr);
    for(auto* item:childrensBooksPtr)
        alphabetizedItems.push_back(item);

    puzzlesAndGamesPtr = BasicInformation::alphaAndFilterEdition(puzzlesAndGamesPtr);
    for(auto* item:puzzlesAndGamesPtr)
        alphabetizedItems.push_back(item);

    cookBooksPtr = BasicInformation::alphaAndFilterEdition(cookBooksPtr);
    for(auto* item:cookBooksPtr)
        alphabetizedItems.push_back(item);

    graphicNovelsPtr = BasicInformation::alphaAndFilterEdition(graphicNovelsPtr);
    for(auto* item:graphicNovelsPtr)
        alphabetizedItems.push_back(item);

    magazinesPtr = BasicInformation::alphaAndFilterIssue(magazinesPtr);
    for(auto* item:magazinesPtr)
        alphabetizedItems.push_back(item);

    alphabetizedItems = BasicInformation::alphabetize(alphabetizedItems);
    for(auto* item:alphabetizedItems)
    {
        item->displayShortForm();
    }

    std::cout << "\n=== 8. Perform a single 'Sale()' of each item which was published before 1900, or cost more than $100 ===" << std::endl;
    float totalCost = 0;
    std::vector<BasicInformation*> sellableItems;

    for(auto& item:allItems) 
    {
        if(item->getYearPublished() < 1900 || item->getPrice() > 100) // check if the item is published before 1900 and cost more than $100 and add to sellableItems
            sellableItems.push_back(item);
    }

    for(ISellable *item:sellableItems) // go through each item in sellableItems and sell it
    {
        item->sell();
    }

    std::cout << "\n=== 9. Perform a 'Sale()' of all items in the inventory by utilizing the `ISellable` interface, using this provided code as-is ===" << std::endl;
    for(ISellable *item:allItems)
    {
        if(item->sell()) // sells the item and if it was sellable and the sell() function returned true (meaning the sale was successful) then add the item's price into totalCost 
            totalCost += item->getCurrentPrice();
    }

    std::cout << "Total Cost: $" << totalCost << std::endl; // displays total cost of the sales of all items in inventory
}