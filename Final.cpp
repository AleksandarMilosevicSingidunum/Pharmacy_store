#include <iostream>
#include <ios>
#include <vector>
#include <string>
#include <unistd.h>
#include <limits>
#include <fstream>
#include <regex>
using namespace std;
//Create all classes
class Person
{

private:
    string name, personID, userPassword, profession;

public:
    Person();
    Person(string name, string personID, string userPassword, string profession)
    {
        this->name = name;
        this->personID = personID;
        this->userPassword = userPassword;
        this->profession = profession;
    }
    friend ostream &operator<<(ostream &out, const Person &p)
    {
        return out << "Person Data are" << endl
                   << "Name: " << p.name << endl
                   << "Person ID: " << p.personID << endl
                   << "Password: " << p.userPassword << endl
                   << "Profession: " << p.profession << endl;
    }
    string getProfession() { return profession; }
    string getpersonID() { return personID; }
    string getName() { return name; }
    string getPassword() { return userPassword; }
    void setProfession(string profession) { profession = profession; }
    void setpersonID(string personID) { personID = personID; }
    void setName(string name) { name = name; }
    void setPassword(string userPassword) { userPassword = userPassword; }
};
class Pharmacist : public Person
{
public:
    using Person ::Person;
};
class Admin : public Person
{
    using Person::Person;
};
class Drug
{
private:
    string name, description;
    double price;
    int stock;
    string prescripted;

public:
    string getName() const { return name; }
    string getDescription() { return description; }
    double getPrice() { return price; }
    int getStock() { return stock; }
    string getPrescripted() { return prescripted; }
    void setName(string name) { name = name; }
    void setDescription(string description) { description = description; }
    void setPrice(double price) { price = price; }
    void setStock(int stock) { stock = stock; }
    void setPrescripted(string prescripted) { prescripted = prescripted; }
    Drug();
    Drug(string name, string description, string prescripted, double price, int stock)
    {
        this->name = name;
        this->description = description;
        this->price = price;
        this->stock = stock;
        this->prescripted = prescripted;
    }
    friend ostream &operator<<(ostream &out, const Drug &d)
    {
        return out << "Name: " << d.name << endl
                   << "Description: " << d.description << endl
                   << "Price: " << d.price << " Din" << endl
                   << "Stock: " << d.stock << " Qty" << endl
                   << "Prescripted: " << d.prescripted << endl;
    }
};
//Split line into substring
vector<string> split(const string &s, char c);
//Menu only pharmacist can enter
void pharmacistMenu(vector<Person *> &persons, vector<Drug *> &drugs, vector<Drug *> &soldDrugs);
//function that allows pharmacist to sell drugs and store store sold drugs to file
void sellDrugs(vector<Person *> &persons, vector<Drug *> &drugs, vector<Drug *> &soldDrugs);
//Print Inventory of sold drugs or drugs that are in stock
void Inventory(vector<Drug *> &drugs);
//Uses vector drugs and store each object to file
void writeDrugToFile(vector<Drug *> &drugs);
//Create a backup of all sold drugs to file(so user can see even if they exit program) file is reseted everytime program is rebooted
void writeSoldDrugToFile(vector<Drug *> &soldDrugs);
//Store all personal into a file using vector persons
void writePersonsToFile(vector<Person *> &persons);
//Allows Admin to increase drug stock or ot add new drug
void stockUpMenu(vector<Drug *> &drugs, vector<Person *> &persons, vector<Drug *> &soldDrugs);
//Menu only admin can enter
void adminMenu(vector<Drug *> &drugs, vector<Person *> &persons, vector<Drug *> &soldDrugs);
//Increase drug stock
void stockUp(vector<Drug *> &drugs, vector<Person *> &persons, vector<Drug *> &soldDrugs);
//Admin can add new Pharmacist to program and to database
void addPharmacist(vector<Drug *> &drugs, vector<Person *> &persons, vector<Drug *> &soldDrugs);
//start program
void startProgram();
//check Password if it matches in database it is done after checkCredentials
bool checkPassword(Person *person)
{
    string testPassword;
    cout << "Enter your Password" << endl;
    cin >> testPassword;
    int y = testPassword.compare(person->getPassword());
    if (y == 0)
    {
        system("CLS");
        cout << "Success!!" << endl;
        sleep(1.5);
        return true;
    }

    return false;
}
//check PersonID if it matches in database
bool checkCredentials(vector<Person *> &persons, vector<Drug *> &drugs, vector<Drug *> &soldDrugs)
{
    string testPersonID;
    cout << "Enter your Person ID" << endl;
    cin >> testPersonID;

    for (auto person : persons)
    {
        int x = testPersonID.compare(person->getpersonID());
        if (x == 0)
        {
            while (checkPassword(person) != true)
                ;
            {
                if (person->getProfession() == "Pharmacist")
                {
                    system("CLS");
                    pharmacistMenu(persons, drugs, soldDrugs);
                }
                else
                {
                    adminMenu(drugs, persons, soldDrugs);
                }
            }
        }
    }
    return false;
}
//Used to login user into system
void login(vector<Person *> &persons, vector<Drug *> &drugs, vector<Drug *> &soldDrugs)
{
    do
    {
        system("cls");
        checkCredentials(persons, drugs, soldDrugs);
    } while (checkCredentials(persons, drugs, soldDrugs) != true);
    exit(0);
}
void pharmacistMenu(vector<Person *> &persons, vector<Drug *> &drugs, vector<Drug *> &soldDrugs)
{
    int Option = 0;

    cout << "############################################" << endl;
    cout << " Welcome to Pharmacy Management System" << endl;
    cout << "############################################" << endl;
    cout << " Enter Option: " << endl;
    cout << " 1.Sell Drugs" << endl;
    cout << " 2.Inventory" << endl;
    cout << " 3.Log out" << endl;
    cout << " 4.Exit" << endl;
    cout << "############################################" << endl;
    while (!(cin >> Option))
    {   
        system("CLS");
        cout << "Must enter Number!!" << endl;
        cin.clear();
        cin.ignore(123, '\n');
        pharmacistMenu(persons, drugs, soldDrugs);
        
    }while (Option>9)
    {  
        system("CLS");
        cin.clear();
        cin.ignore(123, '\n');
        pharmacistMenu(persons, drugs, soldDrugs);
    }
    

    do
    {
        system("CLS");
        switch (Option)
        {
        case 1:
            sellDrugs(persons, drugs, soldDrugs);
            break;
        case 2:
            system("CLS");
            Inventory(drugs);
            pharmacistMenu(persons, drugs, soldDrugs);
            break;
        case 3:
            cout << "logged out" << endl;
            login(persons, drugs, soldDrugs);
            break;
        case 4:
            system("CLS");
            cout << "Goodbye See you next time!" << endl;
            exit(0);
            break;
        default:
            cout << "Please Try Again!" << endl;
            break;
        }
    } while (Option < 1 || Option > 4);
}
void adminMenu(vector<Drug *> &drugs, vector<Person *> &persons, vector<Drug *> &soldDrugs)
{
    int Option = 0;
    system("CLS");
    cout << "############################################" << endl;
    cout << " Welcome to Pharmacy Management System" << endl;
    cout << "############################################" << endl;
    cout << " Enter Option: " << endl;
    cout << " 1.Stock up drugs" << endl;
    cout << " 2.Inventory" << endl;
    cout << " 3.Add new Pharmacist " << endl;
    cout << " 4.Log out" << endl;
    cout << " 5.Exit" << endl;
    cout << "############################################" << endl;
    while (!(cin >> Option))
    {   
        system("CLS");
        cout << "Must enter Number!!" << endl;
        cin.clear();
        cin.ignore(123, '\n');
        adminMenu(drugs, persons, soldDrugs);
        
    }while (Option>9)
    {  
        system("CLS");
        cin.clear();
        cin.ignore(123, '\n');
        adminMenu(drugs, persons, soldDrugs);
    }

    do
    {
        system("CLS");
        switch (Option)
        {
        case 1:
            stockUpMenu(drugs, persons, soldDrugs);
            break;
        case 2:
            system("CLS");
            cout << "1.Inventory of remaining items" << endl
                 << "2.Sold items Inventory" << endl
                 << "3.Return" << endl;
            int x;
            cin >> x;
            if (x == 1)
            {
                Inventory(drugs);
                adminMenu(drugs, persons, soldDrugs);
            }
            if (x == 2)
            {
                writeSoldDrugToFile(soldDrugs);
                Inventory(soldDrugs);
                adminMenu(drugs, persons, soldDrugs);
            }
            if (x == 3)
            {
                adminMenu(drugs, persons, soldDrugs);
            }

            break;
        case 3:
            addPharmacist(drugs, persons, soldDrugs);
            writePersonsToFile(persons);
            adminMenu(drugs, persons, soldDrugs);
            break;
        case 4:
            cout << "Logged out" << endl;
            login(persons, drugs, soldDrugs);
            break;
        case 5:
            system("CLS");
            cout << "Goodbye See you next time!" << endl;
            exit(0);
            break;
        default:
            cout << "Please Try Again!" << endl;
            break;
        }
    } while (Option < 1 || Option > 5 || Option == 0);
}
void sellDrugs(vector<Person *> &persons, vector<Drug *> &drugs, vector<Drug *> &soldDrugs)
{
    cout << "Select Drug by inputing name" << endl;
    string input;
    cin.ignore();
    getline(cin, input);
    int counter = 0;
    for (auto drug : drugs)
    {

        int x = input.compare(drug->getName());
        if (x != 0)
            counter++;
        if (x == 0)
        {
            if (drug->getPrescripted() == "Prescripted")
            {
                cout << "Prescription is required for this drug" << endl;
                cout << "Do user Have Prescription. Y/N" << endl;
                char pre;
                cin >> pre;
                if (pre == 'Y' || pre == 'y')
                {
                    cout << *drug << endl;
                    int qty;
                    cout << "Input the quantity" << endl;
                    cout << "Quantity available " << drug->getStock() << endl;
                    cin >> qty;
                    if (qty > drug->getStock())
                    {
                        cout << "Don't have enough stock" << endl;
                        cout << "1.Try another quantity" << endl;
                        cout << "2.Try another drug" << endl;
                        int option;
                        while (!(cin >> option))
                        {
                            cout << "Must enter Number!!" << endl;
                            cin.clear();
                            cin.ignore(123, '\n');
                        }
                        switch (option)
                        {
                        case 1:
                            cout << "Input the quantity" << endl;
                            cout << "Quantity available " << drug->getStock() << endl;
                            cin >> qty;
                            if (qty > drug->getStock())
                            {
                                cout << "Don't have enough stock" << endl;
                                cout << "Try another drug" << endl;
                                system("pause");
                                system("CLS");
                                sellDrugs(persons, drugs, soldDrugs);
                            }
                            break;
                        case 2:
                            system("CLS");
                            sellDrugs(persons, drugs, soldDrugs);
                            break;
                        default:
                            break;
                        }
                    }
                    else
                    {
                        int newQty = drug->getStock() - qty;
                        int bill = qty * drug->getPrice();
                        cout << "Your bill for " << qty << " " << drug->getName() << "'s is: " << bill << " din" << endl;
                        for (int i = 0; i < drugs.size(); i++)
                        {
                            if (drug->getName() == drugs[i]->getName())
                                drugs.erase(drugs.begin() + i);
                        }
                        Drug sold(drug->getName(), drug->getDescription(), drug->getPrescripted(), drug->getPrice(), qty);
                        soldDrugs.push_back(&sold);
                        writeSoldDrugToFile(soldDrugs);
                        Drug temp(drug->getName(), drug->getDescription(), drug->getPrescripted(), drug->getPrice(), newQty);
                        cout << endl;
                        drugs.push_back(&temp);
                        writeDrugToFile(drugs);
                        system("pause");
                        system("CLS");

                        pharmacistMenu(persons, drugs, soldDrugs);
                    }
                }
                {
                    cout << "Cannot be sold!!" << endl;
                    system("pause");
                    system("CLS");
                    pharmacistMenu(persons, drugs, soldDrugs);
                }
            }
            else if (drug->getPrescripted() != "Prescripted")
            {
                cout << *drug << endl;
                int qty;
                cout << "Input the quantity" << endl;
                cout << "Quantity available " << drug->getStock() << endl;
                cin >> qty;
                if (qty > drug->getStock())
                {
                    cout << "Don't have enough stock" << endl;
                    cout << "1.Try another quantity" << endl;
                    cout << "2.Try another drug" << endl;
                    int option;
                    while (!(cin >> option))
                    {
                        cout << "Must enter Number!!" << endl;
                        cin.clear();
                        cin.ignore(123, '\n');
                    }
                    switch (option)
                    {
                    case 1:
                        cout << "Input the quantity" << endl;
                        cout << "Quantity available " << drug->getStock() << endl;
                        cin >> qty;
                        if (qty > drug->getStock())
                        {
                            cout << "Don't have enough stock" << endl;
                            cout << "Try another drug" << endl;
                            system("pause");
                            system("CLS");
                            sellDrugs(persons, drugs, soldDrugs);
                        }
                        break;
                    case 2:
                        system("CLS");
                        sellDrugs(persons, drugs, soldDrugs);
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    int newQty = drug->getStock() - qty;
                    int bill = qty * drug->getPrice();
                    cout << "Your bill for " << qty << " " << drug->getName() << "'s is: " << bill << " din" << endl;
                    for (int i = 0; i < drugs.size(); i++)
                    {
                        if (drug->getName() == drugs[i]->getName())
                            drugs.erase(drugs.begin() + i);
                    }
                    Drug sold(drug->getName(), drug->getDescription(), drug->getPrescripted(), drug->getPrice(), qty);
                    soldDrugs.push_back(&sold);
                    Drug temp(drug->getName(), drug->getDescription(), drug->getPrescripted(), drug->getPrice(), newQty);
                    cout << endl;
                    drugs.push_back(&temp);
                    writeDrugToFile(drugs);
                    system("pause");
                    system("CLS");

                    pharmacistMenu(persons, drugs, soldDrugs);
                }
            }
        }
    }
    if (counter == drugs.size())
    {
        cout << "Drug dont exist in database!!" << endl;
        system("pause");
        system("CLS");
        sellDrugs(persons, drugs, soldDrugs);
    }
}
void Inventory(vector<Drug *> &drugs)
{
    cout << "Inventory is: " << endl
         << "-----------------------------------" << endl;
    for (auto drug : drugs)
    {
        sleep(1);
        cout << *drug << endl;
        cout << "-----------------------------------" << endl;
    }
    system("pause");
    system("CLS");
}
void writeDrugToFile(vector<Drug *> &drugs)
{

    ofstream file;
    file.open("Database.txt", ios::out);
    if (!file)
    {
        cout << "Error in creating file.." << endl;
    }
    for (auto drug : drugs)
    {
        file << drug->getName() << "_"
             << drug->getDescription() << "_"
             << drug->getPrice() << "_"
             << drug->getStock() << "_"
             << drug->getPrescripted() << endl;
    }
    file.close();
}
void writeSoldDrugToFile(vector<Drug *> &soldDrugs)
{

    ofstream file;
    file.open("SoldDrugsDatabase.txt", ios::out);
    if (!file)
    {
        cout << "Error in creating file.." << endl;
    }
    for (auto drug : soldDrugs)
    {
        file << drug->getName() << "_"
             << drug->getDescription() << "_"
             << drug->getPrice() << "_"
             << drug->getStock() << "_"
             << drug->getPrescripted() << endl;
    }
    file.close();
}
void stockUp(vector<Drug *> &drugs, vector<Person *> &persons, vector<Drug *> &soldDrugs)
{
    cout << "Select Drug by inputing name" << endl;
    string input;
    cin >> input;
    int counter = 0;
    for (auto drug : drugs)
    {

        int x = input.compare(drug->getName());
        if (x != 0)
            counter++;
        if (x == 0)
        {
            cout << *drug << endl;
            cout << "How much to add: " << endl;
            int amount;
            while (!(cin >> amount))
            {
                cout << "Must enter Number!!" << endl;
                cin.clear();
                cin.ignore(123, '\n');
            }

            int newQty = drug->getStock() + amount;
            for (int i = 0; i < drugs.size(); i++)
            {
                if (drug->getName() == drugs[i]->getName())
                    drugs.erase(drugs.begin() + i);
            }
            Drug temp(drug->getName(), drug->getDescription(), drug->getPrescripted(), drug->getPrice(), newQty);
            cout << endl;
            drugs.push_back(&temp);
            writeDrugToFile(drugs);
            system("pause");
            system("CLS");

            stockUpMenu(drugs, persons, soldDrugs);
        }
    }
    if (counter == drugs.size())
    {
        cout << "Drug dont exist in database!!" << endl;
        system("pause");
        system("CLS");
        stockUpMenu(drugs, persons, soldDrugs);
    }
}
void addNewDrug(vector<Drug *> &drugs, vector<Person *> &persons, vector<Drug *> &soldDrugs)
{
    string name;
    string description;
    string prescripted;
    double price;
    int stock;
    cin.ignore();
    cout << "Enter the name of the drug" << endl;
    getline(cin, name);
    system("CLS");
    cout << "Enter the description of the drug" << endl;
    getline(cin, description);
    system("CLS");
    cout << "Is Drug Prescripted" << endl
         << "Enter:(Prescripted or Not Prescripted)" << endl;
    getline(cin, prescripted);
    system("CLS");
    cout << "Enter the price of the drug" << endl;
    cin >> price;
    system("CLS");
    cout << "Enter the stock of the drug" << endl;
    cin >> stock;
    Drug temp(name, description, prescripted, price, stock);
    cout << temp << endl;
    cout << "Confirm Y/N" << endl;
    char con;
    cin >> con;
    if (con == 'Y' || con == 'y')
    {
        drugs.push_back(&temp);
        cout << "Drug is added" << endl;
        stockUpMenu(drugs, persons, soldDrugs);
    }
    else if (con == 'N' || con == 'n')
    {
        stockUpMenu(drugs, persons, soldDrugs);
    }
}
void stockUpMenu(vector<Drug *> &drugs, vector<Person *> &persons, vector<Drug *> &soldDrugs)
{
    cout << "1.Stock up on existing drug" << endl
         << "2.Add new drug" << endl
         << "3.Return to Menu" << endl
         << "4.Exit" << endl;
    int option;
    while (!(cin >> option))
    {
        cout << "Must enter Number!!" << endl;
        cin.clear();
        cin.ignore(123, '\n');
    }
    do
    {
        system("CLS");
        switch (option)
        {
        case 1:
            stockUp(drugs, persons, soldDrugs);
            break;
        case 2:
            addNewDrug(drugs, persons, soldDrugs);
            break;
        case 3:
            adminMenu(drugs, persons, soldDrugs);
            break;
        case 4:
            system("CLS");
            cout << "Goodbye See you next time!" << endl;
            exit(0);
            break;
        default:
            cout << "Please Try Again!" << endl;
            break;
        }
    } while (option < 1 || option > 2 || option == 0);
}
//check if name only contains letter return true if does
bool containsOnlyLetters(string const &str) {
    return str.find_first_not_of(" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") ==
        string::npos;
}
void addPharmacist(vector<Drug *> &drugs, vector<Person *> &persons, vector<Drug *> &soldDrugs)
{
    string name;
    string personID;
    string userPassword;
    string profession;
    cin.ignore();
    cout << "Enter the name of the Pharmacist" << endl;
    getline(cin, name);
    while(name.size() >30 ||!containsOnlyLetters(name))
    {
        cout<<"Name must Only Letters and less then 30"<<endl;
        getline(cin, name);
    }
    system("CLS");
    cout << "Enter the personID of the Pharmacist" << endl;
    getline(cin, personID);
    system("CLS");
    cout << "Enter Pharmacist password" << endl;
    getline(cin, userPassword);
    system("CLS");
    profession = "Pharmacist";
    Person temp(name, personID, userPassword, profession);
    cout << temp << endl;
    cout << "Confirm Y/N" << endl;
    char con;
    cin >> con;
    if (con == 'Y' || con == 'y')
    {
        persons.push_back(&temp);
        cout << "New Pharmacist added" << endl;
        writePersonsToFile(persons);
        adminMenu(drugs, persons, soldDrugs);
    }
    else if (con == 'N' || con == 'n')
    {
        adminMenu(drugs, persons, soldDrugs);
    }
}
void writePersonsToFile(vector<Person *> &persons)
{
    ofstream file;
    file.open("Personal.txt", ios::out);
    if (!file)
    {
        cout << "Error in creating file.." << endl;
    }
    for (auto person : persons)
    {
        file << person->getName() << "_"
             << person->getpersonID() << "_"
             << person->getPassword() << "_"
             << person->getProfession() << "_" << endl;
    }
    file.close();
}
vector<string> split(const string &s, char c)
{
    vector<string> splitted;

    string word;
    for (char ch : s)
    {
        if ((ch == c) && (!word.empty()))
        {
            splitted.push_back(word);
            word.clear();
        }
        else
            word += ch;
    }
    if (!word.empty())
        splitted.push_back(word);

    return splitted;
}
//Load persons into program and store it in vector using file Personal.txt
vector<Person> LoadPersons(vector<Person> &loadPersons)
{
    string name, personID, userPassword, profession;
    string file_path("Personal.txt");
    ifstream Myfile(file_path);

    vector<vector<string>> content;

    if (Myfile)
    {
        string line;
        vector<string> vec;
        while (getline(Myfile, line))
        {
            for (const string &str : split(line, '_'))
                vec.push_back(str);
            content.push_back(vec);
            vec.clear();
        }

        Myfile.close();
    }
    else
        cout << "Could not open: " + file_path << endl;

    for (const vector<string> &str_vec : content)
    {
        name = str_vec[0];
        personID = str_vec[1];
        userPassword = str_vec[2];
        profession = str_vec[3];
        if (profession == "Admin")
        {
            Admin temp(name, personID, userPassword, profession);
            loadPersons.push_back(temp);
        }
        else
        {
            Pharmacist temp(name, personID, userPassword, profession);
            loadPersons.push_back(temp);
        }
    }
    return loadPersons;
}
//Load drugs into program and store it in vector using file Database.txt
vector<Drug> LoadDrugs(vector<Drug> &loadDrugs)
{
    string name, description;
    double price;
    int stock;
    string prescripted;
    string file_path("Database.txt");
    ifstream Myfile(file_path);

    vector<vector<string>> content;

    if (Myfile)
    {
        string line;
        vector<string> vec;
        while (getline(Myfile, line))
        {
            for (const string &str : split(line, '_'))
                vec.push_back(str);
            content.push_back(vec);
            vec.clear();
        }

        Myfile.close();
    }
    else
        cout << "Could not open: " + file_path << endl;

    for (const vector<string> &str_vec : content)
    {
        name = str_vec[0];
        description = str_vec[1];
        price = stod(str_vec[2]);
        stock = stoi(str_vec[3]);
        prescripted = str_vec[4];
        Drug temp(name, description, prescripted, price, stock);
        loadDrugs.push_back(temp);
    }
    return loadDrugs;
}
void startProgram()
{
    system("CLS");
    vector<Person *> persons;
    vector<Person> loadPersons;
    vector<Drug *> drugs;
    vector<Drug> loadDrugs;
    vector<Drug *> soldDrugs;
    loadPersons = LoadPersons(loadPersons);
    loadDrugs = LoadDrugs(loadDrugs);
    for (int i = 0; i < loadPersons.size(); i++)
    {
        persons.push_back(&loadPersons[i]);
    }
    for (int i = 0; i < loadDrugs.size(); i++)
    {
        drugs.push_back(&loadDrugs[i]);
    }

    login(persons, drugs, soldDrugs);

    system("pause");
}

int main()
{

    startProgram();

    return 0;
}
//Aleksandar Milosevic 2020230378