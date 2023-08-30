#include <iostream>
#include <string>
#include <cstdlib>
#include <list>

#include "mdGlobalAddr.h"
#include "GlobalAddressObject.h"
#include "DataContainer.h"

using namespace std;

// function declarations
void ParseArguments(string& license, string& testAddressLine1, string& testAddressLine2, string& testAddressLine3, string& testLocality, string& testAdminArea, string& testPostalCode, string& testCountry, string& dataPath, int argc, char* argv[]);
void RunAsConsole(string license, string testAddressLine1, string testAddressLine2, string testAddressLine3, string testLocality, string testAdminArea, string testPostalCode, string testCountry, string dataPath);
list<string> SplitResultCodes(string s, string delimiter);

int main(int argc, char* argv[])
{
    // variables
    string testAddressLine1 = "";
    string testAddressLine2 = "";
    string testAddressLine3 = "";
    string testLocality = "";
    string testAdminArea = "";
    string testCountry = "";
    string testPostalCode = "";
    string license = "";
    string dataPath = "";

    ParseArguments(license, testAddressLine1, testAddressLine2, testAddressLine3, testLocality, testAdminArea, testPostalCode, testCountry, dataPath, argc, argv);
    RunAsConsole(license, testAddressLine1, testAddressLine2, testAddressLine3, testLocality, testAdminArea, testPostalCode, testCountry, dataPath);

    return 0;
}

void ParseArguments(string& license, string& testAddressLine1, string& testAddressLine2, string& testAddressLine3, string& testLocality, string& testAdminArea, string& testPostalCode, string& testCountry, string& dataPath, int argc, char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "--addressLine1")
        {
            if (argv[i + 1] != NULL)
            {
                testAddressLine1 = argv[i + 1];
            }
        }
        if (string(argv[i]) == "--addressLine2")
        {
            if (argv[i + 1] != NULL)
            {
                testAddressLine2 = argv[i + 1];
            }
        }
        if (string(argv[i]) == "--addressLine3")
        {
            if (argv[i + 1] != NULL)
            {
                testAddressLine3 = argv[i + 1];
            }
        }
        if (string(argv[i]) == "--locality")
        {
            if (argv[i + 1] != NULL)
            {
                testLocality = argv[i + 1];
            }
        }
        if (string(argv[i]) == "--administrativeArea")
        {
            if (argv[i + 1] != NULL)
            {
                testAdminArea = argv[i + 1];
            }
        }
        if (string(argv[i]) == "--postalCode")
        {
            if (argv[i + 1] != NULL)
            {
                testPostalCode = argv[i + 1];
            }
        }
        if (string(argv[i]) == "--country")
        {
            if (argv[i + 1] != NULL)
            {
                testCountry = argv[i + 1];
            }
        }
        if (string(argv[i]) == "--license" || string(argv[i]) == "-l")
        {
            if (argv[i + 1] != NULL)
            {
                license = argv[i + 1];
            }
        }
        if (string(argv[i]) == "--dataPath" || string(argv[i]) == "-d")
        {
            if (argv[i + 1] != NULL)
            {
                dataPath = argv[i + 1];
            }
        }
    }
}

