#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <Windows.h>

//vector and csv includes
#include <sstream>
#include <fstream>
#include <vector>

#include <random>

//Car Detail csv structure: Car, Car cost, addons (1-4), addon total cost, Total car cost, UserID

//Structure to store the Car info
struct CarDetails
{

    //Structure for a single cars details
    std::string sCarName;
    int iCarCost = 0;

    std::string sCarAddon1 = "";
    std::string sCarAddon2 = "";
    std::string sCarAddon3 = "";
    std::string sCarAddon4 = "";
    int iAddonsCost = 0;

    int iTotalCost = 0;

    int iUserID;


};

//Scans the Car Details CSV and sends the information to the function
void ScanCarCSV(std::vector <CarDetails>& vCarStats)
{
    std::vector<std::string> vSplit;
    std::string sResult = "";
    std::string sLine2 = "";

    std::ifstream FileCSV("CarDetails.txt");

    while (FileCSV.is_open())
    {
        while (getline(FileCSV, sLine2))
        {
            std::stringstream ssSplit(sLine2);
            vCarStats.push_back(CarDetails());

            vSplit.resize(0);

            while (getline(ssSplit, sResult, ','))
            {
                vSplit.push_back(sResult);
            }
            //Writes to a vector, carStats
            vCarStats.back().sCarName = vSplit[0];
            vCarStats.back().iCarCost = stoi(vSplit[1]);
            vCarStats.back().sCarAddon1 = vSplit[2];
            vCarStats.back().sCarAddon2 = vSplit[3];
            vCarStats.back().sCarAddon3 = vSplit[4];
            vCarStats.back().sCarAddon4 = vSplit[5];
            vCarStats.back().iAddonsCost = stoi(vSplit[6]);
            vCarStats.back().iTotalCost = stoi(vSplit[7]);
            vCarStats.back().iUserID = stoi(vSplit[8]);            
        }
        FileCSV.close();
    }
}

//reads the current users ID number
int iChecksID(int& LogUserID)
{
    std::ifstream UserFile("LoggedIn.txt");
    std::string line = "";
    std::string result = "";
    std::vector <std::string> vSplit;
    while (std::getline(UserFile, line))
    {
        std::stringstream ssSplit(line);
        vSplit.resize(0);

        while (std::getline(ssSplit, result, ','))
        {
            vSplit.push_back(result);
        }
    }

    LogUserID = stoi(vSplit[0]);
    return LogUserID;
   
}
//Reads the current users admin privilages
bool bChecksBool(bool& LogUserAdmin)
{
    std::ifstream UserFile("LoggedIn.txt");
    std::string line = "";
    std::string result = "";
    std::vector <std::string> vSplit;
    while (std::getline(UserFile, line))
    {
        std::stringstream ssSplit(line);
        vSplit.resize(0);

        while (std::getline(ssSplit, result, ','))
        {
            vSplit.push_back(result);
        }
    }
    int iChecksBool;

    iChecksBool = stoi(vSplit[1]);

    if (iChecksBool == 0)
    {
        LogUserAdmin = 0;
    }
    else if (iChecksBool == 1)
    {
        LogUserAdmin = 1;
    }
    return LogUserAdmin;

}

