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

// Base class basicInformation
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

    void setCopies(int c) { copies = c; }

    virtual void displayLongForm() const = 0;
    virtual void displayShortForm() const = 0;
    virtual std::string getType() const = 0;

    bool findQueried(std::string string, std::string keyword)
    {
        size_t found = string.find(keyword);
        if(found!=std::string::npos)
            return true;
        else
            return false;
    }

    void log(std::string message)
    {
        // Opening the saleFile called 'sales.txt' in append mode to save the record of every sale in one program run
        // but it is cleared out at the beginning of each program run in main()
        std::ofstream saleFile("sales.txt", std::ios::app);

        // If saleFile is open, log the sale in the format TYPE; TITLE; EDITION; ISSUE; YEAR PUBLISHED; COPIES; $PRICE
        if(saleFile.is_open())
        {
            saleFile << message << getPrice() << std::endl;
        }
        saleFile.close();
    }

    float getCurrentPrice() const override 
    {
        return getPrice();
    }

    bool sell() override
    {
        std::cout << "Wrong method";
        return false;
    }

    static std::vector<BasicInformation*> alphabetize(std::vector<BasicInformation*> books)
    {
        // Create a temporary vector 'alphabetized' to store the sorted books
        std::vector<BasicInformation*> alphabetized = books;

        // Use std::sort to sort the 'alphabetized' vector by the title field
        // use a lambda function for the std::sort comparator, compare object titles directly.
        std::sort(alphabetized.begin(), alphabetized.end(), [](const BasicInformation* a, const BasicInformation* b) {
            return a->getTitle() < b->getTitle(); // Compare books by title
        });

        return alphabetized; // The sorted vector is returned
    }

    static std::vector<BasicInformation*> filterNewestIssue(std::vector<BasicInformation*> magazines, std::string title)
    {
        // Creates a vector of type Magazine called titleMagazines to store the magazines with the same title of the parameter 'title'
        std::vector<BasicInformation*> titleMagazines;
        for(BasicInformation* magazine:magazines)
        {
            if(magazine->getTitle() == title)
                titleMagazines.push_back(magazine);
        }

        // Creates a vector of type int to store the numbers of the magazine issues
        std::vector<int> issues;
        for(BasicInformation* magazine:titleMagazines)
        {
            issues.push_back(magazine->getIssue());
        }

        // Sort the numbers from greatest to least
        std::sort(issues.begin(), issues.end(), std::greater<int>());

        // Create a vector of type Magazine called sortedMagazines to store the final sorted magazines of a specific title from latest to oldest issue
        std::vector<BasicInformation*> sortedMagazines;
        // For every element in issue starting from the first element to the last element, go through the magazines in titleMagazines 
        // and check if the issue of the magazine is the same as the value of issue at that index i and if it is add it to the sortedMagazines and loop
        for(int i = 0; i<issues.size(); i++)
        {
            for(BasicInformation* magazine:titleMagazines)
            {
                if(magazine->getIssue() == issues[i])
                    sortedMagazines.push_back(magazine);
            }
        }
        
        return sortedMagazines; // Vector 'sortedMagazines' is returned
    }

    static std::vector<BasicInformation*> filterNewestEdition(std::vector<BasicInformation*> magazines, std::string title)
    {
        // Creates a vector of type Magazine called titleMagazines to store the magazines with the same title of the parameter 'title'
        std::vector<BasicInformation*> titleMagazines;
        for(BasicInformation* magazine:magazines)
        {
            if(magazine->getTitle() == title)
                titleMagazines.push_back(magazine);
        }

        // Creates a vector of type int to store the numbers of the magazine issues
        std::vector<int> issues;
        std::vector<BasicInformation*> magazinesWithNoValidEdition;
        for(BasicInformation* magazine:titleMagazines)
        {
            issues.push_back((magazine->getEdition())[0]);
        }
        
        // Sort the numbers from greatest to least
        std::sort(issues.begin(), issues.end(), std::greater<int>());

        // Create a vector of type Magazine called sortedMagazines to store the final sorted magazines of a specific title from latest to oldest issue
        std::vector<BasicInformation*> sortedMagazines;
        // For every element in issue starting from the first element to the last element, go through the magazines in titleMagazines 
        // and check if the issue of the magazine is the same as the value of issue at that index i and if it is add it to the sortedMagazines and loop
        for(int i = 0; i<issues.size(); i++)
        {
            for(BasicInformation* magazine:titleMagazines)
            {
                if((magazine->getEdition())[0] == issues[i])
                    sortedMagazines.push_back(magazine);
            }
        }
        
        return sortedMagazines; // Vector 'sortedMagazines' is returned
    }

    static std::vector<BasicInformation*> alphaAndFilterIssue(std::vector<BasicInformation*> magazines)
    {
        std::vector<BasicInformation*> alphabetizedFullMags = alphabetize(magazines);

        // Store every unique title of the magazines in alphabetizedFullMags
        std::vector<std::string> titles;
        titles.push_back(alphabetizedFullMags[0]->getTitle()); // storing the first title 
        std::string currentTitle = alphabetizedFullMags[0]->getTitle(); // using currentTitle as a tracker to avoid adding repeated titles
        for(BasicInformation* mag:alphabetizedFullMags)
        {
            // if the current mag title is not equal to the currentTitle then add the title of the mag and set the currentTitle to equal to 
            // the mag title then loop 
            if(mag->getTitle() != currentTitle)
            {
                titles.push_back(mag->getTitle());
                currentTitle = mag->getTitle();
            }
        }

        // Going through all the titles in 'titles' and performing a filter to sort it from latest to oldest issues and display the full
        // information of the magazine and loop
        std::vector<BasicInformation*> alphabetizedAndLatest;
        std::vector<BasicInformation*> returned;
        for(std::string t:titles)
        {
            alphabetizedAndLatest = filterNewestIssue(magazines, t);
            for(BasicInformation* mag:alphabetizedAndLatest)
                returned.push_back(mag);
        }
        return returned;
    }

    static std::vector<BasicInformation*> alphaAndFilterEdition(std::vector<BasicInformation*> magazines)
    {
        std::vector<BasicInformation*> alphabetizedFullMags = alphabetize(magazines);

        // Store every unique title of the magazines in alphabetizedFullMags
        std::vector<std::string> titles;
        titles.push_back(alphabetizedFullMags[0]->getTitle()); // storing the first title 
        std::string currentTitle = alphabetizedFullMags[0]->getTitle(); // using currentTitle as a tracker to avoid adding repeated titles
        for(BasicInformation* mag:alphabetizedFullMags)
        {
            // if the current mag title is not equal to the currentTitle then add the title of the mag and set the currentTitle to equal to 
            // the mag title then loop 
            if(mag->getTitle() != currentTitle)
            {
                titles.push_back(mag->getTitle());
                currentTitle = mag->getTitle();
            }
        }

        // Going through all the titles in 'titles' and performing a filter to sort it from latest to oldest issues and display the full
        // information of the magazine and loop
        std::vector<BasicInformation*> alphabetizedAndLatest;
        std::vector<BasicInformation*> returned;
        for(std::string t:titles)
        {
            alphabetizedAndLatest = filterNewestEdition(magazines, t);
            for(BasicInformation* mag:alphabetizedAndLatest)
                returned.push_back(mag);
        }
        return returned;
    }

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

    std::string getType() const override { return type; }
    std::string getAuthor() const { return author; }
    int getIssue() const override { return 0; }

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

    std::string getType() const override { return type; }
    std::string getAuthor() const { return author; }
    int getIssue() const override { return issue; }
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

    // Filters a vector of type Magazine with a specific title in a desceding order with the latest issue of that magazine displayed first 
    // and the oldest issue is last
    // std::vector<Magazine> filterNewestIssue(std::vector<Magazine> magazines, std::string title)
    // {
    //     // Creates a vector of type Magazine called titleMagazines to store the magazines with the same title of the parameter 'title'
    //     std::vector<Magazine> titleMagazines;
    //     for(Magazine magazine:magazines)
    //     {
    //         if(magazine.getTitle() == title)
    //             titleMagazines.push_back(magazine);
    //     }

    //     // Creates a vector of type int to store the numbers of the magazine issues
    //     std::vector<int> issues;
    //     for(Magazine magazine:titleMagazines)
    //         issues.push_back(magazine.getIssue());

    //     // Sort the numbers from greatest to least
    //     std::sort(issues.begin(), issues.end(), std::greater<int>());

    //     // Create a vector of type Magazine called sortedMagazines to store the final sorted magazines of a specific title from latest to oldest issue
    //     std::vector<Magazine> sortedMagazines;
    //     // For every element in issue starting from the first element to the last element, go through the magazines in titleMagazines 
    //     // and check if the issue of the magazine is the same as the value of issue at that index i and if it is add it to the sortedMagazines and loop
    //     for(int i = 0; i<issues.size(); i++)
    //     {
    //         for(Magazine magazine:titleMagazines)
    //         {
    //             if(magazine.getIssue() == issues[i])
    //                 sortedMagazines.push_back(magazine);
    //         }
    //     }
        
    //     return sortedMagazines; // Vector 'sortedMagazines' is returned
    // }

    // std::vector<Magazine> alphaAndFilter(std::vector<Magazine> magazines)
    // {
    //     std::vector<Magazine> alphabetizedFullMags = alphabetize(magazines);

    //     // Store every unique title of the magazines in alphabetizedFullMags
    //     std::vector<std::string> titles;
    //     titles.push_back(alphabetizedFullMags[0].getTitle()); // storing the first title 
    //     std::string currentTitle = alphabetizedFullMags[0].getTitle(); // using currentTitle as a tracker to avoid adding repeated titles
    //     for(Magazine mag:alphabetizedFullMags)
    //     {
    //         // if the current mag title is not equal to the currentTitle then add the title of the mag and set the currentTitle to equal to 
    //         // the mag title then loop 
    //         if(mag.getTitle() != currentTitle)
    //         {
    //             titles.push_back(mag.getTitle());
    //             currentTitle = mag.getTitle();
    //         }
    //     }

    //     // Going through all the titles in 'titles' and performing a filter to sort it from latest to oldest issues and display the full
    //     // information of the magazine and loop
    //     std::vector<Magazine> alphabetizedAndLatest;
    //     std::vector<Magazine> returned;
    //     for(std::string t:titles)
    //     {
    //         alphabetizedAndLatest = filterNewestIssue(magazines, t);
    //         for(Magazine mag:alphabetizedAndLatest)
    //             returned.push_back(mag);
    //     }
    //     return returned;
    // }

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

    std::string getType() const override { return type; }
    std::string getAuthor() const { return author; }
    std::string getTargetAge() const { return targetAge; }
    int getIssue() const override { return 0; }

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

    std::string getType() const override { return type; }
    std::string getAuthor() const { return author; }
    std::string getTypes() const { return types; }
    int getIssue() const override { return 0; }

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

    std::string getType() const override { return type; }
    std::string getAuthor() const { return author; }
    std::string getCuisineType() const { return cuisineType; }
    int getIssue() const override { return 0; }

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

    std::string getType() const override { return type; }
    std::string getAuthor() const { return author; }
    int getIssue() const override { return issue; }
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
    
    // std::vector<GraphicNovels> filterNewestIssue(std::vector<GraphicNovels> magazines, std::string title)
    // {
    //     // Creates a vector of type Magazine called titleMagazines to store the magazines with the same title of the parameter 'title'
    //     std::vector<GraphicNovels> titleMagazines;
    //     for(GraphicNovels magazine:magazines)
    //     {
    //         if(magazine.getTitle() == title)
    //             titleMagazines.push_back(magazine);
    //     }

    //     // Creates a vector of type int to store the numbers of the magazine issues
    //     std::vector<int> issues;
    //     for(GraphicNovels magazine:titleMagazines)
    //         issues.push_back(magazine.getIssue());

    //     // Sort the numbers from greatest to least
    //     std::sort(issues.begin(), issues.end(), std::greater<int>());

    //     // Create a vector of type Magazine called sortedMagazines to store the final sorted magazines of a specific title from latest to oldest issue
    //     std::vector<GraphicNovels> sortedMagazines;
    //     // For every element in issue starting from the first element to the last element, go through the magazines in titleMagazines 
    //     // and check if the issue of the magazine is the same as the value of issue at that index i and if it is add it to the sortedMagazines and loop
    //     for(int i = 0; i<issues.size(); i++)
    //     {
    //         for(GraphicNovels magazine:titleMagazines)
    //         {
    //             if(magazine.getIssue() == issues[i])
    //                 sortedMagazines.push_back(magazine);
    //         }
    //     }
        
    //     return sortedMagazines; // Vector 'sortedMagazines' is returned
    // } 

    // std::vector<GraphicNovels> alphaAndFilter(std::vector<GraphicNovels> magazines)
    // {
    //     std::vector<GraphicNovels> alphabetizedFullMags = alphabetize(magazines);

    //     // Store every unique title of the magazines in alphabetizedFullMags
    //     std::vector<std::string> titles;
    //     titles.push_back(alphabetizedFullMags[0].getTitle()); // storing the first title 
    //     std::string currentTitle = alphabetizedFullMags[0].getTitle(); // using currentTitle as a tracker to avoid adding repeated titles
    //     for(GraphicNovels mag:alphabetizedFullMags)
    //     {
    //         // if the current mag title is not equal to the currentTitle then add the title of the mag and set the currentTitle to equal to 
    //         // the mag title then loop 
    //         if(mag.getTitle() != currentTitle)
    //         {
    //             titles.push_back(mag.getTitle());
    //             currentTitle = mag.getTitle();
    //         }
    //     }

    //     // Going through all the titles in 'titles' and performing a filter to sort it from latest to oldest issues and display the full
    //     // information of the magazine and loop
    //     std::vector<GraphicNovels> alphabetizedAndLatest;
    //     std::vector<GraphicNovels> returned;
    //     for(std::string t:titles)
    //     {
    //         alphabetizedAndLatest = filterNewestIssue(magazines, t);
    //         for(GraphicNovels mag:alphabetizedAndLatest)
    //             returned.push_back(mag);
    //     }
    //     return returned;
    // }

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
        std::getline(ss, tmp, ',');
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

