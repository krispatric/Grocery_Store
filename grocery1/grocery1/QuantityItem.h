#include "StockItem.h"
#ifndef  QUANTITYITEM_H
#define QUANTITYITEM_H
// Concrete class for items sold by quantity
class QuantityItem;         // forward declaration of the Quantity item class
ostream& operator << (ostream& out, const QuantityItem& item);     // operator << for console ouput

istream& operator >> (istream& out, QuantityItem& item);     // operator  >> for console input 

ofstream& operator << (ofstream& out, const QuantityItem& item);     // operator  << file output 

ifstream& operator >> (ifstream& out, QuantityItem& item);     // operator  >> for file input 
class QuantityItem : public StockItem
{
private:

    string name;
    int quantity;
    double price;

    friend ostream& operator << (ostream& out, const  QuantityItem& item);   // friend  ostream << operator 

    friend istream& operator >> (istream& out, QuantityItem& item);    // friend istream >> operator 

    friend ofstream& operator << (ofstream& out, const QuantityItem& item);     // friend ofstream operator  << file output 

    friend ifstream& operator >> (ifstream& out, QuantityItem& item);   // friend  ifstream >> opertor for file input 
public:
    QuantityItem() :name(""), quantity(0), price(0)  //  default constructor
    {

    }
    QuantityItem(const string& name, int quantity, double price) : name(name), quantity(quantity), price(price) // parametrized constructor  
    {

    }

    void DisplayItem() const override    //  function for displaying items
    {

        cout << "Item Name: " << name << endl;

        cout << "Quantity: " << quantity << endl;

        cout << "Price per Quantity: " << price << endl;

    }

    void SaveItemToFile(ofstream& file) const override         // overrider for saving data to file 
    {

        QuantityItem item = (*this);

        file << "Q" << endl;

        file << item.name << endl;

        file << item.quantity << " " << item.price << endl;

        /* file << (*this);*/           // option call to operator  << for file output
    }

    void LoadItemFromFile(ifstream& file) override      // over rider to the base class loaditem function 
    {
        file.ignore();

        getline(file, name);

        name.erase(remove(name.begin(), name.end(), ' '), name.end());   // algorithm for removing uncessary space from name of item

        name.erase(remove(name.begin(), name.end(), '\n'), name.end());   // algorithm for removing uncessary \n from ifle 

        file >> quantity;

        file >> price;

        //file >> (*this);

    }

    double CalculateCost() const override     // over rider for calcualting the cost
    {
        return quantity * price;
    }
    string getName() const override
    {
        return this->name;
    }

    void setQuantity(int less) override     // over rider for setting quantity of Quantit Item class
    {
        this->quantity -= less;
    }

};

ostream& operator << (ostream& out, const QuantityItem& item)   // overlaoding the ostream << operator  for console output
{
    out << "Item Name: " << item.name << endl;

    out << "Quantity: " << item.quantity << endl;

    out << "Price per Quantity: " << item.price << endl;
    return out;
}
istream& operator >> (istream& in, QuantityItem& item)    // overloading the istream >> operator  for console input 
{
    cout << "Enter item name: ";

    in.ignore();

    getline(in, item.name);

    cout << "Enter quantity: ";

    in >> item.quantity;

    cout << "Enter price per quantity: ";

    in >> item.price;

    return in;
}

ofstream& operator << (ofstream& file, const QuantityItem& item)    //  overloading operator  << file output 
{
    file << "Q" << endl;

    file << item.name << endl;
    file << item.quantity << " " << item.price << endl;

    return file;
}

ifstream& operator >> (ifstream& file, QuantityItem& item)  // overloading operator >> for file input 
{
    file.ignore();

    getline(file, item.name);

    item.name.erase(remove(item.name.begin(), item.name.end(), ' '), item.name.end());

    item.name.erase(remove(item.name.begin(), item.name.end(), '\n'), item.name.end());

    file >> item.quantity;

    file >> item.price;

    return file;
}
#endif // ! QUANTITYITEM_H
