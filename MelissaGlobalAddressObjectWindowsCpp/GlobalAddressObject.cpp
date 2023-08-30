#include "GlobalAddressObject.h"

GlobalAddressObject::GlobalAddressObject(string license, string dataPath)
{
    // Set license string and set path to datafiles (.dat, etc)
    mdGlobalAddressObj->SetLicenseString(license.c_str());
    dataFilePath = dataPath;

    // If you see a different date than expected, check your license string and either download the new data files or use the Melissa Updater program to update your data files.  
    mdGlobalAddressObj->SetPathToGlobalAddrFiles(dataFilePath.c_str());

    mdGlobalAddr::ProgramStatus pStatus = mdGlobalAddressObj->InitializeDataFiles();

    if (pStatus != mdGlobalAddr::ProgramStatus::ErrorNone)
    {
    cout << "Failed to Initialize Object." << endl;
    cout << pStatus << endl;
    return;
    }

    cout << "                   DataBase Date: " + string(mdGlobalAddressObj->GetOutputParameter("databaseDate")) << endl;
    cout << "                 Expiration Date: " + string(mdGlobalAddressObj->GetOutputParameter("databaseExpirationDate")) << endl;

    /**
        * This number should match with the file properties of the Melissa Object binary file.
        * If TEST appears with the build number, there may be a license key issue.
    **/
    cout << "                  Object Version: " + string(mdGlobalAddressObj->GetOutputParameter("buildNumber")) << endl;
}

// This will call the Lookup function to process the inputs as well as generate the result codes
void GlobalAddressObject::ExecuteObjectAndResultCodes(DataContainer& data)
{
    mdGlobalAddressObj->ClearProperties();

    data.FilterRequest();  

    mdGlobalAddressObj->SetInputParameter("inputAddressLine1", data.AddressLine1.c_str());
    mdGlobalAddressObj->SetInputParameter("inputAddressLine2", data.AddressLine2.c_str());
    mdGlobalAddressObj->SetInputParameter("inputAddressLine3", data.AddressLine3.c_str());
    mdGlobalAddressObj->SetInputParameter("inputLocality", data.Locality.c_str());
    mdGlobalAddressObj->SetInputParameter("inputAdministrativeArea", data.AdministrativeArea.c_str());
    mdGlobalAddressObj->SetInputParameter("inputPostalCode", data.PostalCode.c_str());
    mdGlobalAddressObj->SetInputParameter("inputCountry", data.Country.c_str());

    mdGlobalAddressObj->VerifyAddress();

    // ResultsCodes explain any issues Global Address Object has with the object.
    // List of result codes for Global Address Object
    // https://wiki.melissadata.com/index.php?title=Result_Code_Details#Global_Address_Object
}
