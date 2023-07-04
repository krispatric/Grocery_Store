#include "StockItem.h"
#ifndef WEIGHTITEM_H
#define WEIGHTITEM_H
class WeightItem;            // forward declaration of the WeightItem class

ostream& operator << (ostream& out, const WeightItem& item);   // operator << for console ouput

istream& operator >>  (istream& out, WeightItem& item);    // operator  >> for console input 

ofstream& operator << (ofstream& out, const WeightItem& item);  // operator  << file output 

ifstream& operator >>  (ifstream& out, WeightItem& item); // operator  >> for file input 

// Concrete class for items sold by weight

class WeightItem : public StockItem
{
private:
    string name;

    double weight;

    double pricePerKg;

    friend ostream& operator << (ostream& out, const WeightItem& item);

    friend istream& operator >> (istream& in, WeightItem& item);

    friend ofstream& operator << (ofstream& out, const WeightItem& item);     // operator  << file output 

    friend ifstream& operator >> (ifstream& out, WeightItem& item);    // operator  >> for file input 

public:

    WeightItem() : name(""), weight(0), pricePerKg(0)
    {
        // the default constructor
    }
    WeightItem(const string& name, double weight, double pricePerKg) : name(name), weight(weight), pricePerKg(pricePerKg)
    {
        // this is the parametrized constructor 
    }

    void DisplayItem() const override    // overrider of the base class for displaying items
    {
        cout << "Item Name: " << name << endl;

        cout << "Weight: " << weight << " kg" << endl;

        cout << "Price per kg: " << pricePerKg << endl;
    }

    void SaveItemToFile(ofstream& file) const override   // save data to file 
    {
        file << "W" << endl;

        WeightItem item = (*this);

        file << item.name << endl;

        file << item.weight << "  ";

        file << item.pricePerKg << endl;

        //file << item;
    }

    void LoadItemFromFile(ifstream& file) override    // loading data from file 
    {
        file.ignore();
        getline(file, name);

        name.erase(remove(name.begin(), name.end(), ' '), name.end());

        name.erase(remove(name.begin(), name.end(), '\n'), name.end());

        file >> weight;

        file >> pricePerKg;
    }

    double CalculateCost() const override   // calcualting cost over rider of the base class method 
    {
        return weight * pricePerKg;
    }

    string getName() const override     // mutator overrider of base class
    {
        return this->name;
    }

    void setQuantity(int less)  override    // setter overrider for setting Quantity
    {
        this->weight -= less;
    }
};

ostream& operator << (ostream& out, const WeightItem& item)      // overloading operator << for console output 
{
    out << "Item Name: " << item.name << endl;

    out << "Weight: " << item.weight << " kg" << endl;

    out << "Price per kg: " << item.pricePerKg << endl;
    return out;

}

istream& operator >> (istream& in, WeightItem& item)   // overloading the opeator >> for console input 
{
    cout << "Enter item name: ";

    in.ignore();

    getline(in, item.name);

    cout << "Enter weight (in kg): ";

    in >> item.weight;

    cout << "Enter price per kg: ";

    in >> item.pricePerKg;

    return in;
}
ofstream& operator << (ofstream& file, const WeightItem& item)     // overloading  operator  << file output 
{

    file << "W" << endl;

    file << item.name << endl;

    file << item.weight << "  ";

    file << item.pricePerKg << endl;

    return file;
}

ifstream& operator >> (ifstream& file, WeightItem& item)   // overloading operator  >> for file input 
{
    file.ignore();
    getline(file, item.name);

    item.name.erase(remove(item.name.begin(), item.name.end(), ' '), item.name.end());

    item.name.erase(remove(item.name.begin(), item.name.end(), '\n'), item.name.end());

    file >> item.weight;

    file >> item.pricePerKg;
    return file;
}
#endif // !WEIGHTITEM_H
