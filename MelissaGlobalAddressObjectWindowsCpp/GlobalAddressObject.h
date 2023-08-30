#include<iostream>
#include <string>

#include "mdGlobalAddr.h"
#include "DataContainer.h"

using namespace std;

#ifndef GLOBALADDRESSOBJECT_H
#define GLOBALADDRESSOBJECT_H

class GlobalAddressObject
{
public:
    // Path to Global Address Object data files (.dat, etc)
    string dataFilePath;

    // Create instance of Melissa Global Address Object
    mdGlobalAddr* mdGlobalAddressObj = new mdGlobalAddr;

    GlobalAddressObject(string license, string dataPath);

    // This will call the Lookup function to process the inputs as well as generate the result codes
    void ExecuteObjectAndResultCodes(DataContainer& data);
};

#endif