void RunAsConsole(string license, string testAddressLine1, string testAddressLine2, string testAddressLine3, string testLocality, string testAdminArea, string testPostalCode, string testCountry, string dataPath)
{
    cout << "\n\n========== WELCOME TO MELISSA GLOBAL ADDRESS OBJECT WINDOWS C++ ===========\n" << endl;

    GlobalAddressObject* globalAddressObject = new GlobalAddressObject(license, dataPath);

    bool shouldContinueRunning = true;

    while (shouldContinueRunning)
    {
        DataContainer dataContainer = DataContainer();

        if (testAddressLine1.empty() && testAddressLine2.empty() && testAddressLine3.empty() && testLocality.empty() && testAdminArea.empty() && testPostalCode.empty() && testCountry.empty())
        {
            cout << "\nFill in each value to see the Global Address Object results" << endl;

            cout << "Address Line 1: ";
            getline(cin, dataContainer.AddressLine1);

            cout << "Address Line 2: ";
            getline(cin, dataContainer.AddressLine2);

            cout << "Address Line 3: ";
            getline(cin, dataContainer.AddressLine3);

            cout << "Locality: ";
            getline(cin, dataContainer.Locality);

            cout << "Administrative Area: ";
            getline(cin, dataContainer.AdministrativeArea);

            cout << "Postal Code: ";
            getline(cin, dataContainer.PostalCode);

            cout << "Country: ";
            getline(cin, dataContainer.Country);
        }
        else
        {
            dataContainer.AddressLine1 = testAddressLine1;
            dataContainer.AddressLine2 = testAddressLine2;
            dataContainer.AddressLine3 = testAddressLine3;
            dataContainer.Locality = testLocality;
            dataContainer.AdministrativeArea = testAdminArea;
            dataContainer.PostalCode = testPostalCode;
            dataContainer.Country = testCountry;
        }

        // Print user input
        cout << "\n================================= INPUTS ==================================\n" << endl;
        cout << "                  Address Line 1: " + string(dataContainer.AddressLine1) << endl;
        cout << "                  Address Line 2: " + string(dataContainer.AddressLine2) << endl;
        cout << "                  Address Line 3: " + string(dataContainer.AddressLine3) << endl;
        cout << "                        Locality: " + string(dataContainer.Locality) << endl;
        cout << "             Administrative Area: " + string(dataContainer.AdministrativeArea) << endl;
        cout << "                     Postal Code: " + string(dataContainer.PostalCode) << endl;
        cout << "                         Country: " + string(dataContainer.Country) << endl;

        // Execute Address Object
        globalAddressObject->ExecuteObjectAndResultCodes(dataContainer);

        // Print output
        cout << "\n================================= OUTPUT ==================================\n" << endl;
        cout << "\n\tAddress Object Information:" << endl;
        cout << "\t                MAK: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("MAK")) << endl;
        cout << "\t            Company: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("Organization")) << endl;
        cout << "\t     Address Line 1: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("addressline1")) << endl;
        cout << "\t     Address Line 2: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("addressline2")) << endl;
        cout << "\t     Address Line 3: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("addressline3")) << endl;
        cout << "\t     Address Line 4: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("addressline4")) << endl;
        cout << "\t     Address Line 5: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("addressline5")) << endl;
        cout << "\t           Locality: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("locality")) << endl;
        cout << "\tAdministrative Area: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("administrativeArea")) << endl;
        cout << "\t        Postal Code: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("postalCode")) << endl;
        cout << "\t            Postbox: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("postBox")) << endl;
        cout << "\t            Country: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("countryName")) << endl;
        cout << "\t      Country ISO 2: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("iso2Code")) << endl;
        cout << "\t      Country ISO 3: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("iso3Code")) << endl;
        cout << "\t           Latitude: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("latitude")) << endl;
        cout << "\t          Longitude: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("longitude")) << endl;
        cout << "\t  Formatted Address: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("formattedAddress")) << endl;
        cout << "\t       Result Codes: " + string(globalAddressObject->mdGlobalAddressObj->GetOutputParameter("resultCodes")) << endl;

        bool isValid = false;
        if (!(testAddressLine1 + testAddressLine2 + testAddressLine3 + testLocality + testAdminArea + testPostalCode + testCountry).empty())
        {
            isValid = true;
            shouldContinueRunning = false;
        }
        while (!isValid)
        {
            string testAnotherResponse;

            cout << "\nTest another address? (Y/N)" << endl;
            getline(cin, testAnotherResponse);

            if (!testAnotherResponse.empty())
            {
                if (testAnotherResponse == "y" || testAnotherResponse == "Y")
                {
                    isValid = true;
                }
                else if (testAnotherResponse == "n" || testAnotherResponse == "N")
                {
                    isValid = true;
                    shouldContinueRunning = false;
                }
                else
                {
                    cout << "Invalid Response, please respond 'Y' or 'N'" << endl;
                }
            }
        }
    }
    cout << "\n================= THANK YOU FOR USING MELISSA C++ OBJECT ==================\n" << endl;
}

/// <summary>
/// This function splits the resultCodes based on a delimiter
/// </summary>
/// <param name="s">the resultCode string</param>
/// <param name="delimiter"the delimiter string></param>
/// <returns></returns>
list<string> SplitResultCodes(string s, string delimiter) {
    list<string> resultCodes;

    size_t pos = 0;
    string token;

    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        resultCodes.push_back(token);
        s.erase(0, pos + delimiter.length());
    }

    // push back the last resultCode
    resultCodes.push_back(s);

    return resultCodes;
}