// Function Prototypes
void log(std::string message);

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
    std::vector<BasicInformation*> booksPtr;
    for(Book &book:books)
    {
        temp = &book;
        booksPtr.push_back(temp);
        allItems.push_back(temp);
    }
    ID = allItems.size();
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
    
    // std::cout << "\n=== 4. Print all items that were published after `2010`, and cost less than $15, and contain the word `and` in the title or summary ===" << std::endl;
    // for(auto& item:allItems)
    // {
    //     if(item->getYearPublished() > 2010 && item->getPrice() < 15 && (item->findQueried(item->getTitle(), "and") || item->findQueried(item->getSummary(), "and")))
    //         item->displayShortForm();
    // }

    //std::vector<GraphicNovels> findQueried(std::vector<GraphicNovels> gNovels, std::string keyword)
    //look into how to make findQueried, alphabetize and filter latest issue part of base class 
    
    // std::cout << "\n=== 5. Print all items that were published before the year 1900 or cost more than $100 ===" << std::endl;
    // for(auto& item:allItems)
    // {
    //     if(item->getYearPublished() < 1900 || item->getPrice() > 100)
    //         item->displayShortForm();
    // }

    // std::cout << "\n=== 6. Print all Books and Childrens Books that were published between the years 2018 and 2021, do not include out of stock items ===" << std::endl;
    // for(auto& item:allItems)
    // {
    //     if((item->getType() == "Book" || item->getType() == "Children's Book") && (item->getYearPublished() > 2018 && item->getYearPublished() < 2021) && item->getCopies() != 0)
    //         item->displayShortForm();
    // }

    std::cout << "\n=== 7. Print alphabetized list of all items, sorted further by latest issue/edition (for magazines/graphic novels/cookbooks/puzzle books) ===" << std::endl;
    std::vector<BasicInformation*> alphabetizedItems;

    booksPtr = BasicInformation::alphabetize(booksPtr);
    for(auto* item:booksPtr)
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

    // std::cout << "\n=== 8. Perform a single 'Sale()' of each item which was published before 1900, or cost more than $100 ===" << std::endl;
    // float totalCost = 0;
    // std::vector<BasicInformation*> sellableItems;

    // for(auto& item:allItems)
    // {
    //     if(item->getYearPublished() < 1900 || item->getPrice() > 100)
    //         sellableItems.push_back(item);
    // }

    // for(ISellable *item:sellableItems)
    // {
    //     item->sell();
    // }

    // std::cout << "\n=== 9. Perform a 'Sale()' of all items in the inventory by utilizing the `ISellable` interface, using this provided code as-is ===" << std::endl;
    // for(ISellable *item:allItems)
    // {
    //     if(item->sell())
    //         totalCost += item->getCurrentPrice();
    // }

    // std::cout << "Total Cost: $" << totalCost << std::endl;
}