void AddonList()
{
    Sleep(500);
    std::cout << "\n=================\n";
    std::cout << "---CAR ADDONS---\n"
        "=================\n\n"
        "1. A Radio (Not Stolen)   :   \x9C 2000\n"
        "2. A Big Spoiler   :   \x9C 1200\n"
        "3. A Steering Wheel   :   \x9C 3500\n"
        "4. Flames Paint Job   :   \x9C 3000\n";

}
void CarList()
{

    //List of all cars and addons for the user to choose from
    Sleep(500);
    std::cout << "\n=================== \n"
        " --- CAR LIST--- \n"
        "===================\n\n"
        "1. Honda Civic   :   \x9C 25,000\n"
        "2. Honda Fit   :   \x9C 20,000\n"
        "3. Lexus SC   :   \x9C 60,000\n"
        "4. Volkswagen Beetle   :   \x9C 100,000\n"
        "5. Mitsubishi Lancer   :   \x9C 50,000\n\n";



}
//Checks an array given and sees if an input is within the array or not
std::string sCheckList(std::string sOptArr[], std::string& sOptVal, int const iArrSize)
{
    

    bool bCheck = false;
    //While loop to iterate input if the given input is one of the right options

    while (bCheck == false)
    {
        std::cin >> sOptVal;
        //Converts sMenuOpt to lower case
        std::transform(sOptVal.begin(), sOptVal.end(), sOptVal.begin(), ::tolower);

        //For loop checks input by comparing the characters in the array
        for (int iCount = 0; iCount < iArrSize; iCount++)
        {
            //If its in the array, the loop will stop
            if (sOptVal == sOptArr[iCount])
            {
                bCheck = true;
            }
        }
        //If the array has been checked fully and the last character in the array is false, it will ask to re-input sMenuOpt
        if ((sOptVal != sOptArr[iArrSize - 1]) && (bCheck == false))
        {
            std::cout << "Please try again\n";
        }
    }

    //Passed sMenuOpt for the users option and passed bIsAdmin to see if the user is an admin or not
    return sOptVal;
}
//Checks a Y/N input
std::string CheckAB(std::string& sChecksAB, std::string sOpt1, std::string sOpt2)
{
    std::cin >> sChecksAB;
    std::transform(sChecksAB.begin(), sChecksAB.end(), sChecksAB.begin(), ::tolower);

    //checks if their input is write or not
    while (sChecksAB != sOpt1 && sChecksAB != sOpt2)
    {
        std::cout << "Please try again\n";
        std::cin >> sChecksAB;
        std::transform(sChecksAB.begin(), sChecksAB.end(), sChecksAB.begin(), ::tolower);
    }

    return sChecksAB;
}
//Checks a number input that is between 2 numbers
int iCheckNum(int iNumBetween1, int iNumBetween2, int& iChooseNum)
{
    while (iChooseNum < iNumBetween1 || iChooseNum > iNumBetween2 || std::cin.fail())
    {
        std::cout << "Invalid input. Please try again: ";
        //clears and ignores the previous input by the user so it doesnt crash
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> iChooseNum;

    }

    return iChooseNum;


}

//Calls these functions to that CheckAddAnother can use them 
void AddCar();
void EmployeeMainMenu();
void AdminMainMenu();
void CheckAddAnotherCar()
{
    
    std::cout << "Would you like to add another car? (y/n)";
    std::string sAnotherCar;
    std::string sOpt1 = "y";
    std::string sOpt2 = "n";
    CheckAB(sAnotherCar, sOpt1, sOpt2);
    if (sAnotherCar == "y")
    {
        AddCar();
    }
    else if (sAnotherCar == "n")
    {
        //Checks if they are an admin to take them to the right menu
        bool isAdmin = false;
        bChecksBool(isAdmin);
        if (isAdmin == 0)
        {
            EmployeeMainMenu();
        }
        else if (isAdmin == 1)
        {            
            AdminMainMenu();
        }
    }
}

void AddToCSV(struct CarDetails& _CD)
{
    //Checks whos logged onto the program
    int UserID = 0;
    iChecksID(UserID);
    _CD.iUserID = UserID;

    //ios::app sets the position indicatior to the end of the csv
    std::ofstream File("CarDetails.txt", std::ios::app);
    //Writes the structure into the csv and then closes

    if (File.is_open())
    {
        File << _CD.sCarName << ","
            << _CD.iCarCost << ","
            << _CD.sCarAddon1 << ","
            << _CD.sCarAddon2 << ","
            << _CD.sCarAddon3 << ","
            << _CD.sCarAddon4 << ","
            << _CD.iAddonsCost << ","
            << _CD.iTotalCost << ","
            << _CD.iUserID << "\n";
        
        File.close();
    }
    else
    {
        std::cout << "Error occured opening file";
    }
    std::cout << "Successfully Saved \n";

}

