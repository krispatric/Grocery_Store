// Driver program
#include "Stock.h"
int main()
{
    Stock stock;   // creating the instance of the Stock class

    stock.LoadStockFromFile();   // loading stock from file 

    stock.LoadInvoicesFromFile();   // loading invoices from file 

    int choice;

    do    // loop until user quit
    {

        // displaying the manu to the user 

        cout << "-----------------------------" << endl;

        cout << "1. Add item to stock" << endl;

        cout << "2. Display stock" << endl;

        cout << "3. Sell item" << endl;

        cout << "4. Save stock to file" << endl;

        cout << "5. Search the receipt" << endl;

        cout << "6. Exit" << endl;

        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice)     // switching choice of user 
        {
        case 1:    // case for adding item to the Stock 
        {
            cout << "Enter item type (Q for quantity, W for weight): ";

            char itemType;

            cin >> itemType;

            cout << "Enter item name: ";

            string itemName;

            cin.ignore();

            getline(cin, itemName);

            if (itemType == 'Q')   // if item is being added by the Quantity 
            {
                int quantity;

                double price;

                cout << "Enter quantity: ";

                cin >> quantity;

                cout << "Enter price per quantity: ";

                cin >> price;

                QuantityItem* qItem = new QuantityItem(itemName, quantity, price);

                //QuantityItem* qItem = new QuantityItem();

                //cin >> *qItem;

                stock.AddItem(qItem);
            }
            else if (itemType == 'W')   // if the item is being adde by the Weight 
            {
                double weight;

                double pricePerKg;

                cout << "Enter weight (in kg): ";

                cin >> weight;

                cout << "Enter price per kg: ";

                cin >> pricePerKg;

                WeightItem* wItem = new WeightItem(itemName, weight, pricePerKg);

                stock.AddItem(wItem);
            }
            else
            {

                cout << "Error: Invalid item type. Please try again." << endl;
            }
            break;
        }
        case 2:    // case for displaying the whole stock 
        {
            stock.DisplayStock();

            break;
        }
        case 3:    // case for  selling the stock to the customer 
        {
            cout << "Enter item name: ";

            string itemName;

            cin.ignore();

            getline(cin, itemName);

            itemName.erase(remove(itemName.begin(), itemName.end(), ' '), itemName.end());   // use of STL for removing unnessary space from item name   to get correct search by name 

            itemName.erase(remove(itemName.begin(), itemName.end(), '\n'), itemName.end());   // use of STL for removing unnessary \n from item name  to get correct search by name

            double quantity;

            cout << "Enter quantity/weight/Number of items to sell: ";

            cin >> quantity;

            stock.SellItem(itemName, quantity);

            break;
        }
        case 4:  // case for saving data to stock 
        {
            stock.SaveStockToFile();

            break;
        }
        case 5:
        {
            cout << "Enter Receipt Id /Invoice Num to be searched " << endl;
            int id;
            cin >> id;

            stock.searchInvoice(id);  // case for searching the invoice /Receipt 
            break;
        }
        case 6:   // case when user want quit 
        {
            cout << "Exiting..." << endl;
            break;
        }
        default:   // invalid choice case
        {
            cout << "Error: Invalid choice. Please try again." << endl;
            break;
        }

        }
    } while (choice != 6);

    stock.~Stock(); // calling explicitly destructor for memory deallocation 

    return 0;
}

