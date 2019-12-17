#include <iostream>
#include <string>
#include <iomanip> 
#include <vector>
#include <algorithm>

// James B Miller
// 05/11/19
// jmlr.dev
// https://github.com/JMiller02

//Declare functions
void Welcome();
void ATC();
void Checkout();
void Receipt();
void NewCustomer();

//Declare Item list array
std::string itemList[10] = {
   "Milk",
   "Bread",
   "Chocolate",
   "Towel",
   "Toothpaste",
   "Soap",
   "Pen",
   "Biscuits",
   "Lamp",
   "Battery"
};

//Declare Barcode list array
std::string barCodeList[10] = {
  "0120001",
  "0120002",
  "0120003",
  "0120004",
  "0120005",
  "0120006",
  "0120007",
  "0120008",
  "0120009",
  "0120010"
};

//Declare Price list array
double priceList[10] = {
  10.50,
  5.50,
  8.00,
  12.10,
  6.75,
  5.20,
  2.00,
  4.45,
  20.50,
  10.00
};

  //Declaring variables globally.
  std::string barcodeInput, receiptInput, newCustomerInput;
  double cashInput = 0.00;
  double totalCost = 0.00;
  double remainingCost = 0.00;
  double changeGiven;
  bool nextCustomer = true;
  bool itemFound;

  //Declare storage vectors for receipts.
  std::vector<std::string> savedItemName;
  std::vector<std::string> savedBarcode;
  std::vector<double> savedPrice;

int main() 
{
    //Start all functions on launch.
    Welcome();
    ATC();
    Checkout();
    Receipt();
    NewCustomer();
}

//Do I need to explain this?
void Welcome()
{
    std::cout << "******************************************************" << std::endl;
    std::cout << "*  Welcome to the Herts Supermarket Checkout System  *" << std::endl;
    std::cout << "* Scan your barcode or manually enter the barcode ID *" << std::endl;
    std::cout << "******************************************************" << std::endl;
}

void ATC()
{
  while (nextCustomer == true)
  {

    //Loop the barcode input
    do 
    {
      //Read input
      std::cout << "Barcode: (Type F to finish): ";
      std::cin >> barcodeInput;


      bool invalidCode = true;
      //Iterate through the barcode list until match is found
      for (int i = 0; i < 10; ++i)
      {
          if (barCodeList[i] == barcodeInput)
          {  
            // Is valid barcode, so = true
              invalidCode = false;
              std::cout << "Item " << itemList[i] << " recognised. Added to basket." << std::endl;

              //Add barcode, item and price to vector for receipt.
              savedItemName.push_back(itemList[i]);
              savedBarcode.push_back(barCodeList[i]);
              savedPrice.push_back(priceList[i]);
              //Add to total cost
              totalCost = totalCost + priceList[i]; 
          }
      }
      if(invalidCode == true && barcodeInput != "F" && barcodeInput != "f")
      {
        std::cout << "Barcode not found." << std::endl;
      }
    }
    while (barcodeInput != "F" && barcodeInput != "f");
    //While the input is not F, Loop
    break;
  }
}

//CHECKOUT FUNCTION. 
void Checkout()
{
  //After user is done entering barcodes, display total price.
  std::cout << "" << std::endl;
  std::cout << std::fixed << "Total price: " << "£" << std::setprecision(2) << totalCost << std::endl;

  //Declare the remaining cost, which is equal to total cost.
  remainingCost = totalCost;

  //Catches if you haven't bought anything.
  if(remainingCost != 0)
  {
   do
    {
      //Input cash
      std::cout << "Cash recieved: £";
      std::cin >> cashInput;

      remainingCost = remainingCost - cashInput;

      //If cost is greater than 0 do this
      if(remainingCost > 0)
      {
        std::cout << std::fixed << "[!] More cash needed: £" << std::setprecision(2) << remainingCost << std::endl;
      }
      else if(remainingCost < 0)
      {
        //If the remaining cost drops below 0, change will be given.
        //The below line converts the minus value to a positive, and then returns change given.
        changeGiven = -remainingCost;
        std::cout << std::fixed << "Change given: £" << std::setprecision(2) << changeGiven << std::endl; 
      }
    }
    //Keep doing it until the remaining cost is 0.
    while(remainingCost > 0);
  }
  else
  {
    //If value is 0, just new customer.
    std::cout << "Thank you for browsing." << std::endl;
    NewCustomer();
  }
}