void AddAddons(struct CarDetails& _CD)
{
    system("cls");
    AddonList();

    //Checks how many addons for the car the user wants
    int iAddonAmount;
    std::cout << "How many addons would you like to have (1 - 4)\n";
    std::cin >> iAddonAmount;

    //Checks the valid input
    int iImportBetween2 = 1;
    int iImportBetween3 = 4;
    iCheckNum(iImportBetween2, iImportBetween3, iAddonAmount);

    //2 arrays that are used for the car addons and addon 
    const int iAddonSize = 4;
    std::string CarAddonsList[iAddonSize] = { "A Radio (Not Stolen)", "A Big Spoiler", "A Steering Wheel", "Flames Paint Job" };
    int AddonsCost[iAddonSize] = { 4000, 2200, 8500, 7000 };
    bool AddonChosenCheck[iAddonSize] = { false, false, false, false };
    
    //Inputs addons for how many addons the user wants, also checks if the letter is valid
    for (int iCount = 0; iCount < iAddonAmount; iCount++)
    {
        int iAddon;
        std::cout << "Type a number to add an addon to the car\n";
        std::cin >> iAddon;

        int iImportBetween4 = 1;
        iCheckNum(iImportBetween4, iAddonSize, iAddon);

        //Line the chosen addon with the array list
        iAddon--;


        //Checks if the addon has already been added and asks to re input it again if it is
        while (AddonChosenCheck[iAddon] == true)
        {
            std::cout << "\nYou have already used this addon. Please Try again: \n";
            std::cin >> iAddon;
            iAddon--;
            int iImportBetween4 = 0;
            int iImportBetween5 = 3;
            iCheckNum(iImportBetween4, iImportBetween5, iAddon);
            
        }
        
        //Adds the addon chosen on into the structures
        //Makes the position of the bool array true so the user cant repeat the same addon
        if (iCount == 0 && AddonChosenCheck[iAddon] == false)
        {         
            _CD.sCarAddon1 = CarAddonsList[iAddon];
            AddonChosenCheck[iAddon] = 1;
        }
        else if (iCount == 1 && AddonChosenCheck[iAddon] == false)
        {
            _CD.sCarAddon2 = CarAddonsList[iAddon];
            AddonChosenCheck[iAddon] = 1;
        }
        else if (iCount == 2 && AddonChosenCheck[iAddon] == false)
        {
            _CD.sCarAddon3 = CarAddonsList[iAddon];
            AddonChosenCheck[iAddon] = 1;
        }
        else if (iCount == 3 && AddonChosenCheck[iAddon] == false)
        {
            _CD.sCarAddon4 = CarAddonsList[iAddon];
            AddonChosenCheck[iAddon] = 1;
        }
        //Adds the total cost of the addon to the structure
        _CD.iAddonsCost = _CD.iAddonsCost + AddonsCost[iAddon];
    }
    //Calculates the total cost
    _CD.iTotalCost = _CD.iCarCost + _CD.iAddonsCost;
    AddToCSV(_CD);
    CheckAddAnotherCar();

    /*std::cout << "The Car " << _CD.sCarName << "\n";
    std::cout << "Addon Cost " << _CD.iAddonsCost << "\n";
    std::cout << "Car Cost " << _CD.iCarCost << "\n";
    std::cout << "Total Cost " << _CD.iTotalCost << "\n";
    std::cout << "Car Addon 1 " << _CD.sCarAddon1 << "\n";
    std::cout << "Car Addon 2 " << _CD.sCarAddon2 << "\n";
    std::cout << "Car Addon 3 " << _CD.sCarAddon3 << "\n";
    std::cout << "Car Addon 4 " << _CD.sCarAddon4 << "\n";*/
}

void CheckToAddAddon(struct CarDetails _CD)
{

    //Checks if they want to add some addons to the car
    std::cout << "\nDo you want addons for the car?  (y/n)\n";
    std::string sWantAddonOption;
    
    std::string sOpt1 = "y";
    std::string sOpt2 = "n";
    CheckAB(sWantAddonOption, sOpt1, sOpt2);

    if (sWantAddonOption == "y")
    {

        AddAddons(_CD);

    }

    else if (sWantAddonOption == "n")
    {
        
        _CD.iTotalCost = _CD.iCarCost;

        AddToCSV(_CD);

        CheckAddAnotherCar();

        /*std::cout << "The Car " << _CD.sCarName << "\n";
        std::cout << "Addon Cost " << _CD.iAddonsCost << "\n";
        std::cout << "Car Cost " << _CD.iCarCost << "\n";
        std::cout << "Total Cost " << _CD.iTotalCost << "\n";
        std::cout << "Car Addon 1 " << _CD.sCarAddon1 << "\n";
        std::cout << "Car Addon 2 " << _CD.sCarAddon2 << "\n";
        std::cout << "Car Addon 3 " << _CD.sCarAddon3 << "\n";
        std::cout << "Car Addon 4 " << _CD.sCarAddon4 << "\n";*/

    }

}

void AddCar()
{
    //////////////////////////////////////////////////////////////////////////////////
    //Vector to hold the CD structs
    std::vector<CarDetails> vCD;

    struct CarDetails _CD;

    system("cls");
    //2 Arrays that are used together for the car price and car name


    Sleep(500);
    /*std::cout << "\n===================\n"
        "\n ---OPTIONS---\n"
        "===================\n\n";*/
    CarList();
    Sleep(500);

    int iCarChoice;
    std::cout << "\nInput a number to choose a car\n";
    std::cin >> iCarChoice;

    const int iCarListSize = 5;
    std::string CarNameList[iCarListSize] = { "Honda Civic", "Honda Fit", "Lexus SC", "Volkswagen Beetle", "Mitsubishi Lancer" };
    int CarCostsList[iCarListSize] = { 25000, 20000, 60000, 100000, 50000 };

    //Checks if the input is a value that is relatable to the array size and or if its actually an integer or not
    int iImportBetween1 = 1;
    iCheckNum(iImportBetween1, iCarListSize, iCarChoice);

    //Match iCarChoice with the car namelist array

    iCarChoice = iCarChoice - 1;

    //      Creates a txt file (ran once / can be used to overwrites the file)
    //      CarDetails.txt has been created
    //std::ofstream ACarDetails("CarDetails.txt");

    //Adds the 2 variables to the structure
    _CD.sCarName = CarNameList[iCarChoice];
    _CD.iCarCost = CarCostsList[iCarChoice];

    CheckToAddAddon(_CD);

}

