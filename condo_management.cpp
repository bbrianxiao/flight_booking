#include <iostream>
#include <exception>
#include <vector>
using namespace std;

string leftTrim(string str);
string rightTrim(string str);
string toLowerCase(string str);
bool stringToNumber(string numberString, int *number);
bool isValidNumber(string numberString);
bool isValidEmailAddress(string emailAddress);

class MyException : public exception
{
private:
    string exceptionMsg;

public:
    MyException(string msg)
    {
        this->exceptionMsg = msg;
    };

    virtual const char *what() const throw()
    {
        const char *c = exceptionMsg.c_str();
        return c;
    }
};

class Occupant
{
private:
    string name;
    string phoneNumber;
    string email;
    int age;
    string unitNumber;
    string residenceType;

public:
    Occupant() {}

    Occupant(string name, string phoneNumber, string email, int age, string unitNumber, string residenceType)
    {
        this->name = name;
        this->phoneNumber = phoneNumber;
        this->email = email;
        this->age = age;
        this->unitNumber = unitNumber;
        this->residenceType = residenceType;
    }

    string getName()
    {
        return this->name;
    }

    string getPhoneNumber()
    {
        return this->phoneNumber;
    }

    string getEmail()
    {
        return this->email;
    }

    int getAge()
    {
        return this->age;
    }

    string getUnitNumber()
    {
        return this->unitNumber;
    }

    string getResidenceType()
    {
        return this->residenceType;
    }

    void setName(string name)
    {
        this->name = name;
    }

    void setPhoneNumber(string phoneNumber)
    {
        this->phoneNumber = phoneNumber;
    }

    void setEmail(string email)
    {
        this->email = email;
    }

    void setAge(int age)
    {
        this->age = age;
    }

    void setUnitNumber(string unitNumber)
    {
        this->unitNumber = unitNumber;
    }

    void setResidenceType(string residenceType)
    {
        this->residenceType = residenceType;
    }

    // print the Occupant information on screen
    void display()
    {
        string phoneNumber = this->getPhoneNumber();
        string formattedPhoneNumber = "(" + phoneNumber.substr(0, 3) + ")" +
                                      phoneNumber.substr(3, 3) + "-" +
                                      phoneNumber.substr(6);
        cout << " Occupant Name: " << this->getName() << endl;
        cout << "   Residence Type: " << this->getResidenceType() << endl;
        cout << "   Unit #: " << this->getUnitNumber() << endl;
        cout << "   Phone #: " << formattedPhoneNumber << endl;
        cout << "   Email Address: " << this->getEmail() << endl;
        cout << "   Age: " << this->getAge() << endl
             << endl;
    }
};

class CondoManager
{
private:
    // condo is used to store occupants' records
    vector<Occupant> condo = {};

    // print the menu for modification
    void displayModifyMenu()
    {
        cout << "   What would you like to modify?" << endl;
        cout << "    1. Name " << endl;
        cout << "    2. Residence Type " << endl;
        cout << "    3. Unit # " << endl;
        cout << "    4. Phone # " << endl;
        cout << "    5. Email " << endl;
        cout << "    6. Age " << endl;
        cout << "    7. Exit Modification Menu " << endl;
        cout << "   Please select a number to modify: ";
    }

    // get the name of an occupant from user input
    string getNameOnScreen(string selector)
    {
        string input;
        if (selector == "for_modify")
            cout << "         Modified Occupant Name: ";
        else
            cout << "   Occupant Name: ";
        getline(cin, input);
        string name = leftTrim(rightTrim(input));
        return name;
    }

    // get the residence type of an occupant from user input
    string getResidenceTypeOnScreen(string selector)
    {
        string input;
        string residenceType;
        while (true)
        {
            if (selector == "for_modify")
                cout << "         Modified Residence Type (Penthouse - P, Apartment - A, Townhouse - T): ";
            else
                cout << "   Residence Type (Penthouse - P, Apartment - A, Townhouse - T): ";
            getline(cin, input);
            input = leftTrim(rightTrim(input));
            if (input == "P" || input == "p")
                input = "Penthouse";
            else if (input == "A" || input == "a")
                input = "Apartment";
            else if (input == "T" || input == "t")
                input = "Townhouse";
            else
                input = "";
            try
            {
                if (input == "")
                    throw MyException("Invalid residence type. Please enter P for Penthouse, A for Apartment or T for Townhouse.");
                else
                {
                    residenceType = input;
                    break;
                }
            }
            catch (MyException &e)
            {
                cout << endl
                     << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
                cout << "Error: " << e.what() << endl;
                cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
            }
        }
        return residenceType;
    }

