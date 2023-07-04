#ifndef STOCK_H
#define STOCK_H
#include "QuantityItem.h"
#include"StockItem.h"
#include "WeightItem.h"
#include "Invoice.h"
class Stock    // stock class for controlling all processes 

{
private:
    vector<StockItem*> stock;    // STL vector for StockItems pointers 

    vector<Invoice>invoices;   // STL vector for Invoices objects
public:
    void AddItem(StockItem* item)
    {
        stock.push_back(item);
    }

    void DisplayStock() const    // function displaying the stock 
    {
        cout << "Current Stock: " << endl;

        for (const auto& item : stock)
        {
            //item->DisplayItem();

            if (typeid(*item) == typeid(QuantityItem))   // run time binding determining the type of the object 
            {
                QuantityItem  qunat = *(static_cast<QuantityItem*>(item));

                cout << qunat << endl;    // calling stream insertion operator overloading 

                cout << "-----------------------------" << endl;

            }

            if (WeightItem* wItem = dynamic_cast<WeightItem*>(item))   // using the dynamic binding which operator overloaded function should be called
            {
                cout << (*wItem) << endl;   // using stream insertion operator overloading 

                cout << "-----------------------------" << endl;
            }



        }
    }

    void SaveStockToFile() const   // function for saving data to file 
    {
        ofstream file("stock.txt");   // stock.txt for saving all stock 

        if (file.is_open())    // check if file is openeing
        {
            file << this->stock.size() << endl;

            for (const auto& item : this->stock)
            {
                item->SaveItemToFile(file);
            }
            file.close();

            cout << "Stock saved to file." << endl;

        }             // error handling 
        else {
            cout << "Error: Unable to save stock to file." << endl;
        }
    }

    void LoadInvoicesFromFile()
    {
        string fileName = "invoices.txt";

        ifstream fin(fileName); // opeening file in the write mode

        int totalInvoices;

        fin >> totalInvoices;

        Invoice::setInvoies(totalInvoices); // total Invoices that are at the top of the file 

        fin.ignore();

        string name, iteName;

        int totalItems;

        int id;

        double  itemsPrice;
        int i = 0;

        while (i++ < totalInvoices)   // loop until number of invoices 
        {

            getline(fin, name);

            getline(fin, iteName);

            fin >> id >> totalItems >> itemsPrice;

            fin.ignore();

            this->invoices.push_back(Invoice(name, iteName, id, totalItems, itemsPrice));   // push_invoices to the invoice Data Structure

        }


        /* cout << Invoice::totalInvoices << endl;

         for (const auto& inv : this->invoices)
         {
             cout << inv.customerName << endl <<  inv.itemName << endl<< inv.InvoiceNum << "  " << inv.numItems << " " << inv.price << endl;
         }*/

    }

    void LoadStockFromFile()  // load whole stock from file 
    {
        ifstream file("stock.txt");

        if (file.is_open())
        {
            int numItems;

            file >> numItems;

            file.ignore();

            for (int i = 0; i < numItems; ++i)
            {
                char itemType;

                file >> itemType;

                file.ignore();

                if (itemType == 'Q')
                {
                    QuantityItem* qItem = new QuantityItem("", 0, 0.0);

                    qItem->LoadItemFromFile(file);

                    AddItem(qItem);
                }
                else if (itemType == 'W')
                {
                    WeightItem* wItem = new WeightItem("", 0.0, 0.0);

                    wItem->LoadItemFromFile(file);

                    AddItem(wItem);
                }
            }

            file.close();

            cout << "Stock loaded from file." << endl;
        }
        else
        {
            cout << "Error: Unable to load stock from file." << endl;
        }
    }

    StockItem* FindItem(const string& itemName)    // find item in the stock 
    {


        for (auto& item : this->stock)
        {
            if (itemName == item->getName())   // if item exists or not 
            {

                return item;
            }
        }
        return nullptr;
    }

    void SellItem(const string& itemName, double quantity)   // sell item to the customer 
    {
        StockItem* item = FindItem(itemName);   // first find item to be sell

        if (item != nullptr)    // if item exists in the stock 
        {
            double cost = item->CalculateCost();

            cout << "Enter customer Name" << endl;

            cin.ignore();

            string customerName;

            getline(cin, customerName);
            cout << "Sold: " << quantity << " " << itemName << endl;

            cout << "Total Cost: " << cost << endl;

            item->setQuantity(quantity); // updating the quantity of the item

            //this->stock.erase(remove(stock.begin(), stock.end(), item), stock.end());


            this->invoices.push_back(Invoice(customerName, itemName, cost, quantity));   // updating the invoices for new sale 

            this->saveInvoiceToFile();// saving invoices to file    // saving invoices to the file for updation 
        }
        else
        {
            cout << "Error: Item not found in stock." << endl;
        }
    }

    void saveInvoiceToFile()   // function for saving all invoices /Receipts for the file after chaning 
    {
        string fileName = "invoices.txt";
        ofstream fout(fileName);
        if (!fout)
        {
            cout << "File is not found" << endl;
        }
        else
        {
            fout << Invoice::totalInvoices << endl;

            for (const auto& invoice_ : this->invoices)
            {
                fout << invoice_.customerName << endl;

                fout << invoice_.itemName << endl;

                fout << invoice_.InvoiceNum << " " << invoice_.numItems << " " << invoice_.price << endl;
            }
        }
    }

    void searchInvoice(int invNum)    // search for a particular invoice against its ID /Invoice #
    {
        bool status;
        for (const auto& inv : this->invoices)
        {
            if (inv.InvoiceNum == invNum)
            {
                status = true;

                cout << "-------------------------------\nReceipt/ Invoice Exists" << endl;

                cout << "Invoice # /Receipt ID " << invNum << endl;

                cout << "Customer Name : " << inv.customerName << endl;

                cout << "Item Name: " << inv.itemName << endl;

                cout << "Items Weight /Quantity " << inv.numItems << endl;

                cout << "Items price " << inv.price << endl;

            }

        }

        if (!status)               // if invoice not found 

            cout << "The Receipt with Invoice # " << invNum << " Does not exist" << endl;

    }
    ~Stock()
    {
        for (auto& item : stock)    // calling the destructors of the respective classes for the memory dellocation
        {
            delete item;
        }
    }


};

#endif // !STOCK