void PressToMenu()
{
    std::cout << "Press 'm' to go back to menu\n";
    std::string sMenuPress;
    std::cin >> sMenuPress;
    while (sMenuPress != "m")
    {
        std::cout << "Invalid input. Please try again \n";
        std::cin >> sMenuPress;
    }
    if (sMenuPress == "m")
    {
        EmployeeMainMenu();
    }
}

void EmployeeStats()
{
    system("cls");
    std::cout << "\n========================\n"
        "---EMPLOYEE STATISTICS---\n"
        "========================\n\n";
    std::vector <CarDetails> vCarStats;
    ScanCarCSV(vCarStats);

    int UserID = 0;
    iChecksID(UserID);
    std::vector <int> UserSales;
    //Checks what car sales the user has made
    for (int iCount = 0; iCount < vCarStats.size(); iCount++)
    {
        if (UserID == vCarStats[iCount].iUserID)
        {
            UserSales.push_back(iCount);
        }
    }
    if (UserSales.size() == 0)
    {
        system("cls");
        std::cout << "You have made no sales\n";
        PressToMenu();
    }

    //User total rev made
    //User total addon sales made
    int iTotalRev = 0;
    int iTotalAddon = 0;
    for (int iCount = 0; iCount < UserSales.size(); iCount++)
    {
        iTotalRev = iTotalRev + vCarStats[UserSales[iCount]].iTotalCost;
        iTotalAddon = iTotalAddon + vCarStats[UserSales[iCount]].iAddonsCost;
    }
    int iExpectedAddonSale;
    iExpectedAddonSale = iTotalRev * 0.05;
    
    if (iTotalAddon < iExpectedAddonSale)
    {
        std::cout << "\n===============\n"
            "---WARNING---\n"
            "===============\n\n";
        std::cout << "Your addon sales are low!\n";
        std::cout << "Make sure to encourage addons to car sales!\n\n";
    }
    
    std::cout << "Car(s) sold\n";

    //Shows cars sold by the user
    for (int iCount = 0; iCount < UserSales.size(); iCount++)
    {       
        std::cout << "\n=============\n"
            "----Car " << iCount + 1 << "----\n"
            "=============\n\n";
        std::cout << "Car sold: " << vCarStats[UserSales[iCount]].sCarName << "\n";
        std::cout << "Car Cost: " << vCarStats[UserSales[iCount]].iCarCost << "\n";
        std::cout << "Addons sold:\n";
        std::cout << "Addon 1: " << vCarStats[UserSales[iCount]].sCarAddon1 << "\n";
        std::cout << "Addon 2: " << vCarStats[UserSales[iCount]].sCarAddon2 << "\n";
        std::cout << "Addon 3: " << vCarStats[UserSales[iCount]].sCarAddon3 << "\n";
        std::cout << "Addon 4: " << vCarStats[UserSales[iCount]].sCarAddon4 << "\n";
        std::cout << "Addon cost \x9C" << vCarStats[UserSales[iCount]].iAddonsCost << "\n";
        std::cout << "Total Cost: " << vCarStats[UserSales[iCount]].iTotalCost << "\n\n";      
    }
    PressToMenu();



}

int iTotalRevCal(int& iTotalRev, std::vector <CarDetails> vCarStats)
{
    for (int iCount = 0; iCount < vCarStats.size(); iCount++)
    {
        iTotalRev = iTotalRev + vCarStats[iCount].iTotalCost;
    }
    return iTotalRev;
}
int iOpCostCal(int& iOpCost, std::vector <CarDetails> vCarStats)
{    
    int iTotalRev = 0;
    iTotalRevCal(iTotalRev, vCarStats);

    iOpCost = iTotalRev / 2;
    return iOpCost;

}
int iTaxPaidCal(int& iTaxPaid, std::vector <CarDetails> vCarStats)
{
    int iTotalRev = 0;
    iTotalRevCal(iTotalRev, vCarStats);
    iTaxPaid = iTotalRev * 0.2;
    return iTaxPaid;

}