    // get the unit number of an occupant from user input
    string getUnitNumberOnScreen(string selector)
    {
        string input;
        string unitNumber;
        if (selector == "for_modify")
            cout << "         Modified Unit Number: ";
        else
            cout << "   Unit #: ";
        getline(cin, input);
        unitNumber = leftTrim(rightTrim(input));
        return unitNumber;
    }

    // get the phone number of an occupant from user input
    string getPhoneNumberOnScreen(string selector)
    {
        string input;
        string phoneNumber;
        while (true)
        {
            if (selector == "for_modify")
                cout << "         Modified Phone #: ";
            else
                cout << "   Phone #: ";

            getline(cin, input);
            input = leftTrim(rightTrim(input));
            int num;
            try
            {
                if (input.length() < 10 || input.length() > 15)
                    throw MyException("Phone number contains too few/many numbers. ");
                else if (!isValidNumber(input))
                    throw MyException("Invalid phone. Phone number cannot contain non number digits. ");
                else
                {
                    phoneNumber = input;
                    break;
                }
            }
            catch (MyException &e)
            {
                cout << endl
                     << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
                cout << "Error: " << e.what() << endl;
                cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
            }
        }
        return phoneNumber;
    }

    // get the email address of an occupant from user input
    string getEmailOnScreen(string selector)
    {
        string input;
        string email;
        while (true)
        {
            if (selector == "for_modify")
                cout << "         Modified Email Address: ";
            else
                cout << "   Email Address: ";

            getline(cin, input);
            input = leftTrim(rightTrim(input));
            try
            {
                if (!isValidEmailAddress(input))
                    throw MyException("Invalid email address. Email address missing '@' or '.', or has spaces.");
                else
                {
                    email = input;
                    break;
                }
            }
            catch (MyException &e)
            {
                cout << endl
                     << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
                cout << "Error: " << e.what() << endl;
                cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
            }
        }
        return email;
    }

    // get the age of an occupant from user input
    int getAgeOnScreen(string selector)
    {
        string input;
        int age;
        while (true)
        {
            if (selector == "for_modify")
                cout << "         Modified Age: ";
            else
                cout << "   Age: ";
            getline(cin, input);
            input = leftTrim(rightTrim(input));
            try
            {
                if (!stringToNumber(input, &age))
                    throw MyException("Invalid age. Age must be a valid interger number.");
                else if (age < 0 || age > 150)
                    throw MyException("Age input is out of range. Please input a number between 0 and 150.");
                else
                    break;
            }
            catch (MyException &e)
            {
                cout << endl
                     << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
                cout << "Error: " << e.what() << endl;
                cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
            }
        }
        return age;
    }

    // search the records with the combined criteria of name and residence Type
    // return the index of the matched record if matched record is found
    // return -1 if no record matching the search criteria
    int findOccupant(string name, string residenceType)
    {

        for (int i = 0; i < this->condo.size(); i++)
        {
            if (toLowerCase((this->condo[i]).getName()) == toLowerCase(name) &&
                (this->condo[i]).getResidenceType() == residenceType)
                return i;
        }
        return -1;
    }

    bool updataName(Occupant &occupant)
    {
        string name = getNameOnScreen("for_modify");
        occupant.setName(name);
        return true;
    }

    bool updataResidenceType(Occupant &occupant)
    {
        string residenceType = getResidenceTypeOnScreen("for_modify");
        occupant.setResidenceType(residenceType);
        return true;
    }

    bool updataUnitNumber(Occupant &occupant)
    {
        string unitNumber = getUnitNumberOnScreen("for_modify");
        occupant.setUnitNumber(unitNumber);
        return true;
    }

    bool updataPhoneNumber(Occupant &occupant)
    {
        string phoneNumber = getPhoneNumberOnScreen("for_modify");
        occupant.setPhoneNumber(phoneNumber);
        return true;
    }

    bool updataEmail(Occupant &occupant)
    {
        string email = getEmailOnScreen("for_modify");
        occupant.setEmail(email);
        return true;
    }

