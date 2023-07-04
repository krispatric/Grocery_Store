#ifndef INVOICE_H
#define INVOICE_H
#include "Stock.h"
class Stock;
class Invoice    // invoice class for Recipt creation 
{
private:

    friend Stock;  // making Stock friend of the Invoice Class
    string customerName;
    string itemName;
    int InvoiceNum;
    double price;
    int numItems;
    static int totalInvoices;
public:
    Invoice(string customerName = "", string itemName = "", double price = 0, int numItems = 0) :customerName(customerName), price(price), numItems(numItems), itemName(itemName)
    {
        InvoiceNum = ++totalInvoices;
        // parametrized constructor
    }

    Invoice(string name, string itemName, int invNum, int numItems, double price) :customerName(name), InvoiceNum(invNum), numItems(numItems), price(price), itemName(itemName)
    {
        // this is the parametrized constructor
    }

    static void  setInvoies(int inv)   // auto Invoice Number creator 
    {
        totalInvoices = inv;
    }
};

int Invoice::totalInvoices = 0;
#endif // !INVOICE_H