void AESOrMainMenu()
{
    std::cout << "Go back to Main Menu (m) or Statistics Menu (s)\n";
    std::string sMenuOpt;
    std::string sOpt1 = "m";
    std::string sOpt2 = "s";
    CheckAB(sMenuOpt, sOpt1, sOpt2);
    if (sMenuOpt == sOpt1)
    {
        //Dont need to check if they are admin or not because only admins can get into this func already
        AdminMainMenu();

    }
    else if (sMenuOpt == sOpt2)
    {
        void AllEmployeeStats();
        AllEmployeeStats();
    }
}
void AES_TotalCars()
{
    system("cls");
    std::vector<CarDetails> vCarStats;
    ScanCarCSV(vCarStats);
    
    if (vCarStats.size() == 0)
    {
        std::cout << "No cars have been sold\n";
        AESOrMainMenu();
    }

    int iCarsSold = 0;
    iCarsSold = vCarStats.size();

    std::cout << "Total cars sold: \n" << iCarsSold << "\n";
    
    AESOrMainMenu(); 
}
void AES_TotalRev()
{
    system("cls");
    std::vector<CarDetails> vCarStats;
    ScanCarCSV(vCarStats);

    if (vCarStats.size() == 0)
    {
        std::cout << "No cars have been sold\n";
        AESOrMainMenu();
    }

    int iTotalRev = 0;
    iTotalRevCal(iTotalRev, vCarStats);
    std::cout << "Total revenue: \x9C" << iTotalRev << "\n";
    
    AESOrMainMenu();
}
void AES_HighCostAddon()
{
    system("cls");
    std::vector <CarDetails> vCarStats;
    ScanCarCSV(vCarStats);

    std::vector <int> vTheSale;
    int iCurrentAddon = 0;
    if (vCarStats.size() == 0)
    {
        std::cout << "No cars have been sold\n";
        AESOrMainMenu();
    }

    for (int iCount = 0; iCount < vCarStats.size(); iCount++)
    {    
        //If a new high addon found it resets the vector and replaces the var to compare to the rest
        if (iCurrentAddon < vCarStats[iCount].iAddonsCost)
        {
            iCurrentAddon = vCarStats[iCount].iAddonsCost;
            //Adds the place to vector to gain the information at the end
            vTheSale.resize(0);
            vTheSale.push_back(iCount);
        }
        //If its the same, its added to a vector to be outputed later
        //!= 0 stops adding nothing to the vector
        else if (iCurrentAddon == vCarStats[iCount].iAddonsCost && vCarStats[iCount].iAddonsCost != 0)
        {
            //Adds the place to vector to gain the information at the end
            vTheSale.push_back(iCount);
        }
    }
    std::cout << "Car Sale(s) with the highest addon sale\n\n";
    /*std::cout << vHighestAddonList.size() << "\n";
    std::cout << vTheSale.size() << "\n";*/

    for (int iCount = 0; iCount < vTheSale.size(); iCount++)
    {
        if (iCurrentAddon > 0)
        {
            std::cout << "----Car " << iCount + 1 << "----\n";
            std::cout << "Car sold: " << vCarStats[vTheSale[iCount]].sCarName << "\n";
            std::cout << "Addons sold:\n";
            std::cout << "Addon 1: " << vCarStats[vTheSale[iCount]].sCarAddon1 << "\n";
            std::cout << "Addon 2: " << vCarStats[vTheSale[iCount]].sCarAddon2 << "\n";
            std::cout << "Addon 3: " << vCarStats[vTheSale[iCount]].sCarAddon3 << "\n";
            std::cout << "Addon 4: " << vCarStats[vTheSale[iCount]].sCarAddon4 << "\n";
            std::cout << "Addon cost \x9C" << vCarStats[vTheSale[iCount]].iAddonsCost << "\n";
            std::cout << "User ID: " << vCarStats[vTheSale[iCount]].iUserID << "\n\n";            
        }
        else
        {
            std::cout << "No addons have been sold";
            AESOrMainMenu();
        }    
    }  
    AESOrMainMenu();
}
void AES_LowCostAddon()
{
    system("cls");
    std::vector <CarDetails> vCarStats;
    ScanCarCSV(vCarStats);
    std::vector <int> vTheSale;

    int iCurrentAddon = 0;
    if (vCarStats.size() == 0)
    {
        std::cout << "No cars have been sold\n";
        AESOrMainMenu();
    }
    //Starts with the first addon before the loop
    iCurrentAddon = vCarStats[0].iAddonsCost;
    //Started before the loop so iCount = 1 
    for (int iCount = 1; iCount < vCarStats.size(); iCount++)
    {
        //If a new low addon found it resets the vector and replaces the var to compare to the rest
        if (iCurrentAddon > vCarStats[iCount].iAddonsCost)
        {
            iCurrentAddon = vCarStats[iCount].iAddonsCost;
            vTheSale.resize(0);
            vTheSale.push_back(iCount);
        }
        //If its the same, its added to a vector to be outputed later
        //!= 0 stops adding nothing to the vector
        else if (iCurrentAddon == vCarStats[iCount].iAddonsCost && vCarStats[iCount].iAddonsCost != 0)
        {
            vTheSale.push_back(iCount);
        }
    }
    std::cout << "Car Sale(s) with the lowest addon sale\n\n";
    for (int iCount = 0; iCount < vTheSale.size(); iCount++)
    {
        if (iCurrentAddon > 0)
        {
            std::cout << "----Car " << iCount + 1 << "----\n";
            std::cout << "Car sold: " << vCarStats[vTheSale[iCount]].sCarName << "\n";
            std::cout << "Addons sold:\n";
            std::cout << "Addon 1: " << vCarStats[vTheSale[iCount]].sCarAddon1 << "\n";
            std::cout << "Addon 2: " << vCarStats[vTheSale[iCount]].sCarAddon2 << "\n";
            std::cout << "Addon 3: " << vCarStats[vTheSale[iCount]].sCarAddon3 << "\n";
            std::cout << "Addon 4: " << vCarStats[vTheSale[iCount]].sCarAddon4 << "\n";
            std::cout << "Addon cost \x9C" << vCarStats[vTheSale[iCount]].iAddonsCost << "\n";
            std::cout << "User ID: " << vCarStats[vTheSale[iCount]].iUserID << "\n\n";
        }
        else
        {
            std::cout << "No addons have been sold";
            AESOrMainMenu();
        }
        AESOrMainMenu();
    }
}
void AES_Difference()
{
    system("cls");
    std::vector <CarDetails> vCarStats;
    ScanCarCSV(vCarStats);

    if (vCarStats.size() == 1)
    {
        std::cout << "2 Cars in total must of been sold \n";
        AESOrMainMenu();
    }
    else if (vCarStats.size() == 0)
    {
        std::cout << "No cars have been sold\n";
        AESOrMainMenu();
    }
    
    std::vector <int> vTheSale;
    int iSmallestSale = 0;
    int iLargestSale = 0;

    //Finding the largest car sale
    for (int iCount = 0; iCount < vCarStats.size(); iCount++)
    {
        if (iLargestSale < vCarStats[iCount].iCarCost)
        {
            iLargestSale = vCarStats[iCount].iCarCost;
        }
    }
    //Finding the smallest car sale
    iSmallestSale = vCarStats[0].iCarCost;
    for (int iCount = 1; iCount < vCarStats.size(); iCount++)
    {
        if (iSmallestSale > vCarStats[iCount].iCarCost)
        {
            iSmallestSale = vCarStats[iCount].iCarCost;
        }
    }
    int Difference = 0;
    Difference = iLargestSale - iSmallestSale;
    std::cout << "The differnce between the most expensive and the least expensive car sold (Not including addons): \n\n";
    std::cout << "\x9C" << Difference << "\n";
    
    AESOrMainMenu();
}
void AES_OperationalCost()
{
    system("cls");
    std::vector<CarDetails> vCarStats;
    ScanCarCSV(vCarStats);
    
    int iOpCost = 0;
    iOpCostCal(iOpCost, vCarStats);
    
    std::cout << "Estimated Operational Cost: \n";
    std::cout << "\x9C" << iOpCost << "\n";

    AESOrMainMenu();
}
void AES_Tax()
{
    system("cls");
    std::vector<CarDetails> vCarStats;
    ScanCarCSV(vCarStats);    
    int iTaxPaid = 0;
    iTaxPaidCal(iTaxPaid, vCarStats);    
    std::cout << "Estimated Operational Cost: \n";
    std::cout << "\x9C" << iTaxPaid << "\n";
    AESOrMainMenu();
}
void AES_Profit()
{
    system("cls");
    std::vector<CarDetails> vCarStats;
    ScanCarCSV(vCarStats);
    int iTotalRev = 0;
    int iTaxPaid = 0;
    int iOpCost = 0;
    int iProfit = 0;
    iTaxPaidCal(iTaxPaid, vCarStats);
    iOpCostCal(iOpCost, vCarStats);
    iTotalRevCal(iTotalRev, vCarStats);
    iProfit = iTotalRev - iTaxPaid - iOpCost;
    std::cout << "Total profit: \n";
    std::cout << "\x9C" << iProfit << "\n";
    AESOrMainMenu();
}