    bool updataAge(Occupant &occupant)
    {
        int age = getAgeOnScreen("for_modify");
        occupant.setAge(age);
        return true;
    }

public:
    void displayWelcomePage()
    {
        cout << "----Welcome to . . . ------------------------------------------------------------------------" << endl;
        cout << "                                                                                            |" << endl;
        cout << "    ====|  ======  ==    ==  ====    ======                                                 |" << endl;
        cout << "    ||     ||  ||  ||\\\\  ||  ||  \\\\  ||  || ===========================================     |" << endl;
        cout << "    ||     ||  ||  || \\\\ ||  ||   || ||  || ===========================================     |" << endl;
        cout << "    ||     ||  ||  ||  \\\\||  ||  //  ||  || ===========================================     |" << endl;
        cout << "    ====|  ======  ==    ==  ====    ====== ===========================================     |" << endl;
        cout << "                    ===    ===     ===     ==    ==     ===      =====  =====  ====         |" << endl;
        cout << "    =============== ||\\\\  //||    // \\\\    ||\\\\  ||    // \\\\    ||      ||     ||  \\\\       |" << endl;
        cout << "    =============== || \\\\// ||   //===\\\\   || \\\\ ||   //===\\\\   || ===  ||==   ||==||       |" << endl;
        cout << "    =============== ||  ==  ||  //     \\\\  ||  \\\\||  //     \\\\  ||   || ||     || \\\\        |" << endl;
        cout << "                    ==      == ==       == ==    == ==       == ======  =====  ==  ==       |" << endl;
        cout << "---------------------------------------------------------------------------------------------" << endl;
        cout << endl;
    }

    // print the main menu
    void displayMainMenu()
    {
        cout << endl
             << "---------Program Menu------------" << endl;
        cout << "      1. Add Records " << endl;
        cout << "      2. List Records " << endl;
        cout << "      3. Modify Records " << endl;
        cout << "      4. Delete Records " << endl;
        cout << "      5. Exit Records " << endl;
        cout << " Please select a program to run: ";
    }

    // Add a new occupant record
    bool addRecords()
    {
        string name;
        string residenceType;
        string unitNumber;
        string phoneNumber;
        string email;
        int age;
        string recordData;
        bool result = true;
        cout << "--------------------------------------------------------------------------" << endl;
        cout << "                             A D D   R E C O R D " << endl;
        cout << "--------------------------------------------------------------------------" << endl;
        cout << " Unit Information:" << endl;
        name = getNameOnScreen("for_add");
        residenceType = getResidenceTypeOnScreen("for_add");
        unitNumber = getUnitNumberOnScreen("for_add");

        cout << " Occupant Information:" << endl;
        phoneNumber = getPhoneNumberOnScreen("for_add");
        email = getEmailOnScreen("for_add");
        age = getAgeOnScreen("for_add");

        Occupant newOccupant = Occupant(name, phoneNumber, email, age, unitNumber, residenceType);
        condo.push_back(newOccupant);

        cout << endl
             << " New record has been added successfully." << endl;
        cout << "--------------------------------------------------------------------------" << endl;

        return true;
    }

    // Display all occupants' information on screen
    bool listRecords()
    {
        cout << "--------------------------------------------------------------------------" << endl;
        cout << "                             L I S T   R E C O R D S " << endl;
        cout << "--------------------------------------------------------------------------" << endl;

        vector<Occupant>::iterator iter;

        for (iter = this->condo.begin(); iter != (this->condo.end()); ++iter)
            (*iter).display();

        cout << "--------------------------------------------------------------------------" << endl;
        cout << "  Total Number of Occupants: " << this->condo.size() << endl;
        cout << "--------------------------------------------------------------------------" << endl;

        return true;
    }

    // Modify an occupant's information
    bool modifyRecords()
    {
        bool result = true;
        string name;
        string residenceType;
        string unitNumber;
        string phoneNumber;
        string email;
        int age;
        string recordData;
        cout << "--------------------------------------------------------------------------" << endl;
        cout << "                             M O D I F Y   R E C O R D S " << endl;
        cout << "--------------------------------------------------------------------------" << endl;
        name = getNameOnScreen("for_add");
        residenceType = getResidenceTypeOnScreen("for_add");

        try
        {
            int index = findOccupant(name, residenceType);
            if (index >= 0)
            {
                string command = "";
                while (command != "7")
                {
                    cout << "------------------------------------------" << endl;
                    this->condo.at(index).display();
                    displayModifyMenu();
                    getline(cin, command);
                    command = leftTrim(rightTrim(command));
                    try
                    {
                        if (command == "1")
                            updataName(this->condo.at(index));
                        else if (command == "2")
                            updataResidenceType(this->condo.at(index));
                        else if (command == "3")
                            updataUnitNumber(this->condo.at(index));
                        else if (command == "4")
                            updataPhoneNumber(this->condo.at(index));
                        else if (command == "5")
                            updataEmail(this->condo.at(index));
                        else if (command == "6")
                            updataAge(this->condo.at(index));
                        else if (command == "7")
                            continue;
                        else
                            throw MyException("Modification selection invalid. Please enter a program between 1 and 7.");
                    }
                    catch (MyException &e)
                    {
                        cout << endl
                             << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
                        cout << "Error: " << e.what() << endl;
                        cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
                    }
                }
            }
            else
                throw MyException("User entered for modification cannot be found.");
        }
        catch (MyException &e)
        {
            cout << endl
                 << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
            cout << "Error: " << e.what() << endl;
            cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
        }
        return true;
    }