//RECEIPT FUNCTION
void Receipt()
{
  //Ask about receipt printout
    std::cout << "Would you like to print a receipt? (Y/N): ";
    std::cin >> receiptInput;

    //If answer is wrong do this until they get the right answer.
    do
    {
      if(receiptInput != "Y" && receiptInput != "y" && receiptInput != "N" && receiptInput != "n")
      {
        //Prints error message
        std::cout << "Incorrect input. Please use 'Y' or 'N'." << std::endl;
        std::cout << "Would you like to print a receipt? (Y/N): ";
        std::cin >> receiptInput;
      }
      else
      {
        break;
      }
    }
    while(receiptInput != "Y" && receiptInput != "y" && receiptInput != "N" && receiptInput != "n");
    //Above code checks if input is correct.

  //If input is correct
  if(receiptInput == "Y" || receiptInput == "y")
    {
      //Print the receipt header with fixed widths to space correctly.
      std::cout << "" << std::endl;
      std::cout << "------------------------------" << std::endl;
      std::cout.width(19);std::cout <<"Receipt" << std::endl;
      std::cout << "" << std::endl;
      std::cout.width(13); std::cout << std::left << "Item";
      std::cout.width(9); std::cout << "Barcode";
      std::cout.width(8); std::cout << std::right << "Price" << std::endl;
      
      //For each item in our saved item vector, Iterate.
        for (int i = 0; i < savedItemName.size(); ++i)
        {
          //Get the item, price and barcode and print it out on the receipt.
          std::cout.width(13); std::cout << std::left << savedItemName[i];
          std::cout.width(9); std::cout << savedBarcode[i];
          std::cout.width(8); std::cout << std::right << savedPrice[i] << std::endl;
        }

        //Receipt footer.
        std::cout << "" << std::endl;
        std::cout.width(22); std::cout << "Total: ";
        std::cout.width(8); std::cout << std::right << totalCost << std::endl;
        std::cout << "-------------------------------" << std::endl;
    }
  else if (receiptInput == "N" || receiptInput == "n")
    { 
      //If they say no then don't print.
      std::cout << "Receipt will not be printed." << std::endl;
    }
}

//NEW CUSTOMER FUNCTION.
void NewCustomer()
{
      // New Customer Handler
    std::cout << "New customer? (Y/N): ";
    std::cin >> newCustomerInput;

    //If input is not recognised.
    do
    {
      if(newCustomerInput != "Y" && newCustomerInput != "y" && newCustomerInput != "N" && newCustomerInput != "n")
      {
        std::cout << "Incorrect input. Please use 'Y' or 'N'." << std::endl;
        std::cout << "New customer? (Y/N): ";
        std::cin >> newCustomerInput;
      }
      else
      {
        break;
      }
    }
    while(newCustomerInput != "Y" && newCustomerInput != "y" && newCustomerInput != "N" && newCustomerInput != "n");

  	//Handling the new customer function
    if(newCustomerInput == "Y" || newCustomerInput == "y")
    {
      std::cout << "" << std::endl;
      std::cout << "" << std::endl;

      //Ininiate next customer
      nextCustomer = true;
      
      //Clear all values and vectors
      totalCost = 0.00;
      remainingCost = 0.00;
      changeGiven = 0.00;
      savedPrice.clear();
      savedItemName.clear();
      savedBarcode.clear();

      //Re-call functions
      Welcome();
      ATC();
      Checkout();
      Receipt();
      NewCustomer();
    }
    else if (newCustomerInput == "N" || newCustomerInput == "n")
    {
      //End the program.
      std::cout << "" << std::endl;
      std::cout << "Thank you for using Herts Supermarket Checkout" << std::endl;
      std::cout << "Shutting down..." << std::endl;
      nextCustomer = false;
    }
}
