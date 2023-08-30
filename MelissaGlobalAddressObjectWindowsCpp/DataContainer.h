#include<iostream>

using namespace std;

#ifndef DATACONTAINER_H
#define DATACONTAINER_H

class DataContainer
{
public:
    string AddressLine1;
    string AddressLine2;
    string AddressLine3;
    string Locality;
    string AdministrativeArea;
    string PostalCode;
    string Country;
    string ResultCodes;

    DataContainer() {};

    void FilterRequest()
    {
    if (CheckAreaStack(AddressLine3))
    {
        AddressLine3 = "";
    }
    else if (CheckAreaStack(AddressLine2))
    {
        AddressLine2 = "";
        AddressLine3 = "";
    }
    };

    bool CheckAreaStack(string addressLine)
    {
    bool localityCheck = false;
    bool adminAreaCheck = false;
    bool postalCheck = false;

    if (!Locality.empty() && addressLine.find(Locality) != string::npos)
    {
        localityCheck = true;
    }
    if (!AdministrativeArea.empty() && addressLine.find(AdministrativeArea) != string::npos)
    {
        adminAreaCheck = true;
    }
    if (!PostalCode.empty() && addressLine.find(PostalCode) != string::npos)
    {
        postalCheck = true;
    }

    return localityCheck && adminAreaCheck && postalCheck;
    };
};

#endif