void AllEmployeeStats()
{
    system("cls");
    std::cout << "\n===================\n"
        "-- - ADMIN STATISTICS-- - \n"
        "\n===================\n\n";
    std::cout << "What stat would you like shown: \n\n";
    std::cout << ".Total Cars Sold (C)\n";
    std::cout << ".Total Revenue from all cars (R)\n";
    std::cout << ".Sale with the highest cost of addons (H)\n";
    std::cout << ".Sale with the lowest cost of addons (L)\n";
    std::cout << ".Difference between the most expensive and least expensive car sale (No addons) (D)\n";
    std::cout << ".Estimated operational cost (E)\n";
    std::cout << ".Tax Paid (T)\n";
    std::cout << ".Profit (P)\n";
    std::cout << ".Menu (M)\n";

    int const ArrSize = 9;
    std::string sArrayOpt[ArrSize] = { "c","r","h","l","d","e","t","p","m" };
    std::string sOptVal;

    sCheckList(sArrayOpt, sOptVal, ArrSize);

    if (sOptVal == "c")
    {
        AES_TotalCars();
    }
    else if (sOptVal == "r")
    {
        AES_TotalRev();
    }
    else if (sOptVal == "h")
    {
        AES_HighCostAddon();
    }
    else if (sOptVal == "l")
    {
        AES_LowCostAddon();
    }
    else if (sOptVal == "d")
    {
        AES_Difference();
    }
    else if (sOptVal == "e")
    {
        AES_OperationalCost();
    }
    else if (sOptVal == "t")
    {
        AES_Tax();
    }
    else if (sOptVal == "p")
    {
        AES_Profit();
    }
    else if (sOptVal == "m")
    {
        bool isAdmin = false;
        bChecksBool(isAdmin);
        if (isAdmin == false)
        {
            EmployeeMainMenu();
        }
        else if (isAdmin == true)
        {
            AdminMainMenu();
        }
    }    
}

