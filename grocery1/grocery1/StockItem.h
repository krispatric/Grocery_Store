#ifndef STOCKITEM_H
#define STOCKITEM_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <typeinfo>
using namespace std;
// Abstract base class for items in stock
class StockItem {
public:
    virtual void DisplayItem() const = 0;    // pure virtaul function for displaying items

    virtual void SaveItemToFile(ofstream& file) const = 0;    // pure virutal function for saving data to file 

    virtual void LoadItemFromFile(ifstream& file) = 0;    // pure virtaul function for loading data from file 

    virtual double CalculateCost() const = 0;    // pure  virtual function for calculating the cost

    virtual ~StockItem() {}  // this is the virtual destructor

    virtual   string getName() const = 0; // this is the function for getting the name of the StockItem

    virtual void setQuantity(int) = 0;   // pure virtual function for setting the quantity


};

#endif // !STOCKITEM_H