    // Delete an occupant's record
    bool deleteRecords()
    {
        string name;
        string residenceType;
        string recordData;
        cout << "--------------------------------------------------------------------------" << endl;
        cout << "                             D E L E T E   R E C O R D S " << endl;
        cout << "--------------------------------------------------------------------------" << endl;
        name = getNameOnScreen("for_delete");
        residenceType = getResidenceTypeOnScreen("for_delete");
        try
        {
            int index = findOccupant(name, residenceType);
            if (index >= 0)
            {
                name = condo.at(index).getName();
                this->condo.erase(this->condo.begin() + index);
                cout << endl
                     << " Occupant [" << name << "] deleted successfully." << endl;
                cout << "--------------------------------------------------------------------------" << endl;
            }
            else
                throw MyException("User entered for delete cannot be found.");
        }
        catch (MyException &e)
        {
            cout << endl
                 << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
            cout << "Error: " << e.what() << endl;
            cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
        }
        return true;
    }
};

// Remove all leading spaces from the string.
// For example, string "   abc" will be converted to "abc"
string leftTrim(string str)
{
    string result = "";
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != ' ')
        {
            result = result + str.substr(i);
            break;
        }
    }
    return result;
}

// Remove all tailing spaces from the string
// For example, string "abc   " will be converted to "abc"
string rightTrim(string str)
{
    string result = "";
    for (int i = str.size() - 1; i >= 0; i--)
    {
        if (str[i] != ' ')
        {
            result = result + str.substr(0, i + 1);
            break;
        }
    }
    return result;
}

// Convert all characters to lower case in a string
string toLowerCase(string str)
{
    string result = "";
    for (int i = 0; i < str.size(); i++)
    {
        result.push_back(tolower(str[i]));
    }
    return result;
}

// Convert a string to a number
// If a string is a valid number, convert it to an integer, return true.
// Otherwise return false
// For example, string "123" will be converted to number 123 and return true
// string "123B" or "A123" will not be converted and return false
bool stringToNumber(string numberString, int *number)
{
    bool result = true;
    for (int i = 0; i < numberString.size(); i++)
    {

        if ((isdigit(numberString[i]) == 0)) // not a digit
        {
            result = false;
            return result;
        }
    }
    try
    {
        *number = (stoi(numberString));
    }
    catch (const std::invalid_argument &ex)
    {
        result = false;
    }
    catch (const std::out_of_range &ex)
    {
        result = false;
    }

    return result;
}

// If a string is a valid number, return true.
// Otherwise return false
// For example, string "123" will be a valid number and return true
// string "123B" or "A123" will not be a valid number and return false
bool isValidNumber(string numberString)
{
    bool result = true;
    for (int i = 0; i < numberString.size(); i++)
    {

        if ((isdigit(numberString[i]) == 0)) // not a digit
        {
            result = false;
            return result;
        }
    }
    return result;
}

// Return true if the email address is in a valid format, otherwise return false.
// For example, the following email address is not valid:
// - johndoedomainsample.com   (The @ symbol is missing between johndoe and domainsample.com)
// - johndoe@domainsample   (The top level domain (.com) is missing)
// - @domainsample.com  (The recipient name is missing.)
bool isValidEmailAddress(string emailAddress)
{
    bool result = true;
    if ((emailAddress.find(" ") != std::string::npos) || // has spaces
        (emailAddress.find("@") == std::string::npos) || // not contain @
        (emailAddress.find(".") == std::string::npos) || // not contain .
        (isalnum(emailAddress[0]) == 0))                 // first letter is a special character
        result = false;
    return result;
}

int main()
{
    CondoManager condoManager = CondoManager();
    string command = "";
    condoManager.displayWelcomePage();

    while (command != "5")
    {
        condoManager.displayMainMenu();
        getline(cin, command);
        command = leftTrim(rightTrim(command));
        try
        {
            if (command == "1")
                condoManager.addRecords();
            else if (command == "2")
                condoManager.listRecords();
            else if (command == "3")
                condoManager.modifyRecords();
            else if (command == "4")
                condoManager.deleteRecords();
            else if (command == "5")
                continue;
            else
                throw MyException("Program selection invalid. Please enter a program between 1 and 5.");
        }
        catch (MyException &e)
        {
            cout << endl
                 << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
            cout << "Error: " << e.what() << endl;
            cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
        }
    }
    cout << endl
         << "Thank you for using Condo Manager! Have a nice day :)" << endl;
    cout << "   ~The Condo Manager Team" << endl
         << endl;
    return 1;
}