void MenuGoToOpt()
{

    std::string sMenuOpt;

    const int iListSize = 5;

    //An array to check if character input is correct
    std::string sMenuList[iListSize] = { "c", "a", "e", "q" };

    sCheckList(sMenuList, sMenuOpt, iListSize);

    bool bIsAdmin = false;
    bChecksBool(bIsAdmin);
    //Checks sMenuOpt value and goes to the procedure being called
    if (sMenuOpt == "c")
    {
        CarList();
    }
    else if (sMenuOpt == "a")
    {
        AddCar();
    }
    //If the user is not the admin it will only check their stats
    else if ((sMenuOpt == "e") && (bIsAdmin == 0))
    {
        EmployeeStats();
    }
    //If the user is an admin then they will have access to all stats
    else if ((sMenuOpt == "e") && (bIsAdmin == 1))
    {
        AllEmployeeStats();
    }

    else if (sMenuOpt == "q")
    {
        exit(0);
    }
}

void EmployeeMainMenu()
{
    system("cls");
    Sleep(500);

    //Menu format
    std::cout << "\n================\n"
        "---MAIN MENU--- \n"
        "================\n"
        "\n.Car List / Addons(C)\n\n.Add Car(A)\n\n.Employee Statistics(E)\n\n.Quit(Q)\n\n";
    Sleep(500);
    std::cout << "Help: Type a key next to one of the options\n";

    MenuGoToOpt();

}

void AdminMainMenu()
{
    system("cls");
    
    Sleep(500);
    //Admin Menu format

    std::cout << "\n===================\n"
        "--ADMIN MAIN MENU-- \n"
        "===================\n\n.Car List / Addons(C)\n\n.Add(A)\n\n.All Employee Statistics(E)\n\n.Quit(Q)\n\n";
    Sleep(500);
    std::cout << "Help: Type a key next to one of the options\n";

    //Passed inot the next function not to be used yet but to wait to gather the sMenuOpt data as well
    MenuGoToOpt();
}

std::string LogSignInput(std::string& sInpFirst, std::string& sInpLast, std::string& sInpPass)
{

    std::cout << "First Name: \n";
    std::cin >> sInpFirst;
    std::transform(sInpFirst.begin(), sInpFirst.end(), sInpFirst.begin(), ::tolower);

    std::cout << "Last Name: \n";
    std::cin >> sInpLast;
    std::transform(sInpLast.begin(), sInpLast.end(), sInpLast.begin(), ::tolower);

    std::cout << "Password: \n";
    std::cin >> sInpPass;
    std::transform(sInpPass.begin(), sInpPass.end(), sInpPass.begin(), ::tolower);
    //retruns to login or sign up
    return sInpFirst, sInpLast, sInpPass;
    
}

void LoginMenu()
{
    system("cls");
    std::cout << "\n============\n"
        "---LOGIN--- \n"
        "============\n\n";
    std::string sInpFirst;
    std::string sInpLast;
    std::string sInpPass;
    LogSignInput(sInpFirst, sInpLast, sInpPass);
    
    bool bLogCheck = false;

    std::vector<std::string> vSplit;
    std::string line = "";
    std::string sResult = "";

    std::ifstream File("UserDetails.txt");

    while (File.is_open())
    {
        //While the func has found what it's looking for or if it doesnt end
        while ((bLogCheck == false) && (std::getline(File, line)))
        {
            std::stringstream ssSplit(line);

            vSplit.resize(0);

            while (std::getline(ssSplit, sResult, ','))
            {
                vSplit.push_back(sResult);
            }

            /*std::cout << vSplit[0] << "\n";
            std::cout << vSplit[1] << "\n";
            std::cout << vSplit[2] << "\n";
            std::cout << vSplit[3] << "\n";
            std::cout << vSplit[4] << "\n";*/

            if (vSplit[0] == sInpFirst && vSplit[1] == sInpLast && vSplit[2] == sInpPass)
            {             
                bLogCheck = true;
            }
        }
        

        File.close();
    }
    /*std::cout << vSplit[0] << "\n";
    std::cout << vSplit[1] << "\n";
    std::cout << vSplit[2] << "\n";
    std::cout << vSplit[3] << "\n";
    std::cout << vSplit[4] << "\n";*/

    //stores the current users ID and if they have admin access
    std::ofstream UserFile("LoggedIn.txt");
    while (UserFile.is_open())
    {
        //ID , Admin
        UserFile << vSplit[3] << "," << vSplit[4];
        UserFile.close();
    }
    
    if (bLogCheck == true)
    {
        //If not admin go to normal menu
        if (stoi(vSplit[4]) == 0)
        {
            EmployeeMainMenu();
        }
        //if admin go to admin menu
        else if (stoi(vSplit[4]) == 1)
        {
            AdminMainMenu();
        }
    }
    else if (bLogCheck == false)
    {
        std::cout << "Your name or password is wrong";
        Sleep(1700);
        system("cls");
        LoginMenu();

    }

}

void SignUpMenu()
{
    //Sign up, login info to be added to the user CSV
    system("cls");
    std::cout << "=============\n"
        "---SIGN UP---\n"
        "=============\n\n";

    std::string sInpFirst;
    std::string sInpLast;
    std::string sInpPass;
    LogSignInput(sInpFirst, sInpLast, sInpPass);
    

    //User ID
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<> dist(10000, 99999);

    auto iGenID = dist(rng);
    

    bool bCheckAdmin = false;
    if (sInpFirst == "sean" && sInpLast == "shearing")
    {
        bCheckAdmin = true;
    }
    

    std::ofstream File("UserDetails.txt", std::ios::app);
    //Writes the structure into the csv and then closes
    if (File.is_open())
    {
        File << sInpFirst << ","
            << sInpLast << ","
            << sInpPass << ","
            << iGenID << ","
            << bCheckAdmin << "\n";
            

        File.close();
    }
    else
    {
        std::cout << "Error occured opening file";
    }
    std::cout << "Successfully Saved \n";
    Sleep(1000);
    LoginMenu();
}

void LoginSignUp()
{
    //Checks if they want to go to login or sign up
    std::cout << "\n========================\n"
        "--- LOGIN / SIGN UP--- \n"
        "========================\n\n";
    std::cout << "Login (l) : Sign up (s) \n";
    std::string sLogOrSign;

    std::string sOpt1 = "l";
    std::string sOpt2 = "s";
    CheckAB(sLogOrSign, sOpt1, sOpt2);

    if (sLogOrSign == "l")
    {
        LoginMenu();
    }
    else if (sLogOrSign == "s")
    {
        SignUpMenu();
    }

}

int main()
{
    ////TEMPORARY: To test admin and employee menu
    //std::string AorEOpt;

    //std::cout << "TEST: Admin (A) or Emp (E)\n";
    //std::cin >> AorEOpt;

    //if (AorEOpt == "a")
    //{
    //    AdminMainMenu();
    //}
    //else if (AorEOpt == "e")
    //{
    //    EmployeeMainMenu();
    //}

    LoginSignUp();



}

